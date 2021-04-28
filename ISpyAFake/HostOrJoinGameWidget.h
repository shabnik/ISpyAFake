/**
* The HostOrJoinGameWidget is the page/widget that displays the join/create game screen and handles the corresponding routing
* @author  Annie Liang
* @since   2020-12-1
*/

#ifndef ISPYAFAKE_HOSTORJOINGAMEWIDGET_H
#define ISPYAFAKE_HOSTORJOINGAMEWIDGET_H

#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/backend/Sqlite3>
#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include "GameRoom.h"
#include "ISAFGames.h"
#include "Player.h"


class HostOrJoinGameWidget : public Wt::WContainerWidget {
private:
    Wt::Dbo::ptr<Player> playerPtr_;
    Wt::WContainerWidget *HostCon_;
    Wt::Dbo::Session *session_;
    //ui elements for the screen
    Wt::WLineEdit *nameEdit_;
    Wt::WLineEdit *searchGameName_;
    Wt::WPushButton *joinGameButton_;
    Wt::WPushButton *hostGameButton_;
    Wt::WText *greeting_;
    Wt::WText *headerText_;
    Wt::WText *nameError_;
    Wt::WText *gameError_;
    Wt::WText *fullGameError_;
    std::string gameRoom_;
    //handles request to host game and checks for naming errors
    void hostGame();
    //handles request to join game and checks for valid game rooms
    void joinGame();
    void hideErrorMessages();
    //show correct error messages
    void showErrorMessages(int type);
public:
    HostOrJoinGameWidget(Wt::Dbo::Session *session, Wt::WContainerWidget *parent = 0);
    //get name of player
    std::string getUserName();
    //get name of game player wishes to join
    std::string getGameName();
};


#endif //ISPYAFAKE_HOSTORJOINGAMEWIDGET_H


