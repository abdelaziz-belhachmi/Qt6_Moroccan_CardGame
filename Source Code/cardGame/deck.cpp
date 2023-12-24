#include "deck.h"

void deck::setNumberOfCardsToLift(int newNumberOfCardsToLift)
{
    if (numberOfCardsToLift == newNumberOfCardsToLift)
        return;
    numberOfCardsToLift = newNumberOfCardsToLift;
    emit numberOfCardsToLiftChanged();
}

deck::deck(){
}

deck &deck::operator =(const deck &other){

    deckOfCards.clear();
    deckOfCards = other.deckOfCards;

    q.clear();
    q = other.q;

    numberOfCardsToLift = other.numberOfCardsToLift;

    emit numberOfCardsToLiftChanged();
    emit deckOfCardsChanged();

    return *this;
}

void deck::filldeck(){
    QString N = "SFJZ";
    for (int x = 0; x < 4; ++x) {

        QString S = N.mid(x, 1);
        //This code creates a new string S with a length of 1, containing the character at index x from the string N.

        //
        for (int i = 1; i <= 7; ++i) {
            card c(i,S);
            deckOfCards.append(c);
        }

        //
        for (int i = 10; i <= 12; ++i) {
            card c(i,S);
            deckOfCards.append(c);
        }
        //
    }
    return;
}

void deck::reset(){
    if (deckOfCards.size() > 0){
        deckOfCards.clear();
        /* then refill */
        filldeck();
    }else if (deckOfCards.size() == 0 ){
        filldeck();
    }else {
        QList<card> d;
        this->deckOfCards = d;

        filldeck();

    }

    if (q.size() >0){
        q.clear();
    }

    resetNumberOfCardstoLift();

    emit numberOfCardsToLiftChanged();
    emit deckOfCardsChanged();

    return;
}

const int deck::getNumberOfCardsToLift()const {
    int x = numberOfCardsToLift;
    return x;
}

void deck::incrementNumberofCardsToLiftTO(int x){
    this->numberOfCardsToLift = x;
    emit numberOfCardsToLiftChanged();
}

void deck::incrementTwo(){

    switch (numberOfCardsToLift) {
    case 1:
        numberOfCardsToLift = 2;
        emit numberOfCardsToLiftChanged();
        break;
    case 2:
        numberOfCardsToLift = 4;
        emit numberOfCardsToLiftChanged();
        break;
    case 4:
        numberOfCardsToLift = 6;
            emit numberOfCardsToLiftChanged();
        break;
    case 6:
        numberOfCardsToLift = 8;
            emit numberOfCardsToLiftChanged();
        break;
    default:
        resetNumberOfCardstoLift();
        break;
    }
}

void deck::resetNumberOfCardstoLift(){
    this->numberOfCardsToLift = 1;
        emit numberOfCardsToLiftChanged();
}

bool deck::isempty(){
    return deckOfCards.isEmpty();
}

const int deck::deckSize()const{
    int x = deckOfCards.size();
    return x;
}

void deck::shuffle(){
    std::random_device rd;
    std::mt19937 g(rd());

    // Use the random number generator to shuffle the deck
    std::shuffle(deckOfCards.begin(), deckOfCards.end(), g);
    std::shuffle(deckOfCards.begin(), deckOfCards.end(), g);

}

QList<card> deck::give_a_Card(){

    if ( deckOfCards.size() >= numberOfCardsToLift ){

        q.clear();

        for (int i=0 ; i < numberOfCardsToLift; ++i){

            tmpCard = deckOfCards.last();

            q.append(tmpCard);

            deckOfCards.removeLast();

        }

        emit deckOfCardsChanged();

        return q;
    }

}

QList<card> deck::getDeckOfCards()
{
    return deckOfCards;
}

// it appends and shuffle
void deck::setDeckOfCards(QList<card> &newDeckOfCards)
{   
    deckOfCards.append(newDeckOfCards);
    shuffle();

    emit deckOfCardsChanged();
    emit numberOfCardsToLiftChanged();
}
