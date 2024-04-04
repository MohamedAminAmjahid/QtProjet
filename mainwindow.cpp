#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QDebug>
#include <qmessagebox.h>
#include <gestionadminform.h>
#include <gestionserveurform.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    settings("www.ensiie.fr", "Project")
{
    ui->setupUi(this);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    if (!databaseManager_.connectToDatabase("bd")) {
        qDebug() << "Failed to connect to the database!";
        return;
    }

    /*if (!databaseManager_.createTable("recettes", "codeRecette INTEGER PRIMARY KEY AUTOINCREMENT, idserveur INTEGER, totalparjournee DECIMAL, date DATE, FOREIGN KEY(idserveur) REFERENCES personnes(id)")) {
        qDebug() << "Failed to create the table 'recettes'!";
        return;
    }


    if (!databaseManager_.dropTable("commandes")) {
        qDebug() << "Failed to drop the table 'produits'!";
        // Gérer l'échec de suppression de la table ici
        return;
    }
    if (!databaseManager_.createTable("commandes", "id INTEGER PRIMARY KEY AUTOINCREMENT, idserveur INTEGER, produit_id INTEGER, quantite INTEGER, date_commande DATE, FOREIGN KEY(idserveur) REFERENCES personnes(id), FOREIGN KEY(produit_id) REFERENCES produits(id)")) {
        qDebug() << "Failed to create the table 'commande'!";
        // Gérer l'échec de création de la table ici
        return;
    }*/


    /*
    // Créez la table "utilisateurs" si elle n'existe pas déjà
    if (!databaseManager_.createTable("personnes", "id INTEGER PRIMARY KEY AUTOINCREMENT, login TEXT NOT NULL, motdepasse TEXT NOT NULL, cin TEXT NOT NULL, role TEXT NOT NULL")) {
        qDebug() << "Failed to create the table 'utilisateurs'!";
        // Gérer l'échec de création de la table ici
        return;
    }

    Insérez une personne dans la base de données (exemple)
    if (!databaseManager_.insertPerson("admin", "admin", "SA212132", "admin")) {
        qDebug() << "Failed to insert person!";
        // Gérer l'échec de l'insertion de personne ici
    }

    if (!databaseManager_.dropTable("produits")) {
        qDebug() << "Failed to drop the table 'produits'!";
        // Gérer l'échec de suppression de la table ici
        return;
    }

    // Créez la table "produits" si elle n'existe pas déjà
    if (!databaseManager_.createTable("produits", "codeproduit INTEGER PRIMARY KEY AUTOINCREMENT, designation TEXT NOT NULL, prix REAL NOT NULL, quantitestock INTEGER NOT NULL")) {
        qDebug() << "Failed to create the table 'produits'!";
        // Gérer l'échec de création de la table ici
        return;
    }

    // Insérer une commande de dessert
    if (!databaseManager_.insertProduct("Tarte aux fraises", 9.99, 11)) {
        qDebug() << "Failed to insert command!";
        // Gérer l'échec de l'insertion de la commande ici
    }

    if (!databaseManager_.insertProduct("Pizza", 12.99, 2)) {
        qDebug() << "Failed to insert command!";
        // Gérer l'échec de l'insertion de la commande ici
    }

    if (!databaseManager_.insertProduct("Spaghetti bolognaise", 10.99, 3)) {
        qDebug() << "Failed to insert command!";
        // Gérer l'échec de l'insertion de la commande ici
    }
    // Insérer une commande de hamburger
    if (!databaseManager_.insertProduct("Hamburger", 8.99, 4)) {
        qDebug() << "Failed to insert command!";
        // Gérer l'échec de l'insertion de la commande ici
    }

    // Insérer une commande de salade César
    if (!databaseManager_.insertProduct("Salade César", 6.99, 1)) {
        qDebug() << "Failed to insert command!";
        // Gérer l'échec de l'insertion de la commande ici
    }

    // Insérer une commande de sushi assorti
    if (!databaseManager_.insertProduct("Sushi assorti", 14.99, 2)) {
        qDebug() << "Failed to insert command!";
        // Gérer l'échec de l'insertion de la commande ici
    }

    // Insérer une commande de boisson
    if (!databaseManager_.insertProduct("Coca-Cola", 2.5, 6)) {
        qDebug() << "Failed to insert command!";
        // Gérer l'échec de l'insertion de la commande ici
    }

    // Insérer une commande de dessert
    if (!databaseManager_.insertProduct("Tarte aux fraises", 9.99, 11)) {
        qDebug() << "Failed to insert command!";
        // Gérer l'échec de l'insertion de la commande ici
    }

*/


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString login = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();

    if (databaseManager_.verifierAuthentification(login, password)) {
        qDebug() << "Login et mot de passe valides.";

        QString role = databaseManager_.getRole(login, password);

        this->close();

        //databaseManager_.disconnectFromDatabase();
        if (role.toLower() == "admin") {
            //QMessageBox::information(this, "Bonjour Admin", "Hello Admin!");
            GestionAdminForm *gestionAdminForm = new GestionAdminForm(this, &databaseManager_);

            gestionAdminForm->show();
        } else {
            int serverId = databaseManager_.getServerId(login);
            settings.setValue("ServerID", serverId);
            GestionServeurForm *gestionServeurForm = new GestionServeurForm(this, &databaseManager_);

            gestionServeurForm->show();
        }
    } else {
        QMessageBox::information(this, "Erreur", "Login ou mot de passe incorrect.");
    }
}

