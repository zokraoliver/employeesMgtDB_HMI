#pragma once

#include<QList>
#include<QListIterator>
#include "employee.h"
#include "monthlypaidemployee.h"
#include "hourlypaidemployee.h"
#include "salesemployee.h"

#ifndef EMPLOYEESMANAGER_H
#define EMPLOYEESMANAGER_H

/* This class stores the employees of the databases in a memory Qlist structure.
 * It allows the management of the database in memory.
 */
//*todo* to consider the case of vey big files. In this case not all the DB must be dumped in memory.

class EmployeesManager{
public:
    EmployeesManager();
    ~EmployeesManager();
    //EmployeesManager(const EmployeesManager& );
    // **todo, to implement a coy constructor if necessary

    void addMEmployee(QString Name, int SSN, QString TelNum,int ctype, int id,double mc);
    void addHEmployee(QString Name, int SSN, QString TelNum,int ctype, int id,double hc, double nhrs);
    void addSEmployee(QString Name, int SSN, QString TelNum,int ctype, int id,double mc,double bp);
    void SetSalesOutput(int index,double output,bool claim);

    void updateName(int index, QString nam); // to add the other updates
    void updateTel(int index, QString tel);
    void updateSSN(int index, int ssn);
    void updateID(int index, int id);
    void updateCType(int index, int ct);//bit complicated**
    void updateMC(int index, double mc);
    void updateHC(int index, double hc);
    void updateDoneHours(int index, double nhrs);
    void updateBP(int index, double bonus);
    void updateOutput(int index, double output);
    void updateClaim(int index, bool claim);
    void updateSalary(int index);

    int getIndexFromID(int ID);

    QString getName(int index);
    QString getTel(int index);
    int getSSN(int index);
    int getID(int index);
    int getCType(int index);
    double getMC(int index);
    double getHC(int index);
    double getNHRS(int index);
    double getBP(int index);
    double getOutput(int index);
    bool getClaim(int index);
    double getSalary(int index);


    void rmvEmployee(int index);

    void displayContent(); //for debug: it displays the _employees_p_l list elements
    int employeesNumber();

    Employee* getEmployee(int index);

    void reset_ID();

private:
     QList < Employee * > _employees_p_l; //*todo* note that Qlists are not thread safe, to study the case of better alternatives
     static int _employees_count;
};

#endif // EMPLOYEESMANAGER_H
