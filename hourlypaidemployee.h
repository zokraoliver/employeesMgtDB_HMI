
#ifndef HOURLYPAIDEMPLOYEE_H
#define HOURLYPAIDEMPLOYEE_H

#include "employee.h"

class HourlyPaidEmployee:public Employee{

public:
    HourlyPaidEmployee(QString Name, int SSN, QString TelNum,int ctype, int id,double hc, double nhrs);
    ~HourlyPaidEmployee();
    HourlyPaidEmployee(const HourlyPaidEmployee& e);


    double getHourlyCompensation();
    void setHourlyCompensation(double hc);
    double getDoneHours();
    void setDoneHours(double nHrs);

    double getSalary();

    void setSalary(double NumHours);
    void updateSalary();

private:
    double _hourlyCompensation;
    double _doneHours;
};
#endif // HOURLYPAIDEMPLOYEE_H
