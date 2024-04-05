#include "databasemanager.h"
#include <QSqlQuery>
#include <QDate>

DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent)
{
}

bool DatabaseManager::connectToDatabase(const QString &dbName)
{
        m_database = QSqlDatabase::addDatabase("QSQLITE");
        m_database.setDatabaseName(dbName);
        return m_database.open();
}

void DatabaseManager::disconnectFromDatabase()
{
    QString connection;
    connection=m_database.connectionName();
    QSqlDatabase::removeDatabase(connection);
    m_database.close();
}

bool DatabaseManager::createTable(const QString &tableName, const QString &tableDefinition)
{
    if (!m_database.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query;
    query.prepare("CREATE TABLE IF NOT EXISTS " + tableName + " (" + tableDefinition + ")");
    return query.exec();
}

bool DatabaseManager::insertPerson(const QString &login, const QString &password, const QString &cin, const QString &role)
{
    QSqlQuery query;
    query.prepare("INSERT INTO personnes (login, motdepasse, cin, role) VALUES (:login, :password, :cin, :role)");
    query.bindValue(":login", login);
    query.bindValue(":password", password);
    query.bindValue(":cin", cin);
    query.bindValue(":role", role);
    return query.exec();
}

bool DatabaseManager::verifierAuthentification(const QString &login, const QString &motDePasse)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM personnes WHERE login = :login AND motdepasse = :motdepasse");
    query.bindValue(":login", login);
    query.bindValue(":motdepasse", motDePasse);
    return query.exec() && query.next();
}

QString DatabaseManager::getRole(const QString &login, const QString &password)
{
    /*if (!m_database.isOpen()) {
        qDebug() << "Database is not open!";
        return QString();
    }*/

    QSqlQuery query;
    query.prepare("SELECT role FROM personnes WHERE login = :login AND motdepasse = :password");
    query.bindValue(":login", login);
    query.bindValue(":password", password);

    if (query.exec() && query.next()) {
        return query.value(0).toString();
    } else {
        qDebug() << "Failed to retrieve role for login" << login << "and password" << password;
        return QString();
    }
}

bool DatabaseManager::insertProduct(const QString &designation, double price, int quantity)
{
    QSqlQuery query;
    query.prepare("INSERT INTO produits (designation, prix, quantitestock) VALUES (:designation, :price, :quantity)");
    query.bindValue(":designation", designation);
    query.bindValue(":price", price);
    query.bindValue(":quantity", quantity);

    return query.exec();
}

QList<Produit> DatabaseManager::selectProducts()
{
    QList<Produit> productList;

    QSqlQuery query("SELECT * FROM produits");

    if (!query.exec()) {
        qDebug() << "Failed to execute query:";
        return productList;
    }

    while (query.next()) {
        Produit product;
        product.setDesignation(query.value("designation").toString());
        product.setPrix(query.value("prix").toDouble());
        product.setQuantiteStock(query.value("quantitestock").toInt());
        productList.append(product);
    }

    return productList;
}

QList<Serveur> DatabaseManager::selectServers()
{
    QList<Serveur> serverList;

    QSqlQuery query;
    if (query.exec("SELECT * FROM personnes")) {
        while (query.next()) {
            QString login = query.value("login").toString();
            QString cin = query.value("cin").toString();

            Serveur serveur(login, cin);
            serverList.append(serveur);
        }
    } else {
        qDebug() << "Error executing SQL query:";
    }

    return serverList;
}

bool DatabaseManager::dropTable(const QString &tableName)
{
    QSqlQuery query;
    query.prepare("DROP TABLE IF EXISTS " + tableName);
    return query.exec();
}

QSqlQuery DatabaseManager::selectProductDetails(const QString &productCode)
{
    QSqlQuery query;

    query.prepare("SELECT * FROM produits WHERE codeproduit = :code");
    query.bindValue(":code", productCode);

    if (!query.exec()) {
        qDebug() << "Error executing SQL query";
    }

    return query;
}

