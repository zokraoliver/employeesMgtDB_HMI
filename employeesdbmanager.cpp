#include <employeesdbmanager.h>
#include <utility>
#include<QFile>
#include<QDir>

#include<QDebug>


EmployeesDBManager::EmployeesDBManager(const QString &filename){
    QDir dir("D:\\Users\\zokra_o\\Desktop\\CompanyManagement1");
    QStringList pl=filename.split('/');
    int j=pl.count();
    QString rawFileName=pl[j-1];
    qDebug()<<rawFileName;
    QString s_val;

    if(dir.exists(rawFileName)==false){
        qDebug()<<"file init does not exist";
        qDebug()<<filename;
        qDebug()<<rawFileName;

        const QByteArray init("{\"employees\":[{\"ID\":\"1\",\"Name\":\"\",\"SSN\":\"\",\"Tel\":\"\"},{\"ID\":\"2\",\"Name\":\"\",\"SSN\":\"\",\"Tel\":\"\"},{\"ID\":\"3\",\"Name\":\"\",\"SSN\":\"\",\"Tel\":\"\"}]}");

        QFile *f;
        f=new QFile(filename+"_alpha");
        f->open(QIODevice::ReadWrite | QIODevice::Text);
        f->write(init);
        s_val=f->readAll();
        qDebug()<<"file created";
        f->close();
        delete f;

        QJsonParseError *err=new QJsonParseError();
        _employeesDB=QJsonDocument::fromJson(s_val.toUtf8(),err);
        qDebug()<<err->errorString();
        _DBfile=filename+"_alpha";

    }
    else{
        _DBfile=filename;

        QFile *f;
        qDebug()<<"will open" << rawFileName;
        qDebug()<<"filename" << filename;
        f=new QFile(filename);
        f->open(QIODevice::ReadWrite | QIODevice::Text);
        s_val=f->readAll();
        qDebug()<<s_val;
        f->close();
        delete f;

        QJsonParseError *err=new QJsonParseError();

        _employeesDB=QJsonDocument::fromJson(s_val.toUtf8(),err);
       // _employeesDB=&doc;
        qDebug()<<err->errorString();

    //*todo* we are reading all the file in  one string, then we parse it with fromJson:
    // Must be improved

    }
}

EmployeesDBManager::~EmployeesDBManager(){
}

void EmployeesDBManager::addToRecord(QString id, QString key, QLatin1String value){
    // prepare the record value
    QJsonValue id_val= QJsonValue(value);
    QJsonArray emplo_arr =_employeesDB.object().take("employees").toArray();
    int num=emplo_arr.count();
    bool existsInside=false;
    bool modified=false;
    int index=0;
    QJsonObject element_to_add;
    QJsonObject::iterator jsonObjectIterator;
    //check if the id exists, and modify to that object
    for(int i=0;i<num;i++){
        QJsonObject obj=emplo_arr.at(i).toObject();
        QString objectID=obj["ID"].toString();
        if(objectID==id){
            for(jsonObjectIterator=obj.begin();jsonObjectIterator!=obj.end();jsonObjectIterator ++){
                QString objectID_Key=jsonObjectIterator.key();
                if(objectID_Key==key){
                    //modify the field inside the record
                    element_to_add.insert(jsonObjectIterator.key(),id_val);

                    modified=true;
                }
                else{
                    element_to_add.insert(objectID_Key,jsonObjectIterator.value());
                }
            }
            if(modified==false){
                element_to_add=obj;
                // add a field on the record
                QJsonValue field=QJsonValue(value);
                element_to_add.insert(key,field);
            }

            existsInside=true;
            break;
        }
        index++;
    }
    if(existsInside==false){
        //we must add the ID info here so that another record can see it
        QLatin1String addedID=QLatin1String(id.toStdString().c_str());
        QJsonValue idField=QJsonValue(addedID);
        element_to_add.insert("ID",idField);
        // create an new object element
        QJsonValue field=QJsonValue(value);
        element_to_add.insert(key,field);
    }

    if(index==num){
        emplo_arr.append(element_to_add);
    }
    else if(index >=0 && index < num){
        emplo_arr.removeAt(index);
        emplo_arr.insert(index,element_to_add);
    }
    else{
        qDebug()<< " warning : index out of range ";
    }

    QJsonObject rootObject=_employeesDB.object();
    rootObject.insert("employees",emplo_arr);
    _employeesDB.setObject(rootObject);
    qDebug()<<"objects number after adding record: "<<_employeesDB.object().count();

}


QString EmployeesDBManager::getRecord(int index, const QString key){
    //qDebug()<<"getRecord() : "<<_employeesDB.object().count();
    QString value;
    QJsonObject emplo_object=_employeesDB.object();
    QJsonValue emplo_arr =emplo_object.take("employees");
    value= emplo_arr.toArray().at(index).toObject()[key].toString(); // to see
    qDebug()<<"getRecord()";
    qDebug()<<"index"<<index<<",key"<<key;
    //qDebug()<<emplo_arr.toArray().at(index).toObject().count();
    qDebug()<<emplo_arr.toArray().at(index).toObject()[key].toString();
    return value;
}

int EmployeesDBManager::getRecordsCount(){
    qDebug()<<"objects number : "<<_employeesDB.object().count();
    int num=0;
    QJsonObject emplo_object=_employeesDB.object();
    QJsonValue emplo_arr =emplo_object.take("employees");
    num= emplo_arr.toArray().count();
    qDebug()<<"array elements number : "<<num;
    return num;
}

void EmployeesDBManager::updateDB(){
    QByteArray ar=_employeesDB.toJson();
    QFile *f;
    f=new QFile(_DBfile);
    f->open(QIODevice::WriteOnly | QIODevice::Text);
    f->write(ar);
    f->close();
    delete f;
}

void EmployeesDBManager::removeRecord(int id){
    QJsonArray emplo_arr =_employeesDB.object().take("employees").toArray();
    int num=emplo_arr.count();
    bool existsInside=false;
    int index=0;
    //check if the id exists, and modify to that object
    for(int i=0;i<num;i++){
        QJsonObject obj=emplo_arr.at(i).toObject();
        QString objectID=obj["ID"].toString();
        int ob_id=objectID.toInt();
        if(ob_id==id){
            existsInside=true;
            break;
        }
        index++;
    }
    if(existsInside==false){
        //*todo* manage exceptions
        qDebug()<<"record does not exist, so can't be removed!";
    }

   if(index >=0 && index < num){
        emplo_arr.removeAt(index);
    }
    else{
        qDebug()<< " warning : index of removal is out of range ";
    }

    QJsonObject rootObject=_employeesDB.object();
    rootObject.insert("employees",emplo_arr);
    _employeesDB.setObject(rootObject);
    qDebug()<<"objects number after adding record: "<<_employeesDB.object().count();

}
