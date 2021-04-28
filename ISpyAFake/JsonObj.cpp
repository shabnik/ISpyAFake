/*
*@Author: Shabnam Nikpour
@Date: November 25th 2020
*This class reads and writes to json file with the help of open sourse code found on https://github.com/nlohmann/json
*/
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include "json.hpp"
#include "JsonObj.h"
#include "CategoryItem.h"
#include "Category.h"

using json = nlohmann::json;
using namespace std;

/*
*Function that writes to the json file
*@param: string name = the name of the location
*@param: string location = the location on file where it is located
*/
void JsonObj::writeToJsonFile(std::string name, std::string location){
	json j;//json object
	std::ifstream readJson("storeCategory.json");
        readJson >> j;

	//adds the name and location of image to the json object
	j.emplace(name, location);

	//writes the new name and location of the image to a json file
	std::ofstream o;
	o.open("storeCategory.json");
        o << std::setw(4) << j << std::endl;
}

/*
*Function that reads the json file and stores the info into the category array
*/
Category JsonObj::readJsonFileToCategory(){
	Category categoryObj;

	std::ifstream readJson("storeCategory.json");
	json k;
	readJson >> k;

	// iterators json file and adds to category list
	for (json::iterator it = k.begin(); it != k.end(); ++it){
	std::string tempLocation = it.value();
	std::string tempName = it.key();
	categoryObj.addImage(tempName , tempLocation);
	std::cout << tempName << "\t" << tempLocation << "\n" << std::endl;
	//^^should be taken out later
	}
	return categoryObj;
}

