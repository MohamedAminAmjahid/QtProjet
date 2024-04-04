#ifndef ADDCOMMANDDIALOG_H
#define ADDCOMMANDDIALOG_H

#include <QDialog>
#include <QStringList>
#include <QDate>

namespace Ui {
class AddCommandDialog;
}

class AddCommandDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddCommandDialog(QWidget *parent = nullptr);
    ~AddCommandDialog();

    void fillProductComboBox(const QList<QPair<QString, QString>> &productList);

    QDate getDate() const;
    int getQuantity() const;
    QString getSelectedProductId() const;

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::AddCommandDialog *ui;
    QList<QPair<QString, QString>> *productList_;
};

#endif // ADDCOMMANDDIALOG_H
