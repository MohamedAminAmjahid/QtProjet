#ifndef RECETTE_H
#define RECETTE_H

#include <QString>
#include <QDate>

/**
 * @brief La classe Recette représente une recette dans le système.
 * Elle contient des informations telles que le code de la recette, l'identifiant du serveur,
 * le total par journée et la date de la recette.
 */
class Recette {
public:
    /**
     * @brief Constructeur par défaut de la classe Recette.
     */
    Recette();

    /**
     * @brief Constructeur de la classe Recette.
     * @param codeRecette Le code de la recette.
     * @param idServeur L'identifiant du serveur.
     * @param totalParJournee Le total par journée.
     * @param date La date de la recette.
     */
    Recette(int codeRecette, int idServeur, double totalParJournee, QDate date);

    /**
     * @brief Getter pour le code de la recette.
     * @return Le code de la recette.
     */
    int getCodeRecette() const;

    /**
     * @brief Getter pour l'identifiant du serveur.
     * @return L'identifiant du serveur.
     */
    int getIdServeur() const;

    /**
     * @brief Getter pour le total par journée.
     * @return Le total par journée.
     */
    double getTotalParJournee() const;

    /**
     * @brief Getter pour la date de la recette.
     * @return La date de la recette.
     */
    QDate getDate() const;

    /**
     * @brief Setter pour le code de la recette.
     * @param codeRecette Le nouveau code de la recette.
     */
    void setCodeRecette(int codeRecette);

    /**
     * @brief Setter pour l'identifiant du serveur.
     * @param idServeur Le nouvel identifiant du serveur.
     */
    void setIdServeur(int idServeur);

    /**
     * @brief Setter pour le total par journée.
     * @param totalParJournee Le nouveau total par journée.
     */
    void setTotalParJournee(double totalParJournee);

    /**
     * @brief Setter pour la date de la recette.
     * @param date La nouvelle date de la recette.
     */
    void setDate(QDate date);

private:
    int m_codeRecette; /**< Le code de la recette. */
    int m_idServeur; /**< L'identifiant du serveur. */
    double m_totalParJournee; /**< Le total par journée. */
    QDate m_date; /**< La date de la recette. */
};

#endif
