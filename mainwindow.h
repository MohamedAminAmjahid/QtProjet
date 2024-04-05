#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <databasemanager.h>
#include <QSettings>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur de la classe MainWindow.
     * @param parent Le widget parent (par défaut : nullptr).
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructeur de la classe MainWindow.
     */
    ~MainWindow();

    void Initialiser();
private slots:
    /**
     * @brief Slot déclenché lorsqu'on clique sur le bouton pushButton.
     */
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui; /**< Interface utilisateur de la classe. */
    DatabaseManager databaseManager_; /**< Gestionnaire de base de données. */
    QSettings settings; /**< Paramètres de l'application. */
};
#endif
