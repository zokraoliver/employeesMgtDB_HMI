#include "presenter_qml.h"

#include<QDebug>

Presenter_QML::Presenter_QML(QObject *parent):QObject(parent){
    QString fn_new="init_file.json";
    _fileDB="../"+fn_new;
    qDebug()<<"fileDB: "<<_fileDB;
    _EMI =new EmployeesInterfaceToDB(_fileDB); // *tocheck* to see if the file "init_file" does not exist
    _selectedEmployeeIndex=0;
    QObject::connect(this,SIGNAL(Empl_ID_Changed(int,int)),this->_EMI,SLOT(updateRecordID(int,int)));
    QObject::connect(this,SIGNAL(Empl_Name_Changed(int,QString)),this->_EMI,SLOT(updateRecordName(int,QString)));
    QObject::connect(this,SIGNAL(Empl_SSN_Changed(int,int)),this->_EMI,SLOT(updateRecordSSN(int,int)));
    QObject::connect(this,SIGNAL(Empl_Tel_Changed(int,QString)),this->_EMI,SLOT(updateRecordTel(int,QString)));
    QObject::connect(this,SIGNAL(Empl_CType_Changed(int,int)),this->_EMI,SLOT(updateRecordContratType(int,int)));
    QObject::connect(this,SIGNAL(save_Clicked()),this->_EMI,SLOT(On_Saving()));

    QObject::connect(this,SIGNAL(Empl_MC_Changed(int,double)),this->_EMI,SLOT(updateRecordMonthlyCompensation(int,double)));

    QObject::connect(this,SIGNAL(Empl_HC_Changed(int,double)),this->_EMI,SLOT(udpateRecordHourlyCompensation(int,double)));
    QObject::connect(this,SIGNAL(Empl_NHRS_Changed(int,double)),this->_EMI,SLOT(updateRecordDoneHours(int,double)));

    QObject::connect(this,SIGNAL(Empl_ROutput_Changed(int,double)),this->_EMI,SLOT(updateRecordRelaizedOutput(int,double)));
    QObject::connect(this,SIGNAL(Empl_Claim_Changed(int,bool)),this->_EMI,SLOT(updateRecordOutcomeClaim(int,bool)));
    QObject::connect(this,SIGNAL(Empl_BP_Changed(int,double)),this->_EMI,SLOT(updateRecordBonusPercentage(int,double)));
}

Presenter_QML::~Presenter_QML(){
    if(_EMI !=NULL){
        delete _EMI;
    }
}

void Presenter_QML::set_file_DB(QString f){
    EmployeesManager* oldManager=_EMI->get_ptr_to_employees_manager();
    _fileDB="../"+f;
    _EMI->~EmployeesInterfaceToDB();
    _EMI =new EmployeesInterfaceToDB(_fileDB,oldManager);

    _selectedEmployeeIndex=0;
    QObject::connect(this,SIGNAL(Empl_ID_Changed(int,int)),this->_EMI,SLOT(updateRecordID(int,int)));
    QObject::connect(this,SIGNAL(Empl_Name_Changed(int,QString)),this->_EMI,SLOT(updateRecordName(int,QString)));
    QObject::connect(this,SIGNAL(Empl_SSN_Changed(int,int)),this->_EMI,SLOT(updateRecordSSN(int,int)));
    QObject::connect(this,SIGNAL(Empl_Tel_Changed(int,QString)),this->_EMI,SLOT(updateRecordTel(int,QString)));
    QObject::connect(this,SIGNAL(Empl_CType_Changed(int,int)),this->_EMI,SLOT(updateRecordContratType(int,int)));

    QObject::connect(this,SIGNAL(save_Clicked()),this->_EMI,SLOT(On_Saving()));

    QObject::connect(this,SIGNAL(Empl_MC_Changed(int,double)),this->_EMI,SLOT(updateRecordMonthlyCompensation(int,double)));

    QObject::connect(this,SIGNAL(Empl_HC_Changed(int,double)),this->_EMI,SLOT(udpateRecordHourlyCompensation(int,double)));
    QObject::connect(this,SIGNAL(Empl_NHRS_Changed(int,double)),this->_EMI,SLOT(updateRecordDoneHours(int,double)));

    QObject::connect(this,SIGNAL(Empl_ROutput_Changed(int,double)),this->_EMI,SLOT(updateRecordRelaizedOutput(int,double)));
    QObject::connect(this,SIGNAL(Empl_Claim_Changed(int,bool)),this->_EMI,SLOT(updateRecordOutcomeClaim(int,bool)));
    QObject::connect(this,SIGNAL(Empl_BP_Changed(int,double)),this->_EMI,SLOT(updateRecordBonusPercentage(int,double)));


    emit this->file_DB_Changed(f);
}

