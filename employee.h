#pragma once
#include<QString>
#include <QDebug>

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

class Employee{

public:

    Employee(QString Name, int SSN, QString TelNum, int ctype, int id);
    virtual ~Employee();
    Employee(const Employee& e);

    void set_id(int id);
    void set_name(QString n);
    void set_ssn(int s);
    void set_tel(QString t);
    void set_ctype(int ct);

    int get_id();
    int get_ssn();
    QString get_name();
    QString get_tel();
    int get_ctype();

    int get_ID();

    virtual double getSalary()=0;
    virtual void setSalary(double Sal)=0;
    virtual void updateSalary()=0;


protected:
    int _id;//*todo* to create a kind of _id verification and update process
    QString _name;
    int _ssn;
    QString _tel;
    int _contratType; // 0=>monthlypaid, 1=>hourlypaid, 2=>sales
    double _salary;

public:
    static int _ID;
    //*todo* It is public so we can access it from the manager, must find a more suitable way

};


#endif //EMPLOYEE_H
