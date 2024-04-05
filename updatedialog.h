#ifndef UPDATEDIALOG_H
#define UPDATEDIALOG_H

#include <QDialog>
#include <databasemanager.h>

namespace Ui {
class UpdateDialog;
}

/**
 * @brief La classe UpdateDialog permet de mettre à jour les détails d'un produit dans le système.
 */
class UpdateDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur de la classe UpdateDialog.
     * @param productCodes Les codes des produits disponibles pour la mise à jour.
     * @param parent Le widget parent.
     */
    explicit UpdateDialog(const QStringList &productCodes, QWidget *parent = nullptr);

    /**
     * @brief Destructeur de la classe UpdateDialog.
     */
    ~UpdateDialog();

    /**
     * @brief Obtient le code du produit sélectionné.
     * @return Le code du produit sélectionné.
     */
    QString getSelectedCode() const;

    /**
     * @brief Obtient les données du produit.
     * @return Les données du produit.
     */
    QList<QString> getProductData() const;

    /**
     * @brief Définit si les champs sont en lecture seule ou non.
     * @param readOnly Booléen indiquant si les champs doivent être en lecture seule.
     */
    void setFieldsReadOnly(bool readOnly);

public slots:
    /**
     * @brief Définit les détails du produit sélectionné.
     * @param designation La désignation du produit.
     * @param price Le prix du produit.
     * @param quantity La quantité du produit.
     */
    void setProductDetails(const QString &designation, double price, int quantity);

private:
    Ui::UpdateDialog *ui; /**< Interface utilisateur de la boîte de dialogue de mise à jour. */
    DatabaseManager databaseManager_; /**< Gestionnaire de base de données. */

signals:
    /**
     * @brief Signal émis lorsque le code sélectionné change.
     * @param code Le nouveau code sélectionné.
     */
    void selectedCodeChanged(int code);

private slots:
    /**
     * @brief Appelée lorsque l'index de la liste déroulante change.
     * @param index Le nouvel index sélectionné.
     */
    void on_comboBox_currentIndexChanged(int index);
};

#endif
