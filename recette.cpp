#include "recette.h"

Recette::Recette() : m_codeRecette(0), m_idServeur(0), m_totalParJournee(0.0), m_date(QDate::currentDate()) {}

Recette::Recette(int codeRecette, int idServeur, double totalParJournee, QDate date)
    : m_codeRecette(codeRecette), m_idServeur(idServeur), m_totalParJournee(totalParJournee), m_date(date) {}

int Recette::getCodeRecette() const {
    return m_codeRecette;
}

int Recette::getIdServeur() const {
    return m_idServeur;
}

double Recette::getTotalParJournee() const {
    return m_totalParJournee;
}

QDate Recette::getDate() const {
    return m_date;
}

void Recette::setCodeRecette(int codeRecette) {
    m_codeRecette = codeRecette;
}

void Recette::setIdServeur(int idServeur) {
    m_idServeur = idServeur;
}

void Recette::setTotalParJournee(double totalParJournee) {
    m_totalParJournee = totalParJournee;
}

void Recette::setDate(QDate date) {
    m_date = date;
}
