#include "WordSplit.hpp"
#include "Configuration.hpp"
#include "MyLogger.hpp"

#include <dirent.h>

#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <sstream>

namespace MySearchEngine
{
class WordSplit;

class WordDict
{
public:
    WordDict(WordSplit *tool);
    std::vector<std::pair<std::string, int>> &getDict();
    std::unordered_map<std::string, std::set<int>> &getIndex();
    size_t getByNumUTF8(const char byte);

private:
    // 获取一个目录下的所有文件
    std::vector<std::string> getFiles(std::string path);
    // 获取停止词
    void getStopWords();
    // 读取文件名获取内容,停止词最好在这里就不要存进去
    void buildDict(std::string type);
    // 建立下标
    void buildIndex();

    void storeDict(const std::string &filePath);
    void storeIndex(const std::string &filePath);

private:
    WordSplit *_tool;
    std::vector<std::string> _cnFileNames;
    std::vector<std::string> _enFilenames;
    std::vector<std::pair<std::string, int>> _dict;
    std::unordered_map<std::string, std::set<int>> _index;
    std::string _cnDir;
    std::string _enDir;
    std::unordered_set<std::string> _stop_word;
};

} // namespace MySearchEngine
