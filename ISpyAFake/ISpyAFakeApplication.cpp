/**
* The Program is the entry point to the I Spy A Fake application.
* It handles all the page linking/routing and database instantiation/access
*
* @author  Annie Liang
* @since   2020-12-1
*/

#include <unistd.h>
#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/backend/Sqlite3>
#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WStackedWidget>
#include "CategoryImageWidget.h"
#include "CategoryAssignment.h"
#include "GameRoom.h"
#include "HostOrJoinGameWidget.h"
#include "ISAFGames.h"
#include "JsonObj.h"
#include "leadershipWidget.h"
#include "Player.h"
#include "votingScreenWidget.h"
#include "WaitingRoomWidget.h"

using namespace std;
using namespace Wt;
namespace dbo = Wt::Dbo;

typedef dbo::collection< dbo::ptr<Player> > Players;
typedef Wt::Dbo::collection< Wt::Dbo::ptr<GameRoom> > GameRooms;

class ISpyAFakeApplication : public WApplication
{
public:
    ISpyAFakeApplication(const WEnvironment& env);

private:
    // different pages/widgets of the application
    Wt::WStackedWidget *mainStack_;
    WaitingRoomWidget *waitingRoom_;
    CategoryImageWidget *categoryImagePage_;
    leadershipWidget *leadershipScreen_;
    votingScreenWidget *votingScreen_;
    HostOrJoinGameWidget *hostOrJoinGameScreen_;
    // variables to manipulate and track database objects
    dbo::Session session_;
    dbo::backend::Sqlite3 sqlite3_;
    dbo::ptr<Player> playerPtr_;
    dbo::ptr<GameRoom> gameRoomPtr_;
    //store newly created game room object
    ISAFGames* gamesList_;
    /** Handles internal path changes and performs corresponding actions for those different internal paths
      * @param values String of the url/path to direct the user to
      * */
    void handleInternalPath(const std::string &internalPath);
};

/*
 * The env argument contains information about the new session, and
 * the initial request. It must be passed to the WApplication
 * constructor so it is typically also an argument for your custom
 * application constructor.
*/
ISpyAFakeApplication::ISpyAFakeApplication(const WEnvironment& env)
  : WApplication(env), sqlite3_(WApplication::instance()->appRoot() + "ispyafakedata.db")
{
    sqlite3_.setProperty("show-queries", "true");
    //set up database connection
    session_.setConnection(sqlite3_);
    //map tables to its corresponding scheme
    session_.mapClass<Player>("player");
    session_.mapClass<GameRoom>("gameRoom");
    try {
        //create database and tables if it does not already exist
        session_.createTables();
        log("info") << "Database created";
    } catch (...) {
        log("info") << "Using existing database";
    }

    setTitle("I Spy A Fake");
    Wt::WApplication::instance()->useStyleSheet("css/styles.css");

    mainStack_ = new WStackedWidget();
    root()->addWidget(mainStack_);

    hostOrJoinGameScreen_ = new HostOrJoinGameWidget(&session_, mainStack_);
    //set current page to show screen to join or host a new game
    mainStack_->setCurrentWidget(hostOrJoinGameScreen_);

    WApplication::instance()->internalPathChanged()
            .connect(this, &ISpyAFakeApplication::handleInternalPath);
}

void ISpyAFakeApplication::handleInternalPath(const string &internalPath)
{
    JsonObj jsonObj = JsonObj();
    //read in the category items and store it
    Category categoryObjItems = jsonObj.readJsonFileToCategory();

    if (internalPath == "/waitingroom" || internalPath == "/joinedwaitingroom") {
        //keep track of current game room name
        string gameNameReturned;
        if(internalPath == "/waitingroom") {
            //create a new game room
            GameRoom * gameRoomEntry = gamesList_->createNewGame(hostOrJoinGameScreen_->getUserName());
            gameNameReturned = gameRoomEntry->code;

            dbo::Transaction transaction(session_);
            //add game room to the database
            session_.add(gameRoomEntry);
        } else {
            //get name of game room to join
            gameNameReturned = hostOrJoinGameScreen_->getGameName();
        }

        dbo::Transaction transaction(session_);
        //store info for user
        if(!playerPtr_) {
            Player * user = new Player();
            user->id = hostOrJoinGameScreen_->getUserName();
            user->gameRoomID = gameNameReturned;
            try {
                //add user to the database
                playerPtr_ = session_.add(user);
            } catch (dbo::StaleObjectException e) {
                cout << "waiting to read database" << endl;
            }
        }
        //send player to game lobby
        waitingRoom_ = new WaitingRoomWidget(playerPtr_, &session_, playerPtr_->gameRoomID, mainStack_);
        mainStack_->setCurrentWidget(waitingRoom_);
        waitingRoom_->update();

    } else if (internalPath == "/startRound") {
        dbo::Transaction transaction(session_);
        //get pointer to current game room entry in the database
        dbo::ptr<GameRoom> currentGameRoom = session_.find<GameRoom>().where("gameRoomID = ?").bind(playerPtr_->gameRoomID);
        //get assigned category item for game room
        CategoryItem chosenItem = categoryObjItems.findCategory(currentGameRoom->assignedCategoryItem);
        categoryImagePage_ = new CategoryImageWidget(playerPtr_, chosenItem, currentGameRoom->fake, categoryObjItems,
                                               mainStack_);
        //send player to page to see their location/category assignment for the round
        mainStack_->setCurrentWidget(categoryImagePage_);
    } else if(internalPath == "/votingPage") {
        //list to store ids of players in current game room
        vector<string> playersList;
        dbo::Transaction transaction(session_);
        Players players = session_.find<Player>().where("gameRoom = ?").bind(playerPtr_->gameRoomID);
        for (Players::const_iterator i = players.begin(); i != players.end(); ++i) {
            playersList.push_back((*i)->id);
        }
        votingScreen_ = new votingScreenWidget(&session_, playerPtr_->gameRoomID, playersList, playerPtr_, categoryObjItems, mainStack_);
        //send player to voting page
        mainStack_->setCurrentWidget(votingScreen_);
        votingScreen_->votingTime();
    } else if(internalPath == "/leadershipBoard") {
        leadershipScreen_ = new leadershipWidget(&session_, playerPtr_, mainStack_);
        //send player to leadership board page
        mainStack_->setCurrentWidget(leadershipScreen_);
        leadershipScreen_->leaderTime();
    } else {
        mainStack_->setCurrentWidget(hostOrJoinGameScreen_);
    }
}

WApplication *createApplication(const WEnvironment& env)
{
  /*
   * You could read information from the environment to decide whether
   * the user has permission to start a new application
   */
  return new ISpyAFakeApplication(env);
}

int main(int argc, char **argv)
{
  /*
   * The last argument to WRun specifies the function that will instantiate
   * new application objects. That function is executed when a new user surfs
   * to the Wt application, and after the library has negotiated browser
   * support. The function should return a newly instantiated application
   * object.
   */

  return WRun(argc, argv, &createApplication);
}















