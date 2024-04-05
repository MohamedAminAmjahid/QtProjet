#include "gestionserveurform.h"
#include "ui_gestionserveurform.h"
#include <addcommanddialog.h>
#include <QMessageBox>
#include <commande.h>
#include <listform.h>
#include <mainwindow.h>
#include <updatecommanddialog.h>
#include <QTranslator>

GestionServeurForm::GestionServeurForm(QWidget *parent, DatabaseManager *databasemanager)
    : QMainWindow(parent)
    , ui(new Ui::GestionServeurForm),
    databaseManager_(databasemanager),
    settings("www.ensiie.fr", "Project")
{
    ui->setupUi(this);
    QString language = settings.value("language").toString();
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
            QMessageBox::critical(this, tr("Error"), tr("Not enough stock!"));
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
    QStringList columnNames = {tr("Code command"), tr("Name Product"), tr("Quantity"), tr("Unit Price"), tr("Total"), tr("Date")};

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

void GestionServeurForm::on_actionDeleteCommands_triggered()
{
    int idServeur = settings.value("ServerID").toInt();
    UpdateCommandDialog updateCommandDialog(this, idServeur);
    updateCommandDialog.setFieldsReadOnly(true);

    if (updateCommandDialog.exec() == QDialog::Accepted) {
        Commande updatedCommand = updateCommandDialog.getUpdatedCommand();
        if (updatedCommand.codeCommande() != "") {
            QString commandNumber = updatedCommand.codeCommande();

            if (databaseManager_.deleteCommandByNumber(commandNumber)) {
                QMessageBox::information(this, tr("Deleted Successfuly"), tr("The command has been successfully deleted."));
            } else {
                QMessageBox::warning(this, tr("Error"), tr("The command could not be deleted."));
            }
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
    QStringList columnNames = {tr("Total per day"), tr("Date")};

    for (const auto &recette : recettes) {
        QStringList rowData;
        rowData <<QString::number(recette.second.first) << recette.second.second;
        dataList << rowData;
    }

    ListForm *listForm = new ListForm(this);
    listForm->displayData(dataList, columnNames);
    listForm->show();
}

