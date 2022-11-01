#ifndef FILESYSTEMWATCHER_HPP
#define FILESYSTEMWATCHER_HPP

#include <QObject>

class FileSystemWatcher : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isRunning READ isRunning NOTIFY isRunningChanged)
public:
    explicit FileSystemWatcher(QObject *parent = nullptr);

    bool isRunning() const;

public slots:
    void start();
    void stop();
    void clear();

signals:
    void isRunningChanged();

private:
    void setIsRunning(bool value);

    bool m_isRunning = false;
};

#endif // FILESYSTEMWATCHER_HPP
