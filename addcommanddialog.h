#ifndef ADDCOMMANDDIALOG_H
#define ADDCOMMANDDIALOG_H

#include <QDialog>
#include <QStringList>
#include <QDate>

namespace Ui {
class AddCommandDialog;
}

class AddCommandDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur explicite de la classe AddCommandDialog.
     * @param parent Le widget parent de la boîte de dialogue.
     */
    explicit AddCommandDialog(QWidget *parent = nullptr);

    /**
     * @brief Destructeur de la classe AddCommandDialog.
     */
    ~AddCommandDialog();

    /**
     * @brief Remplit la liste déroulante des produits avec la liste spécifiée.
     * @param productList La liste des produits sous forme de paires (ID, nom).
     */
    void fillProductComboBox(const QList<QPair<QString, QString>> &productList);

    /**
     * @brief Récupère la date saisie par l'utilisateur.
     * @return La date saisie.
     */
    QDate getDate() const;

    /**
     * @brief Récupère la quantité saisie par l'utilisateur.
     * @return La quantité saisie.
     */
    int getQuantity() const;

    /**
     * @brief Récupère l'identifiant du produit sélectionné par l'utilisateur.
     * @return L'identifiant du produit sélectionné.
     */
    QString getSelectedProductId() const;

private slots:
    /**
     * @brief Slot appelé lorsque l'utilisateur accepte la saisie.
     */
    void on_buttonBox_accepted();

    /**
     * @brief Slot appelé lorsque l'utilisateur rejette la saisie.
     */
    void on_buttonBox_rejected();

private:
    Ui::AddCommandDialog *ui; ///< Interface utilisateur de la boîte de dialogue.
    QList<QPair<QString, QString>> *productList_; ///< Liste des produits disponibles.
};

#endif
