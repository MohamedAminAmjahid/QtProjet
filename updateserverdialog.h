#ifndef UPDATESERVERDIALOG_H
#define UPDATESERVERDIALOG_H

#include <QDialog>
#include <databasemanager.h>

namespace Ui {
class UpdateServerDialog;
}

/**
 * @brief La classe UpdateServerDialog permet de mettre à jour les informations d'un serveur dans le système.
 */
class UpdateServerDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur de la classe UpdateServerDialog.
     * @param entityCodes La liste des codes d'entité disponibles.
     * @param parent Le widget parent.
     */
    explicit UpdateServerDialog(const QStringList &entityCodes, QWidget *parent = nullptr);

    /**
     * @brief Destructeur de la classe UpdateServerDialog.
     */
    ~UpdateServerDialog();

    /**
     * @brief Obtient le code d'entité sélectionné.
     * @return Le code d'entité sélectionné.
     */
    QString getSelectedCode() const;

    /**
     * @brief Obtient les données du serveur à mettre à jour.
     * @return Une liste contenant les données du serveur à mettre à jour.
     */
    QList<QString> getServerData() const;

    /**
     * @brief Définit si les champs sont en lecture seule ou non.
     * @param readOnly true pour définir les champs en lecture seule, sinon false.
     */
    void setFieldsReadOnly(bool readOnly);

public slots:
    /**
     * @brief Définit les détails du serveur.
     * @param login Le nom d'utilisateur du serveur.
     * @param password Le mot de passe du serveur.
     * @param cin Le numéro de carte d'identité du serveur.
     */
    void setServerDetails(const QString &login, const QString &password, const QString &cin);

signals:
    /**
     * @brief Signale un changement de code sélectionné.
     * @param code Le nouveau code sélectionné.
     */
    void selectedCodeChanged(int code);

private slots:
    /**
     * @brief Appelée lorsque l'index de la liste déroulante change.
     * @param index Le nouvel index sélectionné.
     */
    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::UpdateServerDialog *ui; /**< Interface utilisateur de la boîte de dialogue de mise à jour de serveur. */
    DatabaseManager databaseManager_; /**< Gestionnaire de base de données. */
};

#endif
