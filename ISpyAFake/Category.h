/**
* The Category class stores the names and images of all the category items
* @author  Annie Liang
* @since   2020-12-1
*/
#include <string>
#include <vector>
#include "CategoryItem.h"

#ifndef ISPYAFAKE_CATEGORY_H
#define ISPYAFAKE_CATEGORY_H

class Category {
private:
    //list to store the category items
    std::vector<CategoryItem> itemArray_;
    std::string categoryName_;
    int index_;

public:
    Category();
    //sets name for the category
    void setCategoryName(std::string name);
    //adds category item to the category
    void addImage(std::string itemName, std::string image);
    //returns name of category
    std::string getCategoryName() { return categoryName_; }
    //returns all the items in the category
    std::vector<CategoryItem> getCategoryItems() { return itemArray_; }
    //returns random item from category
    CategoryItem randomizeImage();
    //finds the category item info based on name passed in
    CategoryItem findCategory(std::string name);
};


#endif //ISPYAFAKE_CATEGORY_H


