#include "gestionadminform.h"
#include "ui_gestionadminform.h"
#include <listform.h>
#include <QDialog>
#include <adddialog.h>
#include <updatedialog.h>
#include <QSqlQuery>
#include <QMessageBox>
#include <updateserverdialog.h>
#include <searchproductdialog.h>
#include <mainwindow.h>
#include <addrecettedialog.h>
#include <recette.h>
#include <updaterecettedialog.h>

GestionAdminForm::GestionAdminForm(QWidget *parent, DatabaseManager *databasemanager)
    : QMainWindow(parent)
    , ui(new Ui::GestionAdminForm),
    databaseManager_(databasemanager)
{
    ui->setupUi(this);

    /*if (!databaseManager_.connectToDatabase("bd")) {
        qDebug() << "Failed to connect to the database!";
        // Gérer l'échec de connexion ici
        return;
    }*/
}

GestionAdminForm::~GestionAdminForm()
{
    delete ui;
}

void GestionAdminForm::on_actionListerProduct_triggered()
{
    QList<Produit> productList = databaseManager_.selectProducts();

    QList<QStringList> dataList;
    QStringList columnNames = {"Designation", "Prix", "Quantite en stock"};

    for (const Produit &product : productList) {
        QStringList rowData;
        rowData << product.designation() << QString::number(product.prix()) << QString::number(product.quantiteStock());

        dataList << rowData;
    }

    ListForm *listForm = new ListForm(this);

    listForm->displayData(dataList, columnNames);

    listForm->show();
}

void GestionAdminForm::on_actionListServer_triggered()
{
    QList<Serveur> serverList = databaseManager_.selectServers();

    QList<QStringList> dataList;
    QStringList columnNames = {"Login", "CIN"};
    for (const Serveur &server : serverList) {
        QStringList rowData;
        rowData << server.getLogin() << server.getCin(); // Assuming there are login() and cin() methods in Serveur class
        dataList << rowData;
    }

    ListForm *listForm = new ListForm(this);

    listForm->displayData(dataList, columnNames);

    listForm->show();
}


void GestionAdminForm::on_actionAddServer_triggered()
{
    QStringList columnNames = {"Login", "Password", "Cin"};

    // Créer une instance du dialogue d'ajout de produit
    AddDialog addServerDialog(columnNames, this);

    // Exécuter le dialogue modale pour récupérer les données du produit
    if (addServerDialog.exec() == QDialog::Accepted) {
        // Obtenir les données du produit à partir du dialogue
        QList<QString> serverData = addServerDialog.getProductData();

        // Vérifier si toutes les données ont été saisies
        if (serverData.size() == columnNames.size()) {
            // Insérer le produit dans la base de données
            QString login = serverData.at(0);
            QString pwd = serverData.at(1);
            QString cin = serverData.at(2);

            // Insérez le produit en utilisant votre méthode insertProduct dans DatabaseManager
            if (!databaseManager_.insertPerson(login, pwd, cin, "Server")) {
                qDebug() << "Failed to insert product!";
                // Gérer l'échec de l'insertion du produit ici
            } else {
                qDebug() << "Product inserted successfully!";
                // Gérer le succès de l'insertion du produit ici
            }
        } else {
            qDebug() << "Incomplete product data!";
            // Gérer le cas où les données du produit ne sont pas complètes ici
        }
    }
}


void GestionAdminForm::on_actionAddProduct_triggered()
{
    // Définir les noms des colonnes pour le formulaire
    QStringList columnNames = {"Désignation", "Prix", "Quantité en stock"};

    // Créer une instance du dialogue d'ajout de produit
    AddDialog addProductDialog(columnNames, this);

    // Exécuter le dialogue modale pour récupérer les données du produit
    if (addProductDialog.exec() == QDialog::Accepted) {
        // Obtenir les données du produit à partir du dialogue
        QList<QString> productData = addProductDialog.getProductData();

        // Vérifier si toutes les données ont été saisies
        if (productData.size() == columnNames.size()) {
            // Insérer le produit dans la base de données
            QString designation = productData.at(0);
            double prix = productData.at(1).toDouble();
            int quantiteStock = productData.at(2).toInt();

            // Insérez le produit en utilisant votre méthode insertProduct dans DatabaseManager
            if (!databaseManager_.insertProduct(designation, prix, quantiteStock)) {
                qDebug() << "Failed to insert product!";
                // Gérer l'échec de l'insertion du produit ici
            } else {
                qDebug() << "Product inserted successfully!";
                // Gérer le succès de l'insertion du produit ici
            }
        } else {
            qDebug() << "Incomplete product data!";
        }
    }
}

