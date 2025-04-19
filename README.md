1、对于分词工具的实现
    可以抽象类继承Pimpl模式来实现。 抽象类也可以通过类的前向声明和多态来实现减少编译的目的。
    如果为了更好的封装的话，也可以使用pimpl, pimpl模式如下：
    //WordSplit_Jieba.hpp
    class WordSplit_Jieba{
        WordSplit_Jieba();
        vector<string> cut(std::string &line);

        private:
            class CppJiebaImpl;
            CppJiebaImpl *_cppjiebaImpl;
    };

    // WordSplit_Jieba.cpp
    #include "/otherLIb/Jieba.hpp"

    vector<strng> WordSplit_Jieba::cut(string &line){
        _cppjiebaImpl->cut(line);
    }


    class WordSplit_Jieba::CppJiebaImpl{
        public:
            CppJiebaImpl():_jieba(dict_path,model_path,user_dict_path,idf_dict_path,stop_words_path){
            }
            vector<strng> cut(string &line){
                vector<string> res = _jieba.Cut(line);
                return res;
            }

        private:
            std::string dict_path = "../otherLib/cppjieba/dict/jieba.dict.utf8";
            std::string model_path = "../otherLib/cppjieba/dict/hmm_model.utf8";
            std::string user_dict_path = "../otherLib/cppjieba/dict/user.dict.utf8";
            std::string idf_dict_path = "../otherLib/cppjieba/dict/idf.utf8";
            std::string stop_words_path = "../otherLib/cppjieba/dict/stop_words.utf8";
            cppjieba::Jieba _jieba;
    }

2、对于string中存储的中文字符，需要额外处理，根据其字符宽度来确定遍历的间隔
    对于这一点，在后面进行中英文混合查询的时候也还要单独判断一次

