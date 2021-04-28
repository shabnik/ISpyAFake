/**
* @brief The implementation of the voting screen widget
* @author  Nicholas Pehme
* @since   2020-12-1
*/


#include <Wt/WBreak>
#include "votingScreenWidget.h"

using namespace Wt;
using namespace std;
namespace dbo = Wt::Dbo;



//Constructer for votingscreenWidget
votingScreenWidget::votingScreenWidget(Wt::Dbo::Session *session, std::string gameRoomObj, std::vector<std::string> newplayersList,Wt::Dbo::ptr<Player> playerPointer, Category categoryItems, Wt::WContainerWidget *parent):
        WContainerWidget(parent),
        session(session),
        playerPtr(playerPointer)
{

    setContentAlignment(AlignCenter);
    //Set the categoryObjItems from the parameter
    this->categoryObjItems = categoryItems;

    //Set the list of current playeers and the current Game code
    this->playersList_ = newplayersList;
    this->currentGame_ = gameRoomObj;

    //Initialize votedFor_ as DEFAULT
    this->votedFor_ = "DEFAULT";



}


//votingTime() actually displays the voting buttons
int votingScreenWidget::votingTime(){


    //Initialize the players, session, and gameroom from the current session database
    typedef dbo::collection< dbo::ptr<Player> > Players;
    dbo::Transaction transaction(*session);
    Players players = session->find<Player>().where("gameRoom = ?").bind(playerPtr->gameRoomID);
    dbo::ptr<GameRoom> currentGameRoom = session->find<GameRoom>().where("gameRoomID = ?").bind(playerPtr->gameRoomID);


    //If the current player is a spy, display the location buttons
    if (playerPtr->id == currentGameRoom->fake){

        new WText("<h3> Which location do you think everybody is at? </h3>", this);

        //Store all the CategoryItem (name, image) pairs in a vector
        std::vector<CategoryItem> allLocations = (this->categoryObjItems).getCategoryItems();

        //For each location
        for(unsigned int i=0; i < allLocations.size(); i++){


            //Create a button with the locations name which sends the CategoryItem matching the location pushed to updateSpyVote
            WPushButton *spybutton;
            spybutton =  new WPushButton(allLocations[i].getName(), this);
            spybutton->setStyleClass("votingButtons");
            spybutton->clicked().connect(boost::bind(&votingScreenWidget::updateSpyVote, this, allLocations[i]));

        }

        //Else if the current player is not the spy
    }else{

        new WText("<h3> Who do you think is the spy?</h3>", this);


        //Loop through the list of current players
        for(unsigned int i = 0; i < (this->playersList_).size(); i++) {

            //Create a button allowing each player to vote for anybody but themselves
            if (playerPtr->id != playersList_[i]){

                WPushButton *testbutton;

                //Create the button displaying the players names which on click sends the voted for player to updateVote
                testbutton =  new WPushButton(playersList_[i], this);
                testbutton->setStyleClass("votingButtons");
                testbutton->clicked().connect(boost::bind(&votingScreenWidget::updateVote, this, playersList_[i]));

            }
        }
    }

    //Create a hidden seeScoresButton which runs goToLeadershipBoard
    seeScoresButton_ = new WPushButton("See Scores", this);
    seeScoresButton_->clicked().connect(this, &votingScreenWidget::goToLeadershipBoard);
    seeScoresButton_->setStyleClass("greenButtons");
    seeScoresButton_->hide();

    return 0;
}


//When the seeScoresButton_ is clicked
void votingScreenWidget::goToLeadershipBoard() {


    //Initiate a transaction to connect to the current session
    typedef dbo::collection< dbo::ptr<Player> > Players;
    dbo::Transaction transaction(*session);

    //Get the list of players in the current session as well as the current gameRoom
    Players players = session->find<Player>().where("gameRoom = ?").bind(playerPtr->gameRoomID);
    dbo::ptr<GameRoom> currentGameRoom = session->find<GameRoom>().where("gameRoomID = ?").bind(playerPtr->gameRoomID);

    //A simple checker to see if all the players have voted yet
    int check = 0;

    //Loop through the list of players
    for (Players::const_iterator i = players.begin(); i != players.end(); ++i) {

        //If any player has not voted, set the check to -1
        if ((*i)->hasVoted == false){
            check = -1;
        }

    }

    //If all players have voted, send the player to the /leadershipBoard
    if (check == 0){
        WApplication::instance()->setInternalPath("/leadershipBoard",  true);

    }
}

//When a non-spy votes for the player they think is the spy
void votingScreenWidget::updateVote(std::string votePos){


    //Initiate the transaction to get the list of players and the gameroom
    typedef dbo::collection< dbo::ptr<Player> > Players;
    dbo::Transaction transaction(*session);
    Players players = session->find<Player>().where("gameRoom = ?").bind(playerPtr->gameRoomID);
    dbo::ptr<GameRoom> currentGameRoom = session->find<GameRoom>().where("gameRoomID = ?").bind(playerPtr->gameRoomID);


    //If this is the first time the player has voted
    if (playerPtr->hasVoted == false){

        //Set the player to as having voted
        playerPtr.modify()->hasVoted = true;

        //Loop through each player in the current game session
        for (Players::const_iterator i = players.begin(); i != players.end(); ++i) {

            //If the player in playerlist is the one being voted for
            if (votePos.compare((*i)->id) == 0){

                //Check if they are the spy
                if (((*i)->id) == currentGameRoom->fake){

                    //If the current player voted for the spy, increase their score by 300
                    playerPtr.modify()->score += 300;

                }

            }

        }

        //Show the scores button, and inform the player they cannot continue until all players have voted
        seeScoresButton_->show();
        new WBreak(this);
        WText* error = new WText("\n Cannot continue until everybody has voted.", this);
        error->setStyleClass("error");

        //Set votedFor_ as the whoever was voted for
        this->votedFor_ = votePos;
    }

}


//updateSpyVote occures when the spy votes for a location
void votingScreenWidget::updateSpyVote(CategoryItem voteLocation){

    //Create the transaction to get the list of players and current gameroom
    typedef dbo::collection< dbo::ptr<Player> > Players;
    dbo::Transaction transaction(*session);
    Players players = session->find<Player>().where("gameRoom = ?").bind(playerPtr->gameRoomID);
    dbo::ptr<GameRoom> currentGameRoom = session->find<GameRoom>().where("gameRoomID = ?").bind(playerPtr->gameRoomID);


    //If the current player has not yet voted
    if (playerPtr->hasVoted == false){

        //Set the current player to as having voted
        playerPtr.modify()->hasVoted = true;

        //If the player correctly guessed the location
        if (voteLocation.getName().compare(currentGameRoom->assignedCategoryItem) == 0){
            //Update the spy's score
            playerPtr.modify()->score += 1000;

        }
        new WBreak(this);
        //Create text informing the player they cannot continue until everybody has voted
        WText* error = new WText("\n Cannot continue until everybody has voted.", this);
        error->setStyleClass("error");

        //Make the button to show the scores visible
        seeScoresButton_->show();
    }

}

//returnVote returns who the player voted for
std::string votingScreenWidget::returnVote(){

    //Used for testing purposes
    return this->votedFor_;
}
