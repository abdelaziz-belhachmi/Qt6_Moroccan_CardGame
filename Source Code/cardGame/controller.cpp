#include "controller.h"


deck *controller::getDeck()const
{
    return Deck;
}

void controller::setDeck(deck *newDeck)
{
    Deck = newDeck;
}

player *controller::getP1()const
{
    return p1;
}

void controller::setP1(player *newP1)
{
    p1 = newP1;
}

player *controller::getP2()const
{
    return p2;
}

void controller::setP2(player *newP2)
{
    p2 = newP2;
}

TableCards *controller::getTable()const
{
    return tableCards;
}

void controller::sleep()
{
//    sleep starting...
    QThread::msleep(800);
//  800 mili second passed.
    return;
}

void controller::startNewGame(){

    initialiseDeck();
    initialiseTable();
    initialisePlayers();
    return;
}

QString controller::getDifficulty() const
{
    return Difficulty;
}

void controller::setDifficulty(const QString &newDifficulty)
{
    if (Difficulty == newDifficulty)
        return;
    Difficulty = newDifficulty;
    emit DifficultyChanged();
}

int controller::getPlusxp() const
{
    return plusxp;
}
void controller::setPlusxp(int newPlusxp)
{
//   next should increment score by newPlusxp;
    p1->incrementScore(newPlusxp);
    plusxp = newPlusxp;
    emit plusxpChanged();
}

controller::controller(player &x, player &y, TableCards &t, deck &d ,const int previous_score)
{
    this->previousScore = previous_score;
    qInfo()<<"prev_score :" <<previous_score;

    this->p1 = &x;
    this->p1->incrementScore(previousScore);
    this->p2 = &y;
    this->tableCards = &t;
    this->Deck = &d;
}

void controller::initialiseTable(){
    tableCards->reset();
    return;
}

void controller::initialiseDeck(){
    // start new deck
    Deck->reset();
    Deck->resetNumberOfCardstoLift();
    Deck->shuffle();
    return;
}

void controller::initialisePlayers(){

    // giving the user the first turn to play
    p1->resetUSERHand();
    p1->setMyturn();
    p1->setfirstdist();

    // setting p2 as computer so it can play by executing play();
    p2->resetCOMPUTERHand();
    p2->UnsetMyturn();


    return;
}

