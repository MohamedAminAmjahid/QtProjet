#ifndef COMMANDE_H
#define COMMANDE_H

#include <QString>
#include <QDate>

/**
 * @brief La classe Commande représente une commande passée par un serveur pour un produit à une date donnée.
 */
class Commande
{
public:
    /**
     * @brief Constructeur par défaut de la classe Commande.
     */
    Commande();

    /**
     * @brief Constructeur de la classe Commande.
     * @param codeCommande Le code de la commande.
     * @param idServeur L'ID du serveur effectuant la commande.
     * @param idProduit L'ID du produit commandé.
     * @param quantite La quantité commandée.
     * @param dateCommande La date de la commande.
     */
    Commande(const QString &codeCommande, int idServeur, int idProduit, int quantite, const QDate &dateCommande);

    /**
     * @brief Récupère l'ID du serveur effectuant la commande.
     * @return L'ID du serveur.
     */
    int idServeur() const;

    /**
     * @brief Récupère l'ID du produit commandé.
     * @return L'ID du produit.
     */
    int idProduit() const;

    /**
     * @brief Récupère la quantité commandée.
     * @return La quantité commandée.
     */
    int quantite() const;

    /**
     * @brief Récupère le code de la commande.
     * @return Le code de la commande.
     */
    QString codeCommande() const;

    /**
     * @brief Récupère la date de la commande.
     * @return La date de la commande.
     */
    QDate dateCommande() const;

    /**
     * @brief Définit l'ID du serveur effectuant la commande.
     * @param idServeur L'ID du serveur.
     */
    void setIdServeur(int idServeur);

    /**
     * @brief Définit l'ID du produit commandé.
     * @param idProduit L'ID du produit.
     */
    void setIdProduit(int idProduit);

    /**
     * @brief Définit la quantité commandée.
     * @param quantite La quantité commandée.
     */
    void setQuantite(int quantite);

    /**
     * @brief Définit le code de la commande.
     * @param codeCommande Le code de la commande.
     */
    void setCodeCommande(const QString &codeCommande);

    /**
     * @brief Définit la date de la commande.
     * @param dateCommande La date de la commande.
     */
    void setDateCommande(const QDate &dateCommande);

private:
    int idServeur_; ///< L'ID du serveur effectuant la commande.
    int idProduit_; ///< L'ID du produit commandé.
    int quantite_; ///< La quantité commandée.
    QString codeCommande_; ///< Le code de la commande.
    QDate dateCommande_; ///< La date de la commande.
};

#endif // COMMANDE_H
