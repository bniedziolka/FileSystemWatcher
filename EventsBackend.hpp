#ifndef EVENTSBACKEND_H
#define EVENTSBACKEND_H

#include <vector>

#include <QObject>

#include "Event.hpp"
#include "Singleton.hpp"

class EventsBackend : public QObject, public Singleton<EventsBackend>
{
    Q_OBJECT
public:
    EventsBackend();

    const std::vector<Event> &getEvents() const;

    void clear();

signals:
    void eventAdded();
    void eventsRemoved();

private:
    void onEventCreated(const Event &event);

    std::vector<Event> m_events;
};

#endif // EVENTSBACKEND_H
