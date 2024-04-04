#include "gestionserveurform.h"
#include "ui_gestionserveurform.h"
#include <addcommanddialog.h>
#include <QMessageBox>
#include <commande.h>
#include <listform.h>
#include <mainwindow.h>
#include <updatecommanddialog.h>

GestionServeurForm::GestionServeurForm(QWidget *parent, DatabaseManager *databasemanager)
    : QMainWindow(parent)
    , ui(new Ui::GestionServeurForm),
    databaseManager_(databasemanager),
    settings("www.ensiie.fr", "Project")
{
    ui->setupUi(this);
}

GestionServeurForm::~GestionServeurForm()
{
    delete ui;
}

void GestionServeurForm::on_actionAddCommands_triggered()
{
    QList<QPair<QString, QString>> productCodesAndNames = databaseManager_.selectProductCodesAndNames();

    AddCommandDialog addCommandDialog(this);
    addCommandDialog.fillProductComboBox(productCodesAndNames);

    if (addCommandDialog.exec() == QDialog::Accepted) {
        QString selectedProductId = addCommandDialog.getSelectedProductId();
        QDate commandDate = addCommandDialog.getDate();
        int quantity = addCommandDialog.getQuantity();

        int stockQuantity = databaseManager_.getStockQuantity(selectedProductId);
        if (stockQuantity < quantity) {
            QMessageBox::critical(this, "Error", "Not enough stock!");
            return;
        }

        int serverId = settings.value("ServerID").toInt();

        if (databaseManager_.insertCommand(serverId, selectedProductId, quantity, commandDate)) {
            qDebug() << "Command added successfully!";
        } else {
            qDebug() << "Failed to add command!";
        }
    }
}


void GestionServeurForm::on_actionListCommands_triggered()
{
    QList<Commande> commandList = databaseManager_.selectCommands();

    QList<QStringList> dataList;
    QStringList columnNames = {"Code commande", "Nom Produit", "Quantité", "Prix unitaire", "Total", "Date"};

    int idServeur = settings.value("ServerID").toInt();

    for (const Commande &command : commandList) {
        QString productName = databaseManager_.getProductName(command.idProduit());
        double productPrice = databaseManager_.getProductPrice(command.idProduit());
        double total = command.quantite() * productPrice;

        if(command.idServeur() == idServeur) {
            QStringList rowData;
            rowData <<command.codeCommande() << productName << QString::number(command.quantite()) << QString::number(productPrice) << QString::number(total) << command.dateCommande().toString("yyyy-MM-dd");
            dataList << rowData;
        }
    }

    ListForm *listForm = new ListForm(this);

    listForm->displayData(dataList, columnNames);

    listForm->show();
}



void GestionServeurForm::on_actionLogOut_triggered()
{
    databaseManager_.disconnectFromDatabase();
    this->close();
    MainWindow *mainWindow = new MainWindow(this);

    mainWindow->show();
}


void GestionServeurForm::on_actionUpdateCommands_triggered()
{
    UpdateCommandDialog updateCommandDialog(this);
    updateCommandDialog.exec();

    Commande updatedCommand = updateCommandDialog.getUpdatedCommand();
    if (updatedCommand.codeCommande() != "") {
        QList<QString> commandData = updateCommandDialog.getCommandData();

        QString selectedCommandCode = commandData.at(0);
        int idProduit = commandData.at(1).toInt();
        int quantite = commandData.at(2).toInt();
        QDate dateCommande = QDate::fromString(commandData.at(3), "yyyy-MM-dd");

        int quantite2 = updatedCommand.quantite();
        if(quantite - quantite2 < 0){
            databaseManager_.setQuantite(QString::number(idProduit), quantite2 - quantite);
        }else if (quantite - quantite2 > 0) {
            int stockQuantity = databaseManager_.getStockQuantity(QString::number(idProduit));
            if (stockQuantity < quantite - quantite2 ) {
                QMessageBox::critical(this, "Error", "Not enough stock!");
                return;
            }
            else {
                databaseManager_.setQuantite(QString::number(idProduit), quantite2 - quantite);
            }
        }

        if (!databaseManager_.updateCommand(selectedCommandCode, idProduit, quantite, dateCommande)) {
            qDebug() << "Failed to insert product!";
        } else {
            qDebug() << "Product inserted successfully!";
        }
    }
}

void GestionServeurForm::on_actionDeleteCommands_triggered()
{
    UpdateCommandDialog updateCommandDialog(this);
    updateCommandDialog.setFieldsReadOnly(true);
    updateCommandDialog.exec();

    Commande updatedCommand = updateCommandDialog.getUpdatedCommand();
    if (updatedCommand.codeCommande() != "") {
        QString commandNumber = updatedCommand.codeCommande();

        if (databaseManager_.deleteCommandByNumber(commandNumber)) {
            QMessageBox::information(this, "Suppression réussie", "La commande a été supprimée avec succès.");
        } else {
            QMessageBox::warning(this, "Erreur", "La commande n'a pas pu être supprimée.");
        }
    }
}


void GestionServeurForm::on_actionClose_triggered()
{
    this->close();
}


void GestionServeurForm::on_actionListRecette_triggered()
{
    int idServeur = settings.value("ServerID").toInt();

    if (idServeur <= 0) {
        qDebug() << "Invalid server ID from settings!";
        return;
    }

    QList<QPair<QPair<int, QString>, QPair<double, QString>>> recettes = databaseManager_.selectRecettesWithServerLoginsAndDetails(idServeur);

    QList<QStringList> dataList;
    QStringList columnNames = {"Total Par Journee", "Date"};

    for (const auto &recette : recettes) {
        QStringList rowData;
        rowData <<QString::number(recette.second.first) << recette.second.second;
        dataList << rowData;
    }

    ListForm *listForm = new ListForm(this);
    listForm->displayData(dataList, columnNames);
    listForm->show();
}

