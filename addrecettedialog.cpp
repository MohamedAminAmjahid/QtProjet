#include "addrecettedialog.h"
#include "ui_addrecettedialog.h"

AddRecetteDialog::AddRecetteDialog(QWidget *parent, DatabaseManager *databaseManager) :
    QDialog(parent),
    ui(new Ui::AddRecetteDialog),
    databaseManager_(databaseManager)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());

    ui->lineEdit->setReadOnly(QIODeviceBase::ReadOnly);
    ui->lineEdit->setText("0");

    QList<QPair<int, QString>> serveurs = databaseManager_->getServeursAndLogins();
    for (const auto &serveur : serveurs) {
        ui->comboBox->addItem(QString("%1 - %2").arg(serveur.first).arg(serveur.second));
    }

    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(serveurSelectionChanged(int)));
    connect(ui->dateEdit, SIGNAL(dateChanged(const QDate &)), this, SLOT(dateChanged(const QDate &)));
}

AddRecetteDialog::~AddRecetteDialog()
{
    delete ui;
}

int AddRecetteDialog::getSelectedServeurId() {

    QString selectedText = ui->comboBox->currentText();
    int idServeur = selectedText.split(" - ")[0].toInt();
    return idServeur;
}

double AddRecetteDialog::calculateTotalParJournee() {
    return databaseManager_->calculateTotalParJournee(getSelectedServeurId(), ui->dateEdit->date());
}

void AddRecetteDialog::serveurSelectionChanged(int index) {

    double totalParJournee = calculateTotalParJournee();
    ui->lineEdit->setText(QString::number(totalParJournee));
}

void AddRecetteDialog::dateChanged(const QDate &date) {

    double totalParJournee = calculateTotalParJournee();
    ui->lineEdit->setText(QString::number(totalParJournee));
}

QDate AddRecetteDialog::getRecetteDate() const {
    // Code pour récupérer la date de la recette à partir du date edit
    return ui->dateEdit->date();
}

double AddRecetteDialog::getTotalParJournee() const {
    // Code pour récupérer le total de la journée à partir du line edit
    return ui->lineEdit->text().toDouble();
}
