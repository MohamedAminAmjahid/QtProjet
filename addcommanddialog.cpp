/**
 * @file addcommanddialog.cpp
 */

#include "addcommanddialog.h"
#include "ui_addcommanddialog.h"

/**
 * @brief Constructeur de la classe AddCommandDialog
 * @param parent Widget parent
 */
AddCommandDialog::AddCommandDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCommandDialog),
    productList_(nullptr)
{
    // Initialisation de l'interface utilisateur
    ui->setupUi(this);

    // Configuration de la date actuelle et de l'affichage du calendrier
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit->setCalendarPopup(true);

    // Configuration de la valeur initiale pour la quantité à 1
    ui->spinBoxQuantity->setValue(1);
}

/**
 * @brief Destructeur de la classe AddCommandDialog
 */
AddCommandDialog::~AddCommandDialog()
{
    delete productList_;
    delete ui;
}

/**
 * @brief Remplit la combobox avec la liste des produits
 * @param productList Liste des produits (paires de codes et de noms)
 */
void AddCommandDialog::fillProductComboBox(const QList<QPair<QString, QString>> &productList)
{
    // Efface les éléments existants dans la combobox
    ui->comboBoxProductId->clear();

    // Parcourt la liste des produits et ajoute chaque produit à la combobox
    for (const auto &product : productList) {
        ui->comboBoxProductId->addItem(product.first + "- " +product.second);
    }

    // Stocke la liste des produits pour une utilisation ultérieure
    productList_ = new QList<QPair<QString, QString>>(productList);
}

/**
 * @brief Récupère la date de la commande
 * @return Date de la commande
 */
QDate AddCommandDialog::getDate() const
{
    return ui->dateEdit->date();
}

/**
 * @brief Récupère la quantité de produits commandée
 * @return Quantité de produits commandée
 */
int AddCommandDialog::getQuantity() const
{
    return ui->spinBoxQuantity->value();
}

/**
 * @brief Slot déclenché lors de l'acceptation de la boîte de dialogue
 */
void AddCommandDialog::on_buttonBox_accepted()
{
    accept();
}

/**
 * @brief Slot déclenché lors du rejet de la boîte de dialogue
 */
void AddCommandDialog::on_buttonBox_rejected()
{
    reject();
}

/**
 * @brief Récupère le code du produit sélectionné dans la combobox
 * @return Code du produit sélectionné
 */
QString AddCommandDialog::getSelectedProductId() const
{
    int currentIndex = ui->comboBoxProductId->currentIndex();

    // Vérifie que l'index est valide et que la liste des produits existe
    if (currentIndex >= 0 && productList_ != nullptr && currentIndex < productList_->size()) {
        return (*productList_)[currentIndex].first;
    }

    return "";
}