QStringList DatabaseManager::selectProductCodes()
{
    QStringList productCodes;

    QSqlQuery query("SELECT DISTINCT codeproduit FROM produits");

    if (!query.exec()) {
        qDebug() << "Error executing SQL query:";
        return productCodes;
    }

    while (query.next()) {
        productCodes << query.value("codeproduit").toString();
    }
    return productCodes;
}

bool DatabaseManager::updateProduct(const QString &productCode, const QString &newDesignation, double newPrice, int newQuantity)
{
    QSqlQuery query;

    query.prepare("UPDATE produits SET designation = :designation, prix = :price, quantitestock = :quantity WHERE codeproduit = :code");
    query.bindValue(":designation", newDesignation);
    query.bindValue(":price", newPrice);
    query.bindValue(":quantity", newQuantity);
    query.bindValue(":code", productCode);

    return query.exec();
}

bool DatabaseManager::deleteProduct(const QString &productCode)
{


    QSqlQuery query;
    query.prepare("DELETE FROM produits WHERE codeproduit = :productCode");
    query.bindValue(":productCode", productCode);

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Error executing SQL query" ;
        return false;
    }
}

QStringList DatabaseManager::selectServerCodes()
{
    QStringList serverCodes;

    QSqlQuery query("SELECT DISTINCT id FROM personnes where role = 'Server'");

    if (!query.exec()) {
        qDebug() << "Error executing SQL query:";
        return serverCodes;
    }

    while (query.next()) {
        serverCodes << query.value("id").toString();
    }
    return serverCodes;
}

QSqlQuery DatabaseManager::selectServerDetails(const QString &id)
{
    QSqlQuery query;

    query.prepare("SELECT * FROM personnes WHERE id = :code");
    query.bindValue(":code", id);

    if (!query.exec()) {
        qDebug() << "Error executing SQL query";
    }

    return query;
}

bool DatabaseManager::updateServer(const QString &id, const QString &newLogin, QString newPassword, QString newCin)
{
    QSqlQuery query;

    query.prepare("UPDATE personnes SET login = :login, motdepasse = :password, cin= :cin WHERE id = :id");
    query.bindValue(":login", newLogin);
    query.bindValue(":password", newPassword);
    query.bindValue(":cin", newCin);
    query.bindValue(":id", id);

    return query.exec();
}

bool DatabaseManager::deleteServer(const QString &id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM personnes WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Error executing SQL query" ;
        return false;
    }
}

bool DatabaseManager::insertCommand(int idServeur, QString productId, int quantity, const QDate &date)
{

    QSqlQuery query;
    query.prepare("INSERT INTO commandes (idserveur, produit_id, quantite, date_commande) VALUES (:idServeur, :productId, :quantity, :date)");
    query.bindValue(":idServeur", idServeur);
    query.bindValue(":productId", productId);
    query.bindValue(":quantity", quantity);
    query.bindValue(":date", date);
    if (!query.exec()) {
        qDebug() << "Error inserting command" ;
        return false;
    }
    int newQuantity = getStockQuantity(productId) - quantity;

    query.prepare("UPDATE produits SET quantitestock = :newQuantity WHERE codeproduit = :productId");
    query.bindValue(":newQuantity", newQuantity);
    query.bindValue(":productId", productId);

    if (!query.exec()) {
        qDebug() << "Error updating product quantity";
        return false;
    }
    return true;
}

int DatabaseManager::getServerId(const QString &login) const {
    int serverId = -1;

    QSqlQuery query;
    query.prepare("SELECT id FROM personnes WHERE login = :login AND role = 'Server'");
    query.bindValue(":login", login);

    if (query.exec() && query.next()) {
        serverId = query.value(0).toInt();
    } else {
        qDebug() << "Failed to retrieve server ID for login:" << login;
    }

    return serverId;
}

int DatabaseManager::getStockQuantity(const QString &productId) const
{
    QSqlQuery query;
    query.prepare("SELECT quantiteStock FROM produits WHERE codeproduit = :productId");
    query.bindValue(":productId", productId);

    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    } else {
        qDebug() << "Failed to get stock quantity for product with ID:" << productId;
        return -1;
    }
}

