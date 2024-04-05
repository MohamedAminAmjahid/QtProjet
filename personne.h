#ifndef PERSONNE_H
#define PERSONNE_H

#include <QString>

/**
 * @brief La classe Personne représente une entité générique.
 * Cette classe contient des informations de base sur une personne, telles que le login, le mot de passe, le numéro de CIN et le rôle.
 */
class Personne
{
public:
    /**
     * @brief Constructeur par défaut de la classe Personne.
     */
    Personne();

    /**
     * @brief Constructeur de la classe Personne.
     * @param login Le login de la personne.
     * @param motDePasse Le mot de passe de la personne.
     * @param cin Le numéro de CIN de la personne.
     * @param role Le rôle de la personne.
     */
    Personne(const QString &login, const QString &motDePasse, const QString &cin, const QString &role);

protected:
    QString login_; /**< Le login de la personne. */
    QString motDePasse_; /**< Le mot de passe de la personne. */
    QString cin_; /**< Le numéro de CIN de la personne. */
    QString role_; /**< Le rôle de la personne. */
};

#endif
