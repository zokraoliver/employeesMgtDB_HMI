#include "monthlypaidemployee.h"

MonthlyPaidEmployee::MonthlyPaidEmployee(QString Name, int SSN,
                                         QString TelNum,int ctype,
                                         int id,
                                         double mc=0):Employee(Name,SSN,TelNum,ctype,id){
    _monthlyCompensation=mc;
    _salary=mc;
    //*todo* to find a way better and avoid calculating salary inside the constructor
   _contratType=0; //to force it
}

MonthlyPaidEmployee::~MonthlyPaidEmployee(){
    qDebug()<<"a monthly paid employee is destroyed! \n";
}
MonthlyPaidEmployee::MonthlyPaidEmployee(const MonthlyPaidEmployee& e):Employee(e){
    _monthlyCompensation=e._monthlyCompensation;
}

double MonthlyPaidEmployee::getSalary(){
    return _monthlyCompensation;
}

void MonthlyPaidEmployee::setSalary(double Sal){
    _monthlyCompensation=Sal;
    _salary=_monthlyCompensation;
}

double MonthlyPaidEmployee::get_MonthlyCompensation(){
    return _monthlyCompensation;
}

void MonthlyPaidEmployee::updateSalary(){
    _salary=_monthlyCompensation;
}
