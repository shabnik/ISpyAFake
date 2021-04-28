/**
* Implementation for the ISAFGames class
* @author  Annie Liang
* @since   2020-12-1
*/
#include <chrono>
#include "ISAFGames.h"

using namespace std;
using namespace std::chrono;

GameRoom* ISAFGames::createNewGame(string host) {
    GameRoom* newGame = new GameRoom();
    newGame->host = host;
    newGame->code = this->generateGameRoomId();
    return newGame;
}

std::string ISAFGames::generateGameRoomId() {
    //create string based on time since epoch time to guarantee uniqueness
    milliseconds ms = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );
    return to_string(ms.count());
}




