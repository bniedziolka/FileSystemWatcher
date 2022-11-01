#ifndef FILESYSTEMWATCHERBACKEND_H
#define FILESYSTEMWATCHERBACKEND_H

#include <unordered_map>

#include <QFileSystemWatcher>
#include <QObject>

#include "Event.hpp"
#include "Singleton.hpp"

class FileSystemWatcherBackend : public QObject, public Singleton<FileSystemWatcherBackend>
{
    Q_OBJECT
public:
    FileSystemWatcherBackend();
    void start(const QStringList &paths);
    void stop();

signals:
    void eventCreated(const Event &event);

private:
    void onDirectoryChanged(const QString &path);
    void onFileChanged(const QString &path);

    QFileSystemWatcher m_dirWatcher;
    QFileSystemWatcher m_fileWatcher;
    std::unordered_map<QString, QStringList> m_pathDirsList;
};

#endif // FILESYSTEMWATCHERBACKEND_H
