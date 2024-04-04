#ifndef ADDRECETTEDIALOG_H
#define ADDRECETTEDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QDate>
#include "databaseManager.h"

namespace Ui {
class AddRecetteDialog;
}

class AddRecetteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddRecetteDialog(QWidget *parent = nullptr, DatabaseManager *databaseManager = nullptr);
    ~AddRecetteDialog();

    int getSelectedServeurId();
    double calculateTotalParJournee();
    QDate getRecetteDate() const;
    double getTotalParJournee() const;

private slots:
    void serveurSelectionChanged(int index);
    void dateChanged(const QDate &date);

private:
    Ui::AddRecetteDialog *ui;
    DatabaseManager *databaseManager_;
};

#endif
