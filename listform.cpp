#include "listform.h"
#include "ui_listform.h"

/**
 * @brief Constructeur de la classe ListForm.
 * @param parent Le widget parent (par défaut : nullptr).
 */
ListForm::ListForm(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ListForm)
{
    ui->setupUi(this);

    // Connecte le signal de clic du bouton saveXML à la fonction saveToXml()
    connect(ui->saveXML, &QPushButton::clicked, this, &ListForm::saveToXml);
}

/**
 * @brief Destructeur de la classe ListForm.
 */
ListForm::~ListForm()
{
    delete ui;
}

/**
 * @brief Affiche les données dans la tableWidget.
 * @param dataList La liste des données à afficher.
 * @param columnNames Les noms des colonnes.
 */
void ListForm::displayData(const QList<QStringList> &dataList, const QStringList &columnNames)
{
    // Efface le contenu de la tableWidget
    ui->tableWidget->clearContents();
    // Définit le nombre de lignes de la tableWidget
    ui->tableWidget->setRowCount(dataList.size());

    // Définit le nombre de colonnes et les en-têtes de colonnes de la tableWidget
    ui->tableWidget->setColumnCount(columnNames.size());
    ui->tableWidget->setHorizontalHeaderLabels(columnNames);

    // Remplit la tableWidget avec les données
    int row = 0;
    for (const QStringList &rowData : dataList) {
        int column = 0;
        for (const QString &data : rowData) {
            // Crée un QTableWidgetItem avec les données et le place dans la tableWidget
            QTableWidgetItem *itemData = new QTableWidgetItem(data);
            itemData->setFlags(itemData->flags() & ~Qt::ItemIsEditable);
            ui->tableWidget->setItem(row, column, itemData);
            ++column;
        }
        ++row;
    }
    // Ajuste la largeur des colonnes de la tableWidget en fonction du contenu
    ui->tableWidget->resizeColumnsToContents();
}

/**
 * @brief Enregistre les données de la tableWidget dans un fichier XML.
 */
void ListForm::saveToXml()
{
    // Demande à l'utilisateur de choisir un emplacement pour enregistrer le fichier XML
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save XML File"), QDir::homePath(), tr("XML Files (*.xml)"));
    if (filePath.isEmpty())
        return;

    // Ouvre le fichier XML en mode écriture
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Cannot open file for writing:" << file.errorString();
        return;
    }

    // Crée un écrivain XML pour écrire dans le fichier
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("data");

    // Parcourt la tableWidget et écrit les données dans le fichier XML
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        xmlWriter.writeStartElement("row");
        for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
            xmlWriter.writeStartElement("column");
            xmlWriter.writeCharacters(ui->tableWidget->item(row, col)->text());
            xmlWriter.writeEndElement();
        }
        xmlWriter.writeEndElement();
    }

    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();

    qDebug() << "XML file saved successfully:" << filePath;
}
