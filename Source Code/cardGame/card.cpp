#include "card.h"


card::card(const int &num, const QString &name): cardNumber(num),cardName(name){
}

card::card(const card &c):cardName(c.cardName),cardNumber(c.cardNumber) {
}

bool card::operator ==(const card &c){
    if( cardName == c.cardName && cardNumber == c.cardNumber){
        return true;
    }
    else{
        return false;
    }
}

card &card::operator=(const card &c){

    this->cardName = c.cardName;
    this->cardNumber = c.cardNumber;

    return *this;
}

QString card::getCardImagePath()const{
    QString x = QString::number(cardNumber) + cardName + ".png";
    return x;
}

QString card::getflippedimage()const{
    return "back.png";
}


int card::getCardNumber()const{
    return cardNumber;
}

QString card::getCardName()const{
    return cardName;
}

card::~card()
{

}
