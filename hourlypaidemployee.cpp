#include "hourlypaidemployee.h"

HourlyPaidEmployee::HourlyPaidEmployee(QString Name, int SSN,
                                       QString TelNum,int ctype,
                                       int id,double hc=0,
                                       double nhrs=0):Employee(Name, SSN,TelNum, ctype,id){
    _hourlyCompensation=hc;
    _doneHours=nhrs;
    _salary=_doneHours*_hourlyCompensation;
    //*todo* to find a way better and avoid calculating salary inside the constructor
    _contratType=1; // to force it
}

HourlyPaidEmployee::~HourlyPaidEmployee(){
    qDebug()<<"an hourly paid employee is destroyed! \n";
}

HourlyPaidEmployee::HourlyPaidEmployee(const HourlyPaidEmployee& e):Employee(e){
    _doneHours=e._doneHours;
    _hourlyCompensation=e._hourlyCompensation;
}


double HourlyPaidEmployee::getHourlyCompensation(){
    return _hourlyCompensation;
}

void HourlyPaidEmployee::setHourlyCompensation(double hc){
    _hourlyCompensation=hc;
}

double HourlyPaidEmployee::getDoneHours(){
    return _doneHours;
}

void HourlyPaidEmployee::setDoneHours(double nHrs){
    _doneHours=nHrs;
}

double HourlyPaidEmployee::getSalary(){
    return _doneHours*_hourlyCompensation;
}

void HourlyPaidEmployee::setSalary(double NumHours){
    _doneHours=NumHours;
    _salary=_doneHours*_hourlyCompensation;
}

void HourlyPaidEmployee::updateSalary(){
    _salary=_doneHours*_hourlyCompensation;
}
