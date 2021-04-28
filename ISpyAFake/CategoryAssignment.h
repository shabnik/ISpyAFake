/**
* The CategoryAssignment class assigns a random category item and the player who will be the fake
* @author  Annie Liang
* @since   2020-12-1
*/
#include <vector>
#include "Category.h"
#include "Player.h"

#ifndef ISPYAFAKE_CATEGORYASSIGNMENT_H
#define ISPYAFAKE_CATEGORYASSIGNMENT_H


class CategoryAssignment {
    private:
        std::string fake_;
        std::vector<std::string> usersInGame_;
        //store reference to category
        Category chosenCategory_;
        //selects random player to be the fake
        void randomizeFake();

    public:
        CategoryAssignment(std::vector<std::string> users, Category category);
	    std::string getFake() { return fake_; }
	    //get randomly selected category item
        CategoryItem getAssignCategoryItem();
};


#endif //ISPYAFAKE_CATEGORYASSIGNMENT_H



