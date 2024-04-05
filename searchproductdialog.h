#ifndef SEARCHPRODUCTDIALOG_H
#define SEARCHPRODUCTDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QListWidgetItem>

namespace Ui {
class SearchProductDialog;
}

/**
 * @brief La classe SearchProductDialog représente une boîte de dialogue pour rechercher des produits.
 * Elle permet à l'utilisateur de saisir un mot-clé et d'effectuer une recherche dans la base de données.
 */
class SearchProductDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur de la classe SearchProductDialog.
     * @param parent Le widget parent de la boîte de dialogue.
     */
    explicit SearchProductDialog(QWidget *parent = nullptr);

    /**
     * @brief Destructeur de la classe SearchProductDialog.
     */
    ~SearchProductDialog();

private slots:
    /**
     * @brief Slot appelé lorsque le bouton de recherche est cliqué.
     * Effectue une recherche dans la base de données en utilisant le mot-clé saisi par l'utilisateur.
     */
    void on_pushButton_search_clicked();

private:
    Ui::SearchProductDialog *ui; /**< Interface utilisateur de la boîte de dialogue. */

    /**
     * @brief Effectue une recherche dans la base de données en utilisant le champ spécifié et le mot-clé fourni.
     * @param fieldName Le nom du champ dans lequel effectuer la recherche.
     * @param keyword Le mot-clé à rechercher.
     */
    void searchProducts(const QString &fieldName, const QString &keyword);

    /**
     * @brief Affiche les résultats de la recherche dans l'interface utilisateur.
     * @param query La requête contenant les résultats de la recherche.
     */
    void displaySearchResults(QSqlQuery &query);
};

#endif
