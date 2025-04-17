#include "../include/Configuration.hpp"
#include <iostream>

using namespace MySearchEngine;

using std::string;
using std::unordered_map;
using std::endl;
using std::cout;

int main(){
     unordered_map<string, string> result = Configuration::getInstance()->getConfig();


     for(auto &ele : result){
         cout << ele.first << "---->" << ele.second << endl;
     }

}
