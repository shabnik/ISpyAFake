/**
* The WaitingRoomWidget is the page/widget that displays the game lobby and allows the host to start the game
* @author  Annie Liang
* @since   2020-12-1
*/

#ifndef ISPYAFAKE_WAITINGROOMWIDGET_H
#define ISPYAFAKE_WAITINGROOMWIDGET_H

#include <vector>
#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/backend/Sqlite3>
#include <Wt/WContainerWidget>
#include <Wt/WPushButton>
#include <Wt/WText>
#include "CategoryAssignment.h"
#include "GameRoom.h"

class WaitingRoomWidget: public Wt::WContainerWidget
{
private:
    std::string currentGame_;
    Wt::Dbo::Session *session_;
    Wt::Dbo::ptr<Player> playerPtr_;
    //ui elements to display on page
    Wt::WPushButton *refreshButton_;
    Wt::WPushButton *startButton_;
    Wt::WPushButton *seeLocationButton_;
    Wt::WText *gameNotStartedError_;
    Wt::WText *notEnoughPlayersError_;
    Wt::WText *tempPlayer_;
public:
    WaitingRoomWidget(Wt::Dbo::ptr<Player> playerPointer, Wt::Dbo::Session *session, std::string gameRoomObj, Wt::WContainerWidget *parent = 0);
    //update list of players in the lobby
    void update();
    //assigns category item and spy
    void assignCategories();
    //directs users to page to see their assigned category/role
    void seeLocation();
};


#endif //ISPYAFAKE_WAITINGROOMWIDGET_H





