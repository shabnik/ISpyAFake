/*
/@Author: Shabnam Nikpour
/Header file for GameRoom class
/@Date: Novermber 8th 2020
*/

#ifndef GAMEROOM_H
#define GAMEROOM_H

#include <string>
#include <Wt/Dbo/Types>
#include <Wt/Dbo/WtSqlTraits>
#include "Player.h"

class GameRoom;
typedef Wt::Dbo::collection< Wt::Dbo::ptr<GameRoom> > GameRooms;

class GameRoom {

public:
    std::string code;
    std::string host;
    std::string fake;
    std::string assignedCategoryItem;
    std::string gameStatus;
    GameRoom();
    void start();
	void end(); 

    template<class Action>
    void persist(Action& a)
    {
        Wt::Dbo::field(a, code, "gameRoomID");
        Wt::Dbo::field(a, gameStatus, "gameStatus");
        Wt::Dbo::field(a, fake, "fake");
        Wt::Dbo::field(a, assignedCategoryItem, "categoryItem");
        Wt::Dbo::field(a, host, "host");
    }
};
#endif



