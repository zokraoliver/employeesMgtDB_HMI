#pragma once
#include<QString>

#ifndef MONTHLYPAIDEMPLOYEE_H
#define MONTHLYPAIDEMPLOYEE_H

#include "employee.h"

class MonthlyPaidEmployee:public Employee{

public:
    MonthlyPaidEmployee(QString Name, int SSN, QString TelNum,int ctype, int id, double mc);

    ~MonthlyPaidEmployee();
    MonthlyPaidEmployee(const MonthlyPaidEmployee& e);

    double get_MonthlyCompensation();

    double getSalary();
    void setSalary(double Sal);
    void updateSalary();

private:
    double _monthlyCompensation;
};
#endif // MONTHLYPAIDEMPLOYEE_H
