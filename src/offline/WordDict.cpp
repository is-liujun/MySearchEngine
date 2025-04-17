#include "../../include/WordSplit.hpp"
#include "../../include/Configuration.hpp"
#include "../../include/MyLogger.hpp"

#include <dirent.h>

#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <sstream>

using std::string;
using std::vector;
using std::pair;
using std::set;
using std::unordered_map;
using std::unordered_set;
using std::ifstream;
using std::ofstream;
using std::istringstream;

using namespace MyLog;

namespace MySearchEngine
{

class WordSplit;

class WordDict{
    public:
        WordDict(WordSplit *tool);
        vector<pair<string, int>>& getDict();
        unordered_map<string, set<int>>& getIndex();
        size_t getByNumUTF8(const char byte);

    private:
        //获取一个目录下的所有文件
        vector<string> &getFiles(string path);
        // 获取停止词
        void getStopWords();
        // 读取文件名获取内容,停止词最好在这里就不要存进去
        void buildDict(string type);
        //建立下标
        void buildIndex();

        void storeDict(const string &filePath);
        void storeIndex(const string &filePath);


    private:
        WordSplit *_tool;
        vector<string> _cnFileNames;
        vector<string> _enFilenames;
        vector<pair<string, int>> _dict;
        unordered_map<string, set<int>> _index;
        string _cnDir;
        string _enDir;
        unordered_set<string> _stop_word;
};

WordDict::WordDict(WordSplit *tool)
:_tool(tool)
{
    string storeDictPath = Configuration::getInstance()->getConfig()["Dict"];
    string storeIndexPath = Configuration::getInstance()->getConfig()["DictIndex"];
    _cnDir = Configuration::getInstance()->getConfig()["cnDir"];
    _enDir = Configuration::getInstance()->getConfig()["enDir"];
    _cnFileNames = getFiles(_cnDir);
    _enFilenames = getFiles(_enDir);
    getStopWords();
    buildDict("cn");
    buildDict("en");
    buildIndex();
    storeDict(storeDictPath);
    storeIndex(storeIndexPath);
}


vector<pair<string, int>>& WordDict::getDict(){
    return _dict;
}

unordered_map<string, set<int>>& WordDict::getIndex(){
    return _index;
}

vector<string> & WordDict::getFiles(string path){
    vector<string> tmp;
    DIR *pdir = opendir(path.c_str());
    if(!pdir){
        LogError("open dir failed");
        exit(-1);
    }

    struct dirent *file;
    while((file = readdir(pdir)) != nullptr){
        if(file->d_name[0] == '.'){
            continue;
        }

        tmp.push_back(path + file->d_name);
    }

    closedir(pdir);
    return tmp;
}

void WordDict::getStopWords(){
    string cn_stop_file = Configuration::getInstance()->getConfig()["cnStopFile"];
    string en_stop_file = Configuration::getInstance()->getConfig()["enStopFile"];

    ifstream cn_ifs(cn_stop_file);
    ifstream en_ifs(en_stop_file);
    if(!cn_ifs){
        LogError("open cnStopFile failed");
        exit(-1);
    }

    if(!en_ifs){
        LogError("open enStopFile failed");
        exit(-1);
    }

    string word;
    while(cn_ifs >> word){
        _stop_word.insert(word);
        word.clear();
    }
    while(en_ifs >> word){
        _stop_word.insert(word);
        word.clear();
    }

    en_ifs.close();
    cn_ifs.clear();
}

    void WordDict::buildDict(string type){
        unordered_map<string, int> tmpDict;
        if(type == "cn"){
            for(auto &ele : _cnFileNames){
                ifstream cn_file_ifs(ele);
                if(!cn_file_ifs){
                    LogError("open cn file error");
                }

                string line;
                while(getline(cn_file_ifs, line)){
                    vector<string> words = _tool->cut(line);
                    for(size_t idx = 0; idx < words.size(); ++idx){
                        string word = words[idx];
                        if(word != " " && (_stop_word.find(word) == _stop_word.end())){
                            ++tmpDict[word];
                        }
                    }
                }
            }
        }else if(type == "en"){
            for(auto &filename : _enFilenames){
                ifstream en_file_ifs(filename);
                if(!en_file_ifs){
                    LogError("open en file error");
                }

                string line;
                while(getline(en_file_ifs, line)){
                    string word;
                    istringstream line_iss(line);

                    while(line_iss >> word){
                        string processed_word;
                        processed_word.reserve(word.size());
                        for(char &c : word){
                            if(isupper(c)){
                                tolower(c);
                            }
                            if(isalpha(c) || c == '-'){
                                processed_word.push_back(c);
                            }else{
                                continue;
                            }
                        }

                        if(processed_word.back() == '-'){
                            processed_word.pop_back();
                        }

                        if(processed_word != " " && _stop_word.count(processed_word) == 0){
                            tmpDict[processed_word]++;
                        }
                    }
                }
            }
        }else{
            LogWarn("type is not known");
        }

        std::copy(tmpDict.begin(),tmpDict.end(), std::back_inserter(_dict));
    }






}//namespace MySearchEngine
