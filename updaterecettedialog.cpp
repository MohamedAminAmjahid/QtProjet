/**
 * @file updaterecettedialog.cpp
 */

#include "updaterecettedialog.h"
#include "ui_updaterecettedialog.h"

/**
 * @brief Constructeur de la classe UpdateRecetteDialog
 * @param parent Widget parent
 */
UpdateRecetteDialog::UpdateRecetteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateRecetteDialog)
{
    ui->setupUi(this);

    // Désactiver les champs de saisie
    ui->dateEdit->setEnabled(false);
    ui->lineEdit->setEnabled(false);
}

/**
 * @brief Destructeur de la classe UpdateRecetteDialog
 */
UpdateRecetteDialog::~UpdateRecetteDialog()
{
    delete ui;
}

/**
 * @brief Définit les options pour le choix du code de recette
 * @param codes Liste des codes de recette
 */
void UpdateRecetteDialog::setCodeRecetteOptions(const QList<int> &codes)
{
    ui->comboBox->clear();
    for (int code : codes)
        ui->comboBox->addItem(QString::number(code));
}

/**
 * @brief Définit les options pour le choix de l'identifiant du serveur
 * @param serveursAndLogins Liste des paires d'identifiants de serveur et de login
 */
void UpdateRecetteDialog::setIdServeurOptions(const QList<QPair<int, QString>> &serveursAndLogins)
{
    ui->comboBox_2->clear();
    for (const auto &pair : serveursAndLogins) {
        QString idLogin = QString("%1-%2").arg(pair.first).arg(pair.second);
        ui->comboBox_2->addItem(idLogin);
    }
}

/**
 * @brief Obtient le code de recette sélectionné
 * @return Code de recette sélectionné
 */
int UpdateRecetteDialog::getSelectedCodeRecette() const
{
    return ui->comboBox->currentText().toInt();
}

/**
 * @brief Obtient l'identifiant du serveur sélectionné
 * @return Identifiant du serveur sélectionné
 */
int UpdateRecetteDialog::getSelectedIdServeur() const
{
    QString selectedText = ui->comboBox_2->currentText();
    QStringList parts = selectedText.split("-");
    return parts[0].toInt();
}

/**
 * @brief Slot déclenché lors du changement de sélection dans la combobox de code de recette
 * @param index Nouvel index sélectionné
 */
void UpdateRecetteDialog::on_comboBox_currentIndexChanged(int index)
{
    // Obtention du code de recette sélectionné
    int selectedCodeRecette = ui->comboBox->currentText().toInt();

    // Récupération des informations sur la recette à partir de la base de données
    Recette info = databaseManager_.getRecetteInfo(selectedCodeRecette);

    // Mise à jour des champs de l'interface utilisateur avec les informations récupérées
    ui->lineEdit->setText(QString::number(info.getTotalParJournee()));
    ui->dateEdit->setDate(info.getDate());
}

/**
 * @brief Définit le titre de la fenêtre de dialogue
 * @param title Titre de la fenêtre
 */
void UpdateRecetteDialog::setDialogTitle(const QString &title)
{
    setWindowTitle(title);
}

/**
 * @brief Désactive certains éléments de l'interface utilisateur
 */
void UpdateRecetteDialog::disableUIElements()
{
    ui->comboBox_2->setEnabled(false);
    ui->dateEdit->setEnabled(false);
    ui->lineEdit->setEnabled(false);
}
