#ifndef SERVEUR_H
#define SERVEUR_H

#include "personne.h"

/**
 * @brief La classe Serveur représente un serveur dans le système.
 * Hérite de la classe Personne.
 */
class Serveur : public Personne
{
public:
    /**
     * @brief Constructeur par défaut de la classe Serveur.
     */
    Serveur();

    /**
     * @brief Constructeur de la classe Serveur avec les paramètres de connexion et le numéro d'identification.
     * @param login Le nom de connexion du serveur.
     * @param motDePasse Le mot de passe du serveur.
     * @param cin Le numéro d'identification du serveur.
     */
    Serveur(const QString &login, const QString &motDePasse, const QString &cin);

    /**
     * @brief Constructeur de la classe Serveur avec le nom de connexion et le numéro d'identification.
     * @param login Le nom de connexion du serveur.
     * @param cin Le numéro d'identification du serveur.
     */
    Serveur(const QString &login, const QString &cin);

    /**
     * @brief Obtient le nom de connexion du serveur.
     * @return Le nom de connexion du serveur.
     */
    QString getLogin() const;

    /**
     * @brief Obtient le numéro d'identification du serveur.
     * @return Le numéro d'identification du serveur.
     */
    QString getCin() const;
};

#endif
