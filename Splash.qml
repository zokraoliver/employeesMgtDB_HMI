import QtQuick 2.0
import QtQuick.Window 2.1

Item{
    property alias splash_height: splash_window.height
    property alias splash_width: splash_window.width
    Window{
        id:splash_window
        color:"light green"
        title:"ZOKRA's"
        modality: Qt.ApplicationModal
        flags:Qt.SplashScreen
        property int timeoutinterval: 3000
        signal timeout
        x:(Screen.width-splash_window.width)/2
        y:(Screen.height-splash_window.height)/2

        Image{
            id:splashImage
            source: "../CompanyManagement1/cm1.png"

            transform: Scale{
                origin.x:0
                origin.y:0
                xScale:splash_window.width/splashImage.width
                yScale: splash_window.height/splashImage.height
            }

            MouseArea{
                anchors.fill: parent
                onClicked:Qt.quit()
            }
        }

        Timer{
            interval:splash_window.timeoutinterval; running:true; repeat:false
            onTriggered:
            {
                splash_window.visible= false;
                splash_window.timeout();
            }
        }
        Component.onCompleted: visible= true

    }
}
