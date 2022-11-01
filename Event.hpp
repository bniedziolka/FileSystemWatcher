#ifndef EVENT_HPP
#define EVENT_HPP

#include <QDateTime>

class Event
{
public:
    enum Type
    {
        Created,
        Deleted,
        Edited,
        Renamed
    };
    enum Entry
    {
        File,
        Folder
    };

    Event() = default;

    Type m_type;
    Entry m_entry;
    QString m_path;
    QDateTime m_timestamp;

};

#endif // EVENT_HPP
