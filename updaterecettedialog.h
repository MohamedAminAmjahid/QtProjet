#ifndef UPDATERECETTEDIALOG_H
#define UPDATERECETTEDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QDateEdit>
#include <QLineEdit>
#include <QPair>
#include <databasemanager.h>

namespace Ui {
class UpdateRecetteDialog;
}

class UpdateRecetteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateRecetteDialog(QWidget *parent = nullptr);
    ~UpdateRecetteDialog();

    void setCodeRecetteOptions(const QList<int> &codes);
    void setIdServeurOptions(const QList<QPair<int, QString>> &ids);

    int getSelectedCodeRecette() const;
    int getSelectedIdServeur() const;
    double getNouveauTotalParJournee() const;
    QDate getNouvelleDate() const;

    void setDialogTitle(const QString &title);
    void disableUIElements();

private slots:
    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::UpdateRecetteDialog *ui;
    DatabaseManager databaseManager_;

};

#endif
