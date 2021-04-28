/**
* The implementation for HostOrJoinGameWidget class
* @author  Annie Liang
* @since   2020-12-1
*/
#include <Wt/WBreak>
#include <Wt/WApplication>
#include "HostOrJoinGameWidget.h"

using namespace Wt;
using namespace std;
namespace dbo = Wt::Dbo;
typedef dbo::collection< dbo::ptr<Player> > Players;

HostOrJoinGameWidget::HostOrJoinGameWidget(dbo::Session *session, WContainerWidget *parent) :
        session_(session),
        WContainerWidget(parent)
{
    setContentAlignment(AlignCenter);
    HostCon_= new WContainerWidget(this);
    HostCon_->setStyleClass("mainPage");
    
    headerText_ = new WText("<h1> Welcome to ISpyAFake! </h1>");
    headerText_->setStyleClass("mainHeader");
    HostCon_->addWidget(headerText_);
    HostCon_->addWidget(new WBreak(this));

    greeting_ = new WText("What's your name? ", this);
    HostCon_->addWidget(greeting_);
    HostCon_->addWidget(new WBreak(this));

    //field for user to enter name
    nameEdit_ = new WLineEdit(this);
    nameEdit_->setFocus();
    nameEdit_->setStyleClass("enterBox");
    HostCon_->addWidget(nameEdit_);
    new WBreak(this);
    nameError_ =  new WText("Please choose a different name - cannot be null or the same as someone in your game room ", this);
    nameError_->setStyleClass("error");
    HostCon_->addWidget(nameError_);
    new WBreak(this);
    hostGameButton_ = new WPushButton("Host Game", this);
    hostGameButton_->clicked().connect(this, &HostOrJoinGameWidget::hostGame);
    hostGameButton_->setStyleClass("purpleButtons");
    HostCon_->addWidget(hostGameButton_);
    new WBreak(this);
    //field for user to enter game room they wish to join
    searchGameName_ = new WLineEdit(this);
    searchGameName_->setStyleClass("enterBox");
    HostCon_->addWidget(searchGameName_);
    new WBreak(this);
    joinGameButton_ = new WPushButton("Join Game", this);
    joinGameButton_->clicked().connect(this, &HostOrJoinGameWidget::joinGame);
    joinGameButton_->setStyleClass("purpleButtons");
    HostCon_->addWidget(joinGameButton_);
    new WBreak(this);
    gameError_ =  new WText("Can't join an invalid game room or a game that's already started", this);
    gameError_->setStyleClass("error");
    HostCon_->addWidget(gameError_);
    fullGameError_ =  new WText("Game room is already full (max 6 people)", this);
    fullGameError_->setStyleClass("error");
    HostCon_->addWidget(fullGameError_);
    hideErrorMessages();
}

void HostOrJoinGameWidget::hostGame() {
    string userName = nameEdit_->text().toUTF8();
    if(userName.empty()) {
        showErrorMessages(0);
    } else {
        //send user to waiting room / game lobby if name is valid
        WApplication::instance()->setInternalPath("/waitingroom",  true);
    }
}

string HostOrJoinGameWidget::getGameName() {
    return searchGameName_->text().toUTF8();
}

string HostOrJoinGameWidget::getUserName() {
    return nameEdit_->text().toUTF8();
}

void HostOrJoinGameWidget::showErrorMessages(int type) {
    hideErrorMessages();
    if (type==0) {
        nameError_->show();
    } else if(type==1) {
        gameError_->show();
    } else if(type==2) {
        fullGameError_->show();
    }
}

void HostOrJoinGameWidget::hideErrorMessages() {
    nameError_->hide();
    gameError_->hide();
    fullGameError_->hide();
}

void HostOrJoinGameWidget::joinGame() {
    string userName = nameEdit_->text().toUTF8();
    string gameName = searchGameName_->text().toUTF8();

    dbo::Transaction transaction(*session_);
    Players numOfUserwithID = session_->find<Player>().where("named = ? AND gameRoom = ?").bind(userName).bind(gameName);
    Players numOfUserinGame = session_->find<Player>().where("gameRoom = ?").bind(gameName);
    dbo::ptr<GameRoom> currentGameRoom = session_->find<GameRoom>().where("gameRoomID = ?").bind(gameName);

    if(userName.empty() || numOfUserwithID.size() > 0) {
        //prevent users from joining with duplicate id as someone in the game room or with an empty string
        showErrorMessages(0);
    } else if(gameName.empty() || numOfUserinGame.empty()) {
        //prevent users from joining an invalid room
        showErrorMessages(1);
    } else if(numOfUserinGame.size()>=6) {
        //prevent users from joining when room is full
        showErrorMessages(2);
    } else if (currentGameRoom->gameStatus == "gameStarted") {
        //prevent users from joining if the game has already started
        showErrorMessages(1);
    } else {
        //redirects player to waiting room / game lobby
        WApplication::instance()->setInternalPath("/joinedwaitingroom",  true);
    }
}


