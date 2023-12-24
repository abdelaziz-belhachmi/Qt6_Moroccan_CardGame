import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtMultimedia
import QtQuick.Dialogs


Window {
    id:mainwin
    minimumWidth: 1000
    width: 1500

    minimumHeight: 700
    height: 800

    visible: true
    title: qsTr("Hez 2")

    color: "#292929"
    /*

      #5a0a0a
      #470404
      #0e4738
      #04470b
      #470423

    */

    SoundEffect {
    id: beep
    source: "assets/audios/cardSound.wav"
    }
    SoundEffect{
    id:liftcard
    source: "assets/audios/liftcard.wav"
    }
    SoundEffect {
    id:plusXP
    source:"assets/audios/achivementsound.wav"

    }
    SoundEffect{
    id:shufflesound
    source: "assets/audios/shuffle.wav"
    //
    }
    SoundEffect{
    id:lostsound
    source: "assets/audios/lost.wav"
    //
    }
    SoundEffect{
    id:winnersound
    source: "assets/audios/winner.wav"
    //
    }


// menu page
Rectangle{
    id:rootrect
    anchors.fill:parent
    color:"transparent"
    visible: true


        Rectangle{
            id:homim
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 50
            anchors.top: parent.top
            height: parent.height*0.6
            width: 700
            color: "transparent"

                    Image {
                    id: homeimg
                    anchors.fill: parent
                    anchors.centerIn: parent
                    source: "assets/images/"+Controlleur.getcardStyle()+"/home_image.png"

                    MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        Controlleur.changeCardStyle();
                        parent.source = "assets/images/"+Controlleur.getcardStyle()+"/home_image.png";
                        jJ.source = "assets/images/"+Controlleur.getcardStyle()+"/J.png";
                        sS.source = "assets/images/"+Controlleur.getcardStyle()+"/S.png";
                        zZ.source = "assets/images/"+Controlleur.getcardStyle()+"/Z.png";
                        fF.source = "assets/images/"+Controlleur.getcardStyle()+"/F.png";

                        }
                    }

                    Row{
                        id: rw
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors{
                            topMargin: 50
                            top: parent.bottom
                        }

                    Image {
                        id: buttonMainMenu
                        source: "assets/images/newgame.png"
                        width: 300
                        height: 120

                        MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    rootrect.visible= false
                                    winnerRect.visible = false
                                    gameTable.visible = true

                                    Controlleur.setDifficulty(diffeculty.text);
                                    Controlleur.startTheParty();
                                }
                            }
                    }


                    Image {
                        id: unpauseGame
                        source: "assets/images/resume.png"
                        width: 300
                        height: 120
                        visible: false

                        MouseArea {
                                anchors.fill: parent
                                onClicked: {

                                    gameTable.visible = true
                                    rootrect.visible= false

                                }
                            }
                    }

                    }


                    }
        }

        Image {
            id: enter
            visible: false
            anchors.left: usernameinputfield.right
            anchors.bottom: settingbar.top
            anchors.leftMargin: 10
            width: 25
            height: 25
            source: "assets/images/enter.png"

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    playerusername.text = usernameinputfield.text.toString();

                    Controlleur.setNewUserName(playerusername.text);

                    usernameinputfield.visible = false;
                    enter.visible=false;
                }
            }
        }

        TextField {
            id:usernameinputfield
            anchors.bottom: settingbar.top
            anchors.left: parent.left
            visible: false
            placeholderText: qsTr("Change UserName")
            anchors.leftMargin: 20
            width: 150
            height: 20
        }

        Rectangle{
        id:settingbar
        height: parent.height * 0.1
        color: "transparent"
        anchors.bottom: parent.bottom
        width: parent.width

        // color picker
        Image {
            id: name
            height: 50
            width: 50
            anchors.rightMargin: 30
            anchors.verticalCenter: parent.verticalCenter
            anchors.right:parent.right
            source: "assets/images/colorpick.png"

            MouseArea {
                anchors.fill:parent
                 onClicked: {
                     colorDialog.open()
                 }
            }
        }

        // user score
        Rectangle{
            id:scr
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: 300
            color :"transparent"

            // star
            Rectangle{
                id:starspace
                height:60
                width: 60
                anchors.verticalCenter: parent.verticalCenter
                anchors.leftMargin: 10
                anchors.rightMargin: 10
                anchors.left: parent.left
                color: "transparent"

                Image {
                    id: stars
                    anchors.fill: parent
                    anchors.centerIn: parent
                    source: "assets/images/stars/"+ p1.gettier().toString() +".png"
                }

            }// end start rect

            // player user name and score
            Column {
                id:scorcolumn
                anchors.left: starspace.right
                anchors.leftMargin: 20
                anchors.verticalCenter: parent.verticalCenter
                spacing: 5

                Text {
                    id:playerusername
                    text: Controlleur.getUserName()
                    color: "white"
                    font.family: "Commando"
                    font.pointSize: 18
                    font.bold: true
                }

            Text {
                id:scor
                text: p1.getScore().toString();
                color: "white"
                font.family: "Commando"
                font.pointSize: 14
            }
            Connections {
            target: p1
            function onScoreChanged(){
                    scor.text = p1.getScore().toString();
                    stars.source = "assets/images/stars/"+ p1.gettier().toString() +".png"
                    Controlleur.saveScore();
                }
            }

            }// end column text

            // edit user name pen
            Rectangle{
                height: 20
                width: 20
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                color: "transparent"

                Image {
                    id: editpen
                    anchors.fill: parent
                    anchors.centerIn: parent
                    source: "assets/images/pen1.png"

                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            usernameinputfield.visible = true;
                            enter.visible = true;
                            }
                        }
                }
            }
        }

        // difficulty
        Row{
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter


        Text {
            id:dff
            anchors.verticalCenter: parent.verticalCenter
            text: "CHANGE DIFFICULTY : "
            color: "white"
            font.family: "Commando"
            font.pointSize: 16
            font.bold: true

        }

        Text {
            id:diffeculty
            text: "MEDIUM"
            font.family: "Commando"
            font.pointSize: 24
            font.bold: true
            anchors.verticalCenter: parent.verticalCenter
            color: "darkorange"

            MouseArea{
                anchors.fill : parent
                onClicked: {

                        if(diffeculty.text === "MEDIUM"){
                            diffeculty.text = "HARD";
                            diffeculty.color = "red";
                        }
                        else if(diffeculty.text === "HARD"){
                            diffeculty.text = "EASY";
                            diffeculty.color = "lime";
                        }
                        else if(diffeculty.text === "EASY"){
                            diffeculty.text = "MEDIUM";
                            diffeculty.color = "darkorange";
                        }

                }
            }
        }
}


        ColorDialog {
            id: colorDialog
            selectedColor: mainwin.color
            onAccepted: mainwin.color = selectedColor
        }


        }


}


