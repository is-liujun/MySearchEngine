#include "../../include/WordSplit_Jieba.hpp"

namespace MySearchEngine{

        WordSplit_Jieba::WordSplit_Jieba()
        :_jieba(dict_path,model_path,user_dict_path, idf_dict_path, stop_words_path)
        {
        }

        std::vector<std::string> WordSplit_Jieba::cut(std::string &line) {
            std::vector<std::string> res;
            _jieba.Cut(line, res, true);

            return res;
        }



} //namespace MySearchEngine
