/**
 * @file searchserveranddaterecettedialog.cpp
 */

#include "searchserveranddaterecettedialog.h"
#include <QFormLayout>

/**
 * @brief Constructeur de la classe SearchServerAndDateRecetteDialog
 * @param parent Widget parent
 */
SearchServerAndDateRecetteDialog::SearchServerAndDateRecetteDialog(QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QFormLayout *formLayout = new QFormLayout();
    mainLayout->addLayout(formLayout);

    // Création des widgets
    serverComboBox_ = new QComboBox();
    dateEdit_ = new QDateEdit();
    totalLineEdit_ = new QLineEdit();

    // Ajout des widgets au formulaire
    formLayout->addRow("Server", serverComboBox_);
    formLayout->addRow("Date", dateEdit_);
    formLayout->addRow("Total", totalLineEdit_);

    // Connexions des signaux aux slots
    connect(serverComboBox_, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &SearchServerAndDateRecetteDialog::updateTotal);
    connect(dateEdit_, &QDateEdit::dateChanged, this, &SearchServerAndDateRecetteDialog::updateTotal);

    // Configuration de la date actuelle et de l'affichage du calendrier
    dateEdit_->setDate(QDate::currentDate());
    dateEdit_->setCalendarPopup(true);

    // Définition du titre de la fenêtre
    setWindowTitle("Search Server and Date Recette");

    // Initialisation de la combobox
    initializeComboBox();

    // Mise à jour du total
    updateTotal();
}

/**
 * @brief Initialise la combobox des serveurs
 */
void SearchServerAndDateRecetteDialog::initializeComboBox()
{
    serverComboBox_->clear();

    // Obtention de la liste des serveurs et de leurs identifiants
    QList<QPair<int, QString>> serveurs = databaseManager_->getServeursAndLogins();

    // Remplissage de la combobox avec les serveurs
    for (const auto& pair : serveurs) {
        serverComboBox_->addItem(QString("%1 - %2").arg(pair.first).arg(pair.second), pair.first);
    }
}

/**
 * @brief Met à jour le total des recettes en fonction du serveur et de la date sélectionnés
 */
void SearchServerAndDateRecetteDialog::updateTotal()
{
    // Obtention de l'identifiant du serveur sélectionné
    int selectedServerId = serverComboBox_->currentData().toInt();

    // Obtention de la date sélectionnée
    QDate selectedDate = dateEdit_->date();

    // Requête pour obtenir le total des recettes pour le serveur et la date sélectionnés
    QString totalRecettes = databaseManager_->selectRecettesForServerAndDate(selectedServerId, selectedDate);

    // Mise à jour du champ de texte avec le total des recettes
    totalLineEdit_->setText(totalRecettes);
}