// table page
Rectangle {
   id: gameTable
   visible: false
   width: parent.width
   height: parent.height
   color:"transparent"


   // pause button
   Rectangle{
       id:quitButton
       anchors.top : parent.top
       anchors.left : parent.left
       color:"transparent"
       width: 50
       height: 50

          // Adding 10 pixels of padding to all sides
          anchors.leftMargin: 10
          anchors.topMargin: 10
          anchors.rightMargin: 10
          anchors.bottomMargin: 10

           Image {
               id: pauseImg
               anchors.fill : parent
               source: "assets/images/arrow.png"
           }
           MouseArea{
           anchors.fill: parent
           onClicked: {
               unpauseGame.visible = true
               buttonMainMenu.visible = true
               gameTable.visible = false
               rootrect.visible = true

           }
       }
   }

   Timer {
             id: reqCardsTimer
             interval: 600
             repeat: false
             onTriggered: {
                 logoOfReqCardType.source = "assets/images/"+Controlleur.getcardStyle()+"/"+Table.getRequestedCardType()+".png";
             }
         }

    /* requested card type */
    Rectangle{
    id:reqcardtype
    height: parent.height/2
    width: parent.width*0.20
    anchors.left: parent.left
    anchors.verticalCenter: parent.verticalCenter
    color:"transparent"

        Image {
            id: logoOfReqCardType
            source: ""
            anchors.centerIn: parent
            fillMode: Image.PreserveAspectFit
            width: parent.width / 2
            height: parent.height / 2
        }

        Connections {
        target:Table
            function onRequestedCardTypeChanged(){
                if(p1.isItMyTurn() && ! p1.firstdistrubution() ){
                    logoOfReqCardType.source = "assets/images/"+Controlleur.getcardStyle()+"/"+Table.getRequestedCardType()+".png";
                }
                else if (p2.isItMyTurn() || p1.firstdistrubution()){
                     reqCardsTimer.start();
                }
            }
        }

    }


    /*

     COMPUTER SIDE

    */
    Rectangle {
    id: rect1
    anchors.top: parent.top
    anchors.horizontalCenter: parent.horizontalCenter
    height: parent.height / 3
    width: parent.width *0.45
    color: "transparent"

    Rectangle{
    width: parent.width
    height: 180
    color: "transparent"
    anchors.verticalCenter: parent.verticalCenter

        ListView{
            id: listViewComputer
            width: parent.width
            height: parent.height
            orientation: ListView.Horizontal
            spacing:20
            clip:false
            model: ListModel {
                id: computerSide
                /*
                on startup 0 list elements.
                get loaded dynamically from c++ controller class
                */
            //   ListElement { cardName: "J"; cardNumber: 5; imagePath: "assets/images/back.png" }

            }// end model: ListModel

            delegate: Item {
                      id:itmIDofCArdsComp
                      width: 120
                      height: 180

                      Rectangle {
                          width: parent.width
                          height: 180
                            color:"transparent"
                          Image {
                              source: model.imagePath
                              height: parent.height
                              width: parent.width
                          }

                          MouseArea {
                                anchors.fill: parent
                                onEntered: {
                                    parent.parent.scale =  0.8;
                                }
                                onExited: {
                                     parent.parent.scale = 1;
                                }
                          }
                      }
                  }// end delegate : ITem

            Timer {
                      id: delayTimer2
                      interval: 600
                      repeat: false
                      onTriggered: {

                            var prevhandsize = computerSide.count
                            computerSide.clear();

                            for (var i = p2.numberOfcardsInHand()-1; i >= 0 ; i--) {
                                computerSide.append({ cardName: p2.qmlgetCardNamebyIndex(i), CardNumber: p2.qmlgetCardNumberbyIndex(i), imagePath: p2.qmlgetCardImagePathbyIndex(i) });
                            }

                            if(prevhandsize > p2.numberOfcardsInHand() ){
                                beep.play();
                            }

                            else if( prevhandsize < p2.numberOfcardsInHand()){
                              liftcard.play();  // play sound of lifting a card
                            }

                      }
                  }


            Connections {
                target: p2

                function onHandChanged() {

                    if(p1.firstdistrubution()){
                        computerSide.clear();
                    }

                    delayTimer2.start();
                }

                function showComputerCards(){
                  computerSide.clear();
                    for (var i = p2.numberOfcardsInHand()-1; i >= 0 ; i--) {
                      computerSide.append({ cardName: p2.qmlgetCardNamebyIndex(i), CardNumber: p2.qmlgetCardNumberbyIndex(i), imagePath: p2.qmlgetCardImagePathbyIndex(i) });
                    }
                }
            }
        }// end list view
    }
}//end rect1

    Timer {
              id: computersleeptimer
              interval: 600
              repeat: false
              onTriggered: {
                        Controlleur.computerplayagain();
              }
          }

    Connections{
    target: Controlleur
    function onSleepinqml(){
            computersleeptimer.start();
        }
    }


    /*

        TABLE

    */
    Rectangle {
    id: tableRectangle
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.top: rect1.bottom
    anchors.bottom: rect2.top
    height: parent.height /3
    width: parent.width *0.3
    color: "transparent"

        Rectangle{
            height: parent.height * 0.9
            width: 130
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            color:"transparent"

            Image {
                id: tableCard
                anchors.fill : parent
            }

        Timer {
                  id: tableDelayTimer
                  interval: 600
                  repeat: false
                  onTriggered: {
                      tableCard.source = Table.getLastCardImg();
                  }
              }
            Connections {
                target:Table
                function onTablecardssChanged(){

                        if(p2.isItMyTurn() || p1.firstdistrubution()){
                              tableDelayTimer.start();
                        }
                        else if (p1.isItMyTurn()){
                            tableCard.source = Table.getLastCardImg();
                        }
                }

                function onShufflesignalChanged(){
                 shufflesound.play();
                }
            } // end connection
        }
    } // end tableRectangle

    /*

      +xp score side

    */

    Rectangle {
     height: parent.height /3
     color:"transparent"
     anchors.right: rect3.left
     anchors.left:tableRectangle.right
    anchors.verticalCenter: tableRectangle.verticalCenter
    Image {
        id: addscoreimage
        anchors.centerIn: parent
        height: 200
        width: 200
        source: ""
        visible: false
    }
    Timer {
              id: delayxptimer
              interval: 600
              repeat: false
              onTriggered: {
                  addscoreimage.visible = false;
              }
          }


    Connections {
        target:Controlleur
            function onPlusxpChanged(){
                addscoreimage.source = "assets/images/"+Controlleur.getPlusxp().toString()+".png";
                addscoreimage.visible = true;
                plusXP.play();
                delayxptimer.start();
            }
        }
    }

    /*

      USER SIDE

    */
    Rectangle {
    id: rect2
    anchors.bottom: parent.bottom
    height: parent.height /3
    width: parent.width *0.45
    anchors.horizontalCenter: parent.horizontalCenter
    color: "transparent"


    Rectangle{
        width: parent.width
        height: parent.height
        color: "transparent"
        anchors.verticalCenter: parent.verticalCenter


    ListView{
        id: listViewPlayer
        width: parent.width
        height: parent.height
        orientation: ListView.Horizontal
        anchors.fill: parent
        spacing:20
        clip:false

        model: ListModel {
            id:userSide
           /* initially 0 and get loaded dynamically from c++ controller class */
//                ListElement { cardName: "J"; cardNumber: 7; imagePath: "assets/images/7J.png" }

        }// end model: ListModel

        delegate: Item {
            id:itmIDofCArds
                  width: 120
                  height: 180
                  anchors.verticalCenter: parent.verticalCenter

                  Rectangle {
                      width: parent.width
                      height: 180
                        color:"transparent"
                      Image {
                          source: model.imagePath
                          fillMode: Image.PreserveAspectFit
                          height: parent.height
                          width: parent.width
                      }
                  Text {
                          text: model.cardName
                          anchors.bottom: parent.bottom
                          anchors.horizontalCenter: parent.horizontalCenter
                        }
                      MouseArea {
                          anchors.fill: parent
                          onClicked: {
                              beep.play();
                          }

                            onEntered: {
                                     parent.parent.scale =  1.1;
                            }

                            onExited: {
                                Controlleur.userWantToputcarttoTable(model.CardNumber,model.cardName);
                                 parent.parent.scale = 1;
                            }
                      }
                  }
              }// end delegate : ITem

        Timer {
            id: delayTimer
            interval: 600
            repeat: false
            onTriggered: {
                showCards();
            }
        }

        Timer {
                id: distr
                interval: 600
                running: false
                onTriggered: {
                    userSide.clear();
                    for (var i = p1.numberOfcardsInHand()-1; i >= 0 ; i--) {
                        userSide.append({ cardName: p1.qmlgetCardNamebyIndex(i), CardNumber: p1.qmlgetCardNumberbyIndex(i), imagePath: p1.qmlgetCardImagePathbyIndex(i) });
                    }
                    p1.insetfirstdist();
                }
            }

        Connections {
            target: p1
            function onHandChanged() {

                if(p1.firstdistrubution()){
                    distr.start();
                }
                else {
                    userSide.clear(); 
                    for (var i = p1.numberOfcardsInHand()-1; i >= 0 ; i--) {
                        userSide.append({ cardName: p1.qmlgetCardNamebyIndex(i), CardNumber: p1.qmlgetCardNumberbyIndex(i), imagePath: p1.qmlgetCardImagePathbyIndex(i) });
                    }
                }
            }
        }        
    }// end list view
  }
}// end rect2

/*
      deck
*/
    Rectangle {
    id: rect3
    height: parent.height/3
    width: parent.width/7
    anchors.right: parent.right
    anchors.verticalCenter: parent.verticalCenter
    color: "transparent"
        Rectangle{
            id:deckrect
            height: 220
            width: 130
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            color:"transparent"

            Text {
                id: deckSize
                text: "decksize"
                color: "white"
                font.bold: true
                anchors.bottom: parent.top
            }
            Image {
                id: deckCards
                anchors.fill : parent
                source: "assets/images/"+Controlleur.getcardStyle().toString()+"/back.png";
            }
            Timer {
                    id: clickTimer
                    interval: 600
                    running: false
                    onTriggered: {
                        mouseareaofdeckofcards.enabled = true;
                    }
                }

        MouseArea{
            id:mouseareaofdeckofcards
            anchors.fill: deckCards
            onClicked: {
                liftcard.play();
            }
                onEntered: {
                        deckrect.scale = 1.1;
                }
                onExited: {
                    deckrect.scale = 1;
                    mouseareaofdeckofcards.enabled = false;

                    Controlleur.userWanttoliftcardfromdeck();
                    clickTimer.start();
                }
        }

        Connections {
            target:Deck
                function onDeckOfCardsChanged(){
                    deckSize.text = "Cards Left : "+Deck.deckSize();
                }

                function onNumberOfCardsToLiftChanged(){
                    deckCards.source = "assets/images/"+Controlleur.getcardStyle().toString()+"/back_"+Deck.getNumberOfCardsToLift().toString()+".png";
                }
        }
    }
 }// end rect3
}

