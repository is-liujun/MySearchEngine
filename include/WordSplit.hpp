#ifndef __WORDSPLIT_HPP__
#define __WORDSPLIT_HPP__
#include <vector>
#include <string>

namespace MySearchEngine
{

class WordSplit{
    public:
        WordSplit(){};
        ~WordSplit(){};
        virtual std::vector<std::string> cut(std::string &line) = 0;
};

} //namespace MySearchEngine
#endif
