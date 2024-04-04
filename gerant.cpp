// gerant.cpp
#include "gerant.h"

Gerant::Gerant() {}

Gerant::Gerant(const QString &login, const QString &motDePasse, const QString &cin)
    : Personne(login, motDePasse, cin, "Admin") // Utilisation du constructeur de la classe Personne pour initialiser les attributs
{
    // Initialisation spécifique à un gérant si nécessaire
}