QList<Commande> DatabaseManager::selectCommands() const
{
    QList<Commande> commandList;
    QSqlQuery query("SELECT id, idserveur, produit_id, quantite, date_commande FROM commandes");

    if (query.exec()) {
        while (query.next()) {
            QString id = query.value("id").toString();
            int serverId = query.value("idserveur").toInt();
            int productId = query.value("produit_id").toInt();
            int quantity = query.value("quantite").toInt();
            QDate date = query.value("date_commande").toDate();

            Commande command(id, serverId, productId, quantity, date);

            commandList << command;
        }
    } else {
        qDebug() << "Error executing SQL query ";
    }

    return commandList;
}

QList<QPair<QString, QString>> DatabaseManager::selectProductCodesAndNames()
{
    QList<QPair<QString, QString>> productCodesAndNames;

    QSqlQuery query("SELECT codeproduit, designation FROM produits");

    if (!query.exec()) {
        qDebug() << "Error executing SQL query:";
        return productCodesAndNames;
    }

    while (query.next()) {
        QString productId = query.value("codeproduit").toString();
        QString productName = query.value("designation").toString();
        productCodesAndNames.append(qMakePair(productId, productName));
    }
    return productCodesAndNames;
}

QString DatabaseManager::getProductName(int productId) const
{
    QString productName;

    QSqlQuery query;
    query.prepare("SELECT designation FROM produits WHERE codeproduit = :productId");
    query.bindValue(":productId", productId);

    if (query.exec() && query.next()) {
        productName = query.value(0).toString();
    } else {
        qDebug() << "Failed to retrieve product name for ID:" << productId;
    }

    return productName;
}

bool DatabaseManager::setQuantite(QString productId, int quantity) {
    int newQuantity = getStockQuantity(productId) - quantity;
    QSqlQuery query;

    query.prepare("UPDATE produits SET quantitestock = :newQuantity WHERE codeproduit = :productId");
    query.bindValue(":newQuantity", newQuantity);
    query.bindValue(":productId", productId);

    if (!query.exec()) {
        qDebug() << "Error updating product quantity";
        return false;
    }

    return true;
}


double DatabaseManager::getProductPrice(int productId) const
{
    double productPrice = 0.0;

    QSqlQuery query;
    query.prepare("SELECT prix FROM produits WHERE codeproduit = :productId");
    query.bindValue(":productId", productId);

    if (query.exec() && query.next()) {
        productPrice = query.value(0).toDouble();
    } else {
        qDebug() << "Failed to retrieve product price for ID:" << productId;
    }

    return productPrice;
}

Commande DatabaseManager::getCommandByNumber(QString commandNumber) const
{
    Commande command;

    QSqlQuery query;
    query.prepare("SELECT * FROM commandes WHERE id = :commandNumber");
    query.bindValue(":commandNumber", commandNumber);

    if (query.exec() && query.next()) {
        int idServeur = query.value("idServeur").toInt();
        int idProduit = query.value("produit_id").toInt();
        int quantite = query.value("quantite").toInt();
        QDate dateCommande = query.value("date_commande").toDate();

        command = Commande(commandNumber, idServeur, idProduit, quantite, dateCommande);
    }

    return command;
}

bool DatabaseManager::updateCommand(const QString &codeCommande, int idProduit, int quantite, const QDate &dateCommande)
{
    QSqlQuery query;
    query.prepare("UPDATE commandes SET produit_id = :idProduit, quantite = :quantite, date_commande = :dateCommande WHERE id = :codeCommande");

    query.bindValue(":codeCommande", codeCommande);
    query.bindValue(":idProduit", idProduit);
    query.bindValue(":quantite", quantite);
    query.bindValue(":dateCommande", dateCommande);

    if (!query.exec()) {
        qDebug() << "DatabaseManager::updateCommand - Failed to update command";
    }
    return query.exec();
}

