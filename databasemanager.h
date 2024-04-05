#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <produit.h>
#include <serveur.h>
#include <commande.h>
#include <recette.h>

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructeur de la classe DatabaseManager.
     * @param parent Le parent de l'objet.
     */
    explicit DatabaseManager(QObject *parent = nullptr);

    /**
     * @brief Se connecte à la base de données.
     * @param dbName Le nom de la base de données.
     * @return true si la connexion réussit, sinon false.
     */
    bool connectToDatabase(const QString &dbName);

    /**
     * @brief Se déconnecte de la base de données.
     */
    void disconnectFromDatabase();
    /**
     *
     * @brief Vérifie si une table existe dans la base de données.
     *
     * Cette fonction exécute une requête SQL pour interroger le schéma d'information de la base de données
     * et détermine si une table avec le nom spécifié existe.
     *
     * @param tableName Le nom de la table à vérifier.
     * @return true si la table existe, sinon false.
     */
    bool tableExists(const QString& tableName);

    /**
     * @brief Crée une nouvelle table dans la base de données.
     * @param tableName Le nom de la table à créer.
     * @param tableDefinition La définition de la table.
     * @return true si la table est créée avec succès, sinon false.
     */
    bool createTable(const QString &tableName, const QString &tableDefinition);

    /**
     * @brief Insère une personne dans la base de données.
     * @param login Le login de la personne.
     * @param password Le mot de passe de la personne.
     * @param cin Le numéro de CIN de la personne.
     * @param role Le rôle de la personne.
     * @return true si l'insertion réussit, sinon false.
     */
    bool insertPerson(const QString &login, const QString &password, const QString &cin, const QString &role);


    /**
     * @brief Vérifie l'authentification d'un utilisateur.
     * @param login Le nom d'utilisateur.
     * @param motDePasse Le mot de passe de l'utilisateur.
     * @return true si l'authentification réussit, sinon false.
     */
    bool verifierAuthentification(const QString &login, const QString &motDePasse);

    /**
     * @brief Récupère le rôle d'un utilisateur.
     * @param login Le nom d'utilisateur.
     * @param password Le mot de passe de l'utilisateur.
     * @return Le rôle de l'utilisateur.
     */
    QString getRole(const QString &login, const QString &password);

    /**
    * @brief Insère un nouveau produit dans la base de données.
     * @param designation La désignation du produit.
     * @param price Le prix du produit.
     * @param quantity La quantité en stock du produit.
     * @return true si l'insertion réussit, sinon false.
     */
    bool insertProduct(const QString &designation, double price, int quantity);

    /**
    * @brief Sélectionne tous les produits de la base de données.
    * @return Une liste de tous les produits.
    */
    QList<Produit> selectProducts();

    /**
    * @brief Sélectionne tous les serveurs de la base de données.
    * @return Une liste de tous les serveurs.
    */
    QList<Serveur> selectServers();

    /**
    * @brief Supprime une table de la base de données.
    * @param tableName Le nom de la table à supprimer.
    * @return true si la suppression réussit, sinon false.
    */
    bool dropTable(const QString &tableName);

    /**
     * @brief Sélectionne les détails d'un produit à partir de son code.
     * @param productCode Le code du produit à sélectionner.
     * @return Une requête contenant les détails du produit.
     */
    QSqlQuery selectProductDetails(const QString &productCode);

    /**
     * @brief Sélectionne tous les codes de produits de la base de données.
     * @return Une liste de tous les codes de produits.
     */
    QStringList selectProductCodes();

    /**
     * @brief Met à jour les informations d'un produit dans la base de données.
     * @param productCode Le code du produit à mettre à jour.
     * @param newDesignation La nouvelle désignation du produit.
     * @param newPrice Le nouveau prix du produit.
     * @param newQuantity La nouvelle quantité en stock du produit.
     * @return true si la mise à jour réussit, sinon false.
     */
    bool updateProduct(const QString &productCode, const QString &newDesignation, double newPrice, int newQuantity);

    /**
     * @brief Supprime un produit de la base de données à partir de son code.
     * @param productCode Le code du produit à supprimer.
     * @return true si la suppression réussit, sinon false.
     */
    bool deleteProduct(const QString &productCode);

    /**
     * @brief Sélectionne tous les codes de serveurs de la base de données.
     * @return Une liste de tous les codes de serveurs.
     */
    QStringList selectServerCodes();

    /**
     * @brief Sélectionne les détails d'un serveur à partir de son identifiant.
     * @param id L'identifiant du serveur à sélectionner.
     * @return Une requête contenant les détails du serveur.
     */
    QSqlQuery selectServerDetails(const QString &id);

    /**
     * @brief Met à jour les informations d'un serveur dans la base de données.
     * @param id L'identifiant du serveur à mettre à jour.
     * @param newLogin Le nouveau nom d'utilisateur du serveur.
     * @param newPassword Le nouveau mot de passe du serveur.
     * @param newCin Le nouveau numéro de carte d'identité du serveur.
     * @return true si la mise à jour réussit, sinon false.
     */
    bool updateServer(const QString &id, const QString &newLogin, QString newPassword, QString newCin);

    /**
     * @brief Supprime un serveur de la base de données à partir de son identifiant.
     * @param id L'identifiant du serveur à supprimer.
     * @return true si la suppression réussit, sinon false.
     */
    bool deleteServer(const QString &id);


    /**
     * @brief Insère une nouvelle commande dans la base de données.
     * @param idServeur L'identifiant du serveur effectuant la commande.
     * @param productId L'identifiant du produit commandé.
     * @param quantity La quantité commandée.
     * @param date La date de la commande.
     * @return true si l'insertion réussit, sinon false.
     */
    bool insertCommand(int idServeur, QString productId, int quantity, const QDate &date);

    /**
     * @brief Obtient l'identifiant d'un serveur à partir de son nom d'utilisateur.
     * @param login Le nom d'utilisateur du serveur.
     * @return L'identifiant du serveur, ou -1 s'il n'existe pas.
     */
    int getServerId(const QString &login) const;

    /**
     * @brief Obtient la quantité en stock d'un produit à partir de son identifiant.
     * @param productId L'identifiant du produit.
     * @return La quantité en stock du produit.
     */
    int getStockQuantity(const QString &productId) const;

    /**
     * @brief Sélectionne toutes les commandes enregistrées dans la base de données.
     * @return Une liste contenant toutes les commandes.
     */
    QList<Commande> selectCommands() const;

    /**
     * @brief Sélectionne les codes et les noms de tous les produits de la base de données.
     * @return Une liste contenant les codes et les noms de tous les produits.
     */
    QList<QPair<QString, QString>> selectProductCodesAndNames();

    /**
     * @brief Obtient le nom d'un produit à partir de son identifiant.
     * @param productId L'identifiant du produit.
     * @return Le nom du produit.
     */
    QString getProductName(int productId) const;

    /**
     * @brief Obtient le prix d'un produit à partir de son identifiant.
     * @param productId L'identifiant du produit.
     * @return Le prix du produit.
     */
    double getProductPrice(int productId) const;

    /**
     * @brief Obtient une commande à partir de son numéro.
     * @param commandNumber Le numéro de la commande.
     * @return Les détails de la commande.
     */
    Commande getCommandByNumber(QString commandNumber) const;

    /**
     * @brief Met à jour les informations d'une commande dans la base de données.
     * @param codeCommande Le code de la commande à mettre à jour.
     * @param idProduit Le nouvel identifiant du produit.
     * @param quantite La nouvelle quantité commandée.
     * @param dateCommande La nouvelle date de la commande.
     * @return true si la mise à jour réussit, sinon false.
     */
    bool updateCommand(const QString &codeCommande,int idProduit, int quantite, const QDate &dateCommande);



    /**
     * @brief Met à jour la quantité en stock d'un produit dans la base de données.
     * @param productId L'identifiant du produit.
     * @param quantity La nouvelle quantité en stock.
     * @return true si la mise à jour réussit, sinon false.
     */
    bool setQuantite(QString productId, int quantity);

    /**
     * @brief Supprime une commande de la base de données en utilisant son numéro.
     * @param codeCommande Le numéro de la commande à supprimer.
     * @return true si la suppression réussit, sinon false.
     */
    bool deleteCommandByNumber(const QString &codeCommande);

    /**
     * @brief Sélectionne les identifiants et les noms de tous les serveurs de la base de données.
     * @return Une liste contenant les identifiants et les noms de tous les serveurs.
     */
    QList<QPair<int, QString>> getServeursAndLogins();

    /**
     * @brief Calcule le total des recettes d'un serveur pour une journée donnée.
     * @param idServeur L'identifiant du serveur.
     * @param date La date de la journée.
     * @return Le total des recettes pour la journée.
     */
    double calculateTotalParJournee(int idServeur, const QDate &date);

    /**
     * @brief Insère une nouvelle recette dans la base de données.
     * @param idServeur L'identifiant du serveur.
     * @param totalParJournee Le total des recettes pour la journée.
     * @param date La date de la recette.
     * @return true si l'insertion réussit, sinon false.
     */
    bool insertRecette(int idServeur, double totalParJournee, const QDate &date);

    /**
     * @brief Sélectionne les détails des recettes avec les noms des serveurs correspondants.
     * @return Une liste contenant les détails des recettes et les noms des serveurs.
     */
    QList<QPair<QPair<int, QString>, QPair<double, QString>>> selectRecettesWithServerLoginsAndDetails();

    /**
     * @brief Sélectionne les détails des recettes d'un serveur spécifique avec les noms des serveurs correspondants.
     * @param idServeur L'identifiant du serveur.
     * @return Une liste contenant les détails des recettes et les noms des serveurs pour le serveur spécifié.
     */
    QList<QPair<QPair<int, QString>, QPair<double, QString>>> selectRecettesWithServerLoginsAndDetails(int idServeur);

    /**
     * @brief Sélectionne les codes de toutes les recettes de la base de données.
     * @return Une liste contenant les codes de toutes les recettes.
     */
    QList<int> selectRecetteCodes() const;

    /**
     * @brief Met à jour les informations d'une recette dans la base de données.
     * @param codeRecette Le code de la recette à mettre à jour.
     * @param idServeur Le nouvel identifiant du serveur.
     * @return true si la mise à jour réussit, sinon false.
     */
    bool updateRecette(int codeRecette, int idServeur);

    /**
     * @brief Obtient les informations d'une recette à partir de son code.
     * @param codeRecette Le code de la recette.
     * @return Les informations de la recette.
     */
    Recette getRecetteInfo(int codeRecette);

    /**
     * @brief Supprime une recette de la base de données en utilisant son code.
     * @param codeRecette Le code de la recette à supprimer.
     * @return true si la suppression réussit, sinon false.
     */
    bool deleteRecette(int codeRecette);


    /**
     * @brief Sélectionne les recettes pour une date spécifique.
     *
     * Cette méthode sélectionne les recettes enregistrées pour une date spécifique.
     *
     * @param date La date pour laquelle sélectionner les recettes.
     * @return Une chaîne de caractères représentant les détails des recettes pour la date spécifiée.
     */
    QString selectRecettesForDate(const QDate &date);

    /**
     * @brief Sélectionne les recettes pour un mois spécifique.
     *
     * Cette méthode sélectionne les recettes enregistrées pour un mois spécifique, à partir de la date spécifiée.
     *
     * @param date La date à partir de laquelle extraire le mois.
     * @return Une chaîne de caractères représentant les détails des recettes pour le mois spécifié.
     */
    QString selectRecettesForMonth(const QDate &date);

    /**
     * @brief Sélectionne les recettes pour un serveur spécifique et une date spécifique.
     *
     * Cette méthode sélectionne les recettes enregistrées pour un serveur spécifique et une date spécifique.
     *
     * @param idServeur L'identifiant du serveur.
     * @param date La date pour laquelle sélectionner les recettes.
     * @return Une chaîne de caractères représentant les détails des recettes pour le serveur et la date spécifiés.
     */
    QString selectRecettesForServerAndDate(int idServeur, const QDate &date);


private:
    QSqlDatabase m_database; ///< La base de données.
};

#endif
