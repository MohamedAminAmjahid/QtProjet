#ifndef RECETTE_H
#define RECETTE_H

#include <QString>
#include <QDate>

class Recette {
public:
    Recette();
    Recette(int codeRecette, int idServeur, double totalParJournee, QDate date);

    int getCodeRecette() const;
    int getIdServeur() const;
    double getTotalParJournee() const;
    QDate getDate() const;

    void setCodeRecette(int codeRecette);
    void setIdServeur(int idServeur);
    void setTotalParJournee(double totalParJournee);
    void setDate(QDate date);

private:
    int m_codeRecette;
    int m_idServeur;
    double m_totalParJournee;
    QDate m_date;
};

#endif // RECETTE_H
