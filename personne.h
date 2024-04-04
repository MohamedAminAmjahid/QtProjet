// personne.h
#ifndef PERSONNE_H
#define PERSONNE_H

#include <QString>

class Personne
{
public:
    Personne();
    Personne(const QString &login, const QString &motDePasse, const QString &cin, const QString &role);


protected:
    QString login_;
    QString motDePasse_;
    QString cin_;
    QString role_;
};

#endif // PERSONNE_H
