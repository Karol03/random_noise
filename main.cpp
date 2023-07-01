#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "randomnoise.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    RandomNoise* randomNoise = new RandomNoise();
    engine.rootContext()->setContextProperty("engine", randomNoise);

    const QUrl url(u"qrc:/random_noise/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
