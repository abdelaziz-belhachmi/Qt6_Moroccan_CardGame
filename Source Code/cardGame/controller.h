#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <iostream>
#include <QDebug>
#include <QRandomGenerator>
#include <QThread>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileInfo>


#include "card.h"
#include "Deck.h"
#include "player.h"
#include "table.h"


class controller : public QObject
{
    Q_OBJECT


private:
    TableCards *tableCards;// table
    deck *Deck; // DECK
    player *p1; // the user is p1
    player *p2; // Computer player is p2
    QString cardStyle="A";// its A by default , can be changed by user
    QString Difficulty= "MEDIUM";// by default is MEDIUM
    int previousScore;
    int plusxp;
    QString path ="p";
    bool sleepvar;
    int score;// I will store it on a local file , in order to have it available after leaving the game,
    int successivetwos;// this is a counter used to count how many successive twos been put
    bool gamesinished=false; // signal to show winner page

    // tmp qlists
    QList<card> q;
    QList<card> y;
    QList<card> tmp;
    QList<card> rawTbale;

    // tmp card 
    card x;

    Q_PROPERTY(bool gamesinished NOTIFY gamesinishedChanged FINAL)

    Q_PROPERTY(QString Difficulty READ getDifficulty WRITE setDifficulty NOTIFY DifficultyChanged FINAL)

    Q_PROPERTY(int plusxp READ getPlusxp WRITE setPlusxp NOTIFY plusxpChanged FINAL)

    Q_PROPERTY(bool sleepvar NOTIFY sleepinqml FINAL)

public:

    controller(player & x, player & y , TableCards & t, deck & d,const int previous_score);

    void initialiseTable();

    void initialiseDeck();

    void initialisePlayers();

    void startNewGame();

    void putfirstcardtotable();

    void destributecardstoplayers();

    void switchTurnsToPlayer();

    void switchTurnsToComputer();

    void computerplay();

    void liftcardfromdeck(player & p);

    void decideforseven();

    void CheckIfAWinner(player & p);

    bool getGamesinished() const;

    void setGamesinished(bool newGamesinished);

    bool writeIntToFile(const QString & filename, int newValue);

    deck * getDeck() const;

    void setDeck(deck * newDeck);

    player * getP1()const;

    void setP1(player * newP1);

    player * getP2()const;

    void setP2(player * newP2);

    TableCards * getTable() const;

    void setTable(TableCards * newTable);

    void sleep();

    QString getDifficulty() const;

    void setPlusxp(int newPlusxp);

    QString readUsernameFromFile(const QString& filename, const QString& defaultUsername);

    bool writeUsernameToFile(const QString & filename, const QString& username);

    void setSleep(bool newSleep);

    // slot to start the game from qml button
    Q_INVOKABLE void startTheParty();

    Q_INVOKABLE void computerplayagain();

    Q_INVOKABLE void userWantToputcarttoTable(int num , QString name);

    Q_INVOKABLE void userWanttoliftcardfromdeck();

    Q_INVOKABLE void userchosenewcardtype();

    Q_INVOKABLE void changeCardStyle();

    Q_INVOKABLE QString getcardStyle()const;

    Q_INVOKABLE void saveScore();

    Q_INVOKABLE void setDifficulty(const QString &newDifficulty);

    Q_INVOKABLE int getPlusxp() const;

    Q_INVOKABLE QString getUserName();

    Q_INVOKABLE void setNewUserName(QString userName);

    ~controller();

signals:

    void gamesinishedChanged();
    void DeckChanged();
    void p1Changed();
    void p2Changed();
    void tableChanged();
    void DifficultyChanged();
    void plusxpChanged();
    void sleepinqml();
};

#endif // CONTROLLER_H
