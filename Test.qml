import QtQuick 2.7
import QtQuick.Controls 1.4 // 1.4 pour MenuBar
import QtQuick.Layouts 1.0

import QtQuick.Controls.Styles 1.0
import QtQuick.Dialogs 1.2

import QtQuick.Window 2.0

import CompanyMgtBackend 1.0


//*todo* to add the functionality of showing charachteristics of the employee on double clicking

ApplicationWindow {

    id: mainWindow

    visible: true
    width: Screen.width
    height: Screen.height
    x:(Screen.width-mainWindow.width)/2
    y:(Screen.height-mainWindow.height)/2

    title: qsTr("Company Management")

    property alias elem_height: mainWindow.height
    property alias elem_width: mainWindow.width
    property alias add_dialogIsVisible: _AddEmployeeDialog.visible
    property alias rmv_dialogIsVisible: _RmvEmployeeDialog.visible
    property alias apd_dialogIsVisible: _ApdEmployeeDialog.visible
    property alias importDialogIsVisible: _ImportDialog.visible
    property alias mp_dialogIsVisible: _MonthlyPaidEmployeeDialog.visible
    property alias hp_dialogIsVisible: _HourlyPaidEmployeeDialog.visible
    property alias sp_dialogIsVisible: _SalesEmployeeDialog.visible
    property alias chart_dialogIsVisible: chart_dialog.visible

    property alias name_: _rima.Empl_Name
    property alias id_: _rima.Empl_ID
    property alias ssn_: _rima.Empl_SSN
    property alias tel_: _rima.Empl_Tel
    property alias index_: _rima.Empl_Index
    property alias ctype_:_rima.Empl_CType
    property alias mc_: _rima.Empl_MC
    property alias hc_: _rima.Empl_HC
    property alias nhrs_: _rima.Empl_NHRS
    property alias bp_: _rima.Empl_BP
    property alias routput_: _rima.Empl_ROutput
    property alias claim_: _rima.Empl_Claim

    property alias salary_:_rima.Empl_Salary


    menuBar: MenuBar{
        id: menu_bar

        Menu {
            title: "Database"
            visible: true

            MenuItem {
                text: "Import"
                shortcut: "Ctrl+O"
                onTriggered: {
                    mainWindow.importDialogIsVisible=true;
                }
            }
            MenuItem {
                text: "Export"
                onTriggered: {
                    ;//*todo*
                }
            }
            MenuItem {
                text: "Save"
                shortcut: "Ctrl+S"
                onTriggered: {
                    _rima.save_DB();
                }
            }
        }

        Menu {
            title: "Modifications"
            visible: true

            MenuItem {
                text: "Add Employee"
                shortcut: "Ctrl+N"
                onTriggered: {
                    mainWindow.add_dialogIsVisible=true;
                }
            }

            MenuItem {
                text: "Remove Employee"
                onTriggered: {
                    mainWindow.rmv_dialogIsVisible=true;
                }
            }

            MenuItem {
                text: "Append Employee Infos"
                onTriggered: {
                    mainWindow.apd_dialogIsVisible=true;
                }
            }

            MenuItem {
                text: "Display MEM CONTENT"
                onTriggered: {
                    _rima.display_memory_content();
                }
            }

        }

        Menu {
            title: "Draw"
            visible: true

            MenuItem {
                text: "Draw Chart"
                shortcut: "Ctrl+G"
                onTriggered: {
                    myChart.requestPaint();
                    mainWindow.chart_dialogIsVisible=true;
                }
            }
        }
    }


    Dialog{
        id: _RmvEmployeeDialog
        title: "Remove Employee"
        width:300
        height:300

        contentItem: Rectangle{
            id:content_rect_dialog_rmv
            color:"red"


            property string p_id;
            property string p_name;
            property string p_ssn;
            property string p_tel;
            property string p_ctype;

            ColumnLayout{
                TextField{
                    id:_idField_rmv
                    placeholderText: qsTr("Enter ID to remove")
                    width:content_rect_dialog_rmv.width
                }

                RowLayout{
                    Button {
                        id: _dialog_rmv_remove_button_
                        text:"Remove"
                        onClicked:{
                            content_rect_dialog_rmv.p_id= _idField_rmv.text;
                            var id_tormv;
                            id_tormv=parseInt(content_rect_dialog_rmv.p_id);

                            _rima.set_Empl_Index_byID(id_tormv);
                            model_to_display.remove(index_);
                            _rima.rmv_Empl(id_tormv); //*todo* maybe change the method so it relies only on _selectedemployee

                            _idField_rmv.text="";
                            rmv_dialogIsVisible=false;
                        }
                    }
                    Button {
                        id: _dialog_rmv_cancel_button_
                        text:"Cancel"
                        onClicked: {
                            _idField_rmv.text="";
                            rmv_dialogIsVisible=false;
                        }
                    }
                }
            }
            Component.onCompleted: {
                _idField_rmv.text="";
            }
        }
    }

    Dialog{
        id: _AddEmployeeDialog
        title: "Add Employee"
        width:300
        height:300

        contentItem: Rectangle{
            id:content_rect_dialog1
            color:"light green"


            property string p_id;
            property string p_name;
            property string p_ssn;
            property string p_tel;
            property string p_ctype;

            ColumnLayout{

                TextField{
                    id:_nameField
                    placeholderText: qsTr("Enter name")
                    width:content_rect_dialog1.width
                }

                TextField{
                    id:_ssnField
                    placeholderText: qsTr("Enter ssn")
                    width:content_rect_dialog1.width
                }

                TextField{
                    id:_telField
                    placeholderText: qsTr("Enter telephone number")
                    width:content_rect_dialog1.width
                }
                TextField{
                    id:_contratTypeField
                    placeholderText: qsTr("Enter the contract type (0 for monthly, 1 for hourly, 2 for sales)")
                    width:content_rect_dialog1.width
                }

                RowLayout{
                    Button {
                        id: _dialog1_Add_button_
                        text:"Add"
                        onClicked: {

                            content_rect_dialog1.p_id= "";
                            content_rect_dialog1.p_name= _nameField.text;
                            content_rect_dialog1.p_ssn=_ssnField.text;
                            content_rect_dialog1.p_tel=_telField.text;
                            content_rect_dialog1.p_ctype=_contratTypeField.text;

                            switch(parseInt(content_rect_dialog1.p_ctype)){
                            case 0:
                                _rima.add_MEmpl();
                                break;
                            case 1:
                                _rima.add_HEmpl();
                                break;
                            case 2:
                                _rima.add_SEmpl();
                                break;
                            default:
                                //show an error or exception *todo*
                                console.log("contract type field must be filled");
                            }


                            _rima.set_Empl_Index(_rima.get_EmployeesNumber()-1);


                            if(content_rect_dialog1.p_id==="")
                                id_=0;
                            else
                                id_=parseInt(content_rect_dialog1.p_id);

                            name_=content_rect_dialog1.p_name;
                            tel_=content_rect_dialog1.p_tel;   // no need to parse , it is a string

                            if(content_rect_dialog1.p_ssn==="")
                                ssn_=0;
                            else
                                ssn_=parseInt(content_rect_dialog1.p_ssn);


                            if(content_rect_dialog1.p_ctype==="")
                                ctype_=0;
                            else
                                ctype_=parseInt(content_rect_dialog1.p_ctype);

                            add_dialogIsVisible=false;

                            _nameField.text="";
                            _ssnField.text="";
                            _telField.text="";
                            _contratTypeField.text="";

                            switch(ctype_){
                            case 0:
                                mp_dialogIsVisible=true;
                                break;
                            case 1:
                                hp_dialogIsVisible=true;
                                break;
                            case 2:
                                sp_dialogIsVisible=true;
                                break;
                            default:
                                ;//show an error or exception *todo*
                            }
                        }
                    }

                    Button {
                        id: _dialog1_cancel_button_
                        text:"Cancel"
                        onClicked: {

                            _nameField.text="";
                            _ssnField.text="";
                            _telField.text="";
                            _contratTypeField.text="";

                            add_dialogIsVisible=false;
                        }
                    }
                }
            }
            Component.onCompleted: {

                _nameField.text="";
                _ssnField.text="";
                _telField.text="";
                _contratTypeField.text="";
            }
        }
    }

    Dialog{
        id: _MonthlyPaidEmployeeDialog
        title: "Monthly Paid Employee"

        contentItem: Rectangle{
            id:content_rect_dialog10
            color:"light pink"

            property string p_mc;

            ColumnLayout{
                TextField{
                    id:_mcField
                    placeholderText: qsTr("Enter Monthly Compensation")
                    width:content_rect_dialog10.width*0.9
                }

                RowLayout{
                    Button {
                        id: _dialog10_ok_button_
                        text:"OK"
                        onClicked: {

                            content_rect_dialog10.p_mc= _mcField.text;


                            mc_=parseFloat(content_rect_dialog10.p_mc);

                            model_to_display.append(createElement(_rima.get_EmployeesNumber()-1));

                            mp_dialogIsVisible=false;
                            _mcField.text="";

                            mainWindow.prepareData();

                        }
                    }

                    Button {
                        id: _dialog10_cancel_button_
                        text:"Cancel"
                        onClicked: {
                            _mcField.text="";
                            mp_dialogIsVisible=false;
                        }
                    }
                }
            }

            Component.onCompleted: {
                _mcField.text="";
                }
        }
    }

    Dialog{
            id: _HourlyPaidEmployeeDialog
            title: "Hourly Paid Employee"

            contentItem: Rectangle{
                id:content_rect_dialog11
                color:"light blue"

                property string p_hc;
                property string p_nhrs;

                ColumnLayout{
                    TextField{
                        id:_hcField
                        placeholderText: qsTr("Enter Hourly Compensation")
                        width:content_rect_dialog11.width*0.9
                    }
                    TextField{
                        id:_nhrsField
                        placeholderText: qsTr("Enter Number of Hours Worked")
                        width:content_rect_dialog11.width*0.9
                    }

                    RowLayout{
                        Button {
                            id: _dialog11_ok_button_
                            text:"OK"
                            onClicked: {
                                console.log("index small window: ", index_);

                                content_rect_dialog11.p_hc= _hcField.text;
                                content_rect_dialog11.p_nhrs= _nhrsField.text;
                                hc_=parseFloat(content_rect_dialog11.p_hc);
                                nhrs_=parseFloat(content_rect_dialog11.p_nhrs);

                                console.log(id_,name_,ssn_,tel_,ctype_, hc_, nhrs_);
                                model_to_display.append(createElement(_rima.get_EmployeesNumber()-1));

                                hp_dialogIsVisible=false;
                                _hcField.text="";
                                _nhrsField.text="";
                                mainWindow.prepareData();
                            }
                        }

                        Button {
                            id: _dialog11_cancel_button_
                            text:"Cancel"
                            onClicked: {
                                _hcField.text="";
                                _nhrsField.text="";
                                hp_dialogIsVisible=false;
                            }
                        }
                    }
                }

                Component.onCompleted: {
                    _hcField.text="";
                    _nhrsField.text="";
                    }
            }
    }

    Dialog{
            id: _SalesEmployeeDialog
            title: "Sales Employee"

            contentItem: Rectangle{
                id:content_rect_dialog12
                color:"magenta"

                property string p_mcs;
                property string p_bp;
                property string p_routput;
                property string p_claim;

                ColumnLayout{
                    TextField{
                        id:_mcField_sales
                        placeholderText: qsTr("Enter Monthly Compensation")
                        width:content_rect_dialog12.width*0.9
                    }
                    TextField{
                        id:_bpField
                        placeholderText: qsTr("Enter Bonus Percentage")
                        width:content_rect_dialog12.width*0.9
                    }
                    TextField{
                        id:_routputField
                        placeholderText: qsTr("Enter Realized Output")
                        width:content_rect_dialog12.width*0.9
                    }
                    TextField{
                        id:_claimField
                        placeholderText: qsTr("Enter true or false") //*todo* a checkbox
                        width:content_rect_dialog12.width*0.9
                    }

                    RowLayout{
                        Button {
                            id: _dialog12_ok_button_
                            text:"OK"
                            onClicked: {

                                content_rect_dialog12.p_mcs= _mcField_sales.text;
                                content_rect_dialog12.p_bp= _bpField.text;
                                content_rect_dialog12.p_routput= _routputField.text;
                                content_rect_dialog12.p_claim= _claimField.text;

                                mc_=parseFloat(content_rect_dialog12.p_mcs);
                                bp_=parseFloat(content_rect_dialog12.p_bp);
                                routput_=parseFloat(content_rect_dialog12.p_routput);

                                claim_= content_rect_dialog12.p_claim=="true";

                                model_to_display.append(createElement(_rima.get_EmployeesNumber()-1));

                                sp_dialogIsVisible=false;
                                _mcField_sales.text="";
                                _bpField.text="";
                                _routputField.text="";
                                _claimField.text="";
                                mainWindow.prepareData();
                            }
                        }

                        Button {
                            id: _dialog12_cancel_button_
                            text:"Cancel"
                            onClicked: {
                                _mcField_sales.text="";
                                _bpField.text="";
                                _routputField.text="";
                                _claimField.text="";
                                sp_dialogIsVisible=false;
                            }
                        }
                    }
                }

                Component.onCompleted: {
                    _mcField_sales.text="";
                    _bpField.text="";
                    _routputField.text="";
                    _claimField.text="";

                    }
            }
    }

    Dialog{
        id: _ApdEmployeeDialog
        title: "Append Employee"
        width:300
        height:300

        contentItem: Rectangle{
            id:content_rect_dialog_append
            color:"light green"


            property string p_id;
            property string p_name;
            property string p_ssn;
            property string p_tel;
            property string p_ctype;

            ColumnLayout{
                TextField{
                    id:_idField_append
                    placeholderText: qsTr("Enter ID")
                    width:content_rect_dialog_append.width
                }

                TextField{
                    id:_nameField_append
                    placeholderText: qsTr("Enter name")
                    width:content_rect_dialog_append.width
                }

                TextField{
                    id:_ssnField_append
                    placeholderText: qsTr("Enter ssn")
                    width:content_rect_dialog_append.width
                }

                TextField{
                    id:_telField_append
                    placeholderText: qsTr("Enter telephone number")
                    width:content_rect_dialog_append.width
                }
                TextField{
                    id:_contratTypeField_append
                    placeholderText: qsTr("Enter the contract type (0 for monthly, 1 for hourly, 2 for sales)")
                    width:content_rect_dialog_append.width
                }

                RowLayout{
                    Button {
                        id: _dialog_append_Append_button_
                        text:"Append"
                        onClicked: {
                            content_rect_dialog_append.p_id= _idField_append.text;
                            content_rect_dialog_append.p_name= _nameField_append.text;
                            content_rect_dialog_append.p_ssn=_ssnField_append.text;
                            content_rect_dialog_append.p_tel=_telField_append.text;
                            content_rect_dialog_append.p_ctype=_contratTypeField_append.text;

                            //remove employe
                            var id_tormv;
                            id_tormv=parseInt(content_rect_dialog_append.p_id);
                            _rima.set_Empl_Index_byID(id_tormv);
                            model_to_display.remove(index_);
                            _rima.rmv_Empl(id_tormv); //*todo* maybe change the method so it relies only on _selectedemployee

                            //reset index to end
                            _rima.set_Empl_Index(_rima.get_EmployeesNumber());//***to check

                            // add employee
                            switch(parseInt(content_rect_dialog_append.p_ctype)){
                            case 0:
                                _rima.add_MEmpl();
                                break;
                            case 1:
                                _rima.add_HEmpl();
                                break;
                            case 2:
                                _rima.add_SEmpl();
                                break;
                            default:
                                console.log("contract type field must be filled");
                            }

                            id_=id_tormv;//set id as it was, id_tormv stands for id_to remove
                            name_=content_rect_dialog_append.p_name;
                            tel_=content_rect_dialog_append.p_tel;// no need to parse , it is a string

                            if(content_rect_dialog_append.p_ssn==="")
                                ssn_=0;
                            else
                                ssn_=parseInt(content_rect_dialog_append.p_ssn);


                            if(content_rect_dialog_append.p_ctype==="")
                                ctype_=0;
                            else
                                ctype_=parseInt(content_rect_dialog_append.p_ctype);

                            console.log(id_,name_,ssn_,tel_,ctype_);

                            apd_dialogIsVisible=false;

                            _idField_append.text="";
                            _nameField_append.text="";
                            _ssnField_append.text="";
                            _telField_append.text="";
                            _contratTypeField_append.text="";



                            switch(ctype_){
                            case 0:
                                mp_dialogIsVisible=true;
                                break;
                            case 1:
                                hp_dialogIsVisible=true;
                                break;
                            case 2:
                                sp_dialogIsVisible=true;
                                break;
                            default:
                                ;//show an error or exception *todo*
                            }
                        }
                    }

                    Button {
                        id: _dialog_append_cancel_button_
                        text:"Cancel"
                        onClicked: {
                            _idField_append.text="";
                            _nameField_append.text="";
                            _ssnField_append.text="";
                            _telField_append.text="";
                            _contratTypeField_append.text="";
                            add_dialogIsVisible=false;
                        }
                    }
               }
            }
            Component.onCompleted: {
                _idField_append.text="";
                _nameField_append.text="";
                _ssnField_append.text="";
                _telField_append.text="";
                _contratTypeField_append.text="";
            }
        }
    }

    FileDialog{
        id:_ImportDialog
        title: "Choose file to import"
        nameFilters: "*.json"
        onAccepted: {
            console.log("url : ",_ImportDialog.fileUrl.toString());

            var q= _ImportDialog.fileUrl.toString().split('/');
            var n=q.length;
            console.log("name : ",q[n-1]);
            _rima.set_file_DB(q[n-1]);

            model_to_display.updateModel();
            _rima.set_Empl_Index(_rima.get_EmployeesNumber());
        }
        onRejected: {
            console.log("Canceled");
        }
    }

    RIMA{
        id:_rima
    }

    ListModel{
        id:model_to_display

        Component.onCompleted: {
            _rima.Empl_Index=0;
            for(var i=0;i<_rima.get_EmployeesNumber() /*_rima data base row count*/;i++){
                model_to_display.append(createElement(i));
            }
            mainWindow.prepareData();
        }


        function updateModel () {
            _rima.Empl_Index=0;
            for(var i=0;i<_rima.get_EmployeesNumber() /*_rima data base row count*/;i++){
                model_to_display.clear(i);
            }
            for(var i=0;i<_rima.get_EmployeesNumber() /*_rima data base row count*/;i++){
                model_to_display.append(createElement(i));
            }
        }

    }

    function createElement(k){
        _rima.Empl_Index=k;
       // console.log("element index", _rima.Empl_Index);
       // console.log("index > ",index_,"id > ",id_.toString(),"name > ",name_.toString(), "ssn > ",
                   // ssn_.toString(),"Tel > ",tel_, "Contrat Type >",ctype_,
                   // "Salary: ", salary_);
        return{Idx:index_, I:id_, N:name_,S:ssn_,T:tel_ ,CTp:ctype_, Sal:salary_};
    }

    TableView{
        id:the_table_view
        anchors.fill: parent

        /* //to facilitate debugging we can add the index column
        TableViewColumn{
            role:"Idx"
            title:"Index"

        }*/

        TableViewColumn{
            role:"I"
            title:"ID"

        }

        TableViewColumn{
            role:"N"
            title:"Name"

        }

        TableViewColumn{
            role:"T"
            title:"Tel"

        }

        TableViewColumn{
            role:"S"
            title:"SSN"

        }

        TableViewColumn{
            role:"CTp"
            title:"Contract"

        }

        TableViewColumn{
            role:"Sal"
            title:"Salary"

        }

        model:model_to_display

    }

    Splash{
        splash_height:parent.height*0.7
        splash_width:parent.width*0.9
    }

    property alias xVal: myChart.xvalues;
    property alias yVal: myChart.yvalues;

    function prepareData(){
        var empl_num=_rima.get_EmployeesNumber();
        xVal=[];
        yVal=[];
        for(var myindex=0; myindex<empl_num;myindex++){
            _rima.set_Empl_Index(myindex);
            console.log(index_);
            xVal.push(id_);
            console.log(xVal[myindex]);
            yVal.push(salary_);
            console.log(yVal[myindex]);
        }
    }

    Dialog{
        id:chart_dialog
        visible: false
        width: 400
        height: 300
        Chart{
            id:myChart
            width: parent.width
            height: parent.height
            property int test : 65;
            property var xvalues: ["a","b","c","d","e","f","g"];
            property var yvalues: [1,1,1,1,1,1,1];
            onPaint: {
                //prepareData() function is called when "draw" is clicked and its purpose is to set xvalues qnd yvalues


                line({

                         labels : myChart.xvalues,
                         datasets : [
                             {
                                 fillColor : "rgba(151,187,205,0.5)",
                                 strokeColor : "rgba(151,187,205,1)",
                                 pointColor : "rgba(151,187,205,1)",
                                 pointStrokeColor : "#fff",
                                 data : myChart.yvalues
                             }
                         ]
                     });

            }

            Component.onCompleted: {
                console.debug("Chart is drawn!");
            }
        }
    }
}
