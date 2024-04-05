#ifndef MONTHYEARDIALOG_H
#define MONTHYEARDIALOG_H

#include <QDialog>
#include <QDate>

namespace Ui {
class MonthYearDialog;
}

class MonthYearDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur de la classe MonthYearDialog.
     * @param parent Le widget parent (par défaut : nullptr).
     */
    explicit MonthYearDialog(QWidget *parent = nullptr);

    /**
     * @brief Destructeur de la classe MonthYearDialog.
     */
    ~MonthYearDialog();

    /**
     * @brief Renvoie la date sélectionnée.
     * @return La date sélectionnée.
     */
    QDate selectedDate() const;

private:
    Ui::MonthYearDialog *ui; /**< Interface utilisateur de la classe. */
};

#endif