bool DatabaseManager::deleteCommandByNumber(const QString &codeCommande)
{
    QSqlQuery query;
    query.prepare("DELETE FROM commandes WHERE id = :codeCommande");
    query.bindValue(":codeCommande", codeCommande);

    if (!query.exec()) {
        qDebug() << "DatabaseManager::deleteCommandByNumber - Failed to delete command";
        return false;
    }

    return true;
}

QList<QPair<int, QString>> DatabaseManager::getServeursAndLogins() {
    QList<QPair<int, QString>> serveurs;
    QSqlQuery query;
    if (query.exec("SELECT id, login FROM personnes where role='Server'")) {
        while (query.next()) {
            int idServeur = query.value(0).toInt();
            QString login = query.value(1).toString();
            serveurs.append(qMakePair(idServeur, login));
        }
    } else {
        qDebug() << "Error executing SQL query";
    }

    return serveurs;
}

double DatabaseManager::calculateTotalParJournee(int idServeur, const QDate &date) {
    double total = 0.0;

    QSqlQuery query;
    query.prepare("SELECT SUM(quantite * prix) FROM commandes JOIN produits ON commandes.produit_id = produits.codeproduit WHERE idserveur = :idServeur AND date_commande = :date");
    query.bindValue(":idServeur", idServeur);
    query.bindValue(":date", date);

    if (query.exec() && query.next()) {
        total = query.value(0).toDouble();
    } else {
        qDebug() << "Failed to calculate total for the day";
    }

    return total;
}

bool DatabaseManager::insertRecette(int idServeur, double totalParJournee, const QDate &date) {
    QSqlQuery query;
    query.prepare("INSERT INTO recettes (idserveur, totalparjournee, date) VALUES (:idServeur, :totalParJournee, :date)");
    query.bindValue(":idServeur", idServeur);
    query.bindValue(":totalParJournee", totalParJournee);
    query.bindValue(":date", date);

    if (!query.exec()) {
        qDebug() << "Failed to insert recette into database";
        return false;
    }

    return true;
}

QList<QPair<QPair<int, QString>, QPair<double, QString>>> DatabaseManager::selectRecettesWithServerLoginsAndDetails()
{
    QList<QPair<QPair<int, QString>, QPair<double, QString>>> recettes;

    QSqlQuery query;
    if (query.exec("SELECT recettes.idServeur, personnes.login, recettes.totalParJournee, recettes.date FROM recettes INNER JOIN personnes ON recettes.idServeur = personnes.id")) {
        while (query.next()) {
            int idServeur = query.value(0).toInt();
            QString loginServeur = query.value(1).toString();
            double totalParJournee = query.value(2).toDouble();
            QDate date = query.value(3).toDate();

            QString formattedDate = date.toString("dd/MM/yyyy");
            recettes.append(qMakePair(qMakePair(idServeur, loginServeur), qMakePair(totalParJournee, formattedDate)));
        }
    } else {
        qDebug() << "Error executing SQL query";
    }

    return recettes;
}

QList<QPair<QPair<int, QString>, QPair<double, QString>>> DatabaseManager::selectRecettesWithServerLoginsAndDetails(int idServeur)
{
    QList<QPair<QPair<int, QString>, QPair<double, QString>>> recettes;

    QSqlQuery query;
    query.prepare("SELECT recettes.idServeur, personnes.login, recettes.totalParJournee, recettes.date FROM recettes INNER JOIN personnes ON recettes.idServeur = personnes.id WHERE recettes.idServeur = :idServeur");
    query.bindValue(":idServeur", idServeur);

    if (query.exec()) {
        while (query.next()) {
            int idServeur = query.value(0).toInt();
            QString loginServeur = query.value(1).toString();
            double totalParJournee = query.value(2).toDouble();
            QString date = query.value(3).toDate().toString("dd/MM/yyyy");

            recettes.append(qMakePair(qMakePair(idServeur, loginServeur), qMakePair(totalParJournee, date)));
        }
    } else {
        qDebug() << "Error executing SQL query:";
    }

    return recettes;
}

