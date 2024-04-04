#include "updateserverdialog.h"
#include "ui_updateserverdialog.h"
#include "QSqlQuery"

UpdateServerDialog::UpdateServerDialog(const QStringList &entityCodes, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UpdateServerDialog)
{
    ui->setupUi(this);
    // Remplir la combobox avec les codes des entités
    ui->comboBox->addItems(entityCodes);

    // Connecter le signal de sélection de la combobox à une fonction de mise à jour des détails
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) {
        QString selectedCode = ui->comboBox->currentText();
        // Émettre un signal pour indiquer que le code sélectionné a changé
        emit selectedCodeChanged(selectedCode.toInt());
    });
}

UpdateServerDialog::~UpdateServerDialog()
{
    delete ui;
}


QString UpdateServerDialog::getSelectedCode() const
{
    return ui->comboBox->currentText();
}

void UpdateServerDialog::setServerDetails(const QString &login, const QString &password, const QString &cin)
{
    // Remplir les zones de texte avec les détails du produit
    ui->lineEdit_login->setText(login);
    ui->lineEdit_password->setText(password);
    ui->lineEdit_cin->setText(cin);
}

void UpdateServerDialog::on_comboBox_currentIndexChanged(int index)
{
    QString selectedCode = QString::number(index + 1); // Convertir l'indice en QString

    QSqlQuery query = databaseManager_.selectServerDetails(getSelectedCode()); // Utiliser la fonction selectServerDetails avec le code sélectionné


    if (query.next()) {
        QString login = query.value("login").toString();
        QString password = query.value("motdepasse").toString();
        QString cin = query.value("cin").toString();

        // Afficher les détails du produit dans l'UpdateDialog
        this->setServerDetails(login, password, cin);
    } else {
        qDebug() << "No server found for code:" << index;
    }
}

QList<QString> UpdateServerDialog::getServerData() const
{
    QList<QString> serverData;
    serverData << ui->lineEdit_login->text();
    serverData << ui->lineEdit_password->text();
    serverData << ui->lineEdit_cin->text();
    return serverData;
}


void UpdateServerDialog::setFieldsReadOnly(bool readOnly)
{
    ui->lineEdit_cin->setReadOnly(readOnly);
    ui->lineEdit_login->setReadOnly(readOnly);
    ui->lineEdit_password->setReadOnly(readOnly);
}
