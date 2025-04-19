#include "../../include/WordDict.hpp"

using std::string;
using std::vector;
using std::pair;
using std::set;
using std::unordered_map;
using std::unordered_set;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::endl;

using namespace MyLog;

namespace MySearchEngine
{
WordDict::WordDict(WordSplit *tool) : _tool(tool) {
    string storeDictPath = Configuration::getInstance()->getConfig()["Dict"];
    string storeIndexPath =
        Configuration::getInstance()->getConfig()["DictIndex"];
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

vector<pair<string, int>> &WordDict::getDict() {
    return _dict;
}

unordered_map<string, set<int>> &WordDict::getIndex() {
    return _index;
}

vector<string> WordDict::getFiles(string path) {
    vector<string> tmp;
    DIR *pdir = opendir(path.c_str());
    if (!pdir) {
        LogError("open dir failed");
        exit(-1);
    }

    struct dirent *file;
    while ((file = readdir(pdir)) != nullptr) {
        if (file->d_name[0] == '.') {
            continue;
        }

        tmp.push_back(path + "/" + file->d_name);
    }

    closedir(pdir);
    return tmp;
}

void WordDict::getStopWords() {
    string cn_stop_file =
        Configuration::getInstance()->getConfig()["cnStopFile"];
    string en_stop_file =
        Configuration::getInstance()->getConfig()["enStopFile"];

    ifstream cn_ifs(cn_stop_file);
    ifstream en_ifs(en_stop_file);
    if (!cn_ifs) {
        LogError("open cnStopFile failed");
        exit(-1);
    }

    if (!en_ifs) {
        LogError("open enStopFile failed");
        exit(-1);
    }

    string word;
    while (cn_ifs >> word) {
        _stop_word.insert(word);
        word.clear();
    }
    while (en_ifs >> word) {
        _stop_word.insert(word);
        word.clear();
    }

    en_ifs.close();
    cn_ifs.clear();
}

void WordDict::buildDict(string type) {
    unordered_map<string, int> tmpDict; // 先用unordered_map存储一下，避免重复词
    if (type == "cn") {
        for (auto &ele : _cnFileNames) {
            ifstream cn_file_ifs(ele);
            if (!cn_file_ifs) {
                LogError("open cn file error");
            }

            string line;
            while (getline(cn_file_ifs, line)) {
                vector<string> words = _tool->cut(line);
                for (size_t idx = 0; idx < words.size(); ++idx) {
                    string word = words[idx];
                    if (word != " "
                        && (_stop_word.find(word) == _stop_word.end())) {
                        ++tmpDict[word];
                    }
                }
            }
        }
    } else if (type == "en") {
        for (auto &filename : _enFilenames) {
            ifstream en_file_ifs(filename);
            if (!en_file_ifs) {
                LogError("open en file error");
            }

            string line;
            while (getline(en_file_ifs, line)) {
                string word;
                istringstream line_iss(line);

                while (line_iss >> word) {
                    string processed_word;
                    processed_word.reserve(word.size());
                    for (char &c : word) {
                        if (isupper(c)) {
                            c += 32;
                        }
                        if (isalpha(c) || c == '-') {
                            processed_word.push_back(c);
                        } else {
                            continue;
                        }
                    }

                    if (processed_word.back() == '-') {
                        processed_word.pop_back();
                    }

                    if (processed_word != ""
                        && (_stop_word.count(processed_word) == 0)) {
                        tmpDict[processed_word]++;
                    }
                }
            }
        }
    } else {
        LogWarn("word type is not known in dict");
    }

#ifdef WORDDICTDEBUG
    std::cout << "all the word num in dict is :" << tmpDict.size() << endl;
#endif

    std::copy(tmpDict.begin(), tmpDict.end(), std::back_inserter(_dict));
}

size_t WordDict::getByNumUTF8(const char byte) {
    int byteNum = 0;
    for (size_t idx = 0; idx < 6; ++idx) {
        if (byte & (1 << (7 - idx))) // 从byte的最高位开始判断，最多判断6位
        {
            ++byteNum;
        } else {
            break;
        }
    }
    return byteNum == 0 ? 1 : byteNum;
}

void WordDict::buildIndex() {
    // 遍历_dict中的每一个pair中的key，将key的每个字符和当前下标(vector的下标)存到_index中
    for (size_t lineNum = 0; lineNum < _dict.size(); ++lineNum) {
        string word = _dict[lineNum].first;
        size_t charLen = getByNumUTF8(word[0]);

        for (size_t idx = 0; idx < word.size() - charLen; idx += charLen) {
            string subWord = word.substr(idx, charLen);
            _index[subWord].insert(lineNum);
        }
#ifdef WORDDICTDEBUG
        std::cout << "the last line num in build index:" << lineNum;
        std::cout << ",the word is " << word << endl;

#endif
    }
#ifdef WORDDICTDEBUG
    std::cout << "all the index num :" << _index.size() << endl;
#endif
}

void WordDict::storeDict(const string &filePath) {
    ofstream dict_ofs(filePath);
    if (!dict_ofs) {
        LogError("open file filed");
    }

    for (auto &ele : _dict) {
        dict_ofs << ele.first << " " << ele.second << endl;
    }
}

void WordDict::storeIndex(const string &filePath) {
    ofstream index_ofs(filePath);
    if (!index_ofs) {
        LogError("open file filed");
    }

    for (auto &item : _index) {
        index_ofs << item.first << " ";

        for (auto num : item.second) {
            index_ofs << num << " ";
        }
        index_ofs << endl;
    }
}

} // namespace MySearchEngine
