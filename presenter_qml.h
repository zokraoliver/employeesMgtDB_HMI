#pragma once
#ifndef PRESENTER_QML_H
#define PRESENTER_QML_H

#include <QObject>
#include <QString>
#include "employeesinterfacetodb.h"

class Presenter_QML:public QObject{
    Q_OBJECT
    Q_PROPERTY(QString Empl_Name READ read_Empl_Name WRITE set_Empl_Name )
    Q_PROPERTY(QString Empl_Tel READ read_Empl_Tel WRITE set_Empl_Tel )
    Q_PROPERTY(int Empl_ID READ read_Empl_ID WRITE set_Empl_ID )
    Q_PROPERTY(int Empl_SSN READ read_Empl_SSN WRITE set_Empl_SSN )

    // the role of the index property is to choose the employee that is selected in the interface
    Q_PROPERTY(int Empl_Index READ get_Empl_Index WRITE set_Empl_Index )

    Q_PROPERTY(int Empl_CType READ read_Empl_CType WRITE set_Empl_CType)
    Q_PROPERTY(double Empl_MC READ read_Empl_MC WRITE set_Empl_MC)
    Q_PROPERTY(double Empl_HC READ read_Empl_HC WRITE set_Empl_HC)
    Q_PROPERTY(double Empl_NHRS READ read_Empl_NHRS WRITE set_Empl_NHRS)
    Q_PROPERTY(double Empl_BP READ read_Empl_BP WRITE set_Empl_BP)
    Q_PROPERTY(double Empl_ROutput READ read_Empl_ROutput WRITE set_Empl_ROutput)
    Q_PROPERTY(bool Empl_Claim READ read_Empl_Claim WRITE set_Empl_Claim)
    Q_PROPERTY(double Empl_Salary READ read_Empl_Salary)

public:
    explicit Presenter_QML(QObject *parent=NULL);
    ~Presenter_QML();


    QString read_Empl_Name();
    QString read_Empl_Tel();
    int read_Empl_ID();
    int read_Empl_SSN();
    int read_Empl_CType();
    double read_Empl_MC();
    double read_Empl_HC();
    double read_Empl_NHRS();
    double read_Empl_BP();
    double read_Empl_ROutput();
    bool read_Empl_Claim();
    double read_Empl_Salary();
    QString read_file_DB();

    void set_Empl_Name(const QString &name);
    void set_Empl_Tel(const QString &tel);
    void set_Empl_ID(const int &id);
    void set_Empl_SSN(const int &ssn);
    void set_Empl_CType(const int &ct);
    void set_Empl_MC(const double &mc);
    void set_Empl_HC(const double &hc);
    void set_Empl_NHRS(const double &nhrs);
    void set_Empl_BP(const double &bp);
    void set_Empl_ROutput(const double &routput);
    void set_Empl_Claim(const bool &claim);

    Q_INVOKABLE void set_file_DB(QString f);
    Q_INVOKABLE void save_DB();

    int get_Empl_Index();


    Q_INVOKABLE void set_Empl_Index(int ix);
    Q_INVOKABLE void set_Empl_Index_byID(int the_id);
    Q_INVOKABLE int get_EmployeesNumber();

    Q_INVOKABLE void add_MEmpl();
    Q_INVOKABLE void add_HEmpl();
    Q_INVOKABLE void add_SEmpl();
    Q_INVOKABLE void rmv_Empl(int id);

    Q_INVOKABLE void display_memory_content();

signals:
    void Empl_Name_Changed(int idx, QString n);
    void Empl_Tel_Changed(int idx, QString t);
    void Empl_ID_Changed(int idx, int id);
    void Empl_SSN_Changed(int idx, int ssn);
    void Empl_CType_Changed(int idx, int ct);
    void Empl_MC_Changed(int idx, double mc);
    void Empl_HC_Changed(int idx, double hc);
    void Empl_NHRS_Changed(int idx, double nhrs);
    void Empl_BP_Changed(int idx, double bp);
    void Empl_ROutput_Changed(int idx, double routput);
    void Empl_Claim_Changed(int idx, bool claim);
    void file_DB_Changed(QString fn);
    void Empl_Index_Changed(int ind);

    void save_Clicked();


    //*todo* to see where to use the signal _DBModified


private:
    EmployeesInterfaceToDB *_EMI;
    QString _fileDB;
    int _selectedEmployeeIndex;
};

#endif // PRESENTER_QML_H
