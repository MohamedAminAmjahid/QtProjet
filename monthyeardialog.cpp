#include "monthyeardialog.h"
#include "ui_monthyeardialog.h"
#include <QCalendarWidget>

/**
 * @brief Constructeur de la classe MonthYearDialog.
 * @param parent Le widget parent (par défaut : nullptr).
 */
MonthYearDialog::MonthYearDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MonthYearDialog)
{
    // Initialise l'interface utilisateur
    ui->setupUi(this);

    // Active le sélecteur de calendrier en mode popup
    ui->dateEdit->setCalendarPopup(true);

    // Définit le format d'affichage de la date
    ui->dateEdit->setDisplayFormat("MM/yyyy");

    // Initialise la date avec la date courante
    ui->dateEdit->setDate(QDate::currentDate());
}

/**
 * @brief Destructeur de la classe MonthYearDialog.
 */
MonthYearDialog::~MonthYearDialog()
{
    delete ui;
}

/**
 * @brief Récupère la date sélectionnée.
 * @return La date sélectionnée avec le jour fixé au premier jour du mois.
 */
QDate MonthYearDialog::selectedDate() const
{
    // Récupère la date sélectionnée dans le widget dateEdit
    QDate selectedDate = ui->dateEdit->date();

    // Fixe le jour de la date sélectionnée au premier jour du mois
    selectedDate.setDate(selectedDate.year(), selectedDate.month(), 1);

    return selectedDate;
}
