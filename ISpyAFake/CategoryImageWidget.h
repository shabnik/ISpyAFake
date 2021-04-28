/**
* The CategoryImageWidget is the page/widget that displays the assigned category item and the list of categories on the screen.
* @author  Annie Liang
* @since   2020-12-1
*/

#ifndef ISPYAFAKE_CATEGORYIMAGEWIDGET_H
#define ISPYAFAKE_CATEGORYIMAGEWIDGET_H

#include <vector>
#include <Wt/Dbo/backend/Sqlite3>
#include <Wt/Dbo/Dbo>
#include <Wt/WContainerWidget>
#include <Wt/WPushButton>
#include <Wt/WText>
#include "Category.h"
#include "Player.h"

class CategoryImageWidget : public Wt::WContainerWidget {
private:
    std::vector<Wt::WContainerWidget *> images_;
    //gallery to display all the images
    Wt::WContainerWidget *gallery_;
    Wt::WContainerWidget *possibleLocations_;
    Wt::WContainerWidget *locationItem_;
    Wt::WImage *image_;
    Wt::WImage *tempImage_;
    Wt::WPushButton *readyToVoteButton_;
    Wt::WText *name_;
    //pointer to current player
    Wt::Dbo::ptr<Player> playerPtr_;
public:
    CategoryImageWidget(Wt::Dbo::ptr<Player> playerPointer, CategoryItem selectedCategory, std::string fake, Category categoryItems, Wt::WContainerWidget *parent = 0);
    //set internal path to go to voting page
    void goToVote();
};


#endif //ISPYAFAKE_CATEGORYIMAGEWIDGET_H








