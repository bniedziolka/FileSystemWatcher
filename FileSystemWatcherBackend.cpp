#include "FileSystemWatcherBackend.hpp"

#include <QDebug>
#include <QDirIterator>
#include <QFileInfo>
#include <QSet>
#include <set>

FileSystemWatcherBackend::FileSystemWatcherBackend()
{
    connect(&m_dirWatcher, &QFileSystemWatcher::directoryChanged,
            this, &FileSystemWatcherBackend::onDirectoryChanged);
    connect(&m_fileWatcher, &QFileSystemWatcher::fileChanged,
            this, &FileSystemWatcherBackend::onFileChanged);
}

void FileSystemWatcherBackend::start(const QStringList &paths)
{
    for (const auto &path : paths)
    {
        QFileInfo info(path);
        if (info.isDir())
        {
            m_dirWatcher.addPath(path);

            QDir dir(path);

            QStringList entryList = dir.entryList(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files);
            m_pathDirsList[path] = entryList;

            QStringList files = dir.entryList(QDir::NoDotAndDotDot | QDir::Files);
            for (const auto &file: files)
            {
                m_fileWatcher.addPath(dir.filePath(file));
            }
        }
    }
}

void FileSystemWatcherBackend::stop()
{
    for (const auto &directory : m_dirWatcher.directories())
    {
        m_dirWatcher.removePath(directory);
        m_pathDirsList.erase(directory);
    }

    for (const auto &directory: m_fileWatcher.files())
    {
        m_fileWatcher.removePath(directory);
    }
}

void FileSystemWatcherBackend::onDirectoryChanged(const QString &path)
{
    QDir dir(path);
    QStringList newEntryList = dir.entryList(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files);
    std::set<QString> newEntrySet(newEntryList.begin(), newEntryList.end());

    QStringList currentEntryList = m_pathDirsList[path];
    std::set<QString> currentEntrySet(currentEntryList.begin(), currentEntryList.end());

    std::set<QString> newFilesSet;
    std::set_difference(newEntrySet.begin(), newEntrySet.end(),
                        currentEntrySet.begin(), currentEntrySet.end(),
                        std::inserter(newFilesSet, newFilesSet.begin()));


    std::set<QString> removedFilesSet;
    std::set_difference(currentEntrySet.begin(), currentEntrySet.end(),
                        newEntrySet.begin(), newEntrySet.end(),
                        std::inserter(removedFilesSet, removedFilesSet.begin()));

    m_pathDirsList[path] = newEntryList;

    if (!newFilesSet.empty() && !removedFilesSet.empty())
    {
        if (newFilesSet.size() == 1 && removedFilesSet.size() == 1)
        {
            const QString name = *newFilesSet.begin();
            QFileInfo info(name);
            Event event;
            event.m_type = Event::Type::Renamed;
            event.m_entry = info.isDir() ? Event::Entry::Folder : Event::Entry::File;
            event.m_path = dir.filePath(name);
            event.m_timestamp = QDateTime::currentDateTime();
            emit eventCreated(event);

            if (!info.isDir())
            {
                m_fileWatcher.addPath(dir.filePath(name));
            }
        }
    }
    else
    {
        if (!newFilesSet.empty())
        {
            for (const auto &path: newFilesSet)
            {
                QFileInfo info(path);
                Event event;
                event.m_type = Event::Type::Created;
                event.m_entry = info.isDir() ? Event::Entry::Folder : Event::Entry::File;
                event.m_path = dir.filePath(path);
                event.m_timestamp = QDateTime::currentDateTime();
                emit eventCreated(event);

                if (!info.isDir())
                {
                    m_fileWatcher.addPath(dir.filePath(path));
                }
            }
        }

        if (!removedFilesSet.empty())
        {
            for (const auto &path: removedFilesSet)
            {
                QFileInfo info(path);
                Event event;
                event.m_type = Event::Type::Deleted;
                event.m_entry = info.isDir() ? Event::Entry::Folder : Event::Entry::File;
                event.m_path = dir.filePath(path);
                event.m_timestamp = QDateTime::currentDateTime();
                emit eventCreated(event);
            }
        }
    }
}

void FileSystemWatcherBackend::onFileChanged(const QString &path)
{
    QFileInfo info(path);
    QString absolutePath = info.absolutePath();
    if (m_pathDirsList[absolutePath].contains(info.fileName()))
    {
        Event event;
        event.m_type = Event::Type::Edited;
        event.m_entry = Event::Entry::File;
        event.m_path = info.absoluteFilePath();
        event.m_timestamp = QDateTime::currentDateTime();
        emit eventCreated(event);
    }
}
