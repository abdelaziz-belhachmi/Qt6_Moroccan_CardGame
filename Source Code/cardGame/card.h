#ifndef CARD_H
#define CARD_H

#include <QObject>
#include <iostream>
#include <string.h>
#include <QDebug>

class card : public QObject
{
    Q_OBJECT

private:
    int cardNumber;
    QString cardName;

public:
    card(){};

    card (const int & num,const QString & name);

    card(const card & c);

    bool operator == (const card & c);

    card & operator=(const card & c);

    QString getCardImagePath()const;

    QString getflippedimage()const;

    QString getCardName()const;

    int getCardNumber()const;

    ~card();

signals:

};

#endif // CARD_H
