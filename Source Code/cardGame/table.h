#ifndef TABLE_H
#define TABLE_H

#include <QObject>
#include "card.h"


class TableCards : public QObject
{
    Q_OBJECT
private:

    QList<card> tablecardss;

    QList<card> tmpQ;

    QString LastCardImg;

    QString changeCardType; // using it signal to promt user to request a type after putting a 7

    QString requestedCardType;// only used to store what player choose as card type when he puts 7

    QString cardStyle = "A";// by default its A 

    int numberofConsecutiveTwos=0;

    //  puting 7 ontop of 7 doesnt check for it in first place but overwrite it.
    bool shufflesignal;



    Q_PROPERTY(QString requestedCardType READ getRequestedCardType NOTIFY requestedCardTypeChanged FINAL)

    Q_PROPERTY(QList<card> tablecardss READ getTablecardss NOTIFY tablecardssChanged FINAL)

    Q_PROPERTY(QString LastCardImg READ getLastCardImg NOTIFY LastCardImgChanged FINAL)

    Q_PROPERTY(QString changeCardType READ getChangeCardType  NOTIFY changeCardTypeChanged FINAL)

    Q_PROPERTY(Bool shufflesignal  NOTIFY shufflesignalChanged FINAL)


public:

    TableCards(){};

    TableCards & operator = (const TableCards & otherTable);

    QList<card> & giveBackMostCards();

    QList<card> & getTablecardss();

    QString getChangeCardType() const;

    QString getCardstyle() const;

    card & getLastCard();

    const QString getLastCardName();

    const int getLastCardNumber();

    void addCardtoTable(card & c);

    void reset();

    void setTablecardss(const QList<card> &newTablecardss);

    void setLastCardImg( QString &newLastCardImg);

    void setCardstyle(QString n);

    bool isempty();

    Q_INVOKABLE const QString getRequestedCardType()const;

    Q_INVOKABLE void setRequestedCardType(QString newRequestedCardType);

    Q_INVOKABLE const QString getLastCardImg()const;

signals:

    void requestedCardTypeChanged();
    void tablecardssChanged();
    void LastCardImgChanged();
    void changeCardTypeChanged();
    void shufflesignalChanged();

};

#endif // TABLE_H
