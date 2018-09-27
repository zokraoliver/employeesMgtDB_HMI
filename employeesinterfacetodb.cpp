#include "employeesinterfacetodb.h"
#include <QDebug>

EmployeesInterfaceToDB::EmployeesInterfaceToDB(const QString &filename, EmployeesManager* em_old, QObject *object):QObject(object){
    _db=new EmployeesDBManager(filename);
    if(_em == NULL){
        _em=new EmployeesManager();
    }
    else{
        _em=em_old;
        _em->reset_ID();
    }
    QString name,tel;
    int ssn,id,ct; //ct is for contract type
    int obj_count=_db->getRecordsCount();
    double mcomp,hcomp,nhours; // monthly hourly compensations and number of hours
    double bonusp; //bonus percentage
    double output;//RealizedOutput
    int claim;//OutcomeClaime


    for(int i=0;i<obj_count;i++){
        id=_db->getRecord(i,"ID").toInt();
        name=_db->getRecord(i,"Name");
        ssn=_db->getRecord(i,"SSN").toInt();
        tel=_db->getRecord(i,"Tel");
        ct=_db->getRecord(i,"ContractType").toInt();

        switch(ct){
        case 0:
            mcomp= _db->getRecord(i,"MonthlyCompensation").toDouble();
            _em->addMEmployee(name,ssn,tel,0,id,mcomp);
            break;
        case 1:
            hcomp= _db->getRecord(i,"HourlyCompensation").toDouble();
            nhours=_db->getRecord(i,"NumberOfHours").toDouble();
            _em->addHEmployee(name,ssn,tel,1,id,hcomp,nhours);
            break;
        case 2:
            mcomp= _db->getRecord(i,"MonthlyCompensation").toDouble();
            bonusp=_db->getRecord(i,"BonusPercentage").toDouble();
            output=_db->getRecord(i,"RealizedOutput").toDouble();
            claim=_db->getRecord(i,"OutcomeCalim").toInt();
            _em->addSEmployee(name,ssn,tel,2,id,mcomp,bonusp);
            _em->SetSalesOutput(_em->employeesNumber()-1,output,claim);
            break;
        default:
            qDebug()<<"No Contract type is defined, the record is not loaded. Number : ";
            qDebug()<<i;
        }

    }
}

EmployeesInterfaceToDB::~EmployeesInterfaceToDB(){

    delete _db;

    int num=_em->employeesNumber()-1;
    for(int k=num;k>=0;k--){
        _em->rmvEmployee(0);
    }

}

EmployeesManager* EmployeesInterfaceToDB::get_ptr_to_employees_manager(){
    return this->_em;
}

void EmployeesInterfaceToDB::updateAll(){
    for(int i=0;i<_em->employeesNumber();i++){
        int ct=_em->getCType(i);
        this->updateRecordContratType(i,_em->getCType(i));
        this->updateRecordName(i,_em->getName(i));
        this->updateRecordID(i,_em->getID(i));
        this->updateRecordSSN(i,_em->getSSN(i));
        this->updateRecordTel(i,_em->getTel(i));
        switch(ct){
        case 0:
        {
            this->updateRecordMonthlyCompensation(i,_em->getMC(i));
            this->updateRecordSalary(i);
            break;
        }
        case 1:
        {
            this->udpateRecordHourlyCompensation(i,_em->getHC(i));
            this->updateRecordDoneHours(i,_em->getNHRS(i));
            this->updateRecordSalary(i);
            break;
        }
        case 2:
        {
            this->updateRecordMonthlyCompensation(i,_em->getMC(i));
            this->updateRecordBonusPercentage(i,_em->getBP(i));
            this->updateRecordOutcomeClaim(i,_em->getClaim(i));
            this->updateRecordRelaizedOutput(i,_em->getOutput(i));
            this->updateRecordSalary(i);
            break;
        }
        default:
        {
            qDebug()<<"the employee has bad ctype on index: "<<i<<'\n';
        }
        }
    }
      this->_db->updateDB();
      emit _DBModified();
}

void EmployeesInterfaceToDB::On_Saving(){
    for(int i=0;i<_em->employeesNumber();i++){
        this->updateRecordSalary(i);
        this->updateRecordContratType_dump(i,_em->getCType(i));
    }
    this->_db->updateDB();
    emit _DBModified();
}

void EmployeesInterfaceToDB::updateRecordName(int ix, QString n){
    _em->updateName(ix,n); //*todo* to add a condition if different

    // write directly on the QJsonDocument
    QString name_s=QString("Name");
    _db->addToRecord(QString::number(_em->getID(ix)),name_s,QLatin1String(_em->getName(ix).toLatin1()));
    emit _DBModified();// *todo* to see what to do with
}

void EmployeesInterfaceToDB::updateRecordID(int ix, int id){
    _em->updateID(ix,id);
    QString id_s=QString("ID");
    _db->addToRecord(QString::number(_em->getID(ix)),id_s,QLatin1String(QString::number(_em->getID(ix)).toLatin1()));
     emit _DBModified();
}

void EmployeesInterfaceToDB::updateRecordTel(int ix, QString t){
    _em->updateTel(ix,t);
    QString tel_s=QString("Tel");
    _db->addToRecord(QString::number(_em->getID(ix)),tel_s,QLatin1String(_em->getTel(ix).toLatin1()));
    emit _DBModified();
}

