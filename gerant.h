// gerant.h
#ifndef GERANT_H
#define GERANT_H

#include "personne.h"

class Gerant : public Personne
{
public:
    Gerant();
    Gerant(const QString &login, const QString &motDePasse, const QString &cin);

    // Autres méthodes spécifiques à un gérant si nécessaire
};

#endif // GERANT_H
