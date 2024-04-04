#include "updaterecettedialog.h"
#include "ui_updaterecettedialog.h"

UpdateRecetteDialog::UpdateRecetteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateRecetteDialog)
{
    ui->setupUi(this);

    ui->dateEdit->setEnabled(false);
    ui->lineEdit->setEnabled(false);
}

UpdateRecetteDialog::~UpdateRecetteDialog()
{
    delete ui;
}

void UpdateRecetteDialog::setCodeRecetteOptions(const QList<int> &codes)
{
    ui->comboBox->clear();
    for (int code : codes)
        ui->comboBox->addItem(QString::number(code));

}

void UpdateRecetteDialog::setIdServeurOptions(const QList<QPair<int, QString>> &serveursAndLogins)
{
    ui->comboBox_2->clear();
    for (const auto &pair : serveursAndLogins) {
        QString idLogin = QString("%1-%2").arg(pair.first).arg(pair.second);
        ui->comboBox_2->addItem(idLogin);
    }
}

int UpdateRecetteDialog::getSelectedCodeRecette() const
{
    return ui->comboBox->currentText().toInt();
}

int UpdateRecetteDialog::getSelectedIdServeur() const
{
    QString selectedText = ui->comboBox_2->currentText();
    QStringList parts = selectedText.split("-");
    return parts[0].toInt();
}


double UpdateRecetteDialog::getNouveauTotalParJournee() const
{
    return ui->lineEdit->text().toDouble();
}

QDate UpdateRecetteDialog::getNouvelleDate() const
{
    return ui->dateEdit->date();
}


void UpdateRecetteDialog::on_comboBox_currentIndexChanged(int index)
{
    int selectedCodeRecette = ui->comboBox->currentText().toInt();

    Recette info = databaseManager_.getRecetteInfo(selectedCodeRecette);

    ui->lineEdit->setText(QString::number(info.getTotalParJournee()));
    ui->dateEdit->setDate(info.getDate());
}

void UpdateRecetteDialog::setDialogTitle(const QString &title)
{
    setWindowTitle(title);
}

void UpdateRecetteDialog::disableUIElements()
{
    ui->comboBox_2->setEnabled(false);
    ui->dateEdit->setEnabled(false);
    ui->lineEdit->setEnabled(false);
}
