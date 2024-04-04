// adddialog.cpp

#include "adddialog.h"
#include "ui_adddialog.h"
#include <QLabel>
#include <QLineEdit>


AddDialog::AddDialog(const QStringList &columnNames, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);

    // Set labels for line edits based on column names
    for (const QString &columnName : columnNames) {
        QLabel *label = new QLabel(columnName, this);
        QLineEdit *lineEdit = new QLineEdit(this);
        ui->formLayout->addRow(label, lineEdit);
    }
}

AddDialog::~AddDialog()
{
    delete ui;
}

QList<QString> AddDialog::getProductData() const
{
    QList<QString> productData;
    // Retrieve data from line edits
    for (int i = 0; i < ui->formLayout->rowCount(); ++i) {
        QLineEdit *lineEdit = qobject_cast<QLineEdit*>(ui->formLayout->itemAt(i, QFormLayout::FieldRole)->widget());
        if (lineEdit) {
            productData << lineEdit->text();
        }
    }
    return productData;
}
