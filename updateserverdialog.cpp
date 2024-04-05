/**
 * @file updateserverdialog.cpp
 */

#include "updateserverdialog.h"
#include "ui_updateserverdialog.h"
#include <QSqlQuery>

/**
 * @brief Constructeur de la classe UpdateServerDialog
 * @param entityCodes Liste des codes d'entité
 * @param parent Widget parent
 */
UpdateServerDialog::UpdateServerDialog(const QStringList &entityCodes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateServerDialog)
{
    ui->setupUi(this);
    ui->comboBox->addItems(entityCodes);

    // Connexion du signal currentIndexChanged de la combobox à la fonction lambda
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) {
        // Récupération du code sélectionné dans la combobox
        QString selectedCode = ui->comboBox->currentText();
        // Émission du signal selectedCodeChanged avec le code sélectionné
        emit selectedCodeChanged(selectedCode.toInt());
    });
}

/**
 * @brief Destructeur de la classe UpdateServerDialog
 */
UpdateServerDialog::~UpdateServerDialog()
{
    delete ui;
}

/**
 * @brief Obtient le code sélectionné dans la combobox
 * @return Code sélectionné
 */
QString UpdateServerDialog::getSelectedCode() const
{
    return ui->comboBox->currentText();
}

/**
 * @brief Configure les détails du serveur dans l'interface utilisateur
 * @param login Nom d'utilisateur
 * @param password Mot de passe
 * @param cin Numéro d'identification civile
 */
void UpdateServerDialog::setServerDetails(const QString &login, const QString &password, const QString &cin)
{
    // Configuration des champs de l'interface utilisateur avec les détails du serveur
    ui->lineEdit_login->setText(login);
    ui->lineEdit_password->setText(password);
    ui->lineEdit_cin->setText(cin);
}

/**
 * @brief Slot déclenché lors du changement de l'index sélectionné dans la combobox
 * @param index Nouvel index sélectionné
 */
void UpdateServerDialog::on_comboBox_currentIndexChanged(int index)
{
    // Obtention du code sélectionné dans la combobox
    QString selectedCode = QString::number(index + 1);

    // Exécution d'une requête SQL pour récupérer les détails du serveur
    QSqlQuery query = databaseManager_.selectServerDetails(getSelectedCode());

    // Vérification si la requête a renvoyé des résultats
    if (query.next()) {
        // Récupération des détails du serveur depuis la requête
        QString login = query.value("login").toString();
        QString password = query.value("motdepasse").toString();
        QString cin = query.value("cin").toString();

        // Configuration des détails du serveur dans l'interface utilisateur
        this->setServerDetails(login, password, cin);
    } else {
        qDebug() << "No server found for code:" << index;
    }
}

/**
 * @brief Obtient les données saisies par l'utilisateur pour le serveur
 * @return Données du serveur
 */
QList<QString> UpdateServerDialog::getServerData() const
{
    // Obtention des données du serveur saisies par l'utilisateur
    QList<QString> serverData;
    serverData << ui->lineEdit_login->text();
    serverData << ui->lineEdit_password->text();
    serverData << ui->lineEdit_cin->text();
    return serverData;
}

/**
 * @brief Configure les champs de l'interface utilisateur en lecture seule ou non
 * @param readOnly Vrai pour activer la lecture seule, faux sinon
 */
void UpdateServerDialog::setFieldsReadOnly(bool readOnly)
{
    // Configuration des champs de l'interface utilisateur en lecture seule ou non
    ui->lineEdit_cin->setReadOnly(readOnly);
    ui->lineEdit_login->setReadOnly(readOnly);
    ui->lineEdit_password->setReadOnly(readOnly);
}
