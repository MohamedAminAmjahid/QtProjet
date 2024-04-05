/**
 * @file addrecettedialog.cpp
 */

#include "addrecettedialog.h"
#include "ui_addrecettedialog.h"

/**
 * @brief Constructeur de la classe AddRecetteDialog
 * @param parent Widget parent
 * @param databaseManager Gestionnaire de base de données
 */
AddRecetteDialog::AddRecetteDialog(QWidget *parent, DatabaseManager *databaseManager) :
    QDialog(parent),
    ui(new Ui::AddRecetteDialog),
    databaseManager_(databaseManager)
{
    // Initialisation de l'interface utilisateur
    ui->setupUi(this);

    // Configuration de la date actuelle et de l'affichage du calendrier
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit->setCalendarPopup(true);

    // Configuration du champ de texte en lecture seule et initialisation à zéro
    ui->lineEdit->setReadOnly(QIODeviceBase::ReadOnly);
    ui->lineEdit->setText("0");

    // Récupération de la liste des serveurs et de leurs identifiants
    QList<QPair<int, QString>> serveurs = databaseManager_->getServeursAndLogins();

    // Remplissage de la combobox avec les serveurs
    for (const auto &serveur : serveurs) {
        ui->comboBox->addItem(QString("%1 - %2").arg(serveur.first).arg(serveur.second));
    }

    // Connexion des signaux aux slots pour mettre à jour le total lorsque le serveur ou la date changent
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(serveurSelectionChanged(int)));
    connect(ui->dateEdit, SIGNAL(dateChanged(const QDate &)), this, SLOT(dateChanged(const QDate &)));
}

/**
 * @brief Destructeur de la classe AddRecetteDialog
 */
AddRecetteDialog::~AddRecetteDialog()
{
    delete ui;
}

/**
 * @brief Récupère l'identifiant du serveur sélectionné
 * @return Identifiant du serveur
 */
int AddRecetteDialog::getSelectedServeurId() {
    QString selectedText = ui->comboBox->currentText();
    int idServeur = selectedText.split(" - ")[0].toInt();
    return idServeur;
}

/**
 * @brief Calcule le total des recettes pour la journée sélectionnée
 * @return Total des recettes
 */
double AddRecetteDialog::calculateTotalParJournee() {
    return databaseManager_->calculateTotalParJournee(getSelectedServeurId(), ui->dateEdit->date());
}

/**
 * @brief Met à jour le total lorsque le serveur sélectionné change
 * @param index Index du serveur sélectionné
 */
void AddRecetteDialog::serveurSelectionChanged(int index) {
    double totalParJournee = calculateTotalParJournee();
    ui->lineEdit->setText(QString::number(totalParJournee));
}

/**
 * @brief Met à jour le total lorsque la date sélectionnée change
 * @param date Date sélectionnée
 */
void AddRecetteDialog::dateChanged(const QDate &date) {
    double totalParJournee = calculateTotalParJournee();
    ui->lineEdit->setText(QString::number(totalParJournee));
}

/**
 * @brief Récupère la date de la recette
 * @return Date de la recette
 */
QDate AddRecetteDialog::getRecetteDate() const {
    return ui->dateEdit->date();
}

/**
 * @brief Récupère le total des recettes pour la journée sélectionnée
 * @return Total des recettes pour la journée
 */
double AddRecetteDialog::getTotalParJournee() const {
    return ui->lineEdit->text().toDouble();
}
