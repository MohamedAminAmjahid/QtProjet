#ifndef PRODUIT_H
#define PRODUIT_H

#include <QString>

/**
 * @brief La classe Produit représente un produit dans le système.
 * Cette classe contient des informations sur un produit telles que son code, sa désignation, son prix et sa quantité en stock.
 */
class Produit
{
public:
    /**
     * @brief Constructeur par défaut de la classe Produit.
     */
    Produit();

    /**
     * @brief Constructeur de la classe Produit.
     * @param codeProduit Le code du produit.
     * @param designation La désignation du produit.
     * @param prix Le prix du produit.
     * @param quantiteStock La quantité en stock du produit.
     */
    Produit(const QString &codeProduit, const QString &designation, double prix, int quantiteStock);

    /**
     * @brief Getter pour le code du produit.
     * @return Le code du produit.
     */
    QString codeProduit() const;

    /**
     * @brief Getter pour la désignation du produit.
     * @return La désignation du produit.
     */
    QString designation() const;

    /**
     * @brief Getter pour le prix du produit.
     * @return Le prix du produit.
     */
    double prix() const;

    /**
     * @brief Getter pour la quantité en stock du produit.
     * @return La quantité en stock du produit.
     */
    int quantiteStock() const;

    /**
     * @brief Setter pour le code du produit.
     * @param codeProduit Le nouveau code du produit.
     */
    void setCodeProduit(const QString &codeProduit);

    /**
     * @brief Setter pour la désignation du produit.
     * @param designation La nouvelle désignation du produit.
     */
    void setDesignation(const QString &designation);

    /**
     * @brief Setter pour le prix du produit.
     * @param prix Le nouveau prix du produit.
     */
    void setPrix(double prix);

    /**
     * @brief Setter pour la quantité en stock du produit.
     * @param quantiteStock La nouvelle quantité en stock du produit.
     */
    void setQuantiteStock(int quantiteStock);

private:
    QString codeProduit_; /**< Le code du produit. */
    QString designation_; /**< La désignation du produit. */
    double prix_; /**< Le prix du produit. */
    int quantiteStock_; /**< La quantité en stock du produit. */
};

#endif
