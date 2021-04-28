/**
* The implementation for CategoryAssignment class
* @author  Annie Liang
* @since   2020-12-1
*/
#include "CategoryAssignment.h"

using namespace std;

CategoryAssignment::CategoryAssignment(vector<string> users, Category category) {
    chosenCategory_ = category;
    usersInGame_ = users;
}

CategoryItem CategoryAssignment::getAssignCategoryItem() {
    //randomly choose a fake from our list of players
    randomizeFake();
    //pick a random category item to assign to players
    return chosenCategory_.randomizeImage();
}

void CategoryAssignment::randomizeFake() {
    srand(time(0));
    int randomNum = usersInGame_.size() > 1 ? rand() % usersInGame_.size() : 0;
	//set the randomly selected player to be the spy
    fake_ = usersInGame_[randomNum];
}



