/**
* Implementation for the GameRoom class
* @author  Shabnam Nikpour
* @Date November 20th
*/

#include "GameRoom.h"


GameRoom::GameRoom() {
    gameStatus = "waiting";
}

void GameRoom::start()
{
    gameStatus = "gameStarted";
}
void GameRoom::end()
{
    gameStatus = "gameFinished";
}

