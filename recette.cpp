#include "recette.h"

/**
 * @brief Constructeur par défaut de la classe Recette.
 * Initialise les membres à des valeurs par défaut.
 */
Recette::Recette() : m_codeRecette(0), m_idServeur(0), m_totalParJournee(0.0), m_date(QDate::currentDate()) {}

/**
 * @brief Constructeur de la classe Recette avec initialisation des attributs.
 * @param codeRecette Le code de la recette.
 * @param idServeur L'identifiant du serveur.
 * @param totalParJournee Le total de la recette pour la journée.
 * @param date La date de la recette.
 */
Recette::Recette(int codeRecette, int idServeur, double totalParJournee, QDate date)
    : m_codeRecette(codeRecette), m_idServeur(idServeur), m_totalParJournee(totalParJournee), m_date(date) {}

/**
 * @brief Accesseur pour le code de la recette.
 * @return Le code de la recette.
 */
int Recette::getCodeRecette() const {
    return m_codeRecette;
}

/**
 * @brief Accesseur pour l'identifiant du serveur.
 * @return L'identifiant du serveur.
 */
int Recette::getIdServeur() const {
    return m_idServeur;
}

/**
 * @brief Accesseur pour le total de la recette pour la journée.
 * @return Le total de la recette pour la journée.
 */
double Recette::getTotalParJournee() const {
    return m_totalParJournee;
}

/**
 * @brief Accesseur pour la date de la recette.
 * @return La date de la recette.
 */
QDate Recette::getDate() const {
    return m_date;
}

/**
 * @brief Mutateur pour le code de la recette.
 * @param codeRecette Le nouveau code de la recette.
 */
void Recette::setCodeRecette(int codeRecette) {
    m_codeRecette = codeRecette;
}

/**
 * @brief Mutateur pour l'identifiant du serveur.
 * @param idServeur Le nouvel identifiant du serveur.
 */
void Recette::setIdServeur(int idServeur) {
    m_idServeur = idServeur;
}

/**
 * @brief Mutateur pour le total de la recette pour la journée.
 * @param totalParJournee Le nouveau total de la recette pour la journée.
 */
void Recette::setTotalParJournee(double totalParJournee) {
    m_totalParJournee = totalParJournee;
}

/**
 * @brief Mutateur pour la date de la recette.
 * @param date La nouvelle date de la recette.
 */
void Recette::setDate(QDate date) {
    m_date = date;
}
