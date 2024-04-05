#include "adddialog.h"
#include "ui_adddialog.h"
#include <QLabel>
#include <QLineEdit>

/**
 * @brief Constructeur de la classe AddDialog.
 * @param columnNames Liste des noms de colonnes pour les champs d'entrée.
 * @param parent Widget parent de la boîte de dialogue.
 */
AddDialog::AddDialog(const QStringList &columnNames, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);

    // Ajouter des étiquettes et des champs de texte pour chaque colonne
    for (const QString &columnName : columnNames) {
        QLabel *label = new QLabel(columnName, this);
        QLineEdit *lineEdit = new QLineEdit(this);
        ui->formLayout->addRow(label, lineEdit);
        // Ajouter un QValidator au champ de quantité
        if (columnName.toLower() == "quantity") {
            // Créer un QIntValidator pour restreindre les entrées à des nombres entiers positifs
            QIntValidator *validator = new QIntValidator(0, std::numeric_limits<int>::max(), this);
            // Appliquer le QValidator au champ de quantité
            lineEdit->setValidator(validator);
        }
    }
}

/**
 * @brief Destructeur de la classe AddDialog.
 */
AddDialog::~AddDialog()
{
    delete ui;
}

/**
 * @brief Récupère les données du produit saisies dans le formulaire.
 * @return Liste des données du produit saisies.
 */
QList<QString> AddDialog::getProductData() const
{
    QList<QString> productData;
    // Parcourir chaque ligne du formulaire
    for (int i = 0; i < ui->formLayout->rowCount(); ++i) {
        // Récupérer le champ de texte correspondant à chaque ligne
        QLineEdit *lineEdit = qobject_cast<QLineEdit*>(ui->formLayout->itemAt(i, QFormLayout::FieldRole)->widget());
        if (lineEdit) {
            // Ajouter le texte du champ de texte à la liste des données du produit
            productData << lineEdit->text();
        }
    }
    return productData;
}
