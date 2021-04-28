/**
* The ISAFGames creates a new game room with a unique id
* @author  Annie Liang
* @since   2020-12-1
*/
#ifndef ISPYAFAKE_ISAFGAMES_H
#define ISPYAFAKE_ISAFGAMES_H

#include "GameRoom.h"

class ISAFGames {
public:
    //creates and returns a new game room object
    GameRoom* createNewGame(std::string host);
    //method to generate unique id
    std::string generateGameRoomId();
};


#endif //ISPYAFAKE_ISAFGAMES_H



