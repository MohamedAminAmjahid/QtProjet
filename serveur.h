// admin.h
#ifndef SERVEUR_H
#define SERVEUR_H

#include "personne.h"

class Serveur : public Personne
{
public:
    Serveur();
    Serveur(const QString &login, const QString &motDePasse, const QString &cin);
    Serveur(const QString &login, const QString &cin);

    QString getLogin() const; // Déclaration de la méthode getLogin
    QString getCin() const;   // Déclaration de la méthode getCin


    // Autres méthodes spécifiques à un admin si nécessaire
};

#endif // SERVEUR_H
