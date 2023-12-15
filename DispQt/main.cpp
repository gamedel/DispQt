#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "controller.h"


void myMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    // � ���� ������� �� ������ ������������ ��������� ��� ��� �����.
    // ��������, �� ������ ���������� �� � ���� ��� �������� � �������.
    // � ���� ������� �� ������ ������� ��� ��������� � ����������� �����.
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s\n", localMsg.constData());
        break;
    case QtInfoMsg:
        fprintf(stderr, "Info: %s\n", localMsg.constData());
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s\n", localMsg.constData());
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s\n", localMsg.constData());
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s\n", localMsg.constData());
        abort();
    }
}


int main(int argc, char* argv[])
{

    

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    qInstallMessageHandler(myMessageHandler); // ��������� ����������� ���������


    QQmlApplicationEngine engine;
    Controller controller;

    engine.rootContext()->setContextProperty("controller", &controller);

    engine.load(QUrl(QStringLiteral("qrc:/qt/qml/dispqt/Main.qml")));

   
    if (engine.rootObjects().isEmpty()) 
        return -1;

    return app.exec();
}


