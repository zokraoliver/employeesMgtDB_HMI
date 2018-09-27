
#include "employee.h"

int Employee::_ID=0;


Employee::Employee(QString Name="", int SSN=0,
                   QString TelNum="", int ctype=0,
                   int id=0):_name(Name),_ssn(SSN),_tel(TelNum),_contratType(ctype){//_id=ID++;

    // At an initial strategy for _id setting:
    //if we insert bigger IDs, we continue counting from the inserted id
    //and we omit the use of IDs between the last id and the newly inserted one.

    _ID++;
    if(id<0)
        qDebug()<<"id can't be negative";
    else if(id<_ID && id!=0){
        _id=_ID;
    }
    else if(id==0){
        _id=_ID;
    }
    else{
        _ID=id;
        _id=_ID;
    }
    _salary=0;
} //*todo* to add limits to id parameters


Employee::~Employee(){
    qDebug()<<"employee abstract class destructor is called ";
}
Employee::Employee(const Employee& e){
    _id=e._id;
    _name=e._name;
    _ssn=e._ssn;
    _tel=e._tel;
    _contratType=e._contratType;
    _salary=e._salary;
}

void Employee::set_id(int id){_id=id;} //*todo* to set a strategy to forbid modification
void Employee::set_name(QString n){_name=n;}
void Employee::set_ssn(int s){_ssn=s;}
void Employee::set_tel(QString t){_tel=t;}
void Employee::set_ctype(int ct){_contratType=ct;}

int Employee::get_id(){ return _id;}
int Employee::get_ssn(){ return _ssn;}
QString Employee::get_name(){ return _name;}
QString Employee::get_tel(){ return _tel;}
int Employee::get_ctype(){ return _contratType;}
int Employee::get_ID(){ return _ID;}

