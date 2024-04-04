// searchdialog.cpp
#include "searchproductdialog.h"
#include "ui_searchproductdialog.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

SearchProductDialog::SearchProductDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchProductDialog)
{
    ui->setupUi(this);
}

SearchProductDialog::~SearchProductDialog()
{
    delete ui;
}



void SearchProductDialog::searchProducts(const QString &fieldName, const QString &keyword)
{
    QSqlQuery query;

    if (!query.exec(QString("SELECT * FROM produits WHERE %1 LIKE '%%2%'").arg(fieldName).arg(keyword))) {
        qDebug() << "Error executing SQL query:" << query.lastError().text();
        return;
    }

    displaySearchResults(query);
}

void SearchProductDialog::displaySearchResults(QSqlQuery &query)
{
    ui->listWidget_results->clear();

    while (query.next()) {
        QString designation = query.value("designation").toString();
        double price = query.value("prix").toDouble();
        int quantity = query.value("quantitestock").toInt();

        QString resultText = QString("%1 | Price: %2 | Quantity: %3").arg(designation).arg(price).arg(quantity);
        ui->listWidget_results->addItem(new QListWidgetItem(resultText));
    }
}

void SearchProductDialog::on_pushButton_search_clicked()
{

    QString fieldName = ui->comboBox->currentText();
    QString keyword = ui->lineEdit_keyword->text();
    searchProducts(fieldName, keyword);
}

