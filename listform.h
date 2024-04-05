#ifndef LISTFORM_H
#define LISTFORM_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QXmlStreamWriter>

namespace Ui {
class ListForm;
}

class ListForm : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur de la classe ListForm.
     * @param parent Le widget parent (par défaut : nullptr).
     */
    explicit ListForm(QWidget *parent = nullptr);

    /**
     * @brief Destructeur de la classe ListForm.
     */
    ~ListForm();

    /**
     * @brief Affiche les données dans le tableau.
     * @param dataList La liste des données à afficher.
     * @param columnNames La liste des noms de colonnes.
     */
    void displayData(const QList<QStringList> &dataList, const QStringList &columnNames);

    /**
     * @brief Enregistre les données actuellement affichées dans un fichier XML.
     */
    void saveToXml();

private:
    Ui::ListForm *ui; /**< Interface utilisateur de la classe. */
};

#endif
