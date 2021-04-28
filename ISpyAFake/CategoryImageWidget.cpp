/**
* The implementation for CategoryImageWidget class
* @author  Annie Liang
* @since   2020-12-1
*/
#include <Wt/WApplication>
#include <Wt/WImage>
#include <Wt/WLink>
#include "CategoryImageWidget.h"

using namespace Wt;
using namespace std;

CategoryImageWidget::CategoryImageWidget(Dbo::ptr<Player> playerPointer, CategoryItem selectedCategory, string fake, Category categoryItems, WContainerWidget *parent) :
playerPtr_(playerPointer), WContainerWidget(parent) {

    setContentAlignment(AlignCenter);
    gallery_ = new WContainerWidget(this);
    gallery_->setStyleClass("categoryPage");
    vector<CategoryItem> items_ = categoryItems.getCategoryItems();
    //display player name
    gallery_->addWidget(new WText("<p> Player: " + playerPtr_->id + "</p>", this));
    gallery_->addWidget(new WText("<h2>Game Location</h2>", this));
    //display category item only if player is not the spy
    if(playerPtr_->id == fake) {
        gallery_->addWidget(new WText("<p>You're the fake</p>", this));
    } else {
        tempImage_ = new WImage(Wt::WLink(selectedCategory.getImage()), this);
        tempImage_->resize(150, 150);
        tempImage_->setAlternateText(selectedCategory.getName());
        gallery_->addWidget(tempImage_);
        gallery_->addWidget(new WText("<p>" + selectedCategory.getName() + "</p>", this));
    }
    //button to direct user to voting screen
    readyToVoteButton_ = new WPushButton("Ready To Vote", this);
    readyToVoteButton_->clicked().connect(this, &CategoryImageWidget::goToVote);
    readyToVoteButton_->setStyleClass("purpleButtons");
    gallery_->addWidget(readyToVoteButton_);
    gallery_->addWidget(new WText("<h3>Possible locations: </h3>", this));
    possibleLocations_ = new WContainerWidget(this);
    possibleLocations_->setStyleClass("locationsContainer");
    //show all the possible category items on the screen
    for(int i = 0; i < items_.size(); i++) {
        locationItem_ = new WContainerWidget(this);
        locationItem_->setStyleClass("locationItem");
        tempImage_ = new WImage(Wt::WLink(items_[i].getImage()), this);
        tempImage_->resize(100, 100);
        tempImage_->setAlternateText(items_[i].getName());
        locationItem_->addWidget(tempImage_);
        locationItem_->addWidget(new WText("<p>" + items_[i].getName() + "</p>", this));
        possibleLocations_->addWidget(locationItem_);
    }
    gallery_->show();
    possibleLocations_->show();
}

void CategoryImageWidget::goToVote() {
    WApplication::instance()->setInternalPath("/votingPage",  true);
}










