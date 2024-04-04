#ifndef GESTIONSERVEURFORM_H
#define GESTIONSERVEURFORM_H

#include <QMainWindow>
#include <databasemanager.h>
#include <QSettings>
namespace Ui {
class GestionServeurForm;
}

class GestionServeurForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit GestionServeurForm(QWidget *parent = nullptr, DatabaseManager *databasemanager= nullptr);
    ~GestionServeurForm();

private slots:
    void on_actionAddCommands_triggered();

    void on_actionListCommands_triggered();

    void on_actionLogOut_triggered();

    void on_actionUpdateCommands_triggered();

    void on_actionDeleteCommands_triggered();

    void on_actionClose_triggered();

    void on_actionListRecette_triggered();

private:
    Ui::GestionServeurForm *ui;
    DatabaseManager databaseManager_;
    QSettings settings;
};

#endif
