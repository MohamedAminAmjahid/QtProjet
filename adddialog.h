// addproductdialog.h

#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class AddDialog; }
QT_END_NAMESPACE

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDialog(const QStringList &columnNames, QWidget *parent = nullptr);
    ~AddDialog();

    QList<QString> getProductData() const;

private:
    Ui::AddDialog *ui;
};

#endif
