#ifndef UPDATESERVERDIALOG_H
#define UPDATESERVERDIALOG_H

#include <QDialog>
#include <databasemanager.h>

namespace Ui {
class UpdateServerDialog;
}

class UpdateServerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateServerDialog(const QStringList &entityCodes,QWidget *parent = nullptr);
    ~UpdateServerDialog();
    QString getSelectedCode() const;
    QList<QString> getServerData() const;


    void setFieldsReadOnly(bool readOnly);

public slots:
    void setServerDetails(const QString &login, const QString &password, const QString &cin);

private:
    Ui::UpdateServerDialog *ui;
    DatabaseManager databaseManager_; // Déclarez une instance de DatabaseManager
signals:
    // Déclaration du signal selectedCodeChanged
    void selectedCodeChanged(int code);
private slots:
    void on_comboBox_currentIndexChanged(int index);
};

#endif // UPDATESERVERDIALOG_H