// change card type request rect
Rectangle {
    id:hakem
    visible: false
    width: parent.width
    height: parent.height
    color: "transparent"
    Rectangle {
        width: parent.width / 2
        height: parent.height / 2
        color: "transparent"
        border.color: "black"
        border.width: 2
        Image {
            id:sS
            source: "assets/images/"+Controlleur.getcardStyle()+"/S.png";
            anchors.centerIn: parent
            fillMode: Image.PreserveAspectFit
            width: parent.width / 2
            height: parent.height / 2
            MouseArea {
            anchors.fill:parent
                onClicked:{
                    hakem.visible = false
                    gameTable.visible = true

                    Table.setRequestedCardType("S");
                    Controlleur.userchosenewcardtype();
                }
            }
        }
    }

    Rectangle {
        width: parent.width / 2
        height: parent.height / 2
        color: "transparent"
        border.color: "black"
        border.width: 2
        anchors.right: parent.right
        Image {
            id:zZ
            source: "assets/images/"+Controlleur.getcardStyle()+"/Z.png"
            anchors.centerIn: parent
            fillMode: Image.PreserveAspectFit
            width: parent.width / 2
            height: parent.height / 2
            MouseArea {
            anchors.fill:parent
                onClicked:{
                    hakem.visible = false
                    gameTable.visible = true

                    Table.setRequestedCardType("Z");
                    Controlleur.userchosenewcardtype();
                }
            }
        }
    }

    Rectangle {
        width: parent.width / 2
        height: parent.height / 2
        color: "transparent"
        border.color: "black"
        border.width: 2
        anchors.bottom: parent.bottom
        Image {
            id:jJ
            source: "assets/images/"+Controlleur.getcardStyle()+"/J.png"
            anchors.centerIn: parent
            fillMode: Image.PreserveAspectFit
            width: parent.width / 2
            height: parent.height / 2
            MouseArea {
            anchors.fill:parent
                onClicked:{
                    hakem.visible = false
                    gameTable.visible = true


                    Table.setRequestedCardType("J");
                    Controlleur.userchosenewcardtype();

                }
            }
        }
    }

    Rectangle {
        width: parent.width / 2
        height: parent.height / 2
        color: "transparent"
        border.color: "black"
        border.width: 2
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        Image {
            id:fF
            source: "assets/images/"+Controlleur.getcardStyle()+"/F.png"
            anchors.centerIn: parent
            fillMode: Image.PreserveAspectFit
            width: parent.width / 2
            height: parent.height / 2
            MouseArea {
            anchors.fill:parent
                onClicked:{
                    hakem.visible = false
                    gameTable.visible = true


                    Table.setRequestedCardType("F");
                    Controlleur.userchosenewcardtype();

                }
            }
        }

    }

    Timer {
            id: hakemtimer
            interval: 600
            repeat: false
            onTriggered: {
                hakem.visible = true
                gameTable.visible = false
                rootrect.visible = false
                winnerRect.visible = false
            }
        }

    Connections {
        target: p1
        function onHakemChanged(){
            hakemtimer.start();
        }
    }
}

