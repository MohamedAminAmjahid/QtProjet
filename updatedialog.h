// updatedialog.h
#ifndef UPDATEDIALOG_H
#define UPDATEDIALOG_H

#include <QDialog>
#include <databasemanager.h>

namespace Ui {
class UpdateDialog;
}


class UpdateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateDialog(const QStringList &productCodes, QWidget *parent = nullptr);

    ~UpdateDialog();

    QString getSelectedCode() const;
    QList<QString> getProductData() const;

    void setFieldsReadOnly(bool readOnly);

public slots:
    void setProductDetails(const QString &designation, double price, int quantity);

private:
    Ui::UpdateDialog *ui;
    DatabaseManager databaseManager_; // Déclarez une instance de DatabaseManager
signals:
    // Déclaration du signal selectedCodeChanged
    void selectedCodeChanged(int code);
private slots:
    void on_comboBox_currentIndexChanged(int index);
};

#endif // UPDATEDIALOG_H
