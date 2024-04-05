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
    /**
     * @brief Constructeur de la classe GestionServeurForm.
     * @param parent Le widget parent (par défaut : nullptr).
     * @param databasemanager Pointeur vers le gestionnaire de base de données (par défaut : nullptr).
     */
    explicit GestionServeurForm(QWidget *parent = nullptr, DatabaseManager *databasemanager= nullptr);

    /**
     * @brief Destructeur de la classe GestionServeurForm.
     */
    ~GestionServeurForm();

private slots:
    /**
     * @brief Slot privé appelé lorsqu'on ajoute des commandes.
     */
    void on_actionAddCommands_triggered();

    /**
     * @brief Slot privé appelé lorsqu'on liste des commandes.
     */
    void on_actionListCommands_triggered();

    /**
     * @brief Slot privé appelé lorsqu'on se déconnecte.
     */
    void on_actionLogOut_triggered();

    /**
     * @brief Slot privé appelé lorsqu'on supprime des commandes.
     */
    void on_actionDeleteCommands_triggered();

    /**
     * @brief Slot privé appelé lorsqu'on ferme l'application.
     */
    void on_actionClose_triggered();

    /**
     * @brief Slot privé appelé lorsqu'on liste des recettes.
     */
    void on_actionListRecette_triggered();

private:
    Ui::GestionServeurForm *ui; /**< Interface utilisateur de la classe. */
    DatabaseManager databaseManager_; /**< Gestionnaire de base de données de la classe. */
    QSettings settings; /**< Paramètres de la classe. */
};

#endif
