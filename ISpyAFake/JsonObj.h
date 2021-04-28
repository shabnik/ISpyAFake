/*
*@author:Shabnam Nikpour
*@Date: November 25th 2020
*Header file for the JsonObj class
*/
#ifndef JSONOBJ_H
#define JSONOBJ_H

#include <vector>
#include <fstream>
#include <string>
#include "json.hpp"
#include "Category.h"

using json = nlohmann::json;

class JsonObj{
private:
    json j;

public:
	JsonObj(){};
	Category readJsonFileToCategory();
	void writeToJsonFile(std::string, std::string);
};


#endif //ISPYAFAKE_Json_H