void GestionAdminForm::on_actionUpdateProduct_triggered()
{
    QStringList productCodes = databaseManager_.selectProductCodes();

    UpdateDialog *updateDialog = new UpdateDialog(productCodes, this);

    if (updateDialog->exec() == QDialog::Accepted) {
    QList<QString> productData = updateDialog->getProductData();

    QString selectedProductCode = updateDialog->getSelectedCode();
        QString newDesignation = productData.at(0);
        double newPrice = productData.at(1).toDouble();
        int newQuantity = productData.at(2).toInt();
        if (!databaseManager_.updateProduct(selectedProductCode, newDesignation, newPrice, newQuantity)) {
            qDebug() << "Failed to insert product!";
        } else {
            qDebug() << "Product inserted successfully!";
        }
    }

}


void GestionAdminForm::on_actionDeleteProduct_triggered()
{

    QStringList productCodes = databaseManager_.selectProductCodes();


    UpdateDialog *updateDialog = new UpdateDialog(productCodes, this);

    updateDialog->setFieldsReadOnly(true);

    if (updateDialog->exec() == QDialog::Accepted) {
        QString selectedProductCode = updateDialog->getSelectedCode();


        QMessageBox::StandardButton confirmation = QMessageBox::question(this, "Confirmation", "Are you sure you want to delete this product?",
                                                                         QMessageBox::Yes | QMessageBox::No);
        if (confirmation == QMessageBox::Yes) {


            if (databaseManager_.deleteProduct(selectedProductCode)) {
                QMessageBox::information(this, "Success", "Product deleted successfully.");
            } else {
                QMessageBox::critical(this, "Error", "Failed to delete product.");
            }
        }
    }
}


void GestionAdminForm::on_actionUpdateServer_triggered()
{
    QStringList serverCodes = databaseManager_.selectServerCodes();

    UpdateServerDialog *updateServerDialog = new UpdateServerDialog(serverCodes, this);

    if (updateServerDialog->exec() == QDialog::Accepted) {
        QList<QString> productData = updateServerDialog->getServerData();

        QString selectedServerCode = updateServerDialog->getSelectedCode();
        QString newLogin = productData.at(0);
        QString newPassword = productData.at(1);
        QString newCin = productData.at(2);

        if (!databaseManager_.updateServer(selectedServerCode, newLogin, newPassword, newCin)) {
            qDebug() << "Failed to insert product!";
        } else {
            qDebug() << "Product inserted successfully!";
        }
    }

}

void GestionAdminForm::on_actionDeleteServer_triggered()
{
    QStringList serverCodes = databaseManager_.selectServerCodes();

    UpdateServerDialog *updateServerDialog = new UpdateServerDialog(serverCodes, this);

    updateServerDialog->setFieldsReadOnly(true);
    if (updateServerDialog->exec() == QDialog::Accepted) {
        QString selectedServerCode = updateServerDialog->getSelectedCode();

        QMessageBox::StandardButton confirmation = QMessageBox::question(this, "Confirmation", "Are you sure you want to delete this server?",
                                                                         QMessageBox::Yes | QMessageBox::No);
        if (confirmation == QMessageBox::Yes) {

            if (databaseManager_.deleteServer(selectedServerCode)) {
                QMessageBox::information(this, "Success", "Product deleted successfully.");
            } else {
                QMessageBox::critical(this, "Error", "Failed to delete product.");
            }
        }
    }
}

void GestionAdminForm::on_actionSearchProduct_triggered()
{
    SearchProductDialog searchProductDialog(this);
    if (searchProductDialog.exec() == QDialog::Accepted) {
    }
}

void GestionAdminForm::on_actionLogOut_triggered()
{
    databaseManager_.disconnectFromDatabase();
    this->close();
    MainWindow *mainWindow = new MainWindow(this);

    mainWindow->show();
}


void GestionAdminForm::on_actionClose_triggered()
{
    this->close();
}

