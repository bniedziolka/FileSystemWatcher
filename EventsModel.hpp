#ifndef EVENTSMODEL_H
#define EVENTSMODEL_H

#include <QAbstractTableModel>

#include <Event.hpp>

class EventsModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit EventsModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

#endif // EVENTSMODEL_H
