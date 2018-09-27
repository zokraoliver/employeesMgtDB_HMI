#include "employeesmanager.h"

#include <QDebug>

int EmployeesManager::_employees_count=0;

EmployeesManager::EmployeesManager(){}

EmployeesManager::~EmployeesManager(){
    if(_employees_count>0){
        int numberOfEmployees=_employees_count;
        for(int h=numberOfEmployees-1;h>=0;h--){
                delete _employees_p_l.takeAt(0);
                _employees_count--;
               }
    }
}

/*
EmployeesManager::EmployeesManager(const EmployeesManager& em){ // **todo, to recheck
    if(_employees_count!=0){
         for(int i=0;i<_employees_count;i++){
            em._employees_p_l.append(_employees_p_l[i]); // a copy of my pointer
        }
         em._employees_count=_employees_count;
    }
} */  // *todo* to verify if i need a copy constructor

void EmployeesManager::addMEmployee(QString Name, int SSN, QString TelNum,int ctype, int id,double mc){
    MonthlyPaidEmployee *mpEmpl=new MonthlyPaidEmployee(Name, SSN,TelNum,ctype,id,mc);
    Employee *empl=mpEmpl;
    this->_employees_p_l.push_back(empl);
    _employees_count++;
}

void EmployeesManager::addHEmployee(QString Name, int SSN, QString TelNum,int ctype, int id,double hc, double nhrs){
    HourlyPaidEmployee *hpEmpl=new HourlyPaidEmployee(Name, SSN,TelNum,ctype,id,hc,nhrs);
    Employee *empl=hpEmpl;
    this->_employees_p_l.push_back(empl);
    _employees_count++;
}

void EmployeesManager::addSEmployee(QString Name, int SSN, QString TelNum,int ctype, int id,double mc,double bp){
    SalesEmployee *spEmpl=new SalesEmployee(Name, SSN,TelNum,ctype,id,mc,bp);
    Employee *empl=spEmpl;
    this->_employees_p_l.push_back(empl);
    _employees_count++;
}

void EmployeesManager::SetSalesOutput(int index,double output,bool claim){ // ** todo, to change the index to id because it is a list (access by the index from the 0 pos does not exist)
    if(index>=0 && index<_employees_p_l.count()){
        if(this->_employees_p_l[index]->get_ctype()==2){
            SalesEmployee *spEmpl=(SalesEmployee*)this->_employees_p_l[index];
            if(claim==true) spEmpl->setOutcomeClaim();
            spEmpl->setOutcomeClaim();
            this->_employees_p_l[index]->setSalary(output);
        }
        else{
            qDebug()<<"SetSalesOutput does not appply to contracts type different from 2";
        }
    }
    else{
        qDebug()<<"index is out of _employees_p_l range";
    }

}


void EmployeesManager::displayContent(){
    QListIterator<Employee *> l_it(this->_employees_p_l);
    while(l_it.hasNext()){
        Employee *e=l_it.next();
        qDebug()<<"name: "<<e->get_name();
        qDebug()<<"id: "<<e->get_id();
        qDebug()<<"ssn: "<<e->get_ssn();
        qDebug()<<"tel: "<<e->get_tel();
        qDebug()<<"contract type: "<<e->get_ctype();
        qDebug()<<"salary: "<<e->getSalary();
        qDebug()<<'\n';
        qDebug()<<"_ID: "<<e->get_ID();
        qDebug()<<'\n';
    }
}



void EmployeesManager::rmvEmployee(int index){
    if(_employees_count>0 && index>=0){
        if(index<_employees_count-1){
            delete _employees_p_l.takeAt(index);
            _employees_count--;
            qDebug()<<"\n after removing the employee, the content of the list at index is: "<<_employees_p_l[index]->get_id();//get_ID to change
        }
        else if(index==_employees_count-1){
            delete _employees_p_l.takeLast();
            _employees_count--;
            qDebug()<<"\n after removing the employee, the content of the list at index is removed";
        }
        else{
            qDebug()<<"\n Can't remove \n";
        }
        //_employees_p_l.removeAt(index);
    }

}

