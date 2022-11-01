#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "EventsModel.hpp"

#include "WatchedPathsBackend.hpp"
#include "WatchedPathsModel.hpp"

#include "FileSystemWatcher.hpp"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    qmlRegisterType<WatchedPathsModel>("com.models", 1, 0, "WatchedPathsModel");
    qmlRegisterType<EventsModel>("com.models", 1, 0, "EventsModel");
    qmlRegisterType<FileSystemWatcher>("com.others", 1, 0, "FileSystemWatcher");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
