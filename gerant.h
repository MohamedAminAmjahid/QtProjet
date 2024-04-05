#ifndef GERANT_H
#define GERANT_H

#include "personne.h"

/**
 * @brief La classe Gerant représente un gérant du restaurant.
 *
 * Cette classe hérite de la classe Personne et représente un gérant du restaurant.
 */
class Gerant : public Personne
{
public:
    /**
     * @brief Constructeur par défaut de la classe Gerant.
     */
    Gerant();

    /**
     * @brief Constructeur de la classe Gerant.
     *
     * @param login Le login du gérant.
     * @param motDePasse Le mot de passe du gérant.
     * @param cin Le numéro de carte d'identité nationale du gérant.
     */
    Gerant(const QString &login, const QString &motDePasse, const QString &cin);
};

#endif
