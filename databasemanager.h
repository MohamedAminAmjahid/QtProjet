// databasemanager.h
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
    explicit DatabaseManager(QObject *parent = nullptr);

    bool connectToDatabase(const QString &dbName);
    void disconnectFromDatabase();
    bool createTable(const QString &tableName, const QString &tableDefinition);
    bool insertPerson(const QString &login, const QString &password, const QString &cin, const QString &role);

    bool verifierAuthentification(const QString &login, const QString &motDePasse);
    QString getRole(const QString &login, const QString &password);

    bool insertProduct(const QString &designation, double price, int quantity);
    QList<Produit> selectProducts();

    QList<Serveur> selectServers();
    bool dropTable(const QString &tableName);

    QSqlQuery selectProductDetails(const QString &productCode);
    QStringList selectProductCodes();
    bool updateProduct(const QString &productCode, const QString &newDesignation, double newPrice, int newQuantity);

    bool deleteProduct(const QString &productCode);
    QStringList selectServerCodes();
    QSqlQuery selectServerDetails(const QString &id);
    bool updateServer(const QString &id, const QString &newLogin, QString newPassword, QString newCin);
    bool deleteServer(const QString &id);

    bool insertCommand(int idServeur, QString productId, int quantity, const QDate &date);
    int getServerId(const QString &login) const;
    int getStockQuantity(const QString &productId) const;
    QList<Commande> selectCommands() const;


    QList<QPair<QString, QString>> selectProductCodesAndNames();
    QString getProductName(int productId) const;
    double getProductPrice(int productId) const;
    Commande getCommandByNumber(QString commandNumber) const;
    bool updateCommand(const QString &codeCommande,int idProduit, int quantite, const QDate &dateCommande);


    bool setQuantite(QString productId, int quantity);

    bool deleteCommandByNumber(const QString &codeCommande);

    QList<QPair<int, QString>> getServeursAndLogins();
    double calculateTotalParJournee(int idServeur, const QDate &date);
    bool insertRecette(int idServeur, double totalParJournee, const QDate &date);
    QList<QPair<QPair<int, QString>, QPair<double, QString>>> selectRecettesWithServerLoginsAndDetails();
    QList<QPair<QPair<int, QString>, QPair<double, QString>>> selectRecettesWithServerLoginsAndDetails(int idServeur);


    QList<int> selectRecetteCodes() const;
    bool updateRecette(int codeRecette, int idServeur);
    Recette getRecetteInfo(int codeRecette);
    bool deleteRecette(int codeRecette);

private:
    QSqlDatabase m_database;
};

#endif
