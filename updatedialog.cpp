/**
 * @file updatedialog.cpp
 */

#include "updatedialog.h"
#include "ui_updatedialog.h"
#include "QSqlQuery"

/**
 * @brief Constructeur de la classe UpdateDialog
 * @param entityCodes Liste des codes d'entité
 * @param parent Widget parent
 */
UpdateDialog::UpdateDialog(const QStringList &entityCodes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateDialog)
{
    ui->setupUi(this);

    // Ajout des codes d'entité à la combobox
    ui->comboBox->addItems(entityCodes);

    // Connexion du signal currentIndexChanged de la combobox à la fonction lambda
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) {
        QString selectedCode = ui->comboBox->currentText();
        emit selectedCodeChanged(selectedCode.toInt());
    });
}

/**
 * @brief Destructeur de la classe UpdateDialog
 */
UpdateDialog::~UpdateDialog()
{
    delete ui;
}

/**
 * @brief Obtient le code sélectionné dans la combobox
 * @return Code sélectionné
 */
QString UpdateDialog::getSelectedCode() const
{
    return ui->comboBox->currentText();
}

/**
 * @brief Définit les détails du produit
 * @param designation Désignation du produit
 * @param price Prix du produit
 * @param quantity Quantité du produit
 */
void UpdateDialog::setProductDetails(const QString &designation, double price, int quantity)
{
    ui->lineEdit_designation->setText(designation);
    ui->lineEdit_price->setText(QString::number(price));
    ui->lineEdit_quantity->setText(QString::number(quantity));
}

/**
 * @brief Slot déclenché lors du changement de sélection dans la combobox
 * @param index Nouvel index sélectionné
 */
void UpdateDialog::on_comboBox_currentIndexChanged(int index)
{
    // Obtention du code sélectionné
    QString selectedCode = QString::number(index + 1);

    // Récupération des détails du produit depuis la base de données
    QSqlQuery query = databaseManager_.selectProductDetails(getSelectedCode());

    // Si la requête a réussi, mettre à jour les détails du produit
    if (query.next()) {
        QString designation = query.value("designation").toString();
        double price = query.value("prix").toDouble();
        int quantity = query.value("quantitestock").toInt();

        this->setProductDetails(designation, price, quantity);
    } else {
        qDebug() << "No product found for code:" << index;
    }
}

/**
 * @brief Obtient les données du produit
 * @return Liste contenant la désignation, le prix et la quantité du produit
 */
QList<QString> UpdateDialog::getProductData() const
{
    QList<QString> productData;
    productData << ui->lineEdit_designation->text();
    productData << ui->lineEdit_price->text();
    productData << ui->lineEdit_quantity->text();
    return productData;
}

/**
 * @brief Définit la lecture seule des champs
 * @param readOnly Si vrai, les champs sont en lecture seule ; sinon, ils sont éditables
 */
void UpdateDialog::setFieldsReadOnly(bool readOnly)
{
    ui->lineEdit_designation->setReadOnly(readOnly);
    ui->lineEdit_price->setReadOnly(readOnly);
    ui->lineEdit_quantity->setReadOnly(readOnly);
}
