/**
* The Player class stores the info for each user and is used as a schema for the player table in the database
* @author  Annie Liang
* @since   2020-12-1
*/

#include <string>
#include <Wt/Dbo/Types>
#include <Wt/Dbo/WtSqlTraits>

#ifndef ISPYAFAKE_PLAYER_H
#define ISPYAFAKE_PLAYER_H

class Player;
typedef Wt::Dbo::collection< Wt::Dbo::ptr<Player> > Players;

class Player {

public:
    Player() {};
    std::string id;
    int score = 0;
    std::string gameRoomID;
    bool isSpy = false;
    bool isHost;
    bool hasVoted = false;
    std::string categoryItem;

    template<class Action>
    void persist(Action& a)
    {
        Wt::Dbo::field(a, id, "named");
        Wt::Dbo::field(a, gameRoomID, "gameRoom");
        Wt::Dbo::field(a, score, "score");
        Wt::Dbo::field(a, isSpy, "isSpy");
        Wt::Dbo::field(a, isHost, "isHost");
        Wt::Dbo::field(a, hasVoted, "hasVoted");
        Wt::Dbo::field(a, categoryItem, "categoryItem");
    }
};

DBO_EXTERN_TEMPLATES(Player);
#endif //ISPYAFAKE_PLAYER_H







