#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "presenter_qml.h"

#include<QFile>
#include <QDebug>

/* When you find *todo* in the code, it is an indication
 * of lacking functionnalities.
 * Feel free to improve it!
 */
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<Presenter_QML>("CompanyMgtBackend",1,0,"RIMA");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("../Test.qml")));

    return app.exec();

}

//*todo* to recheck the code and to replace the qDebug() warnings by exception handlers
