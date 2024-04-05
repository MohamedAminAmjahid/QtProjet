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
#include <QInputDialog>
#include <monthyeardialog.h>
#include <searchserveranddaterecettedialog.h>
#include <updatecommanddialog.h>
#include <QTranslator>
#include <QDir>

GestionAdminForm::GestionAdminForm(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GestionAdminForm),
    settings_("www.ensiie.fr", "Project")
{
    ui->setupUi(this);

    QString language = settings_.value("language").toString();
    QTranslator translator;

    if (language == "French") {
        if (translator.load("../GestionRestaurant/translations/gestionrestaurant_fr_FR.qm")) {
            qApp->installTranslator(&translator);
        } else {
            qDebug() << "Erreur : Impossible de charger le fichier de traduction pour le français.";
        }
    } else{
        if (translator.load("../GestionRestaurant/translations/gestionrestaurant_en_US.qm")) {
            qApp->installTranslator(&translator);
        } else {
            qDebug() << "Erreur : Impossible de charger le fichier de traduction pour l'anglais.";
        }
    }

    ui->retranslateUi(this);
}

GestionAdminForm::~GestionAdminForm()
{
    delete ui;
}

void GestionAdminForm::on_actionListerProduct_triggered()
{
    QList<Produit> productList = databaseManager_.selectProducts();

    QList<QStringList> dataList;
    QStringList columnNames = {tr("Description"), tr("Price"), tr("Quantity")};


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
    QStringList columnNames = {tr("Login"), tr("CIN")};
    for (const Serveur &server : serverList) {
        QStringList rowData;
        rowData << server.getLogin() << server.getCin();
        dataList << rowData;
    }

    ListForm *listForm = new ListForm(this);

    listForm->displayData(dataList, columnNames);

    listForm->show();
}


void GestionAdminForm::on_actionAddServer_triggered()
{
    QStringList columnNames = {tr("Login"), tr("Password"), tr("Cin")};

    AddDialog addServerDialog(columnNames, this);

    if (addServerDialog.exec() == QDialog::Accepted) {
        QList<QString> serverData = addServerDialog.getProductData();

        if (serverData.size() == columnNames.size()) {
            QString login = serverData.at(0);
            QString pwd = serverData.at(1);
            QString cin = serverData.at(2);

            if (!databaseManager_.insertPerson(login, pwd, cin, "Server")) {
                qDebug() << "Failed to insert server!";
            } else {
                qDebug() << "Server inserted successfully!";
            }
        } else {
            qDebug() << "Incomplete server data!";
        }
    }
}


