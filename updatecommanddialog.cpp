#include "updatecommanddialog.h"
#include "ui_updatecommanddialog.h"
#include <QMessageBox>

UpdateCommandDialog::UpdateCommandDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateCommandDialog)
{
    ui->setupUi(this);

    connect(ui->lineEditCommandNumber, &QLineEdit::editingFinished, this, &UpdateCommandDialog::on_lineEditCommandNumber_editingFinished);

    // Remplir le ComboBox avec les produits
    fillProductComboBox(databaseManager_.selectProductCodesAndNames()); // Supposons que vous avez une fonction pour obtenir tous les produits
}

UpdateCommandDialog::~UpdateCommandDialog()
{
    delete ui;
}

Commande UpdateCommandDialog::getUpdatedCommand() const
{
    return updatedCommand;
}

void UpdateCommandDialog::fillProductComboBox(const QList<QPair<QString, QString>> &productList)
{
    ui->comboBox->clear();
    for (const auto &product : productList) {
        ui->comboBox->addItem(product.second, product.first);
    }
}

void UpdateCommandDialog::on_lineEditCommandNumber_editingFinished()
{
    QString commandNumber = ui->lineEditCommandNumber->text();
    Commande command = databaseManager_.getCommandByNumber(commandNumber);

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

QList<QString> UpdateCommandDialog::getCommandData() const
{
    QList<QString> commandData;
    commandData << ui->lineEditCommandNumber->text();
    commandData << ui->comboBox->currentData().toString();
    commandData << QString::number(ui->spinBoxQuantity->value());
    commandData << ui->dateEdit->date().toString("yyyy-MM-dd");

    return commandData;
}

void UpdateCommandDialog::setFieldsReadOnly(bool readOnly)
{
    ui->comboBox->setEnabled(!readOnly);
    ui->spinBoxQuantity->setReadOnly(readOnly);
    ui->dateEdit->setReadOnly(readOnly);
}
