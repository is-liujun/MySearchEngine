#include "../include/Configuration.hpp"

#include<fstream>
#include <sstream>
#include <iostream>

using std::unordered_map;
using std::string;
using std::ifstream;
using std::istringstream;
using std::cout;
using std::endl;

namespace MySearchEngine
{
    Configuration * Configuration::_pInstance = Configuration::getInstance();

    Configuration::Configuration(){
        loadFile();
    }

    Configuration::~Configuration(){
    }

    Configuration *Configuration::getInstance(){
        if(!_pInstance){
            _pInstance = new Configuration();
            atexit(destroy);
        }

        return _pInstance;
    }

    void Configuration::destroy(){
        if(_pInstance){
            delete _pInstance;
        }
    }

    void Configuration::loadFile(){
        ifstream ifs(_filename);
        if(!ifs){
            cout << "文件打开失败" << endl;
        }

        string line;
        while(getline(ifs,line)){
            if(line.empty() || line[0] == '#'){
                continue;
            }

            string key;
            string value;
            istringstream iss(line);
            iss >> key;
            iss >> value;
            _config[key] = value;
        }
    }

    unordered_map<string, string> &Configuration::getConfig(){
        return _config;
    }

} //namespace MySearchEngine
