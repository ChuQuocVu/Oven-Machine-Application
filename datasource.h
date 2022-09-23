#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QObject>
#include "recipe.h"

class DataSource : public QObject
{
    Q_OBJECT
public:
    explicit DataSource(QObject *parent = nullptr);

    QList<Recipe *> DataItems();

    Q_INVOKABLE void addRecipe(Recipe * receipe);
    Q_INVOKABLE void addRecipe(const QString &name, float &cookingTime, float &temperature, QString &fileImage);
    Q_INVOKABLE void removeRecipe(int index);
    Q_INVOKABLE void removeLast();

signals:

    void preRecipeAdded();
    void postRecipeAdded();
    void preRecipeRemoved(int index);
    void postRecipeRemoved();

private:
    QList<Recipe *> mRecipes;
};

#endif // DATASOURCE_H
