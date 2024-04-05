#include "produit.h"

/**
 * @brief Constructeur par défaut de la classe Produit.
 * Initialise le prix et la quantité stockée à zéro.
 */
Produit::Produit() : prix_(0.0), quantiteStock_(0) {}

/**
 * @brief Constructeur de la classe Produit avec initialisation des attributs.
 * @param codeProduit Le code du produit.
 * @param designation La désignation du produit.
 * @param prix Le prix du produit.
 * @param quantiteStock La quantité en stock du produit.
 */
Produit::Produit(const QString &codeProduit, const QString &designation, double prix, int quantiteStock)
    : codeProduit_(codeProduit), designation_(designation), prix_(prix), quantiteStock_(quantiteStock) {}

/**
 * @brief Accesseur pour le code du produit.
 * @return Le code du produit.
 */
QString Produit::codeProduit() const {
    return codeProduit_;
}

/**
 * @brief Accesseur pour la désignation du produit.
 * @return La désignation du produit.
 */
QString Produit::designation() const {
    return designation_;
}

/**
 * @brief Accesseur pour le prix du produit.
 * @return Le prix du produit.
 */
double Produit::prix() const {
    return prix_;
}

/**
 * @brief Accesseur pour la quantité en stock du produit.
 * @return La quantité en stock du produit.
 */
int Produit::quantiteStock() const {
    return quantiteStock_;
}

/**
 * @brief Mutateur pour le code du produit.
 * @param codeProduit Le nouveau code du produit.
 */
void Produit::setCodeProduit(const QString &codeProduit) {
    codeProduit_ = codeProduit;
}

/**
 * @brief Mutateur pour la désignation du produit.
 * @param designation La nouvelle désignation du produit.
 */
void Produit::setDesignation(const QString &designation) {
    designation_ = designation;
}

/**
 * @brief Mutateur pour le prix du produit.
 * @param prix Le nouveau prix du produit.
 */
void Produit::setPrix(double prix) {
    prix_ = prix;
}

/**
 * @brief Mutateur pour la quantité en stock du produit.
 * @param quantiteStock La nouvelle quantité en stock du produit.
 */
void Produit::setQuantiteStock(int quantiteStock) {
    quantiteStock_ = quantiteStock;
}
