#ifndef DECK_H
#define DECK_H

#include <QObject>
#include <random>
#include <vector>
#include "card.h"
#include <QDebug>

class deck : public QObject
{
    Q_OBJECT

private:
    QList<card> deckOfCards;
    QList<card> q;
    card tmpCard;

    int numberOfCardsToLift=1;// counter for consecutive twos . usualy you sould lift 1 card , unless if you got two-ed on :)

    Q_PROPERTY(QList<card> deckOfCards READ getDeckOfCards WRITE setDeckOfCards NOTIFY deckOfCardsChanged FINAL)

    Q_PROPERTY(int numberOfCardsToLift READ getNumberOfCardsToLift WRITE setNumberOfCardsToLift RESET resetNumberOfCardstoLift NOTIFY numberOfCardsToLiftChanged FINAL)

public:
    // constructor of deck of cards , it construct all the neccessary cards inside the Qlist deckOfCards.
    deck();

    deck & operator = (const deck & other);

    QList<card> getDeckOfCards() ;

    QList<card> give_a_Card();

    void filldeck();

    // reset the whole deck instance , clearing all values and reseting to base values
    void reset();

    void incrementNumberofCardsToLiftTO(int x);

    void incrementTwo();

    void resetNumberOfCardstoLift();

    bool isempty();

    void shuffle();

    void setDeckOfCards(QList<card> & newDeckOfCards);

    void setNumberOfCardsToLift(int newNumberOfCardsToLift);

    Q_INVOKABLE const int getNumberOfCardsToLift()const ;

    Q_INVOKABLE const int deckSize()const;


signals:

    void deckOfCardsChanged();
    void numberOfCardsToLiftChanged();

};

#endif // DECK_H
