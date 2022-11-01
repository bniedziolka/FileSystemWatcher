#include "WatchedPathsBackend.hpp"

void WatchedPathsBackend::addPath(const QString &path)
{
    m_paths.append(path);
}

bool WatchedPathsBackend::removePath(size_t index)
{
    try
    {
        m_paths.removeAt(index);
        return true;
    }
    catch(...)
    {
    }

    return false;
}

bool WatchedPathsBackend::pathExists(const QString &path) const
{
    return m_paths.contains(path);
}

const QStringList &WatchedPathsBackend::getPaths() const
{
    return m_paths;
}