// winner page
Rectangle {
    id:winnerRect
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenter: parent.verticalCenter
    height: parent.height
    width:parent.width
    color: "transparent"
    visible: false

    Image {
        id: won
        source: "assets/images/winn.png"
        height: 450
        width: 800
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

    Row{
        anchors.horizontalCenter: won.horizontalCenter
        anchors{
            verticalCenter: parent.bottom
        }

    Image {
        id: playagain
        source: "assets/images/playagain.png"
        width: 300
        height: 120

        MouseArea {
                anchors.fill: parent
                onClicked: {
                    rootrect.visible= false
                    winnerRect.visible = false
                    gameTable.visible = true
                    Controlleur.startTheParty();
                }
            }
        }

    Image {
        id: gohome
        source: "assets/images/home2.png"
        width: 300
        height: 120

        MouseArea {
                anchors.fill: parent
                onClicked: {
                    winnerRect.visible = false
                    gameTable.visible = false
                    unpauseGame.visible = false
                    rootrect.visible= true
                    buttonMainMenu.visible = true
                }
            }
        }
      }
    }

    Connections {
        target: Controlleur

        function onGamesinishedChanged(){
            gameTable.visible = false
            rootrect.visible = false

        if(p1.isMyHandEmpty()){
            won.source = "assets/images/winn.png";
            winnerRect.visible = true
            winnersound.play();
        }else if (p2.isMyHandEmpty()){
            won.source = "assets/images/gameover.png";
            winnerRect.visible = true
            lostsound.play();
        }
      }
    }
}
}
