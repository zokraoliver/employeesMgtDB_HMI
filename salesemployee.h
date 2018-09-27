#ifndef SALESEMPLOYEE_H
#define SALESEMPLOYEE_H
#include "employee.h"

class SalesEmployee:public Employee{

public:
    SalesEmployee(QString Name, int SSN, QString TelNum,int ctype,
                  int id, double mc, double bp);
    ~SalesEmployee();
    SalesEmployee(const SalesEmployee& e);

    double getMonthlyCompensation();
    void setMonthlyCompensation(double mc);

    double getBonusPercentage();
    void setBonusPercentage(double bp);

    double getSalary();
    void setSalary(double outcome);
    void updateSalary();


    void resetSalaryParam(double mc, double bp);
    void setRealizedOutcome(double o);

    double getRealizedOutcome();
    void setOutcomeClaim();

    bool getOutcomeClaim();
    void resetOutcomeClaim();


private:
    double _monthlyCompensation;
    double _bonusPercentage;
    double _realizedOutcome;
    bool _outcomeClaim;
};

#endif // SALESEMPLOYEE_H
