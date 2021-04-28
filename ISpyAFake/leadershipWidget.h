/** leadershipWidget.h
* The leadershipWidget is the widget which allows players to view the scores post-game. Also contains the buttons to start a new game.
* @author  Nicholas Pehme
* @since   2020-12-1
*/
#ifndef ISPYAFAKE_LEADERSHIPWIDGET_H
#define ISPYAFAKE_LEADERSHIPWIDGET_H

#include <stdio.h>
#include <string>
#include <vector>
#include "GameRoom.h"
#include "Player.h"
#include "Wt/Dbo/backend/Sqlite3"
#include "Wt/Dbo/Dbo"
#include <Wt/WApplication>
#include "Wt/WButtonGroup"
#include "Wt/WContainerWidget"
#include "Wt/WLink"
#include "Wt/WPushButton"
#include "Wt/WString"
#include "Wt/WTable"
#include "Wt/WTemplate"
#include "Wt/WText"




class leadershipWidget: public Wt::WContainerWidget
{
private:

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

    /** leaveGameButton_
	*
	*	used to allow a player to leave the current game
	 */
    Wt::WPushButton *leaveGameButton_;

    /** endGameButton_
	*
	*	used by host to end the current game for all players
	 */
    Wt::WPushButton *endGameButton_;

    /** newRoundButton_
	*
	*	used to create the button which starts a new round
	 */
    Wt::WPushButton *newRoundButton_;

    /** endedGameError_
	*
	*	text containing the end game error message
	 */
    Wt::WText *endedGameError_;

    /** endGame()
	*
	*	Function used by the endGameButton
	 */
    void endGame();

    /** leaveGame()
	*	function used by the leaveGameButton
	 */
    void leaveGame();

    /** newRound()
	*
	*	function used by the newRoundButton_
	 */
    void newRound();

public:

    /** leadershipWidget constructor
     * @param *session - the current game session
     * @param playerPointer - a pointer to the current player
     * @param *parent - the parent of the container widget
     */
    leadershipWidget(Wt::Dbo::Session *session, Wt::Dbo::ptr<Player> playerPointer, Wt::WContainerWidget *parent=0);

    /** leaderTime()
     *  A function used to display the scoreboard and buttons
     */
    void leaderTime();


};


#endif
