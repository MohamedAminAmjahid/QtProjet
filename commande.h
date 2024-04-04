#ifndef COMMANDE_H
#define COMMANDE_H

#include <QString>
#include <QDate>

class Commande
{
public:
    Commande();
    Commande(const QString &codeCommande, int idServeur, int idProduit, int quantite, const QDate &dateCommande);

    int idServeur() const;
    int idProduit() const;
    int quantite() const;
    QString codeCommande() const;
    QDate dateCommande() const;

    void setIdServeur(int idServeur);
    void setIdProduit(int idProduit);
    void setQuantite(int quantite);
    void setCodeCommande(const QString &codeCommande);
    void setDateCommande(const QDate &dateCommande);

private:
    int idServeur_;
    int idProduit_;
    int quantite_;
    QString codeCommande_;
    QDate dateCommande_;
};

#endif // COMMANDE_H
