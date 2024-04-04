#include "listform.h"
#include "ui_listform.h"

ListForm::ListForm(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ListForm)
{
    ui->setupUi(this);
}

ListForm::~ListForm()
{
    delete ui;
}

void ListForm::displayData(const QList<QStringList> &dataList, const QStringList &columnNames)
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(dataList.size());

    ui->tableWidget->setColumnCount(columnNames.size());
    ui->tableWidget->setHorizontalHeaderLabels(columnNames);

    int row = 0;
    for (const QStringList &rowData : dataList) {
        int column = 0;
        for (const QString &data : rowData) {
            QTableWidgetItem *itemData = new QTableWidgetItem(data);
            itemData->setFlags(itemData->flags() & ~Qt::ItemIsEditable);
            ui->tableWidget->setItem(row, column, itemData);
            ++column;
        }
        ++row;
    }
    ui->tableWidget->resizeColumnsToContents();
}
