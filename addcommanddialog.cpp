#include "addcommanddialog.h"
#include "ui_addcommanddialog.h"

AddCommandDialog::AddCommandDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCommandDialog),
    productList_(nullptr)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->spinBoxQuantity->setValue(1);
}

AddCommandDialog::~AddCommandDialog()
{
    delete productList_;
    delete ui;
}

void AddCommandDialog::fillProductComboBox(const QList<QPair<QString, QString>> &productList)
{
    ui->comboBoxProductId->clear();
    for (const auto &product : productList) {
        ui->comboBoxProductId->addItem(product.first + "- " +product.second);
    }
    productList_ = new QList<QPair<QString, QString>>(productList);
}


QDate AddCommandDialog::getDate() const
{
    return ui->dateEdit->date();
}

int AddCommandDialog::getQuantity() const
{
    return ui->spinBoxQuantity->value();
}

void AddCommandDialog::on_buttonBox_accepted()
{
    accept();
}

void AddCommandDialog::on_buttonBox_rejected()
{
    reject();
}

QString AddCommandDialog::getSelectedProductId() const
{
    int currentIndex = ui->comboBoxProductId->currentIndex();

    if (currentIndex >= 0 && productList_ != nullptr && currentIndex < productList_->size()) {
        return (*productList_)[currentIndex].first;
    }

    return "";
}

