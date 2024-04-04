#ifndef GESTIONADMINFORM_H
#define GESTIONADMINFORM_H

#include <QMainWindow>
#include <produit.h>
#include <databasemanager.h>
#include <serveur.h>

namespace Ui {
class GestionAdminForm;
}

class GestionAdminForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit GestionAdminForm(QWidget *parent = nullptr, DatabaseManager *databasemanager= nullptr);
    ~GestionAdminForm();

private slots:
    void on_actionListerProduct_triggered();

    void on_actionListServer_triggered();

    void on_actionAddServer_triggered();

    void on_actionAddProduct_triggered();

    void on_actionUpdateProduct_triggered();

    void on_actionDeleteProduct_triggered();

    void on_actionUpdateServer_triggered();

    void on_actionDeleteServer_triggered();

    void on_actionSearchProduct_triggered();

    void on_actionLogOut_triggered();

    void on_actionClose_triggered();

    void on_actionAddRecette_triggered();

    void on_actionListRecette_triggered();

    void on_actionListCommand_triggered();

    void on_actionUpdateRecette_triggered();

    void on_actionDeleteRecette_triggered();

private:
    Ui::GestionAdminForm *ui;
    DatabaseManager databaseManager_;
};

#endif // GESTIONADMINFORM_H
