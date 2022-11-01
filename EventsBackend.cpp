#include "EventsBackend.hpp"

#include "FileSystemWatcherBackend.hpp"

EventsBackend::EventsBackend()
{
    connect(&FileSystemWatcherBackend::instance(),
            &FileSystemWatcherBackend::eventCreated,
            this,
            &EventsBackend::onEventCreated);
}

const std::vector<Event> &EventsBackend::getEvents() const
{
    return m_events;
}

void EventsBackend::clear()
{
    m_events.clear();
    emit eventsRemoved();
}

void EventsBackend::onEventCreated(const Event &event)
{
    m_events.push_back(event);
    emit eventAdded();
}

