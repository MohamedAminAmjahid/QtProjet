#include "personne.h"
#include <QSqlQuery>

/**
 * @brief Constructeur par défaut de la classe Personne.
 */
Personne::Personne()
{
}

/**
 * @brief Constructeur de la classe Personne avec initialisation des attributs.
 * @param login Le login de la personne.
 * @param motDePasse Le mot de passe de la personne.
 * @param cin Le numéro de carte d'identité de la personne.
 * @param role Le rôle de la personne.
 */
Personne::Personne(const QString &login, const QString &motDePasse, const QString &cin, const QString &role)
    : login_(login), motDePasse_(motDePasse), cin_(cin), role_(role)
{
}
