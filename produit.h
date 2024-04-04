// produit.h
#ifndef PRODUIT_H
#define PRODUIT_H

#include <QString>

class Produit
{
public:
    Produit();
    Produit(const QString &codeProduit, const QString &designation, double prix, int quantiteStock);

    // Getters
    QString codeProduit() const;
    QString designation() const;
    double prix() const;
    int quantiteStock() const;

    // Setters
    void setCodeProduit(const QString &codeProduit);
    void setDesignation(const QString &designation);
    void setPrix(double prix);
    void setQuantiteStock(int quantiteStock);

private:
    QString codeProduit_;
    QString designation_;
    double prix_;
    int quantiteStock_;
};

#endif // PRODUIT_H
