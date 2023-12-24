#include "player.h"

int player::getScore() const
{
    return Score;
}

QString player::gettier() const
{
    int sc = getScore();
    if ( sc <= 99 ){
        // bronze
        return "bronzestar";
    }
    else if( sc > 99  && sc <= 249 ){
        return "silverstar";
        //silver
    }
    else if( sc > 249 && sc <= 499 ){
        //gold
        return "goldstar";
    }
    else if( sc > 499 && sc <= 999 ){
        // red
        return "redstar";
    }
    else if(sc > 999 && sc <= 1999){
//        black
        return "blackstar";
    }
    else if(sc > 1999){
        // plat
        return "bluestar";
    }

}

void player::incrementScore(int newScore)
{
    if (newScore == 0){
        return;
    }
    Score += newScore;
    emit scoreChanged();
}

bool player::setAsComputerPlayer(){
    this->isComputer = true;
    return isComputer;
}

bool player::unSetAsComputerPlayer(){
    this->isComputer = false;
    return isComputer;
}

bool player::isItMyTurn(){
    return turn;
}
bool player::firstdistrubution(){
    return firstdistro;
}
void player::setfirstdist(){
    firstdistro = true;
}
void player::insetfirstdist(){
    firstdistro = false;
}
void player::setMyturn(){
    turn = true;
}

void player::UnsetMyturn(){
    turn =false;
}

bool player::isMyHandEmpty(){
    return hand.isEmpty();
}

bool player::iscomputer(){
    return isComputer;
}

/*
 *  showHand and getHand are similar ,
 *   but getHand is const and invokable from qml i will leave it here if i need it later
 */
QList<card> player::getHand() const
{
    return hand;
}

const int player::numberOfcardsInHand()const{
    int tmp = hand.size();
    return tmp;
}

const int player::qmlgetCardNumberbyIndex(int i)const{
    int tmp = hand[i].getCardNumber();
    return tmp;
}

const QString player::qmlgetCardNamebyIndex(int i)const{
    QString x = hand[i].getCardName();
     return x;

}

QString player::getCardstyle()const{
    return cardStyle;
}

void player::setCardstyle(QString n){
    cardStyle = n;
}

const QString player::qmlgetCardImagePathbyIndex(int i)const{
   QString x = "assets/images/" + getCardstyle()+"/";
    if(isComputer){
          x += hand[i].getflippedimage();

    }else if (!isComputer){
       x += hand[i].getCardImagePath();
    }
     return x;
}

player::~player(){
    this->hand.clear();
}

QList<card> player::showHand(){
    return hand;
}

QString player::typeoffirstcardinhand()const{
       return hand[0].getCardName();
}

QList<QString> player::returnqlistofcardtypes(){
       QList<QString> qs;
       for (int x = 0; x < hand.size(); ++x) {
       QString cn = hand[x].getCardName();
       qs.append(cn);
       }
       return qs;
}

void player::setName(QString &name){
       PlayerName = name;
}

void player::resetUSERHand(){
       hand.clear();
       turn = true;
       isComputer = false;

       emit handChanged();
}

void player::resetCOMPUTERHand(){
       hand.clear();
       turn = false;
       isComputer = true ;

       emit handChanged();
}

QString player::whatcardtypeidonthave(){

       QString x;
       QList<QString> cqs = returnqlistofcardtypes();
       QSet<QString> s(cqs.begin(),cqs.end());

       if (! s.contains("S")){
       x = "S";
       }
       else if (!s.contains("F")){
       x = "F";
       }
       else if (!s.contains("J")){
       x = "J";
       }
       else if (!s.contains("Z")){
       x = "Z";
       }
       else {
               // we have all 4 types , so i will choose randomly
               int n = QRandomGenerator::global()->bounded(4);
               switch (n) {
               case 0:
                   x = "S";
                   break;
               case 1:
                   x = "J";
                   break;
               case 2:
                   x = "Z";
                   break;
               case 3:
                   x = "F";
                   break;

               default:
                   x = "F";
                   break;
               }
       }
       return x;
}

player &player::operator =(const player &other){
       PlayerName=other.PlayerName;
       hand.clear();
       hand = other.hand;
       turn = other.turn;
       isComputer = other.isComputer;

       return *this;
}

