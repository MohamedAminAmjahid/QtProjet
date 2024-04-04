// produit.cpp
#include "produit.h"

Produit::Produit() : prix_(0.0), quantiteStock_(0) {}

Produit::Produit(const QString &codeProduit, const QString &designation, double prix, int quantiteStock)
    : codeProduit_(codeProduit), designation_(designation), prix_(prix), quantiteStock_(quantiteStock) {}

QString Produit::codeProduit() const {
    return codeProduit_;
}

QString Produit::designation() const {
    return designation_;
}

double Produit::prix() const {
    return prix_;
}

int Produit::quantiteStock() const {
    return quantiteStock_;
}

void Produit::setCodeProduit(const QString &codeProduit) {
    codeProduit_ = codeProduit;
}

void Produit::setDesignation(const QString &designation) {
    designation_ = designation;
}

void Produit::setPrix(double prix) {
    prix_ = prix;
}

void Produit::setQuantiteStock(int quantiteStock) {
    quantiteStock_ = quantiteStock;
}
