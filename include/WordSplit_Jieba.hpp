#ifndef __WORDSPLIT_JIEBA_HPP__
#define __WORDSPLIT_JIEBA_HPP__
#include "WordSplit.hpp"
#include "../otherLib/cppjieba/Jieba.hpp"

namespace MySearchEngine
{

class WordSplit_Jieba
:public WordSplit
{
    public:
        WordSplit_Jieba();
        std::vector<std::string> cut(std::string &line) override;
    private:
        std::string dict_path = "../otherLib/cppjieba/dict/jieba.dict.utf8";  //注意，这些路径相对的是程序运行时的当前工作目录
        std::string model_path = "../otherLib/cppjieba/dict/hmm_model.utf8";
        std::string user_dict_path = "../otherLib/cppjieba/dict/user.dict.utf8";
        std::string idf_dict_path = "../otherLib/cppjieba/dict/idf.utf8";
        std::string stop_words_path = "../otherLib/cppjieba/dict/stop_words.utf8";
        cppjieba::Jieba _jieba;
};

}

#endif
