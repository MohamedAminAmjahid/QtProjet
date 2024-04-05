#ifndef SEARCHSERVERANDDATERECETTEDIALOG_H
#define SEARCHSERVERANDDATERECETTEDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QDateEdit>
#include <QLineEdit>
#include "databasemanager.h"

/**
 * @brief La classe SearchServerAndDateRecetteDialog représente une boîte de dialogue permettant de rechercher
 * une recette par serveur et date.
 * L'utilisateur peut sélectionner un serveur et une date, puis la recette totale pour cette journée et ce serveur
 * est affichée.
 */
class SearchServerAndDateRecetteDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur de la classe SearchServerAndDateRecetteDialog.
     * @param parent Le widget parent de la boîte de dialogue.
     */
    SearchServerAndDateRecetteDialog(QWidget *parent = nullptr);

private slots:
    /**
     * @brief Slot appelé lorsque les valeurs du serveur ou de la date sont modifiées.
     * Met à jour le montant total de la recette pour la journée et le serveur sélectionnés.
     */
    void updateTotal();

private:
    /**
     * @brief Initialise le menu déroulant des serveurs.
     */
    void initializeComboBox();

    QComboBox *serverComboBox_; /**< Menu déroulant pour sélectionner un serveur. */
    QDateEdit *dateEdit_; /**< Sélecteur de date pour choisir une date. */
    QLineEdit *totalLineEdit_; /**< Champ de texte pour afficher le montant total de la recette. */
    DatabaseManager *databaseManager_; /**< Gestionnaire de base de données pour effectuer les requêtes de recherche. */
};

#endif
