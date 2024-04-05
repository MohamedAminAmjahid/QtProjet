#ifndef ADDRECETTEDIALOG_H
#define ADDRECETTEDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QDate>
#include "databaseManager.h"

namespace Ui {
class AddRecetteDialog;
}

class AddRecetteDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur explicite de la classe AddRecetteDialog.
     * @param parent Le widget parent de la boîte de dialogue.
     * @param databaseManager Le gestionnaire de base de données utilisé pour récupérer les données des serveurs.
     */
    explicit AddRecetteDialog(QWidget *parent = nullptr, DatabaseManager *databaseManager = nullptr);

    /**
     * @brief Destructeur de la classe AddRecetteDialog.
     */
    ~AddRecetteDialog();

    /**
     * @brief Récupère l'ID du serveur sélectionné.
     * @return L'ID du serveur sélectionné.
     */
    int getSelectedServeurId();

    /**
     * @brief Calcule le total par journée pour la recette.
     * @return Le total par journée calculé.
     */
    double calculateTotalParJournee();

    /**
     * @brief Récupère la date de la recette.
     * @return La date de la recette.
     */
    QDate getRecetteDate() const;

    /**
     * @brief Récupère le total par journée de la recette.
     * @return Le total par journée de la recette.
     */
    double getTotalParJournee() const;

private slots:
    /**
     * @brief Slot appelé lorsque la sélection du serveur est modifiée.
     * @param index L'index du serveur sélectionné dans la liste déroulante.
     */
    void serveurSelectionChanged(int index);

    /**
     * @brief Slot appelé lorsque la date est modifiée.
     * @param date La nouvelle date sélectionnée.
     */
    void dateChanged(const QDate &date);

private:
    Ui::AddRecetteDialog *ui; ///< Interface utilisateur de la boîte de dialogue.
    DatabaseManager *databaseManager_; ///< Gestionnaire de base de données utilisé pour récupérer les données des serveurs.
};

#endif
