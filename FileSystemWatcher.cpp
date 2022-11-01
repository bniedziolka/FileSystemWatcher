#include "FileSystemWatcher.hpp"

#include "EventsBackend.hpp"
#include "FileSystemWatcherBackend.hpp"
#include "WatchedPathsBackend.hpp"

FileSystemWatcher::FileSystemWatcher(QObject *parent) : QObject(parent)
{

}

bool FileSystemWatcher::isRunning() const
{
    return m_isRunning;
}

void FileSystemWatcher::start()
{
    const auto &paths = WatchedPathsBackend::instance().getPaths();
    FileSystemWatcherBackend::instance().start(paths);

    setIsRunning(true);
}

void FileSystemWatcher::stop()
{
    FileSystemWatcherBackend::instance().stop();

    setIsRunning(false);
}

void FileSystemWatcher::clear()
{
    EventsBackend::instance().clear();
}

void FileSystemWatcher::setIsRunning(bool value)
{
    if (value != m_isRunning)
    {
        m_isRunning = value;
        emit isRunningChanged();
    }
}
