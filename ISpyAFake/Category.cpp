/**
* Implementation for the Category class
* @author  Annie Liang
* @since   2020-12-1
*/

#include <stdlib.h>
#include "Category.h"

using namespace std;

Category::Category() {
    index_ = 0;
}

void Category::setCategoryName(string name) {
    categoryName_ = name;
}

void Category::addImage(string itemName, string image) {
    //add new category item to category list
    itemArray_.push_back(CategoryItem(itemName, image));
    index_++;
}

CategoryItem Category::findCategory(std::string name) {
    for(int i = 0; i < itemArray_.size(); i++) {
        if(itemArray_[i].getName() == name) {
            return itemArray_[i];
        }
    }
}

CategoryItem Category::randomizeImage() {
    srand(time(0));
    //select random number from 0 to [number of images]
    int randomNum = rand() % index_;
    //return randomly assigned image
    return itemArray_[randomNum];
}


