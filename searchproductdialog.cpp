#include "searchproductdialog.h"
#include "ui_searchproductdialog.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

/**
 * @brief Constructeur de la classe SearchProductDialog.
 * @param parent Le widget parent.
 */
SearchProductDialog::SearchProductDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchProductDialog)
{
    ui->setupUi(this);
}

/**
 * @brief Destructeur de la classe SearchProductDialog.
 */
SearchProductDialog::~SearchProductDialog()
{
    delete ui;
}

/**
 * @brief Recherche des produits dans la base de données en fonction du champ et du mot-clé spécifiés.
 * @param fieldName Le nom du champ sur lequel effectuer la recherche.
 * @param keyword Le mot-clé à rechercher.
 */
void SearchProductDialog::searchProducts(const QString &fieldName, const QString &keyword)
{
    QSqlQuery query;

    // Exécution de la requête SQL pour rechercher les produits
    if (!query.exec(QString("SELECT * FROM produits WHERE %1 LIKE '%%2%'").arg(fieldName).arg(keyword))) {
        qDebug() << "Error executing SQL query:" << query.lastError().text();
        return;
    }

    // Affichage des résultats de la recherche
    displaySearchResults(query);
}

/**
 * @brief Affiche les résultats de la recherche dans la liste des résultats.
 * @param query La requête SQL contenant les résultats de la recherche.
 */
void SearchProductDialog::displaySearchResults(QSqlQuery &query)
{
    ui->listWidget_results->clear();

    // Parcours des résultats de la requête SQL et ajout à la liste des résultats
    while (query.next()) {
        QString designation = query.value("designation").toString();
        double price = query.value("prix").toDouble();
        int quantity = query.value("quantitestock").toInt();

        QString resultText = QString("%1 | Price: %2 | Quantity: %3").arg(designation).arg(price).arg(quantity);
        ui->listWidget_results->addItem(new QListWidgetItem(resultText));
    }
}

/**
 * @brief Slot appelé lors du clic sur le bouton de recherche.
 * Effectue la recherche des produits en utilisant les champs spécifiés.
 */
void SearchProductDialog::on_pushButton_search_clicked()
{
    QString fieldName = ui->comboBox->currentText();
    QString keyword = ui->lineEdit_keyword->text();
    searchProducts(fieldName, keyword);
}
