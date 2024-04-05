#ifndef UPDATECOMMANDDIALOG_H
#define UPDATECOMMANDDIALOG_H

#include <QDialog>
#include "commande.h"
#include "databasemanager.h"

namespace Ui {
class UpdateCommandDialog;
}

/**
 * @brief La classe UpdateCommandDialog permet de mettre à jour une commande dans le système.
 */
class UpdateCommandDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur de la classe UpdateCommandDialog.
     * @param parent Le widget parent.
     * @param admin Un indicateur spécifiant les autorisations de l'utilisateur.
     */
    explicit UpdateCommandDialog(QWidget *parent = nullptr, int admin = 1);

    /**
     * @brief Destructeur de la classe UpdateCommandDialog.
     */
    ~UpdateCommandDialog();

    /**
     * @brief Obtient la commande mise à jour.
     * @return La commande mise à jour.
     */
    Commande getUpdatedCommand() const;

    /**
     * @brief Obtient les données de la commande.
     * @return Les données de la commande.
     */
    QList<QString> getCommandData() const;

    /**
     * @brief Remplit la liste déroulante des produits avec la liste spécifiée.
     * @param productList La liste des produits à afficher dans la liste déroulante.
     */
    void fillProductComboBox(const QList<QPair<QString, QString>> &productList);

    /**
     * @brief Définit si les champs sont en lecture seule ou non.
     * @param readOnly Booléen indiquant si les champs doivent être en lecture seule.
     */
    void setFieldsReadOnly(bool readOnly);

private slots:
    /**
     * @brief Appelée lorsque l'édition du numéro de commande est terminée.
     */
    void on_lineEditCommandNumber_editingFinished();

private:
    Ui::UpdateCommandDialog *ui; /**< Interface utilisateur de la boîte de dialogue de mise à jour de commande. */
    Commande updatedCommand; /**< Commande mise à jour. */
    DatabaseManager databaseManager_; /**< Gestionnaire de base de données. */
    int admin_; /**< Indicateur des autorisations de l'utilisateur. */
};

#endif