QString Presenter_QML::read_file_DB(){
    return _fileDB;
}

int Presenter_QML::get_Empl_Index(){
    return this->_selectedEmployeeIndex;
}

void Presenter_QML::set_Empl_Index(int index){
    this->_selectedEmployeeIndex=index;
}

void Presenter_QML::set_Empl_Index_byID(int the_id){
    int index;
    index=this->_EMI->getIndex_byID(the_id);
    this->_selectedEmployeeIndex=index;
}



void Presenter_QML::set_Empl_ID(const int &id){ //*todo* shall be forbidden for existing ids

    if(id!=0){ //*todo* to follow and to correct the case where we enter a duplicated ID
        emit Empl_ID_Changed(_selectedEmployeeIndex,id);
    }
    else{
        ;//do not change the generated id
    }
}


int Presenter_QML::read_Empl_ID(){
    return this->_EMI->getEmployee_byIndex(_selectedEmployeeIndex)->get_id();
}

void Presenter_QML::set_Empl_Name(const QString &name){
    emit Empl_Name_Changed(_selectedEmployeeIndex,name);
}
QString Presenter_QML::read_Empl_Name(){
    return this->_EMI->getEmployee_byIndex(_selectedEmployeeIndex)->get_name();//******************
}

void Presenter_QML::set_Empl_SSN(const int &ssn){
   emit Empl_SSN_Changed(_selectedEmployeeIndex,ssn);
}
int Presenter_QML::read_Empl_SSN(){
    return this->_EMI->getEmployee_byIndex(_selectedEmployeeIndex)->get_ssn();//********************
}

void Presenter_QML::set_Empl_Tel(const QString &tel){
    emit Empl_Tel_Changed(_selectedEmployeeIndex,tel);
}
QString Presenter_QML::read_Empl_Tel(){
    return this->_EMI->getEmployee_byIndex(_selectedEmployeeIndex)->get_tel();//********
}

void Presenter_QML::set_Empl_CType(const int &ct){
   if(ct!=this->read_Empl_CType()){ //*todo*
        emit Empl_CType_Changed(_selectedEmployeeIndex,ct);
    }

}
int Presenter_QML::read_Empl_CType(){
    return this->_EMI->getEmployee_byIndex(_selectedEmployeeIndex)->get_ctype();//********
}


double Presenter_QML::read_Empl_MC(){
    switch(this->_EMI->getEmployee_byIndex(_selectedEmployeeIndex)->get_ctype()){
    case 0:
    {
        MonthlyPaidEmployee *mpEmpl= (MonthlyPaidEmployee *)this->_EMI->getEmployee_byIndex(_selectedEmployeeIndex);
        return mpEmpl->get_MonthlyCompensation();
    }
    case 1:
    {
        // *todo* either raise an exception or a message error
        return 1;//*****
    }
    case 2:
    {
        SalesEmployee *spEmpl= (SalesEmployee *)this->_EMI->getEmployee_byIndex(_selectedEmployeeIndex);
        return spEmpl->getMonthlyCompensation();
        break;
    }
    }
    return 0;
}

double Presenter_QML::read_Empl_HC(){
    switch(this->_EMI->getEmployee_byIndex(_selectedEmployeeIndex)->get_ctype()){
    case 0:
    {
        // *todo* either raise an exception or a message error
        return 1;//*******
    }
    case 1:
    {
        HourlyPaidEmployee *hpEmpl= (HourlyPaidEmployee *)this->_EMI->getEmployee_byIndex(_selectedEmployeeIndex);
        return hpEmpl->getHourlyCompensation();
    }
    case 2:
    {
        // *todo* either raise an exception or a message error
        return 1;//*******
    }
    }
    return 0;
}

