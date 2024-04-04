// personne.cpp
#include "personne.h"
#include <QSqlQuery>

Personne::Personne()
{
}

Personne::Personne(const QString &login, const QString &motDePasse, const QString &cin, const QString &role)
    : login_(login), motDePasse_(motDePasse), cin_(cin), role_(role)
{
}