void EmployeesInterfaceToDB::updateRecordSSN(int ix, int ssn){
   _em->updateSSN(ix,ssn);
   QString id_s=QString("SSN"); //*todo* define these _s -terminated variables as global
   _db->addToRecord(QString::number(_em->getID(ix)),id_s,QLatin1String(QString::number(_em->getSSN(ix)).toLatin1()));
    emit _DBModified();
}




void EmployeesInterfaceToDB::updateRecordContratType(int ix, int ct){
    _em->updateCType(ix,ct);
    QString ctype_s=QString("ContractType");
    _db->addToRecord(QString::number(_em->getID(ix)),ctype_s,QLatin1String(QString::number(_em->getCType(ix)).toLatin1()));
    emit _DBModified();
}

void EmployeesInterfaceToDB::updateRecordContratType_dump(int ix, int ct){
    QString ctype_s=QString("ContractType");
    _db->addToRecord(QString::number(_em->getID(ix)),ctype_s,QLatin1String(QString::number(_em->getCType(ix)).toLatin1()));
    emit _DBModified();
}


void EmployeesInterfaceToDB::updateRecordMonthlyCompensation(int ix, double mc){
    _em->updateMC(ix,mc);
    QString mcomp_s=QString("MonthlyCompensation");
    _db->addToRecord(QString::number(_em->getID(ix)),mcomp_s,QLatin1String(QString::number(_em->getMC(ix)).toLatin1()));

    emit _DBModified();
}

void EmployeesInterfaceToDB::udpateRecordHourlyCompensation(int ix, double hc){
    _em->updateHC(ix,hc);
    QString hcomp_s=QString("HourlyCompensation");
    _db->addToRecord(QString::number(_em->getID(ix)),hcomp_s,QLatin1String(QString::number(_em->getHC(ix)).toLatin1()));

    emit _DBModified();

}

void EmployeesInterfaceToDB::updateRecordDoneHours(int ix, double nhrs){
    _em->updateDoneHours(ix,nhrs);
    QString nhours_s=QString("NumberOfHours");
    _db->addToRecord(QString::number(_em->getID(ix)),nhours_s,QLatin1String(QString::number(_em->getNHRS(ix)).toLatin1()));

    emit _DBModified();
}
void EmployeesInterfaceToDB::updateRecordBonusPercentage(int ix, double bp){
    _em->updateBP(ix,bp);
    QString bonusp_s=QString("BonusPercentage");
    _db->addToRecord(QString::number(_em->getID(ix)),bonusp_s,QLatin1String(QString::number(_em->getBP(ix)).toLatin1()));
    emit _DBModified();
}
void EmployeesInterfaceToDB::updateRecordRelaizedOutput(int ix, double output){
    _em->updateOutput(ix,output);
    QString output_s=QString("RealizedOutput");
    _db->addToRecord(QString::number(_em->getID(ix)),output_s,QLatin1String(QString::number(_em->getOutput(ix)).toLatin1()));
    emit _DBModified();
}
void EmployeesInterfaceToDB::updateRecordOutcomeClaim(int ix, bool claim){
    _em->updateClaim(ix,claim);
    QString claim_s=QString("OutcomeClaim");
    _db->addToRecord(QString::number(_em->getID(ix)),claim_s,QLatin1String(QString::number(_em->getClaim(ix)).toLatin1()));
    emit _DBModified();
}
void EmployeesInterfaceToDB::updateRecordSalary(int ix){ //*todo* to verify
    _em->updateSalary(ix);
    QString salary_s= QString("Salary");
    //double theID_=_em->getID(ix);
    //double the_Salary=_em->getSalary(ix);
    _db->addToRecord(QString::number(_em->getID(ix)),salary_s,QLatin1String(QString::number(_em->getSalary(ix)).toLatin1()));
    emit _DBModified();
}

Employee* EmployeesInterfaceToDB::getEmployee_byIndex(int ix){
    return this->_em->getEmployee(ix);
}

Employee* EmployeesInterfaceToDB::getEmployee_byID(int id){
    for(int i=0;i<_em->employeesNumber();i++)
    {
        if(this->_em->getID(i)==id)
            return _em->getEmployee(i);
    }
    return NULL; //*todo* to verify
}

int EmployeesInterfaceToDB::getIndex_byID(int id){
    for(int i=0;i<_em->employeesNumber();i++)
    {
        if(this->_em->getID(i)==id)
            return i;
    }
    return -1; //*todo* to verify
}

void EmployeesInterfaceToDB::addRecord_MEmpl(int id, QString name,
                                             int ssn, QString tel,
                                             double mc){
    _em->addMEmployee(name,ssn,tel,0,id,mc);
}

void EmployeesInterfaceToDB::addRecord_HEmpl(int id, QString name,
                                             int ssn, QString tel,
                                             double hc, double nhrs){
    _em->addHEmployee(name,ssn,tel,1,id,hc,nhrs);
}

void EmployeesInterfaceToDB::addRecord_SEmpl(int id, QString name,
                                             int ssn, QString tel,
                                             double mc, double bp,
                                             double outcome, bool claim){
    _em->addSEmployee(name,ssn,tel,2,id,mc,bp);
    _em->SetSalesOutput(_em->employeesNumber()-1,outcome,claim);
}

void EmployeesInterfaceToDB::rmvRecord(int index){
    _em->rmvEmployee(index);
}

void EmployeesInterfaceToDB::rmvRecord_byID(int id){
    int idx_tor=this->getIndex_byID(id);
    _em->rmvEmployee(idx_tor);
    _db->removeRecord(id);

}

int EmployeesInterfaceToDB::get_EmployeesNumber(){
    return _em->employeesNumber();
}
