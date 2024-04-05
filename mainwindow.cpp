/**
 * @file mainwindow.cpp
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QTranslator>
#include "gestionadminform.h"
#include "gestionserveurform.h"
#include <QFile>

/**
 * @brief Constructeur de la classe MainWindow
 * @param parent Widget parent
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    settings("www.ensiie.fr", "Project")
{
    // Initialisation de l'interface utilisateur
    ui->setupUi(this);

    // Charge et applique la feuille de style adaptic.qss à la fenêtre.
    QFile styleFile("../GestionRestaurant/styles/adaptic.qss");
    styleFile.open(QFile::ReadOnly | QFile::Text);
    QString styleSheet = QLatin1String(styleFile.readAll());
    this->setStyleSheet(styleSheet);
    styleFile.close();

    ui->lineEdit_2->setEchoMode(QLineEdit::Password);

    // Connexion à la base de données
    if (!databaseManager_.connectToDatabase("bd")) {
        qDebug() << "Failed to connect to the database!";
        return;
    }

    // Initialise la base de données et insère des données initiales
    //Initialiser();

    // Configuration de la traduction
    QString language = settings.value("language").toString();
    QTranslator translator;

    if (language == "French") {
        if (translator.load("../GestionRestaurant/translations/gestionrestaurant_fr_FR.qm")) {
            qApp->installTranslator(&translator);
        } else {
            qDebug() << "Erreur : Impossible de charger le fichier de traduction pour le français.";
        }
    } else {
        if (translator.load("../GestionRestaurant/translations/gestionrestaurant_en_US.qm")) {
            qApp->installTranslator(&translator);
        } else {
            qDebug() << "Erreur : Impossible de charger le fichier de traduction pour l'anglais.";
        }
    }

    // Réaffichage de l'interface utilisateur avec la nouvelle traduction
    ui->retranslateUi(this);

    // Icon pour les fenêtres de notre application
    QIcon icon("../GestionRestaurant/icons/applicationIcon.jpeg");
    setWindowIcon(icon);
}

/**
 * @brief Destructeur de la classe MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief Slot déclenché lors du clic sur le bouton de connexion
 */
void MainWindow::on_pushButton_clicked()
{
    // Récupération du nom d'utilisateur et du mot de passe
    QString login = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();

    // Vérification de l'authentification
    if (databaseManager_.verifierAuthentification(login, password)) {
        qDebug() << "Login et mot de passe valides.";

        // Récupération du rôle de l'utilisateur
        QString role = databaseManager_.getRole(login, password);

        // Ouverture de la fenêtre correspondant au rôle de l'utilisateur
        this->close();
        if (role.toLower() == "admin") {
            GestionAdminForm *gestionAdminForm = new GestionAdminForm(this);
            gestionAdminForm->show();
        } else {
            int serverId = databaseManager_.getServerId(login);
            settings.setValue("ServerID", serverId);
            GestionServeurForm *gestionServeurForm = new GestionServeurForm(this, &databaseManager_);
            gestionServeurForm->show();
        }
    } else {
        QMessageBox::information(this, tr("Error"), tr("Login or password incorrect."));
    }
}

/**
 * @brief Initialise la base de données et insère des données initiales
 */
void MainWindow::Initialiser()
{
    // Vérifie si la table "personnes" existe
    if (!databaseManager_.tableExists("personnes")) {
        // Si la table n'existe pas, créez-la
        if (!databaseManager_.createTable("personnes", "id INTEGER PRIMARY KEY AUTOINCREMENT, login TEXT NOT NULL, motdepasse TEXT NOT NULL, cin TEXT NOT NULL, role TEXT NOT NULL")) {
            qDebug() << "Failed to create the table 'personnes'!";
            return;
        }

        // Insérez une personne dans la base de données (exemple)
        if (!databaseManager_.insertPerson("admin", "admin", "SA212132", "admin")) {
            qDebug() << "Failed to insert person!";
            // Gérer l'échec de l'insertion de personne ici
        }
    }

    // Vérifie si la table "produits" existe
    if (!databaseManager_.tableExists("produits")) {
        // Si la table n'existe pas, créez-la
        if (!databaseManager_.createTable("produits", "codeproduit INTEGER PRIMARY KEY AUTOINCREMENT, designation TEXT NOT NULL, prix REAL NOT NULL, quantitestock INTEGER NOT NULL")) {
            qDebug() << "Failed to create the table 'produits'!";
            return;
        }

        // Insérer des produits dans la base de données (exemple)
        if (!databaseManager_.insertProduct("Tarte aux fraises", 9.99, 11)) {
            qDebug() << "Failed to insert product!";
            // Gérer l'échec de l'insertion de produit ici
        }

        if (!databaseManager_.insertProduct("Pizza", 12.99, 2)) {
            qDebug() << "Failed to insert product!";
            // Gérer l'échec de l'insertion de produit ici
        }

        if (!databaseManager_.insertProduct("Spaghetti bolognaise", 10.99, 3)) {
            qDebug() << "Failed to insert product!";
            // Gérer l'échec de l'insertion de produit ici
        }

        if (!databaseManager_.insertProduct("Hamburger", 8.99, 4)) {
            qDebug() << "Failed to insert product!";
            // Gérer l'échec de l'insertion de produit ici
        }

        if (!databaseManager_.insertProduct("Salade César", 6.99, 1)) {
            qDebug() << "Failed to insert product!";
            // Gérer l'échec de l'insertion de produit ici
        }

        if (!databaseManager_.insertProduct("Sushi assorti", 14.99, 2)) {
            qDebug() << "Failed to insert product!";
            // Gérer l'échec de l'insertion de produit ici
        }

        if (!databaseManager_.insertProduct("Coca-Cola", 2.5, 6)) {
            qDebug() << "Failed to insert product!";
            // Gérer l'échec de l'insertion de produit ici
        }
    }

    // Vérifie si la table "recettes" existe
    if (!databaseManager_.tableExists("recettes")) {
        // Si la table n'existe pas, créez-la
        if (!databaseManager_.createTable("recettes", "codeRecette INTEGER PRIMARY KEY AUTOINCREMENT, idserveur INTEGER, totalparjournee DECIMAL, date DATE, FOREIGN KEY(idserveur) REFERENCES personnes(id)")) {
            qDebug() << "Failed to create the table 'recettes'!";
            return;
        }
    }

    // Insérer des recettes dans la base de données

    if (!databaseManager_.insertRecette(1, 25.99, QDate::fromString("2024-03-25", "yyyy-MM-dd"))) {
        qDebug() << "Failed to insert recipe!";
        // Gérer l'échec de l'insertion de recette ici
    }


    // Vérifie si la table "commandes" existe
    if (!databaseManager_.tableExists("commandes")) {
        // Si la table n'existe pas, créez-la
        if (!databaseManager_.createTable("commandes", "id INTEGER PRIMARY KEY AUTOINCREMENT, idserveur INTEGER, produit_id INTEGER, quantite INTEGER, date_commande DATE, FOREIGN KEY(idserveur) REFERENCES personnes(id), FOREIGN KEY(produit_id) REFERENCES produits(id)")) {
            qDebug() << "Failed to create the table 'commandes'!";
            return;
        }
    }
}
