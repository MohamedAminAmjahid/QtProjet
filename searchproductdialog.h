// searchdialog.h
#ifndef SEARCHPRODUCTDIALOG_H
#define SEARCHPRODUCTDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QListWidgetItem>

namespace Ui {
class SearchProductDialog;
}

class SearchProductDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchProductDialog(QWidget *parent = nullptr);
    ~SearchProductDialog();

private slots:

    void on_pushButton_search_clicked();

private:
    Ui::SearchProductDialog *ui;

    void searchProducts(const QString &fieldName, const QString &keyword);
    void displaySearchResults(QSqlQuery &query);
};

#endif // SEARCHDIALOG_H

