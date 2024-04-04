#ifndef LISTFORM_H
#define LISTFORM_H

#include <QMainWindow>

namespace Ui {
class ListForm;
}

class ListForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit ListForm(QWidget *parent = nullptr);
    ~ListForm();

    void displayData(const QList<QStringList> &dataList, const QStringList &columnNames);

private:
    Ui::ListForm *ui;
};

#endif // LISTFORM_H