void GestionAdminForm::on_actionAddProduct_triggered()
{
    QStringList columnNames = {tr("Description"), tr("Price"), tr("Quantity")};

    AddDialog addProductDialog(columnNames, this);

    if (addProductDialog.exec() == QDialog::Accepted) {
        QList<QString> productData = addProductDialog.getProductData();

        if (productData.size() == columnNames.size()) {
            QString designation = productData.at(0);
            double prix = productData.at(1).toDouble();
            int quantiteStock = productData.at(2).toInt();

            if (!databaseManager_.insertProduct(designation, prix, quantiteStock)) {
                qDebug() << "Failed to insert product!";
            } else {
                qDebug() << "Product inserted successfully!";
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
            qDebug() << "Failed to update product!";
        } else {
            qDebug() << "Product updated successfully!";
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

        QMessageBox::StandardButton confirmation = QMessageBox::question(this, tr("Confirmation"), tr("Are you sure you want to delete this product?"), QMessageBox::Yes | QMessageBox::No);
        if (confirmation == QMessageBox::Yes) {
            if (databaseManager_.deleteProduct(selectedProductCode)) {
                QMessageBox::information(this, tr("Success"), tr("Product deleted successfully."));
            } else {
                QMessageBox::critical(this, tr("Error"), tr("Failed to delete product."));
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
            qDebug() << "Failed to update server!";
        } else {
            qDebug() << "Server updated successfully!";
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

        QMessageBox::StandardButton confirmation = QMessageBox::question(this, tr("Confirmation"), tr("Are you sure you want to delete this server?"),
                                                                         QMessageBox::Yes | QMessageBox::No);
        if (confirmation == QMessageBox::Yes) {

            if (databaseManager_.deleteServer(selectedServerCode)) {
                QMessageBox::information(this, tr("Success"), tr("Server deleted successfully."));
            } else {
                QMessageBox::critical(this, tr("Error"), tr("Failed to delete server."));
            }
        }
    }
}

void GestionAdminForm::on_actionSearchProduct_triggered()
{
    SearchProductDialog searchProductDialog(this);
    searchProductDialog.exec();
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
    QStringList columnNames = {tr("ID Server"), tr("Login Server"), tr("Total Per Day"), tr("Date")};

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
    QStringList columnNames = {tr("Code command"), tr("Id Server"),tr("Name Product"), tr("Quantity"), tr("Unit Price"), tr("Total"), tr("Date")};

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

    UpdateRecetteDialog deleteRecetteDialog(this);
    deleteRecetteDialog.disableUIElements();
    deleteRecetteDialog.setDialogTitle(tr("Delete Daily Earning"));
    deleteRecetteDialog.setCodeRecetteOptions(codeRecettes);

    if (deleteRecetteDialog.exec() == QDialog::Accepted) {
        int selectedCodeRecette = deleteRecetteDialog.getSelectedCodeRecette();

        QMessageBox::StandardButton confirmation;
        confirmation = QMessageBox::question(this, tr("Delete daily earning"), tr("Are you sure you want to delete this daily earning?"),
                                             QMessageBox::Yes|QMessageBox::No);
        if (confirmation == QMessageBox::No) {
            qDebug() << "Operation canceled.";
            return;
        }

        if (!databaseManager_.deleteRecette(selectedCodeRecette)) {
            qDebug() << "Failed to delete recette!";
        } else {
            qDebug() << "Recette deleted successfully!";
        }
    }
}

void GestionAdminForm::on_actionTotal_per_day_triggered()
{
    QDate selectedDate = QDate::currentDate();
    selectedDate = QDate::fromString(QInputDialog::getText(this, tr("Enter Date"), tr("Enter date (YYYY-MM-DD):"), QLineEdit::Normal, selectedDate.toString("yyyy-MM-dd")), "yyyy-MM-dd");

    QString total = databaseManager_.selectRecettesForDate(selectedDate);

    QMessageBox::information(this, tr("Total for ") + selectedDate.toString("yyyy-MM-dd"), tr("Total for the day: ") + total);
}

void GestionAdminForm::on_actionTotal_per_month_triggered()
{
    MonthYearDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QDate selectedDate = dialog.selectedDate();
        QString totalRecettesMois = databaseManager_.selectRecettesForMonth(selectedDate);
        QMessageBox::information(this, tr("Total Daily Earnings for Month"), tr("Total Daily Earnings for Month: ") + totalRecettesMois);
    }
}

void GestionAdminForm::on_actionTotal_per_server_and_date_triggered()
{
    SearchServerAndDateRecetteDialog searchDialog(this);

    searchDialog.exec();
}

void GestionAdminForm::on_actionDeleteCommand_triggered()
{
    UpdateCommandDialog updateCommandDialog(this, 1);
    updateCommandDialog.setFieldsReadOnly(true);
    if (updateCommandDialog.exec() == QDialog::Accepted) {
        Commande updatedCommand = updateCommandDialog.getUpdatedCommand();
        if (updatedCommand.codeCommande() != "") {
            QString commandNumber = updatedCommand.codeCommande();

            if (databaseManager_.deleteCommandByNumber(commandNumber)) {
                QMessageBox::information(this, tr("Deleted Successfully"), tr("Command has been successfully deleted."));
            } else {
                QMessageBox::warning(this, tr("Error"), tr("The command could not be deleted."));
            }
        }
    }

}

void GestionAdminForm::on_actionUpdateCommand_triggered()
{
    UpdateCommandDialog updateCommandDialog(this, 1);
    if (updateCommandDialog.exec() == QDialog::Accepted) {
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
                    QMessageBox::critical(this, tr("Error"), tr("Not enough stock!"));
                    return;
                }
                else {
                    databaseManager_.setQuantite(QString::number(idProduit), quantite2 - quantite);
                }
            }

            if (!databaseManager_.updateCommand(selectedCommandCode, idProduit, quantite, dateCommande)) {
                qDebug() << "Failed to update command!";
            } else {
                qDebug() << "Command Updated successfully!";
            }
        }
    }

}

void GestionAdminForm::on_actionFrench_triggered()
{
    settings_.setValue("language", "French");

    QTranslator translator;
    if(translator.load("../GestionRestaurant/translations/gestionrestaurant_fr_FR.qm")) {
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
    } else {
        qDebug() << "Erreur : Impossible de charger le fichier de traduction pour le français.";
    }
}



void GestionAdminForm::on_actionEnglish_triggered()
{
    settings_.setValue("language", "English");

    QTranslator translator;
    translator.load("../GestionRestaurant/translations/gestionrestaurant_en_US.qm");
    qApp->installTranslator(&translator);

    ui->retranslateUi(this);
}
