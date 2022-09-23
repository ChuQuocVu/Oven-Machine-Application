#include "datasource.h"

DataSource::DataSource(QObject *parent)
    : QObject{parent}
{
    addRecipe(new Recipe("Beef", 300, 200, false, ":/Recipes Images/cooked/beef.jpg"));
    addRecipe(new Recipe("Cake", 450, 200, false, ":/Recipes Images/cooked/cake.jpg"));
    addRecipe(new Recipe("Chicken", 750, 200, false, ":/Recipes Images/cooked/chicken.jpg"));
    addRecipe(new Recipe("Pizza", 350, 200, false, ":/Recipes Images/cooked/pizza.jpg"));

//    addRecipe(new Recipe("Beef", 15, 200, false, ":/Recipes Images/cooked/beef1.jpg"));
//    addRecipe(new Recipe("Cake", 15, 200, false, ":/Recipes Images/cooked/cake1.jpg"));
//    addRecipe(new Recipe("Chicken", 15, 200, false, ":/Recipes Images/cooked/chicken1.jpg"));
//    addRecipe(new Recipe("Pizza", 15, 200, false, ":/Recipes Images/cooked/pizza1.jpg"));
}

QList<Recipe *> DataSource::DataItems()
{
    return mRecipes;
}

void DataSource::addRecipe(Recipe * receipe)
{
    emit preRecipeAdded();
    mRecipes.append(receipe);
    emit postRecipeAdded();
}

void DataSource::addRecipe(const QString &name, float &cookingTime, float &temperature, QString &fileImage)
{
    Recipe * recipe = new Recipe(name, cookingTime, temperature, false,fileImage, this);
    addRecipe(recipe);
}

void DataSource::removeRecipe(int index)
{
    emit preRecipeRemoved(index);
    mRecipes.removeAt(index);
    emit postRecipeRemoved();
}

void DataSource::removeLast()
{
    int idx = mRecipes.size();
    removeRecipe(idx - 1);
}
