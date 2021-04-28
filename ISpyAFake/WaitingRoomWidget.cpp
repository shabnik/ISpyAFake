/**
* The implementation for WaitingRoomWidget class
* @author  Annie Liang
* @since   2020-12-1
*/
#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WText>
#include "WaitingRoomWidget.h"
#include "JsonObj.h"

using namespace Wt;
using namespace std;
namespace dbo = Wt::Dbo;

typedef dbo::collection< dbo::ptr<Player> > Players;

WaitingRoomWidget::WaitingRoomWidget(dbo::ptr<Player> playerPointer, dbo::Session *session, string gameRoomObj, WContainerWidget *parent):
        playerPtr_(playerPointer),
        session_(session),
        WContainerWidget(parent)
{
    currentGame_ = gameRoomObj;
    setContentAlignment(AlignCenter);
}

void WaitingRoomWidget::update()
{
    clear();
    //display current game room id
    new WText("<h2>Game Room : " + currentGame_ + " </h2>", this);
    new WText("<h3> Players </h3>", this);
    //button to refresh and see the updated list of people who joined the game
    refreshButton_ = new WPushButton("Refresh list", this);
    refreshButton_->clicked().connect(this, &WaitingRoomWidget::update);
    refreshButton_->setStyleClass("refreshButton");

    dbo::Transaction transaction(*session_);
    //find list of players in the game room
    Players players = session_->find<Player>().where("gameRoom = ?").bind(currentGame_);
    dbo::ptr<GameRoom> currentGameRoom = session_->find<GameRoom>().where("gameRoomID = ?").bind(currentGame_);

    for (Players::const_iterator i = players.begin(); i != players.end(); ++i) {
        //display names of players in game room
        tempPlayer_ = new WText("<p>" + (*i)->id + "</p>", this);
        tempPlayer_->setStyleClass("playerList");
    }

    //allow only the host to start the  game
    if(playerPtr_->id == currentGameRoom->host) {
        startButton_ = new WPushButton("Start Game", this);
        startButton_->clicked().connect(this, &WaitingRoomWidget::assignCategories);
        startButton_->setStyleClass("greenButtons");
    }

    seeLocationButton_ = new WPushButton("See Location", this);
    seeLocationButton_->clicked().connect(this, &WaitingRoomWidget::seeLocation);
    seeLocationButton_->setStyleClass("purpleButtons");
    new WBreak(this);
    gameNotStartedError_ = new WText("Need to wait for the host to start the game before proceeding", this);
    gameNotStartedError_->setStyleClass("error");
    gameNotStartedError_->hide();
    new WBreak(this);
    notEnoughPlayersError_ = new WText("Need more than 2 people to play this game", this);
    notEnoughPlayersError_->setStyleClass("error");
    notEnoughPlayersError_->hide();
}

void WaitingRoomWidget::seeLocation() {
    dbo::Transaction transaction(*session_);
    //only allow users to be redirected to see their assigned category if the host started the game
    dbo::ptr<GameRoom> currentGameRoom = session_->find<GameRoom>().where("gameRoomID = ?").bind(playerPtr_->gameRoomID);
    if(currentGameRoom->gameStatus == "gameStarted") {
        WApplication::instance()->setInternalPath("/startRound",  true);
    } else {
        //show error message if host has not started game
        gameNotStartedError_->show();
    }
}

void WaitingRoomWidget::assignCategories() {
    JsonObj jsonObj = JsonObj();
    Category categoryObjItems = jsonObj.readJsonFileToCategory();

    vector<string> playersList;
    dbo::Transaction transaction(*session_);
    Players players = session_->find<Player>().where("gameRoom = ?").bind(currentGame_);
    dbo::ptr<GameRoom> currentGameRoom = session_->find<GameRoom>().where("gameRoomID = ?").bind(currentGame_);
    if(players.size() < 2) {
        //prevent host from starting a game with less than 2 players
        notEnoughPlayersError_->show();
    } else {
        notEnoughPlayersError_->hide();
        gameNotStartedError_->hide();
        for (Players::const_iterator i = players.begin(); i != players.end(); ++i) {
            playersList.push_back((*i)->id);
        }
        //assign category
        CategoryAssignment assignCategory = CategoryAssignment(playersList, categoryObjItems);
        CategoryItem selectedItem = assignCategory.getAssignCategoryItem();
        string fake = assignCategory.getFake();
        //update the game room assignment in database
        currentGameRoom.modify()->fake = fake;
        currentGameRoom.modify()->assignedCategoryItem = selectedItem.getName();
        currentGameRoom.modify()->gameStatus = "gameStarted";

        transaction.commit();
        sleep(3);
    }
}






