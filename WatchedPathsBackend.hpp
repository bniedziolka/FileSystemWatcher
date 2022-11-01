#ifndef WATCHEDPATHSBACKEND_HPP
#define WATCHEDPATHSBACKEND_HPP

#include <QObject>
#include <QStringList>

#include "Singleton.hpp"

class WatchedPathsBackend : public QObject, public Singleton<WatchedPathsBackend>
{
    Q_OBJECT
public:
    void addPath(const QString &path);
    bool removePath(size_t index);

    bool pathExists(const QString &path) const;

    const QStringList &getPaths() const;

private:
    QStringList m_paths;
};

#endif // WATCHEDPATHSBACKEND_HPP
