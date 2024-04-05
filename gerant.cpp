#include "gerant.h"

/**
 * @brief Constructeur par défaut de la classe Gerant.
 */
Gerant::Gerant() {}

/**
 * @brief Constructeur de la classe Gerant avec initialisation des attributs.
 * @param login Le login du gérant.
 * @param motDePasse Le mot de passe du gérant.
 * @param cin Le numéro de CIN du gérant.
 */
Gerant::Gerant(const QString &login, const QString &motDePasse, const QString &cin)
    : Personne(login, motDePasse, cin, "Admin")
{
}
