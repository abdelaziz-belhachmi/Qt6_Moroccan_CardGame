#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>
#include "Deck.h"
#include "table.h"
#include "player.h"
#include "controller.h"


bool writeIntToFile(const QString& filename,const int newValue) {
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QFileInfo fileInfo(file);
        QTextStream out(&file);
        out << newValue;
        file.close();
        return true;
    } else {
        return false;
    }
}

int readIntFromFile(const QString& filename) {
    QFile file(filename);

    if (!file.exists()) {
        int defaultValue = 20;
        if (writeIntToFile(filename, defaultValue)) {
            QFileInfo fileInfo(file);
            return defaultValue;
        } else {
           return -1;
        }
    }

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        int value = in.readAll().toInt();
        file.close();
        return value;
    } else {
          return -1;
    }
}


int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    player p1;

    player p2;

    TableCards Tablecards;

    deck DeckOfCards;


    const int prev_score = readIntFromFile("p");


    controller Controller(p1,p2,Tablecards,DeckOfCards,prev_score);

    const QUrl url(u"qrc:/cardGame/Main.qml"_qs);

    engine.rootContext()->setContextProperty("Controlleur", &Controller);

    engine.rootContext()->setContextProperty("p1", &p1);

    engine.rootContext()->setContextProperty("p2", &p2);

    engine.rootContext()->setContextProperty("Table", &Tablecards);

    engine.rootContext()->setContextProperty("Deck", &DeckOfCards);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
