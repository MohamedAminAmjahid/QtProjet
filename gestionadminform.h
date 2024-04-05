#ifndef GESTIONADMINFORM_H
#define GESTIONADMINFORM_H

#include <QMainWindow>
#include <produit.h>
#include <databasemanager.h>
#include <serveur.h>
#include <qsettings.h>

namespace Ui {
class GestionAdminForm;
}

/**
 * @brief La classe GestionAdminForm représente la fenêtre principale de l'interface
 *        d'administration du système.
 *
 * Cette classe gère l'ensemble des fonctionnalités de l'interface d'administration,
 * telles que la gestion des produits, des serveurs, des recettes, etc.
 */
class GestionAdminForm : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur de la classe GestionAdminForm.
     *
     * @param parent Le widget parent de la fenêtre.
     */
    explicit GestionAdminForm(QWidget *parent = nullptr);

    /**
     * @brief Destructeur de la classe GestionAdminForm.
     */
    ~GestionAdminForm();

    /**
     * @brief Parcourir les sous-répertoires à partir du chemin spécifié.
     *
     * Cette méthode permet de parcourir les sous-répertoires à partir du chemin spécifié
     * et d'effectuer des opérations sur chacun d'entre eux.
     *
     * @param path Le chemin du répertoire à parcourir.
     */
    void parcourirSousRepertoires(const QString &path);

private slots:
    /**
     * @brief Slot privé appelé lorsqu'on demande de lister les produits.
     */
    void on_actionListerProduct_triggered();

    /**
     * @brief Slot privé appelé lorsqu'on demande de lister les serveurs.
     */
    void on_actionListServer_triggered();

    /**
     * @brief Slot privé appelé lorsqu'on demande d'ajouter un serveur.
     */
    void on_actionAddServer_triggered();

    /**
     * @brief Slot privé appelé lorsqu'on demande d'ajouter un produit.
     */
    void on_actionAddProduct_triggered();

    /**
     * @brief Slot privé appelé lorsqu'on demande de mettre à jour un produit.
     */
    void on_actionUpdateProduct_triggered();

    /**
     * @brief Slot privé appelé lorsqu'on demande de supprimer un produit.
     */
    void on_actionDeleteProduct_triggered();

    /**
     * @brief Slot privé appelé lorsqu'on demande de mettre à jour un serveur.
     */
    void on_actionUpdateServer_triggered();

    /**
     * @brief Slot privé appelé lorsqu'on demande de supprimer un serveur.
     */
    void on_actionDeleteServer_triggered();

    /**
     * @brief Slot privé appelé lorsqu'on demande de rechercher un produit.
     */
    void on_actionSearchProduct_triggered();

    /**
     * @brief Slot privé appelé lorsqu'on demande de se déconnecter.
     */
    void on_actionLogOut_triggered();

    /**
     * @brief Slot privé appelé lorsqu'on demande de fermer l'application.
     */
    void on_actionClose_triggered();

    /**
     * @brief Slot privé appelé lorsqu'on demande d'ajouter une recette.
     */
    void on_actionAddRecette_triggered();

    /**
     * @brief Slot privé appelé lorsqu'on demande de lister les recettes.
     */
    void on_actionListRecette_triggered();

    /**
     * @brief Slot privé appelé lorsqu'on demande de lister les commandes.
     */
    void on_actionListCommand_triggered();

    /**
     * @brief Slot privé appelé lorsqu'on demande de mettre à jour une recette.
     */
    void on_actionUpdateRecette_triggered();

    /**
     * @brief Slot privé appelé lorsqu'on demande de supprimer une recette.
     */
    void on_actionDeleteRecette_triggered();

    /**
     * @brief Slot privé appelé lorsqu'on demande le total par jour.
     */
    void on_actionTotal_per_day_triggered();

    /**
     * @brief Slot privé appelé lorsqu'on demande le total par mois.
     */
    void on_actionTotal_per_month_triggered();

    /**
     * @brief Slot privé appelé lorsqu'on demande le total par serveur et date.
     */
    void on_actionTotal_per_server_and_date_triggered();

    /**
     * @brief Slot privé appelé lorsqu'on demande de supprimer une commande.
     */
    void on_actionDeleteCommand_triggered();

    /**
     * @brief Slot privé appelé lorsqu'on demande de mettre à jour une commande.
     */
    void on_actionUpdateCommand_triggered();

    /**
     * @brief Slot privé appelé lorsqu'on demande de passer à la langue française.
     */
    void on_actionFrench_triggered();

    /**
     * @brief Slot privé appelé lorsqu'on demande de passer à la langue anglaise.
     */
    void on_actionEnglish_triggered();

private:
    Ui::GestionAdminForm *ui; ///< Interface utilisateur associée à la fenêtre.
    DatabaseManager databaseManager_; ///< Gestionnaire de la base de données.
    QSettings settings_; ///< Paramètres de l'application.
};

#endif