double Presenter_QML::read_Empl_NHRS(){
    switch(this->_EMI->getEmployee_byIndex(_selectedEmployeeIndex)->get_ctype()){
    case 0:
    {
        // *todo* either raise an exception or a message error
        return 1;//*******
    }
    case 1:
    {
        HourlyPaidEmployee *hpEmpl= (HourlyPaidEmployee *)this->_EMI->getEmployee_byIndex(_selectedEmployeeIndex);
        return hpEmpl->getDoneHours();
    }
    case 2:
    {
        // *todo* either raise an exception or a message error
        return 1;//*******
    }
    }
    return 0;
}

double Presenter_QML::read_Empl_BP(){
    switch(this->_EMI->getEmployee_byIndex(_selectedEmployeeIndex)->get_ctype()){
    case 0:
    {
        // *todo* either raise an exception or a message error
        return 1;//*******
    }
    case 1:
    {
        // *todo* either raise an exception or a message error
        return 1;//*******
    }
    case 2:
    {
        SalesEmployee *spEmpl= (SalesEmployee *)this->_EMI->getEmployee_byIndex(_selectedEmployeeIndex);
        return spEmpl->getBonusPercentage();
    }
    }
    return 0;
}

double Presenter_QML::read_Empl_ROutput(){
    switch(this->_EMI->getEmployee_byIndex(_selectedEmployeeIndex)->get_ctype()){
    case 0:
    {
        // *todo* either raise an exception or a message error
        return 1;//*******
        break;
    }
    case 1:
    {
        // *todo* either raise an exception or a message error
        return 1;//*******
        break;
    }
    case 2:
    {
        SalesEmployee *spEmpl= (SalesEmployee *)this->_EMI->getEmployee_byIndex(_selectedEmployeeIndex);
        return spEmpl->getRealizedOutcome();
        break;
    }
    }
    return 0;
}

bool Presenter_QML::read_Empl_Claim(){
    switch(this->_EMI->getEmployee_byIndex(_selectedEmployeeIndex)->get_ctype()){
    case 0:
    {
        // *todo* either raise an exception or a message error
        return 1;//*******
        break;
    }
    case 1:
    {
        // *todo* either raise an exception or a message error
        return 1;//*******
        break;
    }
    case 2:
    {
        SalesEmployee *spEmpl=(SalesEmployee *) this->_EMI->getEmployee_byIndex(_selectedEmployeeIndex);
        return spEmpl->getOutcomeClaim();
        break;
    }
    }
    return 0;
}

void Presenter_QML::set_Empl_MC(const double &mc){
    emit Empl_MC_Changed(_selectedEmployeeIndex,mc);
}

void Presenter_QML::set_Empl_HC(const double &hc){
    emit Empl_HC_Changed(_selectedEmployeeIndex,hc);
}

void Presenter_QML::set_Empl_NHRS(const double &nhrs){
    emit Empl_NHRS_Changed(_selectedEmployeeIndex,nhrs);
}

void Presenter_QML::set_Empl_BP(const double &bp){
    emit Empl_BP_Changed(_selectedEmployeeIndex,bp);
}

void Presenter_QML::set_Empl_ROutput(const double &routput){
    emit Empl_ROutput_Changed(_selectedEmployeeIndex,routput);
}

void Presenter_QML::set_Empl_Claim(const bool &claim){
    emit Empl_Claim_Changed(_selectedEmployeeIndex,claim);
}

void Presenter_QML::save_DB(){

    emit save_Clicked();
}

void Presenter_QML::add_MEmpl(){
    this->_EMI->addRecord_MEmpl(0,"",0,"",0);
}
void Presenter_QML::add_HEmpl(){
    this->_EMI->addRecord_HEmpl(0,"",0,"",0);
}
void Presenter_QML::add_SEmpl(){
    this->_EMI->addRecord_SEmpl(0,"",0,"",0,0,0,0);
}

void Presenter_QML::rmv_Empl(int id){
    this->_EMI->rmvRecord_byID(id);
}

int Presenter_QML::get_EmployeesNumber(){
    return this->_EMI->get_EmployeesNumber();
}

double Presenter_QML::read_Empl_Salary(){
    return this->_EMI->getEmployee_byIndex(_selectedEmployeeIndex)->getSalary();
}

void Presenter_QML::display_memory_content(){
    this->_EMI->_em->displayContent();
}
