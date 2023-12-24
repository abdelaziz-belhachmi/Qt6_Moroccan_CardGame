#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QSet>
#include <QRandomGenerator>
#include "card.h"

class player : public QObject
{
    Q_OBJECT


private:
    QString PlayerName;
    QList<card> hand;// have a Q_property to notify qml onChange
    bool turn= false; 
    bool isComputer = false ; 
    card tmp;
    bool firstdistro=true;
    bool hakem;
    QString cardStyle = "A"; // card style is A by default user can chose other style
    int Score;

    Q_PROPERTY(QList<card> hand READ getHand WRITE liftCards NOTIFY handChanged FINAL)

    Q_PROPERTY(bool hakem NOTIFY hakemChanged FINAL)

    Q_PROPERTY(int Score READ getScore NOTIFY scoreChanged FINAL)

public:
    // player constructor
    player(QString const name): PlayerName(name) {};

    player(){};

    player(QString const name,bool isplayerComputer): PlayerName(name),isComputer(isplayerComputer) {};

    player & operator = (const player & other);

    QString cardtypeofdos()const;

    QString typeoffirstcardinhand()const;

    QString whatcardtypeidonthave();

    QList<QString> returnqlistofcardtypes();

    QList<card> showHand();

    QList<card> getHand() const;

    QString getCardstyle()const;

    void setName(QString & name);

    void resetUSERHand();

    void resetCOMPUTERHand();

    void setCardstyle(QString n);

    // this function should be called when initialising new instance of player and setting it as computer player
    bool setAsComputerPlayer();

    bool unSetAsComputerPlayer();

    void setfirstdist();

    void setMyturn();

    void UnsetMyturn();

    bool iscomputer();

    void incrementScore(int newScore);

    // takes a QList as parametre in order to get one or multiple cards at once
    void liftCards( QList<card> & ListOfCards);

    // player will return only 1 card to the table , no more , so the retun type is card , only the table will be getting the card from the player.
    card PutDownCArd(int num ,bool); // if it takes int and bool , it means that this function puts card matching number given as parametre

    card PutDownCArd(int const index);// if it take int only , mean put card by given index

    card PutDownCArd(QString const name);// put card by matching the given name
    // put card matching either name or number, case doesnt matter for computer , but matter for player . for player it put exactly the card with name and number
    card PutDownCArd(int num , QString const name);

    int findCardIndex(int const num ,QString const name)const;

    int findCardIndex(int const num )const;

    int findCardIndex(QString const name)const;

    bool doihavecondidateCard(int const num , QString const cardname);

    // check if i have card with number 2
    bool doihavedos();

    // check if i have card with number 7
    bool doihaveseven();

    // checks for player hand each turn after playing, to see if the player won or not yet
    // return true if empty
    Q_INVOKABLE bool isMyHandEmpty();

    Q_INVOKABLE const int numberOfcardsInHand()const;

    Q_INVOKABLE const int qmlgetCardNumberbyIndex(int i)const;

    Q_INVOKABLE const QString qmlgetCardNamebyIndex(int i)const;

    Q_INVOKABLE const QString qmlgetCardImagePathbyIndex(int i)const;

    Q_INVOKABLE QString gettier() const;

    Q_INVOKABLE int getScore() const;

    Q_INVOKABLE bool isItMyTurn();

    Q_INVOKABLE bool firstdistrubution();

    Q_INVOKABLE void insetfirstdist();


    ~player();

signals:
    void handChanged();
    void hakemChanged();
    void scoreChanged();
};

#endif // PLAYER_H