int EmployeesManager::getIndexFromID(int ID){
    for(int i=0;i<_employees_count;i++){
        if(_employees_p_l[i]->get_id()==ID)
            return i;
    }
    return -1; //in case the index is not found
}

int EmployeesManager::employeesNumber(){
    return _employees_count;
}

QString EmployeesManager::getName(int index){
    return this->_employees_p_l[index]->get_name();
}

QString EmployeesManager::getTel(int index){
    return this->_employees_p_l[index]->get_tel();
}

int EmployeesManager::getSSN(int index){
    return this->_employees_p_l[index]->get_ssn();
}

int EmployeesManager::getID(int index){
    return this->_employees_p_l[index]->get_id();
}

int EmployeesManager::getCType(int index){
    return this->_employees_p_l[index]->get_ctype();
}

double EmployeesManager::getMC(int index){
    int theCT=this->getCType(index);
    switch(theCT){
    case 0:
    {
        MonthlyPaidEmployee* mEmpl=dynamic_cast<MonthlyPaidEmployee*>(this->getEmployee(index));
        return mEmpl->get_MonthlyCompensation();
        break;
    }
    case 1:
    {
        HourlyPaidEmployee* hEmpl=dynamic_cast<HourlyPaidEmployee*>(this->getEmployee(index));
        qDebug()<<"Monthly Compensation does not exist for Hourly Paid Employees Contract, the hourly compensation is then: \n";
        return hEmpl->getHourlyCompensation();
        break;
    }
    case 2:
    {
        SalesEmployee* sEmpl=dynamic_cast<SalesEmployee*>(this->getEmployee(index));
        return sEmpl->getMonthlyCompensation();
        break;
    }

    default:
    {
        qDebug()<<"Unknown type of contract! or it is not found at least! \n";
        return -1;
        // *todo*
    }
    }
    //return -1;
}

double EmployeesManager::getHC(int index){
    int theCT=this->getCType(index);
    switch(theCT){
    case 0:
    {
        MonthlyPaidEmployee* mEmpl=(MonthlyPaidEmployee*)this->getEmployee(index);
        qDebug()<<"Hourly Compensation does not exist for Hourly Paid Employees Contract, the monthly compensation is then: \n";
        return mEmpl->get_MonthlyCompensation();
    }
    case 1:
    {
        HourlyPaidEmployee* hEmpl=(HourlyPaidEmployee*)this->getEmployee(index);
        return hEmpl->getHourlyCompensation();
    }
    case 2:
    {
        SalesEmployee* sEmpl=(SalesEmployee*)this->getEmployee(index);
        qDebug()<<"Hourly Compensation does not exist for Sales Employees Contract, the monthly compensation is then: \n";
        return sEmpl->getMonthlyCompensation();
    }
    default:
    {
        qDebug()<<"Unknown type of contract! or it is not found at least! \n";
        return -1;
        // *todo*
    }
    }
}

double EmployeesManager::getNHRS(int index){
    int theCT=this->getCType(index);
    switch(theCT){
    case 0:
    {
        qDebug()<<"Number of hours does not exist for Hourly Paid Employees Contract \n";
        break;
    }
    case 1:
    {
        HourlyPaidEmployee* hEmpl=(HourlyPaidEmployee*)this->getEmployee(index);
        return hEmpl->getDoneHours();
    }
    case 2:
    {
        qDebug()<<"Number of hours does not exist for Sales Employees Contract \n";
        break;
    }
    default:
    {
        qDebug()<<"Unknown type of contract! or it is not found at least! \n";
        // *todo*
    }
    }
    return 0;
}

double EmployeesManager::getBP(int index){
    int theCT=this->getCType(index);
    switch(theCT){
    case 0:
    {
        qDebug()<<"Bonus Percentage does not exist for Monthly Paid Employees Contract, the hourly compensation is then: \n";
        break;
    }
    case 1:
    {
        qDebug()<<"Bonus Percentage does not exist for Hourly Paid Employees Contract, the hourly compensation is then: \n";
        break;
    }
    case 2:
    {
        SalesEmployee* sEmpl=(SalesEmployee*)this->getEmployee(index);
        return sEmpl->getBonusPercentage();
    }
    default:
    {
        qDebug()<<"Unknown type of contract! or it is not found at least! \n";
        return -1;
        // *todo*
    }
    }
    return 0; //*todo* to launch exceptions
}

