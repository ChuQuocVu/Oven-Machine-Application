#ifndef RECIPEMODEL_H
#define RECIPEMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "recipe.h"
#include "datasource.h"

class RecipeModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(DataSource* dataSource READ dataSource WRITE setDataSource NOTIFY dataSourceChanged)

    enum RecipeRoles
    {
        NameRole = Qt::UserRole + 1,
        CookingTimeRole,
        TemperatureRole,
        StatusRole,
        FileImageRole
    };

public:
    explicit RecipeModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex& index) const;
    QHash<int, QByteArray> roleNames() const;

    DataSource *dataSource() const;
    void setDataSource(DataSource* dataSource);

signals:

    void dataSourceChanged(DataSource* dataSource);

private:
    DataSource* m_dataSource;
    bool isConnected{false};
};

#endif // RECIPEMODEL_H
