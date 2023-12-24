#include "table.h"


const QString TableCards::getRequestedCardType()const
{
    return requestedCardType;
}

void TableCards::setRequestedCardType(QString newRequestedCardType)
{
    if (requestedCardType == newRequestedCardType)
        return;
    requestedCardType = newRequestedCardType;
    //
    emit requestedCardTypeChanged();
}

QList<card> & TableCards::getTablecardss()
{
    return tablecardss;
}

QString TableCards::getCardstyle()const{
    return cardStyle;
}
void TableCards::setCardstyle(QString n){
        cardStyle = n;
}

QString const TableCards::getLastCardImg()const
{
    QString x = "assets/images/"+getCardstyle()+"/"+LastCardImg;
    return x;
}

void TableCards::setLastCardImg( QString &newLastCardImg)
{
    LastCardImg = newLastCardImg;
}

// sets lastcardimg and this card as last requestedcardtype
QString TableCards::getChangeCardType() const
{
    return changeCardType;
}

TableCards &TableCards::operator =(const TableCards &otherTable){

    tablecardss.clear();
    this->tablecardss = otherTable.tablecardss;

    tmpQ.clear();
    this->tmpQ = otherTable.tmpQ;

    this->numberofConsecutiveTwos=otherTable.numberofConsecutiveTwos;
    this->LastCardImg = otherTable.LastCardImg;
    this->changeCardType = otherTable.changeCardType;
    this->requestedCardType = otherTable.requestedCardType;

    return *this;
}

void TableCards::addCardtoTable(card & c)
{
    //   adding new card to table
    tablecardss.append(c);
    QString x = c.getCardImagePath();
    setLastCardImg(x);

    QString rt = c.getCardName();
    setRequestedCardType( rt );

    emit tablecardssChanged();
}

card & TableCards::getLastCard()
{
    return tablecardss.last();
}

const QString TableCards::getLastCardName(){
    return tablecardss.last().getCardName();
}

const int TableCards::getLastCardNumber(){
    return tablecardss.last().getCardNumber();
}

QList<card> & TableCards::giveBackMostCards(){

    emit shufflesignalChanged();

    tmpQ.clear();

        // i give back most cards
        int sz = tablecardss.size();

        for (int i= 0 ; i < sz-2 ; ++i){
        card tm(tablecardss[i]);
        tmpQ.append(tm);
     }

        card lst(tablecardss.last());
        tablecardss.clear();
        tablecardss.append(lst);

     return tmpQ;
}

void TableCards::reset(){
        tablecardss.clear();
        tmpQ.clear();
        numberofConsecutiveTwos = 0;
        LastCardImg = "";
        requestedCardType = "";
        changeCardType = "";

        emit LastCardImgChanged();
        emit changeCardTypeChanged();
        emit tablecardssChanged();
        emit requestedCardTypeChanged();

        return;
}

bool TableCards::isempty(){
        return tablecardss.empty();
}