QString player::cardtypeofdos()const{
       int CardIndex = findCardIndex(2);

       if(CardIndex != -1){
               QString x = hand[CardIndex].getCardName();
               return x;
       }
}

/* should lift card from deck , on user click event controller deside to number of elements to pass in the Qlist, depending on the card put by oponent in table */
void player::liftCards(QList<card> & ListOfCards){

    if (ListOfCards.size()>0){
    hand.append(ListOfCards); // append new cards from the given Qlist to the hand Qlist
    emit handChanged(); // emit signal to qml
    }else{
        //  Couldnt liftCards
    }
}

card player::PutDownCArd(int const index){
    if(index != -1){

        card c(hand[index]);// constructor by copy
        hand.removeAt(index);// clear the element from hand , NOTE : i believe the memory space isnt freed yet!
        emit handChanged();// signal to qml that Qlist hand changed
        //returning the card
        return c;
    }
    else{
        //    requested Card to put down was not Found in hand
    }
}
// this function should transfer the desired card to the table , and remove it from player hand
card player::PutDownCArd(int const num,bool){
    // index of card in player hand
    int CardIndex = findCardIndex(num);

    if(CardIndex != -1){

        card c(hand[CardIndex]);// constructor by copy
        hand.removeAt(CardIndex);// clear the element from hand
        emit handChanged();// signal to qml that Qlist hand changed
        //returning the card
        return c;
    }
    else{
        //    requested Card to put down was not Found in hand"
    }
}

// this function should transfer the desired card to the table , and remove it from player hand
card player::PutDownCArd(QString const name){

    // index of card in player hand
    int CardIndex = findCardIndex(name);

    if(CardIndex != -1){

        card c(hand[CardIndex]);// constructor by copy
        hand.removeAt(CardIndex);// clear the element from hand
        emit handChanged();// signal to qml that Qlist hand changed
        //returning the card
        return c;
    }
    else{
        //  requested Card to put down was not Found in hand
    }
}

// this function should transfer the desired card to the table , and remove it from player hand
card player::PutDownCArd(int const num , QString const name){

    // index of card in player hand
    int CardIndex = findCardIndex(num,name);

    if(CardIndex != -1){

        card c(hand[CardIndex]);// constructor by copy
        hand.removeAt(CardIndex);// clear the element from hand
        emit handChanged();// signal to qml that Qlist hand changed
        //returning the card
        return c;
    }
    else{
        //      requested Card to put down was not Found in hand
    }
}

// finds index of the card in hand Qlist , get called on user click
int player::findCardIndex(int num ,QString name)const{
    if(!isComputer){
    card tmpCard(num,name);// creating tmp object similar to the card looking for

    for (int var = 0; var < hand.size(); ++var) {
        card t(hand[var]);
        if (t == tmpCard){
            return var;
        }
    }

    }
    // for computer this function behave more like find me condidate card that i can put down
    else if(isComputer){

    for (int var = 0; var < hand.size(); ++var) {
        if (hand[var].getCardNumber() == num || hand[var].getCardName() == name){
            return var;// return index of a card matching by name or number
        }
    }


    }

    return -1;
}

// those two ovearridings used inorder for the cumputer to deside if he can put down a card or just lift a card
int player::findCardIndex(QString const name)const{
    for(int i = 0; i< hand.size();++i){
        if (hand[i].getCardName() == name){
            return i;// return index of a card matching by name
        }
    }
    return -1;
}

bool player::doihavecondidateCard(const int num, const QString cardname)
{
    if(findCardIndex(num) != -1 || findCardIndex(cardname) != -1){
        return true;
    }
    else{
        return false;
        }
}

// get called when looking for a card by number , it takes just the first occurence
int player::findCardIndex(int const num)const {
    for(int i = 0; i< hand.size();++i){
        if (hand[i].getCardNumber() == num){
            return i;// return index of a card matching by number
        }
    }
    return -1;
}

bool player::doihavedos(){
    /* search cards by number to find if i have card with number 2 */
    foreach (card c, hand) {
        if (c.getCardNumber() == 2){
            return true;
        }
    }
    return false;
}

bool player::doihaveseven(){
    /* search cards by number to find if i have card with number 7 */
    foreach (card c, hand) {
        if (c.getCardNumber() == 7){
            return true;
        }
    }
    return false;
}