bool controller::writeIntToFile(const QString& filename, int newValue) {
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

void controller::saveScore(){
    writeIntToFile(path ,p1->getScore());
    return;
}

controller::~controller(){
    saveScore();
}


void controller::putfirstcardtotable(){
    tmp.clear();
    bool success = false;

    // this keep getting cards from deck untill the card is not a 7 or 1 or 2 . game rule !
    while(!success){
        y = Deck->give_a_Card();
        tmp.append(y);// by default it return 1 card in a QList

            // last card lifted from deck is differant than 1 or 2 or 7 , then i take it , and return the deck what left
        if(tmp.last().getCardNumber()!= 2 && tmp.last().getCardNumber()!= 1 && tmp.last().getCardNumber()!= 7){
            success = true;
            y.clear();
        }
        y.clear();
    }

    // taking last card  using contructor by copy
    x = tmp.last();

    // removing it from tmp
    tmp.removeLast();

    // returning rest of tmp to deck
    Deck->setDeckOfCards(tmp);// setDeckOfcards actually append to deck of cards, and shuffle

    tmp.clear();// clearing the tmp Qlist

    // putting it to table
    tableCards->addCardtoTable(x);// passing the card to table

    /* end putting first card to table*/
    return;
}

void controller::destributecardstoplayers(){
    //here i give each player x number of cards
    int x=5;

    if(getDifficulty() == "EASY"){
        x=3;
    }else if (getDifficulty() == "MEDIUM"){
        x=5;
    }else if (getDifficulty() == "HARD"){
        x=7;
    }else {
        x = 5; // i set this else just in case if getDifficulty return garbage value
    }

    Deck->incrementNumberofCardsToLiftTO(x);// by default its 1 , so new value is x depending on game defficulty

    tmp.append(Deck->give_a_Card()); // this will return a Qlist of 7 cards to tmp

    p1->liftCards(tmp);

    emit p1->handChanged();

    tmp.clear();

    tmp.append(Deck->give_a_Card());// x new cards should be passed to tmp

    p2->liftCards(tmp);

    tmp.clear();

    Deck->resetNumberOfCardstoLift();// ! reseting number of cards deck should be set to 1.

    return;
}

void controller::startTheParty(){
//   game starting.......

    // reseting any previous values to start new game
    startNewGame();

    // putting first card to table
    putfirstcardtotable();

    // giving players first cards in the beginning of the game
    destributecardstoplayers();
    return;
}

void controller::CheckIfAWinner(player &p){
    if(p.isMyHandEmpty()){
        setGamesinished(true);
    }
    return;
}

bool controller::getGamesinished() const
{
    return gamesinished;
}

void controller::setGamesinished(bool newGamesinished)
{
    if (gamesinished == newGamesinished)
        return;
    gamesinished = newGamesinished;
    emit gamesinishedChanged();
}

void controller::userWantToputcarttoTable(int num, QString name){
    //  here i follow the rules for the game , each card should be matching before puting any card blindly

    //  if lastcard == requested type thats fine , else { next card should match the requested type }
    if(p1->isItMyTurn()){

    QString lastcardinTable_Name = tableCards->getLastCardName();
    int lastCardinTbale_Number = tableCards->getLastCardNumber();
    QString Req = tableCards->getRequestedCardType();

    int putCardNumber=0;
    bool allowedCard = false;

    // before every thing , it should check if he last card was 2 , then check hand if it contain a 2 , if not lift card , if he does have a two and not the one clicked on , dont put that card , if the card he tried to put is a two , then allow the card to be put
    // i check if its matching the requested type , when he put 7 and request another type
    // if requested matching the last card added , mean he didnt put a 7 to request type change

    if( Deck->getNumberOfCardsToLift() > 1 && num != 2 && lastCardinTbale_Number == 2){
            // lift cards , you cant just try to put other card than 2 and you have cards in deck to lift
            liftcardfromdeck(*p1);// takes care for switching turn
            computerplay();
            return;
    }

    if ( lastcardinTable_Name == Req ){

        if (lastcardinTable_Name == name || lastCardinTbale_Number == num){
            allowedCard = true;
            card u = p1->PutDownCArd(num,name);
            putCardNumber = u.getCardNumber();
            tableCards->addCardtoTable(u);
        }

        // if requested not matching the last card added , mean last player did put a 7 and requested a differant type change
    }else if(lastcardinTable_Name != Req){
        // only allowing cards that matches the request type
        if ( name == Req || num == 7){
            allowedCard = true;
            card u = p1->PutDownCArd(num,name);// allow user to put that card
            putCardNumber = u.getCardNumber();
            tableCards->addCardtoTable(u);
        }
        // tried to put else card than allowed .
        else{
//           # user tried to put a card differant than requested
        }
    }

    // if indeed he had a valid card to put down
    if (allowedCard && (putCardNumber != 0) ){

        if(p1->isMyHandEmpty()){
            setPlusxp(50); // when user wins ,he get 50xp
            emit gamesinishedChanged();// user won , end game
            return;
        }else if (!p1->isMyHandEmpty()){

                   if (putCardNumber == 2 ){
                        setPlusxp(10); // gets 10 xp for puting "2" card
                        // increment table buffer by 2.
                        Deck->incrementTwo();
                        // switch turns
                        switchTurnsToComputer();
                        // execute play function for computer
                        computerplay();
                        return;
                    }

                    else if(putCardNumber == 1){
                        setPlusxp(3); // gets 3xp for putting "1" card
                        return; // don't run computer turn, aka do nothing. to let the user play once again
                    }

                    else if(putCardNumber == 7){
                        p1->UnsetMyturn(); // unset player his turn , because of annimation time he may want to try putting others cards , so i revoke his turn.
                        setPlusxp(5); // gets 5xp for putting "7" card

                        // emit to qml to prompt from user to choose what type of card he desire
                        emit p1->hakemChanged(); // in qml i take the user input , and invoque the function setCardRequestedtype() that will store it in the variable in table class it getter is getRequestedCardType() that next players should respect

                        //  i just emited hakemChanged in p1 , this should trigger qml to prompt user for his choice,
                        //  his clicked choise should trigger 2 function :
                        // first is for setting new requested type
                        // and second is to switch turns to computer and computerplay() from qml after timer
                        return;
                    }
                    else {
                        // switch turns
                        switchTurnsToComputer();

                        // execute play function for computer
                        computerplay();
                        return;
                    }
            }
        }
    return;
    }

    else{
//        Not your turn !
    return;
    }
}

void controller::userWanttoliftcardfromdeck(){

    if(p1->isItMyTurn()){
        liftcardfromdeck(*p1);// takes care for switching turn
        computerplay();
    }

    return;
}

void controller::userchosenewcardtype(){
    switchTurnsToComputer();
    computerplay();
    return;
}

void controller::changeCardStyle(){
    if (cardStyle == "A"){

        cardStyle="B";
        p1->setCardstyle(cardStyle);
        p2->setCardstyle(cardStyle);
        tableCards->setCardstyle(cardStyle);

    }else if (cardStyle == "B"){
        cardStyle="A";
        p1->setCardstyle(cardStyle);
        p2->setCardstyle(cardStyle);
        tableCards->setCardstyle(cardStyle);
    }
}

QString controller::getcardStyle() const{
    return cardStyle;
}

void controller::switchTurnsToComputer(){
    p2->setMyturn();
    p1->UnsetMyturn();
}

void controller::switchTurnsToPlayer(){

    if (p2->isMyHandEmpty()){
        emit gamesinishedChanged();
        return;
    }

    else if(!p2->isMyHandEmpty()){
        p1->setMyturn();
        p2->UnsetMyturn();
    }

    return;
}

void controller::computerplay(){

    if(p2->isItMyTurn()){

        const QString qr = tableCards->getRequestedCardType();
        const QString TlastCardName =tableCards->getLastCardName();
        const int TlastCardNumber = tableCards->getLastCardNumber();

        if (TlastCardNumber == 2){

            // for easy mode it directly lift 2 cards , only if the deck number of cards is set to 2 , if not it mean the card 2 in table is old and 2 cards already been lifted
            if(Deck->getNumberOfCardsToLift()>1){

                // lift cards directly if game difficulty is set to easy
                    if(getDifficulty() == "EASY"){

                        liftcardfromdeck(*p2);// this function take care of switching turn when after lifting cards
                        switchTurnsToPlayer();// but i have trust issues with cpp
                        return;

                    } else if (getDifficulty() == "MEDIUM" || getDifficulty() == "HARD"){

                        // find if i have a card number 2 , if yes put it , else lift cards from deck
                        if (p2->doihavedos()){
                            // put 2 down
                            card dos(p2->PutDownCArd(2,true));
                            tableCards->addCardtoTable(dos);
                            Deck->incrementTwo();
                            switchTurnsToPlayer();
                            return;
                        }
                        else {
                            // i dont have a card to play with , so i will lift a card simply
                            liftcardfromdeck(*p2);// this function take care of switching turn when after lifting cards
                            switchTurnsToPlayer();// but i have trust issues with cpp
                            return;
                        }
                    }
            }

            else {
                // old 2 : i should either put card if i have a candidate , or lift 1 card for not having a candidate card
                if(  p2->doihavecondidateCard(TlastCardNumber,TlastCardName)  ){
                    // put down the candidate card
                    // PutDown Card take care for finding the card by name or number , removing it from hand and returning it
                    card tmp(p2->PutDownCArd(TlastCardNumber,TlastCardName));
                    tableCards->addCardtoTable(tmp);

                        if (tmp.getCardNumber() == 2 ){
                        Deck->incrementTwo();
                        }
                        else if(tmp.getCardNumber() == 7){
                        // make decision for name choice
                        decideforseven();
                        //
                        }
                        else if (tmp.getCardNumber() == 1){
                        emit sleepinqml(); // this signal qml to start timer to sleep then after that it will trigger computerplay() to let computer play for 2nd time

                        // here i used to call computerplay(); but it will get called from qml after qml timer is triggered
                        // maybe you asking , why is that , well qml stop sync with cpp if cpp sleep , so any updates before sleep wont be noticable , until sleeping ends , and all updates happens at once , so we wont notice the flow or succession of multiple steps or plays by computer.
                        return;
                        }

                        switchTurnsToPlayer();
                        return;
                }else{
                       // lift a card
                        liftcardfromdeck(*p2);// this function take care of switching turn when after lifting cards
                        switchTurnsToPlayer();// but i have to be sure

                    return;
                }
            }
        }
        else if(TlastCardNumber == 7) {
            // in this case we match card by requested cardname or 7 only

            // if we have a 7 we put it
            if( p2->doihaveseven() ){
                // put down 7
                card tmp(p2->PutDownCArd(7,false));// put card by matching the number
                tableCards->addCardtoTable(tmp);

                // make decision for name choice
                decideforseven();
                //

                switchTurnsToPlayer();
                return;

            }else if(  p2->findCardIndex(qr) != -1 ){

                // if i have a condidate card matching name we put it
                // put card that match requested type
                card tmp=p2->PutDownCArd(qr);

                tableCards->addCardtoTable(tmp);
                if ( tmp.getCardNumber() == 2 ){
                    Deck->incrementTwo();
                }
                if(tmp.getCardNumber() == 7){
                    // make decision for name choice
                    decideforseven();
                    //
                }
                if (tmp.getCardNumber() == 1){
                    emit sleepinqml(); // this signal qml to start timer to sleep then after that it will trigger computerplay() to let computer play for 2nd time
                    return;
                }

                switchTurnsToPlayer();
                return;
            }
            else{
                // else lift a card
                liftcardfromdeck(*p2);
                switchTurnsToPlayer();
                return;
            }
        }
        else{
            // do i have candidate
            // yes : put it down
            // no : lift a card

            if(  p2->doihavecondidateCard(TlastCardNumber,TlastCardName)  ){
            // put down the candidate card
            // PutDown Card take care for finding the card by name or number , removing it from hand and returning it
            card tmp(p2->PutDownCArd(TlastCardNumber,TlastCardName));
            tableCards->addCardtoTable(tmp);

            if (tmp.getCardNumber() == 2 ){
                    Deck->incrementTwo();
            }
            if(tmp.getCardNumber() == 7){
                    // make decision for name choice
                    decideforseven();
                    //
            }
            if (tmp.getCardNumber() == 1){
                    if (p2->isMyHandEmpty()){
                        emit gamesinishedChanged();
                        return;
                    }

                    emit sleepinqml(); // this signal qml to start timer to sleep then after that it will trigger computerplay() to let computer play for 2nd time
                    return;
            }

            switchTurnsToPlayer();
            return;

            }else{
            // lift a card
            liftcardfromdeck(*p2);
            switchTurnsToPlayer();

            return;
            }

            // end
        }

        switchTurnsToPlayer();


    }else {
//     "not the turn of computer , this function shouldnt be called without passing turn to computer."
    }

    switchTurnsToPlayer();
    return;
}

void controller::computerplayagain(){
    computerplay();
    return;
}

void controller::decideforseven(){
    QString y;

    if(getDifficulty() == "EASY"){
        // find card type that computer doesnt have , and 7kem biha
        y = p2->whatcardtypeidonthave();
    }

    else if(getDifficulty() == "MEDIUM"){
        // random , there is chance to have the randomly chosen type , same as there is a chance to not have the randomly chosen type
        int x = QRandomGenerator::global()->bounded(4);
        switch (x) {
        case 0:
            y = "S";
            break;
        case 1:
            y = "J";
            break;
        case 2:
            y = "Z";
            break;
        case 3:
            y = "F";
            break;

        default:
            y = "F";
            break;
        }

    }
    else if(getDifficulty() == "HARD"){

        // dificulty hard , i will check if i have a 2 , i will request it type to put it on my next turn
        if(p2->doihavedos()){
            // yes i have a two and i will request it type
           y = p2->cardtypeofdos();// find card index of a 2 card

        }else if ( ! p2->isMyHandEmpty()){

            // i dont have a 2 but i will request type of first card in my hand
           y = p2->typeoffirstcardinhand();

        }else if (p2->isMyHandEmpty()){

           // i dont have to request , since 7 was my last card ,i directly win
           emit gamesinishedChanged();
           return;
        }

    }

    // set requested type by computer
    tableCards->setRequestedCardType(y); // it takes care to signal qml

    return;
}

void controller::liftcardfromdeck(player & p){

if(Deck->getNumberOfCardsToLift() < Deck->deckSize() ){

    QList tpl= Deck->give_a_Card(); // gives you what buffer counter been counting
    p.liftCards(tpl);
    Deck->resetNumberOfCardstoLift();
    emit p.handChanged(); // emit signal to qml

    //then switch turns
    if (p.iscomputer()){
        switchTurnsToPlayer();

    }else{
        switchTurnsToComputer();
    }

return;
}

        else if ( Deck->getNumberOfCardsToLift() >= Deck->deckSize() || Deck->isempty() ){

            // get most cards from table and shuffle
            QList tt = tableCards->giveBackMostCards();
            Deck->setDeckOfCards(tt);
            tt.clear();

            // then lift the cards you need
            QList tpl= Deck->give_a_Card(); // gives you what buffer counter been counting
            p.liftCards(tpl);

            Deck->resetNumberOfCardstoLift();
            tpl.clear();

            emit p.handChanged(); // emit signal to qml

                //then switch turns
                if (p.iscomputer()){
                switchTurnsToPlayer();

                }else if(!p.iscomputer()){
                switchTurnsToComputer();
                }

            return;
        }

}

QString controller::readUsernameFromFile(const QString& filename, const QString& defaultUsername) {
        QFile file(filename);

        if ( ! file.exists() ) {
            if (writeUsernameToFile(filename, defaultUsername)) {
                return defaultUsername;
            }
            else {
                return QString();
            }
        }

        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString username = in.readAll();
            file.close();
            return username;
        } else {
            return QString("error in reading username");
        }
}

bool controller::writeUsernameToFile(const QString& filename, const QString& username) {
        QFile file(filename);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out<<username;
            file.close();
            return true;
        } else {
            return false;
        }
}

QString controller::getUserName(){
        QString x = readUsernameFromFile("uname","Default UserName");
        return x;
}

void controller::setNewUserName(QString userName){
        writeUsernameToFile("uname",userName);
}
