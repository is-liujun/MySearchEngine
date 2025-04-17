#include "../include/WordSplit_Jieba.hpp"

#include <string>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using namespace MySearchEngine;

int main(){
   string s1 = "你是个好人 we all from a world, 我不想玩了";

   WordSplit_Jieba tool;
   vector<string> words=tool.cut(s1);
   for(auto &word : words){
    cout << word << " ";
   }
   cout << endl;
}
