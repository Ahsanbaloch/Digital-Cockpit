#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "vcan.h"
#include "vcanworker.h"
#include <QTimer>
#include <QQmlContext>
#include <iostream>
#include <QThread>

int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // Create an instance of vcan
    vcan v_can;

    // Register the vcan class with QML
    qmlRegisterType<vcan>("com.example.vcan", 1, 0, "VCan");

    // Set the v_can instance as a context property for QML
    engine.rootContext()->setContextProperty("vcan", &v_can);

     // Create a worker and move it to a new thread
    VCanWorker *worker = new VCanWorker(&v_can); // Pass v_can instance to worker
    QThread *workerThread = new QThread();

    worker->moveToThread(workerThread);


    QObject::connect(workerThread, &QThread::started, worker, &VCanWorker::run);
    QObject::connect(worker, &VCanWorker::finished, workerThread, &QThread::quit);
    QObject::connect(worker, &VCanWorker::finished, worker, &QObject::deleteLater);
    QObject::connect(workerThread, &QThread::finished, workerThread, &QObject::deleteLater);

    QObject::connect(worker, &VCanWorker::error, [](const QString &errorString) {
        qCritical() << "Error:" << errorString;
        QCoreApplication::exit(-1);
    });

    // Start the worker thread
    workerThread->start();
    engine.load(QUrl(QStringLiteral("qrc:/Instrument_cluster/Main.qml")));

    // engine.loadFromModule("Instrument_cluster", "Main");
    
    return app.exec();
    
}