QList<int> DatabaseManager::selectRecetteCodes() const
{
    QList<int> codeRecettes;

    QSqlQuery query;
    query.exec("SELECT codeRecette FROM recettes");

    while (query.next()) {
        int code = query.value(0).toInt();
        codeRecettes.append(code);
    }

    return codeRecettes;
}

bool DatabaseManager::updateRecette(int codeRecette, int idServeur)
{
    QSqlQuery query;

    query.prepare("UPDATE recettes SET idServeur = :idServeur WHERE codeRecette = :codeRecette");

    query.bindValue(":idServeur", idServeur);
    query.bindValue(":codeRecette", codeRecette);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la mise à jour de la recette";
        return false;
    }

    return true;
}

Recette DatabaseManager::getRecetteInfo(int codeRecette)
{
    Recette recette;

    QSqlQuery query;
    query.prepare("SELECT totalparjournee, date FROM recettes WHERE codeRecette = :codeRecette");
    query.bindValue(":codeRecette", codeRecette);

    if (query.exec() && query.next()) {
        recette.setTotalParJournee(query.value("totalparjournee").toDouble());
        recette.setDate(query.value("date").toDate());
    } else {
        qDebug() << "Failed to retrieve recette info for code:" << codeRecette;
    }

    return recette;
}

bool DatabaseManager::deleteRecette(int codeRecette)
{
    QSqlQuery query;
    query.prepare("DELETE FROM recettes WHERE codeRecette = :codeRecette");
    query.bindValue(":codeRecette", codeRecette);

    if (!query.exec()) {
        qDebug() << "Failed to delete recette for code:" << codeRecette;
        return false;
    }

    return true;
}

QString DatabaseManager::selectRecettesForDate(const QDate &date)
{
    QString totalParJournee = "0";

    QSqlQuery query;

    query.prepare("SELECT sum(totalparjournee) FROM recettes WHERE date = ?");
    query.addBindValue(date.toString("yyyy-MM-dd"));

    if (!query.exec()) {
        qDebug() << "Error executing query";
        return totalParJournee;
    }

    while (query.next()) {
        totalParJournee = query.value(0).toString();
    }
    if(totalParJournee == ""){
        totalParJournee = "0";
    }
    return totalParJournee;
}

QString DatabaseManager::selectRecettesForMonth(const QDate &date)
{
    QString totalParMois = "0";

    QSqlQuery query;

    query.prepare("SELECT SUM(totalparjournee) FROM recettes WHERE strftime('%m', date) = ? AND strftime('%Y', date) = ?");
    query.addBindValue(date.toString("MM"));
    query.addBindValue(date.toString("yyyy"));

    if (!query.exec()) {
        qDebug() << "Error executing query";
        return totalParMois;
    }

    while (query.next()) {
        totalParMois = query.value(0).toString();
    }
    if(totalParMois == ""){
        totalParMois = "0";
    }
    return totalParMois;
}

QString DatabaseManager::selectRecettesForServerAndDate(int idServeur, const QDate &date)
{
    QString totalRecettes = "0";

    QSqlQuery query;

    query.prepare("SELECT SUM(totalparjournee) FROM recettes WHERE idServeur = :idServeur AND date = :date");
    query.bindValue(":idServeur", idServeur);
    query.bindValue(":date", date);

    if (!query.exec()) {
        qDebug() << "Error executing query";
        return totalRecettes;
    }

    while (query.next()) {
        totalRecettes = query.value(0).toString();
    }

    if(totalRecettes.isEmpty()){
        totalRecettes = "0";
    }

    return totalRecettes;
}

bool DatabaseManager::tableExists(const QString& tableName) {
    QSqlQuery query;
    query.prepare("SELECT name FROM sqlite_master WHERE type='table' AND name=:tableName;");
    query.bindValue(":tableName", tableName);

    if (query.exec() && query.next()) {
        QString existingTableName = query.value(0).toString();
        return existingTableName == tableName;
    }

    return false;
}
