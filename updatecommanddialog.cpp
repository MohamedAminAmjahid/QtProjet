/**
 * @file updatecommanddialog.cpp
 */

#include "updatecommanddialog.h"
#include "ui_updatecommanddialog.h"
#include <QMessageBox>

/**
 * @brief Constructeur de la classe UpdateCommandDialog
 * @param parent Widget parent
 * @param admin Identifiant de l'administrateur
 */
UpdateCommandDialog::UpdateCommandDialog(QWidget *parent, int admin) :
    QDialog(parent),
    ui(new Ui::UpdateCommandDialog),
    admin_(admin)
{
    ui->setupUi(this);

    // Connexion du signal editingFinished du lineEditCommandNumber à la fonction on_lineEditCommandNumber_editingFinished
    connect(ui->lineEditCommandNumber, &QLineEdit::editingFinished, this, &UpdateCommandDialog::on_lineEditCommandNumber_editingFinished);

    // Remplissage de la combobox de produits avec la liste des codes et noms de produits
    fillProductComboBox(databaseManager_.selectProductCodesAndNames());
}

/**
 * @brief Destructeur de la classe UpdateCommandDialog
 */
UpdateCommandDialog::~UpdateCommandDialog()
{
    delete ui;
}

/**
 * @brief Obtient la commande mise à jour
 * @return Commande mise à jour
 */
Commande UpdateCommandDialog::getUpdatedCommand() const
{
    return updatedCommand;
}

/**
 * @brief Remplit la combobox de produits avec une liste de produits
 * @param productList Liste de paires (code, nom) de produits
 */
void UpdateCommandDialog::fillProductComboBox(const QList<QPair<QString, QString>> &productList)
{
    ui->comboBox->clear();
    for (const auto &product : productList) {
        ui->comboBox->addItem(product.second, product.first);
    }
}

/**
 * @brief Slot appelé lorsque l'édition du lineEditCommandNumber est terminée
 */
void UpdateCommandDialog::on_lineEditCommandNumber_editingFinished()
{
    QString commandNumber = ui->lineEditCommandNumber->text();
    Commande command;
    command = databaseManager_.getCommandByNumber(commandNumber);
    if(admin_ != 1 & command.idServeur() != admin_){
        QMessageBox::warning(this, "Erreur", "La commande n'a pas été trouvée.");
    }
    else{
        if (!command.codeCommande().isEmpty()) {
            updatedCommand = command;

            for (int i = 0; i < ui->comboBox->count(); ++i) {
                if (ui->comboBox->itemData(i).toString() == QString::number(command.idProduit())) {
                    ui->comboBox->setCurrentIndex(i);
                    break;
                }
            }
            ui->spinBoxQuantity->setValue(command.quantite());
            ui->dateEdit->setDate(command.dateCommande());
        } else {
            QMessageBox::warning(this, "Erreur", "La commande n'a pas été trouvée.");
        }
    }
}

/**
 * @brief Obtient les données de la commande
 * @return Liste contenant les données de la commande
 */
QList<QString> UpdateCommandDialog::getCommandData() const
{
    QList<QString> commandData;
    commandData << ui->lineEditCommandNumber->text();
    commandData << ui->comboBox->currentData().toString();
    commandData << QString::number(ui->spinBoxQuantity->value());
    commandData << ui->dateEdit->date().toString("yyyy-MM-dd");

    return commandData;
}

/**
 * @brief Définit la lecture seule des champs
 * @param readOnly Si vrai, les champs sont en lecture seule ; sinon, ils sont éditables
 */
void UpdateCommandDialog::setFieldsReadOnly(bool readOnly)
{
    ui->comboBox->setEnabled(!readOnly);
    ui->spinBoxQuantity->setReadOnly(readOnly);
    ui->dateEdit->setReadOnly(readOnly);
}
