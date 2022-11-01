#include "EventsModel.hpp"

#include "EventsBackend.hpp"

namespace
{
constexpr int COLUMN_COUNT = 4;
}

EventsModel::EventsModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    connect(&EventsBackend::instance(), &EventsBackend::eventAdded,
            this, [&]{
        const auto size = EventsBackend::instance().getEvents().size();
        beginInsertRows({}, size, size);
        endInsertRows();
    });

    connect(&EventsBackend::instance(), &EventsBackend::eventsRemoved,
            this, [&]{
       beginResetModel();
       endResetModel();
    });
}

QHash<int, QByteArray> EventsModel::roleNames() const
{
    return {
        { Qt::DisplayRole, "cellValue" },
    };
}

QVariant EventsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section)
        {
        case 0: return tr("Event type");
        case 1: return tr("Path");
        case 2: return tr("Is folder");
        case 3: return tr("Timestamp");
        default: return {};
        }
    }
    return {};
}

int EventsModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : EventsBackend::instance().getEvents().size();
}

int EventsModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : COLUMN_COUNT;
}

QVariant EventsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
    {
        return {};
    }

    auto typeToString = [](Event::Type type) -> QString {
        switch (type)
        {
        case Event::Type::Created:
            return tr("Created");
        case Event::Type::Deleted:
            return tr("Deleted");
        case Event::Type::Edited:
            return tr("Edited");
        case Event::Type::Renamed:
            return tr("Renamed");
        default:
            return {};
        }
    };

    try
    {
        const auto &row = EventsBackend::instance().getEvents().at(index.row());
        switch (index.column())
        {
        case 0: return typeToString(row.m_type);
        case 1: return row.m_path;
        case 2: return row.m_entry == Event::Entry::File ? tr("No") : tr("Yes");
        case 3: return row.m_timestamp.toString("dd/MM/yyyy HH:mm");
        default: return {};
        }
    }
    catch(...)
    {
        return {};
    }
}
