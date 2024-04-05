#include "commande.h"

/**
 * @brief Constructeur par défaut de la classe Commande.
 */
Commande::Commande() {}

/**
 * @brief Constructeur de la classe Commande avec paramètres.
 * @param codeCommande Le code de la commande.
 * @param idServeur L'ID du serveur.
 * @param idProduit L'ID du produit.
 * @param quantite La quantité de produit commandée.
 * @param dateCommande La date de la commande.
 */
Commande::Commande(const QString &codeCommande, int idServeur, int idProduit, int quantite, const QDate &dateCommande)
    : idServeur_(idServeur), idProduit_(idProduit), quantite_(quantite), codeCommande_(codeCommande), dateCommande_(dateCommande) {}

/**
 * @brief Getter pour l'ID du serveur.
 * @return L'ID du serveur.
 */
int Commande::idServeur() const {
    return idServeur_;
}

/**
 * @brief Getter pour l'ID du produit.
 * @return L'ID du produit.
 */
int Commande::idProduit() const {
    return idProduit_;
}

/**
 * @brief Getter pour la quantité de produits commandée.
 * @return La quantité de produits commandée.
 */
int Commande::quantite() const {
    return quantite_;
}

/**
 * @brief Getter pour le code de la commande.
 * @return Le code de la commande.
 */
QString Commande::codeCommande() const {
    return codeCommande_;
}

/**
 * @brief Getter pour la date de la commande.
 * @return La date de la commande.
 */
QDate Commande::dateCommande() const {
    return dateCommande_;
}

/**
 * @brief Setter pour l'ID du serveur.
 * @param idServeur Le nouvel ID du serveur.
 */
void Commande::setIdServeur(int idServeur) {
    idServeur_ = idServeur;
}

/**
 * @brief Setter pour l'ID du produit.
 * @param idProduit Le nouvel ID du produit.
 */
void Commande::setIdProduit(int idProduit) {
    idProduit_ = idProduit;
}

/**
 * @brief Setter pour la quantité de produits commandée.
 * @param quantite La nouvelle quantité de produits commandée.
 */
void Commande::setQuantite(int quantite) {
    quantite_ = quantite;
}

/**
 * @brief Setter pour le code de la commande.
 * @param codeCommande Le nouveau code de la commande.
 */
void Commande::setCodeCommande(const QString &codeCommande) {
    codeCommande_ = codeCommande;
}

/**
 * @brief Setter pour la date de la commande.
 * @param dateCommande La nouvelle date de la commande.
 */
void Commande::setDateCommande(const QDate &dateCommande) {
    dateCommande_ = dateCommande;
}
