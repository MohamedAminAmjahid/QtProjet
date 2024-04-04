#include "commande.h"

Commande::Commande() {}

Commande::Commande(const QString &codeCommande, int idServeur, int idProduit, int quantite, const QDate &dateCommande)
    : idServeur_(idServeur), idProduit_(idProduit), quantite_(quantite), codeCommande_(codeCommande), dateCommande_(dateCommande) {}

int Commande::idServeur() const {
    return idServeur_;
}

int Commande::idProduit() const {
    return idProduit_;
}

int Commande::quantite() const {
    return quantite_;
}

QString Commande::codeCommande() const {
    return codeCommande_;
}

QDate Commande::dateCommande() const {
    return dateCommande_;
}

void Commande::setIdServeur(int idServeur) {
    idServeur_ = idServeur;
}

void Commande::setIdProduit(int idProduit) {
    idProduit_ = idProduit;
}

void Commande::setQuantite(int quantite) {
    quantite_ = quantite;
}

void Commande::setCodeCommande(const QString &codeCommande) {
    codeCommande_ = codeCommande;
}

void Commande::setDateCommande(const QDate &dateCommande) {
    dateCommande_ = dateCommande;
}
