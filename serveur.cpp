#include "serveur.h"

Serveur::Serveur() : Personne() {}

/**
 * @brief Constructeur de la classe Serveur avec login, mot de passe et CIN.
 * @param login Le login du serveur.
 * @param motDePasse Le mot de passe du serveur.
 * @param cin Le numéro CIN du serveur.
 */
Serveur::Serveur(const QString &login, const QString &motDePasse, const QString &cin)
    : Personne(login, motDePasse, cin, "Server")
{
}

/**
 * @brief Constructeur de la classe Serveur avec login et CIN.
 * Le mot de passe est initialisé à "0000".
 * @param login Le login du serveur.
 * @param cin Le numéro CIN du serveur.
 */
Serveur::Serveur(const QString &login, const QString &cin)
    : Personne(login, "0000", cin, "Server")
{
}

/**
 * @brief Obtient le login du serveur.
 * @return Le login du serveur.
 */
QString Serveur::getLogin() const
{
    return login_;
}

/**
 * @brief Obtient le numéro CIN du serveur.
 * @return Le numéro CIN du serveur.
 */
QString Serveur::getCin() const
{
    return cin_;
}
