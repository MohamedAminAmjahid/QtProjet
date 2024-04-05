#ifndef UPDATERECETTEDIALOG_H
#define UPDATERECETTEDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QDateEdit>
#include <QLineEdit>
#include <QPair>
#include <databasemanager.h>

namespace Ui {
class UpdateRecetteDialog;
}

/**
 * @brief La classe UpdateRecetteDialog permet de mettre à jour les informations d'une recette dans le système.
 */
class UpdateRecetteDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur de la classe UpdateRecetteDialog.
     * @param parent Le widget parent.
     */
    explicit UpdateRecetteDialog(QWidget *parent = nullptr);

    /**
     * @brief Destructeur de la classe UpdateRecetteDialog.
     */
    ~UpdateRecetteDialog();

    /**
     * @brief Définit les options de code de recette disponibles.
     * @param codes La liste des codes de recette disponibles.
     */
    void setCodeRecetteOptions(const QList<int> &codes);

    /**
     * @brief Définit les options d'identifiant de serveur disponibles.
     * @param ids La liste des paires (identifiant de serveur, nom du serveur) disponibles.
     */
    void setIdServeurOptions(const QList<QPair<int, QString>> &ids);

    /**
     * @brief Obtient le code de recette sélectionné.
     * @return Le code de recette sélectionné.
     */
    int getSelectedCodeRecette() const;

    /**
     * @brief Obtient l'identifiant de serveur sélectionné.
     * @return L'identifiant de serveur sélectionné.
     */
    int getSelectedIdServeur() const;

    /**
     * @brief Obtient le nouveau total par journée saisi.
     * @return Le nouveau total par journée saisi.
     */
    double getNouveauTotalParJournee() const;

    /**
     * @brief Obtient la nouvelle date saisie.
     * @return La nouvelle date saisie.
     */
    QDate getNouvelleDate() const;

    /**
     * @brief Définit le titre de la boîte de dialogue.
     * @param title Le titre de la boîte de dialogue.
     */
    void setDialogTitle(const QString &title);

    /**
     * @brief Désactive les éléments de l'interface utilisateur.
     */
    void disableUIElements();

private slots:
    /**
     * @brief Appelée lorsque l'index de la liste déroulante change.
     * @param index Le nouvel index sélectionné.
     */
    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::UpdateRecetteDialog *ui; /**< Interface utilisateur de la boîte de dialogue de mise à jour de recette. */
    DatabaseManager databaseManager_; /**< Gestionnaire de base de données. */
};

#endif
