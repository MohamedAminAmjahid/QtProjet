// updatedialog.cpp
#include "updatedialog.h"
#include "ui_updatedialog.h"
#include "QSqlQuery"

UpdateDialog::UpdateDialog(const QStringList &entityCodes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateDialog)
{
    ui->setupUi(this);

    // Remplir la combobox avec les codes des entités
    ui->comboBox->addItems(entityCodes);

    // Connecter le signal de sélection de la combobox à une fonction de mise à jour des détails
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) {
        QString selectedCode = ui->comboBox->currentText();
        // Émettre un signal pour indiquer que le code sélectionné a changé
        emit selectedCodeChanged(selectedCode.toInt());
    });
}

UpdateDialog::~UpdateDialog()
{
    delete ui;
}

QString UpdateDialog::getSelectedCode() const
{
    return ui->comboBox->currentText();
}

void UpdateDialog::setProductDetails(const QString &designation, double price, int quantity)
{
    // Remplir les zones de texte avec les détails du produit
    ui->lineEdit_designation->setText(designation);
    ui->lineEdit_price->setText(QString::number(price));
    ui->lineEdit_quantity->setText(QString::number(quantity));
}

void UpdateDialog::on_comboBox_currentIndexChanged(int index)
{
    QString selectedCode = QString::number(index + 1); // Convertir l'indice en QString

    QSqlQuery query = databaseManager_.selectProductDetails(getSelectedCode());

    // Vérifier si la requête a retourné des résultats
    if (query.next()) {
        // Récupérer les détails du produit à partir du résultat de la requête
        QString designation = query.value("designation").toString();
        double price = query.value("prix").toDouble();
        int quantity = query.value("quantitestock").toInt();

        // Afficher les détails du produit dans l'UpdateDialog
        this->setProductDetails(designation, price, quantity);
    } else {
        qDebug() << "No product found for code:" << index;
    }
}

QList<QString> UpdateDialog::getProductData() const
{
    QList<QString> productData;
    productData << ui->lineEdit_designation->text();
    productData << ui->lineEdit_price->text();
    productData << ui->lineEdit_quantity->text();
    return productData;
}

void UpdateDialog::setFieldsReadOnly(bool readOnly)
{
    ui->lineEdit_designation->setReadOnly(readOnly);
    ui->lineEdit_price->setReadOnly(readOnly);
    ui->lineEdit_quantity->setReadOnly(readOnly);
}
