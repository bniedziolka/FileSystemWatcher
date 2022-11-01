#include <QUrl>

#include "WatchedPathsModel.hpp"

#include "WatchedPathsBackend.hpp"

WatchedPathsModel::WatchedPathsModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

QHash<int, QByteArray> WatchedPathsModel::roleNames() const
{
    return {
        { Qt::DisplayRole, "path" },
    };
}

int WatchedPathsModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : WatchedPathsBackend::instance().getPaths().size();
}

QVariant WatchedPathsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || Qt::DisplayRole != role)
    {
        return {};
    }

    try
    {
        const auto &row = WatchedPathsBackend::instance().getPaths().at(index.row());
        return row;
    }
    catch(...)
    {
    }

    return {};
}

bool WatchedPathsModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    auto result = WatchedPathsBackend::instance().removePath(row);
    endRemoveRows();
    return result;
}

void WatchedPathsModel::addPath(const QString &path)
{
    const QUrl url{path};

    if (WatchedPathsBackend::instance().pathExists(url.toLocalFile()))
    {
        return;
    }

    const auto size = WatchedPathsBackend::instance().getPaths().size();
    beginInsertRows({}, size, size);
    WatchedPathsBackend::instance().addPath(url.toLocalFile());
    endInsertRows();
}