double EmployeesManager::getOutput(int index){
    int theCT=this->getCType(index);
    switch(theCT){
    case 0:
    {
        qDebug()<<"Realized Output does not exist for Monthly Paid Employees Contract, the hourly compensation is then: \n";
        break;
    }
    case 1:
    {
        qDebug()<<"Realized Output does not exist for Hourly Paid Employees Contract, the hourly compensation is then: \n";
        break;
    }
    case 2:
    {
        SalesEmployee* sEmpl=(SalesEmployee*)this->getEmployee(index);
        return sEmpl->getRealizedOutcome();
    }
    default:
    {
        qDebug()<<"Unknown type of contract! or it is not found at least! \n";
        return -1;
        // *todo*
    }
    }
    return 0; //*todo* to launch exceptions
}

bool EmployeesManager::getClaim(int index){
    int theCT=this->getCType(index);
    switch(theCT){
    case 0:
    {
        qDebug()<<"Output Claim does not exist for Monthly Paid Employees Contract, the hourly compensation is then: \n";
        break;
    }
    case 1:
    {
        qDebug()<<"Output Claim does not exist for Hourly Paid Employees Contract, the hourly compensation is then: \n";
        break;
    }
    case 2:
    {
        SalesEmployee* sEmpl=(SalesEmployee*)this->getEmployee(index);
        return sEmpl->getOutcomeClaim();
    }
    default:
    {
        qDebug()<<"Unknown type of contract! or it is not found at least! \n";
        return -1;
        // *todo*
    }
    }
    return 0; //*todo* to launch exceptions
}

double EmployeesManager::getSalary(int index){
    return this->_employees_p_l[index]->getSalary();
}

void EmployeesManager::updateName(int index, QString n){
    this->_employees_p_l[index]->set_name(n);
}

void EmployeesManager::updateTel(int index, QString tel){
    this->_employees_p_l[index]->set_tel(tel);
}

void EmployeesManager::updateSSN(int index, int ssn){
    this->_employees_p_l[index]->set_ssn(ssn);
}

void EmployeesManager::updateID(int index, int id){
    this->_employees_p_l[index]->set_id(id);
}

void EmployeesManager::updateCType(int index, int ct){
//*todo* later on, to avoid enter this function if no change happened

    //we will have to get the parameters of the employee, destroy it,
    //reconstruct it with the right parameters then finally add it to the list

    QString name_t,tel_t; //_t for transfering variable
    int ssn_t,id_;

    name_t=this->getName(index);
    tel_t=this->getTel(index);
    ssn_t=this->getSSN(index);
    id_=this->getID(index);

    this->_employees_p_l[index]->set_ctype(ct);

    switch(ct){// todo
    case 0:
        this->addMEmployee(name_t,ssn_t,tel_t,ct,id_,0);
        break;
    case 1:
        this->addHEmployee(name_t,ssn_t,tel_t,ct,id_,0,0);
        break;
    case 2:
        this->addSEmployee(name_t,ssn_t,tel_t,ct,id_,0,0);
        break;
    default:
        qDebug()<<"The entered contract type does not exist \n";
    }
    this->rmvEmployee(index);
}
void EmployeesManager::updateMC(int index, double mc){
    int theCT=this->getCType(index);
    switch(theCT){
    case 0:
    {
        MonthlyPaidEmployee* mEmpl=(MonthlyPaidEmployee*)this->getEmployee(index);
        mEmpl->setSalary(mc);
        break;
    }
    case 1:
    {
        qDebug()<<"Monthly Compensation does not exist for Hourly Paid Employees Contract, the hourly compensation is then: \n";
        break;
    }
    case 2:
    {
        SalesEmployee* sEmpl=(SalesEmployee*)this->getEmployee(index);
        sEmpl->setMonthlyCompensation(mc);
        break;
    }
    default:
    {
        qDebug()<<"Unknown type of contract! or it is not found at least! \n";
        // *todo*
    }
    }
}

