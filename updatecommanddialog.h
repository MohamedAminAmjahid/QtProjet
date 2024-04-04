#ifndef UPDATECOMMANDDIALOG_H
#define UPDATECOMMANDDIALOG_H

#include <QDialog>
#include "commande.h"
#include "databasemanager.h"

namespace Ui {
class UpdateCommandDialog;
}

class UpdateCommandDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateCommandDialog(QWidget *parent = nullptr);
    ~UpdateCommandDialog();

    Commande getUpdatedCommand() const;
    QList<QString> getCommandData() const;
    void fillProductComboBox(const QList<QPair<QString, QString>> &productList);

    void setFieldsReadOnly(bool readOnly);

private slots:
    void on_lineEditCommandNumber_editingFinished();

private:
    Ui::UpdateCommandDialog *ui;
    Commande updatedCommand;
    DatabaseManager databaseManager_;
};

#endif
