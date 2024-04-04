// serveur.cpp
#include "serveur.h"

Serveur::Serveur() : Personne() {}

Serveur::Serveur(const QString &login, const QString &motDePasse, const QString &cin)
    : Personne(login, motDePasse, cin, "Server") // Assuming "serveur" is the role for servers
{
    // Additional initialization if needed
}

Serveur::Serveur(const QString &login, const QString &cin)
    : Personne(login, "0000", cin, "Server") // Assuming "serveur" is the role for servers
{
    // Additional initialization if needed
}

QString Serveur::getLogin() const
{
    return login_;
}

QString Serveur::getCin() const
{
    return cin_;
}