void EmployeesManager::updateHC(int index, double hc){
    int theCT=this->getCType(index); // the CT is the contract type
    switch(theCT){
    case 0:
    {
        qDebug()<<"Hourly Compensation does not exist for Monthly Paid Employees Contract, the monthly compensation is then: \n";
        break;
    }
    case 1:
    {
        HourlyPaidEmployee* hEmpl=(HourlyPaidEmployee*)this->getEmployee(index);
        hEmpl->setHourlyCompensation(hc);
        break;
    }
    case 2:
    {
        qDebug()<<"Hourly Compensation does not exist for Sales Employees Contract, the monthly compensation is then: \n";
        break;
    }
    default:
    {
        qDebug()<<"Unknown type of contract! or it is not found at least! \n";
        // *todo*
    }
    }
}

void EmployeesManager::updateDoneHours(int index, double nhrs){
    int theCT=this->getCType(index); // the CT is the contract type
    switch(theCT){
    case 0:
    {
        qDebug()<<"Done hours does not exist for Monthly Paid Employees Contract \n";
        break;
    }
    case 1:
    {
        HourlyPaidEmployee* hEmpl=(HourlyPaidEmployee*)this->getEmployee(index);
        hEmpl->setDoneHours(nhrs);
        break;
    }
    case 2:
    {
        qDebug()<<"Done hours does not exist for Sales Employees Contract \n";
        break;
    }
    default:
    {
        qDebug()<<"Unknown type of contract! or it is not found at least! \n";
        // *todo*
    }
    }
}

void EmployeesManager::updateBP(int index, double bonus){
    int theCT=this->getCType(index); // the CT is the contract type
    switch(theCT){
    case 0:
    {
        qDebug()<<"Bonus parameter does not exist for Monthly Paid Employees Contract \n";
        break;
    }
    case 1:
    {
        qDebug()<<"Bonus parameter does not exist for Hourly Paid Employees Contract \n";
        break;
    }
    case 2:
    {
        SalesEmployee* sEmpl=(SalesEmployee*)this->getEmployee(index);
        sEmpl->setBonusPercentage(bonus);
        break;
    }
    default:
    {
        qDebug()<<"Unknown type of contract! or it is not found at least! \n";
        // *todo*
    }
    }
}

void EmployeesManager::updateOutput(int index, double output){
    int theCT=this->getCType(index); // the CT is the contract type
    switch(theCT){
    case 0:
    {
        qDebug()<<"Realized outcome parameter does not exist for Monthly Paid Employees Contract \n";
        break;
    }
    case 1:
    {
        qDebug()<<"Realized outcome parameter does not exist for Hourly Paid Employees Contract \n";
        break;
    }
    case 2:
    {
        SalesEmployee* sEmpl=(SalesEmployee*)this->getEmployee(index);
        sEmpl->setRealizedOutcome(output);
        break;
    }
    default:
    {
        qDebug()<<"Unknown type of contract! or it is not found at least! \n";
        // *todo*
    }
    }
}

void EmployeesManager::updateClaim(int index, bool claim){
    int theCT=this->getCType(index); // the CT is the contract type
    switch(theCT){
    case 0:
    {
        qDebug()<<"Outcome claim parameter does not exist for Monthly Paid Employees Contract \n";
        break;
    }
    case 1:
    {
        qDebug()<<"Outcome claim outcome parameter does not exist for Hourly Paid Employees Contract \n";
        break;
    }
    case 2:
    {
        SalesEmployee* sEmpl=(SalesEmployee*)this->getEmployee(index);
        if (claim == true) sEmpl->setOutcomeClaim();
        else sEmpl->resetOutcomeClaim();
        break;
    }
    default:
    {
        qDebug()<<"Unknown type of contract! or it is not found at least! \n";
        // *todo*
    }
    }
}

void EmployeesManager::updateSalary(int index){
    this->getEmployee(index)->updateSalary();
}

Employee* EmployeesManager::getEmployee(int index){
    return this->_employees_p_l[index];
}

void EmployeesManager::reset_ID(){ Employee::_ID=0;}
