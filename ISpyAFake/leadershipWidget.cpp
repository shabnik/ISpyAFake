/**
* @brief The implementation of the leadership widget (scoreboard)
* @author  Nicholas Pehme
* @since   2020-12-1
*/
#include <Wt/WBreak>
#include "leadershipWidget.h"

using namespace Wt;
using namespace std;
namespace dbo = Wt::Dbo;



//The constructor for the widget
leadershipWidget::leadershipWidget(Wt::Dbo::Session *session, Wt::Dbo::ptr<Player> playerPointer, Wt::WContainerWidget *parent):
        WContainerWidget(parent),
        session(session),
        playerPtr(playerPointer)
{
    setContentAlignment(AlignCenter);
}


//leaderTime() is used to display the scoreboard and buttons
void leadershipWidget::leaderTime(){

    //Create a transaction to get the list of players and the current gameRoom
    typedef dbo::collection< dbo::ptr<Player> > Players;
    dbo::Transaction transaction(*session);
    Players players = session->find<Player>().where("gameRoom = ?").bind(playerPtr->gameRoomID).orderBy("score desc");
    dbo::ptr<GameRoom> currentGameRoom = session->find<GameRoom>().where("gameRoomID = ?").bind(playerPtr->gameRoomID);


    //Header
    new WText("<h3> Player Scores: </h3>", this);

    //Create the table
    Wt::WTable *leaderTable = new Wt::WTable(this);

    //A counter used to add players to incrementing rows
    int counter = 0;


    //Loop through the list of current players, ordered by score
    for (Players::const_iterator i = players.begin(); i != players.end(); ++i) {


        //Add the players name to the table
        leaderTable->elementAt(counter, 0)->addWidget(new Wt::WText((*i)->id));
        leaderTable->elementAt(counter, 1)->addWidget(new Wt::WText("****************"));

        //Add the players score to the table
        leaderTable->elementAt(counter, 2)->addWidget(new Wt::WText( to_string((*i)->score)));


        counter++;

    }


    //If the player is the host, create the endGame button which ends game for all players
    if(playerPtr->id == currentGameRoom->host) {
        endGameButton_ = new WPushButton("End Game", this);
        endGameButton_->clicked().connect(this, &leadershipWidget::endGame);
        endGameButton_->setStyleClass("leaveGameButton");


        //Else the player is not the host, they get the leaveGameButton
    } else {
        leaveGameButton_ = new WPushButton("Leave Game", this);
        leaveGameButton_->clicked().connect(this, &leadershipWidget::leaveGame);
        leaveGameButton_->setStyleClass("leaveGameButton");
    }

    //Every player gets the newRound button
    newRoundButton_ = new WPushButton("New Round", this);
    newRoundButton_->setStyleClass("greenButtons");
    newRoundButton_->clicked().connect(this, &leadershipWidget::newRound);
    new WBreak(this);
    //If the host ended the game, this message will be displayed
    endedGameError_ = new WText("Host has ended game, cannot play a new round", this);
    endedGameError_->setStyleClass("error");
    endedGameError_->hide();


}


//When the endGame button is clicked
void leadershipWidget::endGame() {

    //Create a new transaction to get the gameroom
    dbo::Transaction transaction(*session);
    dbo::ptr<GameRoom> currentGameRoom = session->find<GameRoom>().where("gameRoomID = ?").bind(playerPtr->gameRoomID);

    //Remove the gameroom and leave the game
    currentGameRoom.remove();
    leaveGame();
}


//If a player chooses to leave the game
void leadershipWidget::leaveGame() {

    //Remove the player pointer, reset the internal path
    playerPtr.remove();
    WApplication::instance()->setInternalPath("",  true);
}


//If the player clicks the newRound button
void leadershipWidget::newRound() {

    //Create a new transaction to get the current game room
    dbo::Transaction transaction(*session);
    dbo::ptr<GameRoom> currentGameRoom = session->find<GameRoom>().where("gameRoomID = ?").bind(playerPtr->gameRoomID);

    //If the current game room still exists
    if(currentGameRoom) {

        //Reset the hasVoted and set the gameStatus to waiting
        currentGameRoom.modify()->gameStatus = "waiting";
        playerPtr.modify()->hasVoted = false;

        //If the player is the host, send them to the waiting room, else send the players to the joinedwaitingroom
        if(playerPtr->id == currentGameRoom->host) {
            WApplication::instance()->setInternalPath("waitingroom", true);
        } else {
            WApplication::instance()->setInternalPath("joinedwaitingroom", true);
        }

        //Show the error message if the room no longer exists
    } else {
        endedGameError_->show();
    }
}
