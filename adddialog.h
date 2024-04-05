#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <QIntValidator>

QT_BEGIN_NAMESPACE
namespace Ui { class AddDialog; }
QT_END_NAMESPACE

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur explicite de la classe AddDialog.
     * @param columnNames La liste des noms de colonnes pour les champs de saisie.
     * @param parent Le widget parent de la boîte de dialogue.
     */
    explicit AddDialog(const QStringList &columnNames, QWidget *parent = nullptr);

    /**
     * @brief Destructeur de la classe AddDialog.
     */
    ~AddDialog();

    /**
     * @brief Récupère les données du produit saisies par l'utilisateur.
     * @return Une liste de chaînes de caractères contenant les données du produit.
     */
    QList<QString> getProductData() const;

private:
    Ui::AddDialog *ui; ///< Interface utilisateur de la boîte de dialogue.
};

#endif
