#pragma once
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonParseError>


#ifndef EMPLOYEESDBMANAGER_H
#define EMPLOYEESDBMANAGER_H

/* This class manages the read/writes operation from and to a JSON file. */
//*todo* to optimize the number of access to the file
//*todo* to consider the case of very big files and to treat the case we need memory buffers

class EmployeesDBManager{

public:
    EmployeesDBManager(const QString &fileName);
    ~EmployeesDBManager();

    void removeRecord(int id); //but it is not really useful for this phase of the project because the removal is made in memory
    void addToRecord(QString id,QString key, QLatin1String value); //modify the QJsonDocument
    void updateDB(); //erase and rewrite the QJsonDocument on the DB file

    QString getRecord(int index, const QString key); //to ameliorate: use QJsonDocument in Qml
    int getRecordsCount();

    QJsonDocument get_employeesDB(){
        return _employeesDB;
    }

private:
    QJsonDocument _employeesDB;
    QString _DBfile;

};

#endif // EMPLOYEESDBMANAGER_H
