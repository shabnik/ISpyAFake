/** votingScreenWidget.h
* The votingScreenWidget is the widget that allows the players to vote.
* Normal players can vote for who they think is the spy, and the spy can vote for the location given to the normal players.
* @author  Nicholas Pehme
* @since   2020-12-1
*/
#ifndef ISPYAFAKE_VOTINGSCREENWIDGET_H
#define ISPYAFAKE_VOTINGSCREENWIDGET_H

#include <stdio.h>
#include <string>
#include <vector>
#include "CategoryAssignment.h"
#include "CategoryImageWidget.h"
#include "GameRoom.h"
#include "Player.h"
#include "Wt/Dbo/backend/Sqlite3"
#include "Wt/Dbo/Dbo"
#include "Wt/WApplication"
#include "Wt/WButtonGroup"
#include "Wt/WContainerWidget"
#include "Wt/WLink"
#include "Wt/WPushButton"
#include "Wt/WString"
#include "Wt/WTemplate"
#include "Wt/WText"

namespace dbo = Wt::Dbo;



class votingScreenWidget: public Wt::WContainerWidget
{
private:


    /** playersList
     *
     *	PlayersList will hold a string list of all players in the current game lobby
     */
    std::vector<std::string> playersList_;


    /** votedFor
	 *
	 *	votedFor will store the name of the player/location that has been voted for
	 */
    std::string votedFor_;

    /** currentGame
	 *
	 *	currentGame will store the string code of the current game
	 */
    std::string currentGame_;

    /** session
	 *
	 *	session stores the current game session, used when connecting to the database
	 */
    Wt::Dbo::Session *session;

    /** playerPtr
	 *
	 *	playerPtr is a pointer which stores a Player object of the current player
	 */
    Wt::Dbo::ptr<Player> playerPtr;

    /** categoryObjItems
	*
	*	Stores each of the category name/file pairs
	 */
    Category categoryObjItems;

    /** seeScoresButton_
	*
	*	used during creation of the button taking users to the leadershipWidget
	 */
    Wt::WPushButton *seeScoresButton_;


public:

    /**votingScreenWidget Constructor
     * @param *session - the current game session
     * @param gameRoomObj - the current gameroom code
     * @param newPlayersList - a string list of the current players
     * @param playerPointer - pointer to the current player
     * @param categoryItems - all the location names/images
     * @param *parent - the parent container
     */
    votingScreenWidget(Wt::Dbo::Session *session, std::string gameRoomObj, std::vector<std::string> newplayersList,Wt::Dbo::ptr<Player> playerPointer, Category categoryItems, Wt::WContainerWidget *parent=0);

    /** votingTime
     * votingTime is the function which will be called when it is time to vote, and the buttons should be displayed
     * 
     */
    int votingTime();

    /** updateVote
     * Occures when a nonspy clicks on a player to vote for, must check if correct and adjust player score
     * @param votePos - Takes in the string name of the player being voted for
     */
    void updateVote(std::string votePos);

    /** updateSpyVote
     * Occures when a spy clicks on a location to vote for, must check if correct and adjust player score
     * @param voteLocation - Takes the CategoryItem location that the player voted for
     */
    void updateSpyVote(CategoryItem voteLocation);

    /** returnVote
     * Will return the votedFor_ variable.
     * @returns will return the votedFor_ string
     */
    std::string returnVote();

    /** goToLeadershipBoard
     * occures when the showScores button is clicked, takes the player to the scorboard if voting has completed.
     */
    void goToLeadershipBoard();

};


#endif
