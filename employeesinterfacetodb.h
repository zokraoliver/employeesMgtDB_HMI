#pragma once

#include "employeesdbmanager.h"
#include "employeesmanager.h"
#include <QObject>

#include "employee.h"
#include "monthlypaidemployee.h"
#include "hourlypaidemployee.h"
#include "salesemployee.h"

#ifndef EMPLOYEESINTERFACETODB_H
#define EMPLOYEESINTERFACETODB_H

/* This class comes between the presenter on one side and,
 * on the other side, the DB manager and Employees Manager.
 * The update methods work on 2 levels, on the memory
 * represented by the employees manager, and on the DB
 * represented by the QJsonDocument structure
 * On saving, only a write operation applied on this QJsonDocument,
 * make the DB file updated.
 * Note that the EmployeesManager class managing the memory is
 * to allow the interaction with the user.
*/

class EmployeesInterfaceToDB: public QObject{
    friend class Presenter_QML;
    Q_OBJECT
public:
    //constructor shall instantiates: all the employees from the database
    // the em is not destroyed on import, instead all the records are deleted from it then it is passed to be used again (this will avoid memory crash)
    EmployeesInterfaceToDB(const QString &filename, EmployeesManager* em_old=NULL, QObject *object=0);
    ~EmployeesInterfaceToDB();

    EmployeesManager* get_ptr_to_employees_manager();//used for import

    void updateAll(); // to write the QJSONDoc structure into the Json file when saving

    //int getIndex_byID(int id);
    Employee* getEmployee_byIndex(int i);
    Employee* getEmployee_byID(int i);
    int getIndex_byID(int id);

signals:
    /*todo*/ //_RecordChanged(int index); // no need, for now, instead I will emit one signal just to update the model representation
    void _DBModified();
public slots:
    /*todo*/
    //On_PresenterRecordChanged(int index);
    //to define later the parameters that come from the fileDialog
    // for now I will rewrite all the record

    void updateRecordName(int index, QString n); //update the model (the employee info) on every signal received, and update the JSonDoc structure
    void updateRecordID(int index, int id);
    void updateRecordSSN(int index, int ssn);
    void updateRecordTel(int index, QString tel);

    void updateRecordContratType(int index, int ct);
    //change the memory structure then write, but we are not using it
    //because we are removing the record then adding it in the qml file
    void updateRecordContratType_dump(int index, int ct);//just to write in the dbfile

    void updateRecordMonthlyCompensation(int index, double mc);
    void udpateRecordHourlyCompensation(int index, double hc);
    void updateRecordDoneHours(int index, double nhrs);
    void updateRecordBonusPercentage(int index, double bp);
    void updateRecordRelaizedOutput(int index, double output);
    void updateRecordOutcomeClaim(int index, bool claim);
    void updateRecordSalary(int ix);

    void addRecord_MEmpl(int id=0, QString name="",
                         int ssn=0, QString tel="",
                         double mc=0);
    void addRecord_HEmpl(int id=0, QString name="",
                         int ssn=0, QString tel="",
                         double hc=0, double nhrs=0);
    void addRecord_SEmpl(int id=0, QString name="",
                         int ssn=0, QString tel="",
                         double mc=0, double bp=0,
                         double outcome=0, bool claim=false);
    void rmvRecord(int index);
    void rmvRecord_byID(int id);
    int get_EmployeesNumber();

    void On_Saving();

public: //*to check* so that _em and _db could be called from the destructor of the presenter
     EmployeesDBManager *_db;
     EmployeesManager *_em; //*todo* maybe transfroming it to static could be a way to optimize the code

};

#endif // EMPLOYEESINTERFACETODB_H

