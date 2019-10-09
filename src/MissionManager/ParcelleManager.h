#include <QDialog>
//#include "DbManager.h"
#include "MissionController.h"

#include <QSqlTableModel>

#ifndef PARCELLEMANAGER_H
#define PARCELLEMANAGER_H

namespace Ui {
class ParcelleManager;
}

class ParcelleManager : public QDialog
{
    Q_OBJECT

public:
    explicit ParcelleManager(QWidget *parent = nullptr);
    explicit ParcelleManager(QWidget *parent, MissionController *missionControler);

    ~ParcelleManager();

private slots:
    void deleteParcelle();
    void addToMission();
    void addParcelle();
    void saveToDb();

private:
    void closeEvent(QCloseEvent *bar);
    QList<QString> *toDel;
    Ui::ParcelleManager *ui;
    MissionController *missionControler;
};

#endif // PARCELLEMANAGER_H