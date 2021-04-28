/**
* The CategoryItem stores the name and image of a location
* @author  Annie Liang
* @since   2020-12-1
*/
#include <string>

#ifndef ISPYAFAKE_CATEGORYITEM_H
#define ISPYAFAKE_CATEGORYITEM_H

class CategoryItem {
private:
    std::string name_;
    std::string image_;
public:
    CategoryItem(std::string itemName, std::string itemImage) {
        name_ = itemName;
        image_ = itemImage;
    }
    //getter methods to retrieve name and image
    std::string getName() { return name_; }
    std::string getImage() { return image_; }
};

#endif //ISPYAFAKE_CATEGORYITEM_H

