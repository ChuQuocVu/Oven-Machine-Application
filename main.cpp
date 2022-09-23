#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "recipemodel.h"
#include "recipe.h"
#include "counter.h"
#include "datasource.h"
#include "learnimage.h"
#include "oven.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    RecipeModel mModel;
    DataSource * ds = new DataSource(&mModel);
    mModel.setDataSource(ds);

//    qmlRegisterType<Counter>();
    qmlRegisterType<Counter>("QUOCVU.Oven", 1, 0, "Timer");
    qmlRegisterType<LearnImage>("QUOCVU.Oven", 1, 0, "RecipeImage");
    qmlRegisterType<Oven>("QUOCVU.Oven", 1, 0, "Mode");

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("RecipeModel", &mModel);
    engine.rootContext()->setContextProperty("myDataSource", ds);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
