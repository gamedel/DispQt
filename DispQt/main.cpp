#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "apihandler.h"


void myMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    // В этой функции вы можете обрабатывать сообщения как вам нужно.
    // Например, вы можете записывать их в файл или выводить в консоль.
    // В этом примере мы просто выводим все сообщения в стандартный вывод.
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
    qInstallMessageHandler(myMessageHandler); // Установка обработчика сообщений


    QQmlApplicationEngine engine;
    ApiHandler apiHandler;

    engine.rootContext()->setContextProperty("apiHandler", &apiHandler);

    engine.load(QUrl(QStringLiteral("qrc:/qt/qml/dispqt/main.qml")));

   
    if (engine.rootObjects().isEmpty()) 
        return -1;

    return app.exec();
}