void GestionAdminForm::on_actionAddRecette_triggered()
{
    AddRecetteDialog addRecetteDialog(this, &databaseManager_);

    if (addRecetteDialog.exec() == QDialog::Accepted) {
        // Obtenir l'idServeur sélectionné à partir du dialogue
        int idServeur = addRecetteDialog.getSelectedServeurId();
        QDate date = addRecetteDialog.getRecetteDate();
        double totalParJournee = addRecetteDialog.getTotalParJournee();

        if (!databaseManager_.insertRecette(idServeur, totalParJournee, date)) {
            qDebug() << "Failed to insert recette!";
        } else {
            qDebug() << "Recette inserted successfully!";
        }
    }
}

void GestionAdminForm::on_actionListRecette_triggered()
{
    QList<QPair<QPair<int, QString>, QPair<double, QString>>> recettes = databaseManager_.selectRecettesWithServerLoginsAndDetails();

    QList<QStringList> dataList;
    QStringList columnNames = {"ID Serveur", "Login Serveur", "Total Par Journee", "Date"};

    for (const auto &recette : recettes) {
        QStringList rowData;
        rowData << QString::number(recette.first.first) << recette.first.second << QString::number(recette.second.first) << recette.second.second;
        dataList << rowData;
    }

    ListForm *listForm = new ListForm(this);
    listForm->displayData(dataList, columnNames);
    listForm->show();
}

void GestionAdminForm::on_actionListCommand_triggered()
{
    QList<Commande> commandList = databaseManager_.selectCommands();

    QList<QStringList> dataList;
    QStringList columnNames = {"Code commande", "Id Serveur","Nom Produit", "Quantité", "Prix unitaire", "Total", "Date"};

    for (const Commande &command : commandList) {
        QString productName = databaseManager_.getProductName(command.idProduit());
        double productPrice = databaseManager_.getProductPrice(command.idProduit());
        double total = command.quantite() * productPrice;

        QStringList rowData;
        rowData <<command.codeCommande()<< QString::number(command.idServeur())<< productName << QString::number(command.quantite()) << QString::number(productPrice) << QString::number(total) << command.dateCommande().toString("yyyy-MM-dd");
        dataList << rowData;

    }

    ListForm *listForm = new ListForm(this);

    listForm->displayData(dataList, columnNames);

    listForm->show();
}

void GestionAdminForm::on_actionUpdateRecette_triggered()
{
    QList<int> codeRecettes = databaseManager_.selectRecetteCodes();
    QList<QPair<int, QString>> serveursAndLogins = databaseManager_.getServeursAndLogins();

    UpdateRecetteDialog updateRecetteDialog(this);
    updateRecetteDialog.setCodeRecetteOptions(codeRecettes);
    updateRecetteDialog.setIdServeurOptions(serveursAndLogins);

    if (updateRecetteDialog.exec() == QDialog::Accepted) {
        int selectedCodeRecette = updateRecetteDialog.getSelectedCodeRecette();
        int selectedIdServeur = updateRecetteDialog.getSelectedIdServeur();
        double newTotalParJournee = updateRecetteDialog.getNouveauTotalParJournee();
        QDate newDate = updateRecetteDialog.getNouvelleDate();

        if (!databaseManager_.updateRecette(selectedCodeRecette, selectedIdServeur)) {
            qDebug() << "Failed to update recette!";
        } else {
            qDebug() << "Recette updated successfully!";
        }
    }
}

void GestionAdminForm::on_actionDeleteRecette_triggered()
{
    QList<int> codeRecettes = databaseManager_.selectRecetteCodes();

    // Afficher le UpdateRecetteDialog pour sélectionner la recette à supprimer
    UpdateRecetteDialog deleteRecetteDialog(this);
    deleteRecetteDialog.disableUIElements(); // Désactiver les éléments de l'interface utilisateur
    deleteRecetteDialog.setDialogTitle("Delete Recette"); // Définir le titre du dialogue
    deleteRecetteDialog.setCodeRecetteOptions(codeRecettes);

    if (deleteRecetteDialog.exec() == QDialog::Accepted) {
        int selectedCodeRecette = deleteRecetteDialog.getSelectedCodeRecette();

        // Demander confirmation avant de supprimer la recette
        QMessageBox::StandardButton confirmation;
        confirmation = QMessageBox::question(this, "Delete Recette", "Are you sure you want to delete this recette?",
                                             QMessageBox::Yes|QMessageBox::No);
        if (confirmation == QMessageBox::No) {
            qDebug() << "Operation canceled.";
            return;
        }

        // Supprimer la recette
        if (!databaseManager_.deleteRecette(selectedCodeRecette)) {
            qDebug() << "Failed to delete recette!";
        } else {
            qDebug() << "Recette deleted successfully!";
        }
    }
}

