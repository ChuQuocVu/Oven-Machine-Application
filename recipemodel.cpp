#include "recipemodel.h"

RecipeModel::RecipeModel(QObject *parent)
    : QAbstractListModel{parent}
{

}

int RecipeModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_dataSource->DataItems().size();
}

QVariant RecipeModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() > m_dataSource->DataItems().size())
    {
        return QVariant();
    }

    Recipe * recipe = m_dataSource->DataItems().at(index.row());

    switch (role) {
    case NameRole:
        return recipe->name();
    case CookingTimeRole:
        return recipe->cookingTime();
    case TemperatureRole:
        return recipe->temperature();
    case StatusRole:
        return recipe->state();
    case FileImageRole:
        return recipe->fileImage();
    default:
        return QVariant();
    }

    return QVariant();
}

bool RecipeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Recipe * recipe = m_dataSource->DataItems().at(index.row());
    bool isSomeThingChanged = false;

    switch (role) {

    case NameRole:
        if(recipe->name() != value.toString())
        {
            recipe->setname(value.toString());
            qDebug() << "Name has changed to: " << recipe->name() << Qt::endl;
            isSomeThingChanged = true;
        }
        break;
    case CookingTimeRole:
        if(recipe->cookingTime() != value.toFloat())
        {
            recipe->setCookingTime(value.toFloat());
            qDebug() << "CookingTime has changed to:" << recipe->cookingTime() << Qt::endl;
            isSomeThingChanged = true;
        }
        break;
    case TemperatureRole:
        if(recipe->temperature() != value.toFloat())
        {
            recipe->setTemperature(value.toFloat());
            qDebug() << "Temperature has changed to:" << recipe->temperature() << Qt::endl;
            isSomeThingChanged = true;
        }
        break;
    case StatusRole:
        if(recipe->state() != value.toBool())
        {
            recipe->setState(value.toBool());
            qDebug() << "State has changed to:" << recipe->state() << Qt::endl;
            isSomeThingChanged = true;
        }
        break;

        // Check Later (This role may not working)
    case FileImageRole:
        if(recipe->fileImage() != value.toString())
        {
            recipe->setFileImage(value.toString());
            qDebug() << "State has changed to:" << recipe->fileImage() << Qt::endl;
            isSomeThingChanged = true;
        }
        break;
    }

    if(isSomeThingChanged)
    {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags RecipeModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
    {
        return Qt::NoItemFlags;
    }

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> RecipeModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "Name";
    roles[CookingTimeRole] = "CookingTime";
    roles[TemperatureRole] = "Temperature";
    roles[StatusRole] = "State";
    roles[FileImageRole] = "FileImage";

    return roles;
}

DataSource *RecipeModel::dataSource() const
{
    return m_dataSource;
}

void RecipeModel::setDataSource(DataSource *dataSource)
{
    beginResetModel();

    if(m_dataSource && isConnected)
        m_dataSource->disconnect(this);

    m_dataSource = dataSource;

    connect(m_dataSource, &DataSource::preRecipeAdded, this, [=](){
        const int index = m_dataSource->DataItems().size();
        beginInsertRows(QModelIndex(), index, index);
    });

    connect(m_dataSource, &DataSource::postRecipeAdded, this, [=](){
        endInsertRows();
    });

    connect(m_dataSource, &DataSource::preRecipeRemoved, this, [=](int index){
        beginRemoveRows(QModelIndex(), index, index);
    });

    connect(m_dataSource, &DataSource::postRecipeRemoved, this, [=]()
    {
        endRemoveRows();
    });

    isConnected = true;

    endResetModel();
}









