#include "salesemployee.h"

SalesEmployee::SalesEmployee(QString Name, int SSN,
                             QString TelNum,int ctype,
                             int id, double mc=0,
                             double bp=0):Employee(Name,SSN, TelNum,ctype,id){
    _monthlyCompensation=mc;
    _bonusPercentage=bp;
    _outcomeClaim=false;
    _realizedOutcome=0;
    if(_outcomeClaim==true){
         _salary=_monthlyCompensation+_bonusPercentage*_realizedOutcome;
    }
    else{
         _salary=_monthlyCompensation;
    }
    //*todo* to find a way better and avoid calculating salary inside the constructor
    _contratType=2; //to force it
}

SalesEmployee::~SalesEmployee(){
    qDebug()<<"Sales Employee is destroyed ! \n";
}

SalesEmployee::SalesEmployee(const SalesEmployee& e): Employee(e){
    _monthlyCompensation=e._monthlyCompensation;
    _bonusPercentage=e._bonusPercentage;
    _outcomeClaim=e._outcomeClaim;
    _realizedOutcome=e._realizedOutcome;
}

double SalesEmployee::getMonthlyCompensation(){
    return _monthlyCompensation;
}

void SalesEmployee::setMonthlyCompensation(double mc){
    _monthlyCompensation=mc;
}

double SalesEmployee::getBonusPercentage(){
    return _bonusPercentage;
}

void SalesEmployee::setBonusPercentage(double bp){
    _bonusPercentage=bp;
}



double SalesEmployee::getSalary(){
    if(_outcomeClaim==true){
         return _monthlyCompensation+_bonusPercentage*_realizedOutcome;
    }
    else{
         return _monthlyCompensation;
    }
}

void SalesEmployee::setSalary(double outcome){
    this->setRealizedOutcome(outcome);
    if(_outcomeClaim==true){
         _salary=_monthlyCompensation+_bonusPercentage*_realizedOutcome;
    }
    else{
         _salary=_monthlyCompensation;
    }
}



void SalesEmployee::resetSalaryParam(double mc, double bp){
    _monthlyCompensation=mc;
    _bonusPercentage=bp;
}

void SalesEmployee::setRealizedOutcome(double o){
    _realizedOutcome=o;
}

double SalesEmployee::getRealizedOutcome(){
    return _realizedOutcome;
}

void SalesEmployee::setOutcomeClaim(){
    _outcomeClaim=true;
}

bool SalesEmployee::getOutcomeClaim(){
    return _outcomeClaim;
}

void SalesEmployee::resetOutcomeClaim(){
    _outcomeClaim=false;
}

void SalesEmployee::updateSalary(){
    if(_outcomeClaim==true){
         _salary=_monthlyCompensation+_bonusPercentage*_realizedOutcome;
    }
    else{
         _salary=_monthlyCompensation;
    }
}
