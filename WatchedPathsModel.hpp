#ifndef WATCHEDPATHSMODEL_H
#define WATCHEDPATHSMODEL_H

#include <vector>

#include <QAbstractListModel>

class WatchedPathsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit WatchedPathsModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

public slots:
    void addPath(const QString &path);
};

#endif // WATCHEDPATHSMODEL_H
