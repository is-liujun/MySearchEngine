#include "../include/MyLogger.hpp"

using std::endl;
using std::cout;
using std::string;

namespace MyLog
{

MyLogger::MyLogger()
:_root(log4cpp::Category::getRoot())
{
    using namespace log4cpp;

    PatternLayout *p1 = new PatternLayout();
    p1->setConversionPattern("%d: [%p] %m%n"); // 日志格式：%c: %d: [%p] %m%n ———— 类别: 时间: [优先级] 消息

    PatternLayout *p2 = new PatternLayout();
    p2->setConversionPattern("%d: [%p] %m%n");

    OstreamAppender *poa = new OstreamAppender("console", &std::cout);
    poa->setLayout(p1);

    RollingFileAppender *prfa = new RollingFileAppender("RollingFileAppender", "../log/mylog.log",1024*1024*10, 10);
    prfa->setLayout(p2);

    _root.addAppender(poa);
    _root.addAppender(prfa);

    _root.setPriority(Priority::DEBUG);
}

MyLogger::~MyLogger(){
    _root.shutdown();
}

void MyLogger::error(const char *msg){
     _root.error(msg);
}

void MyLogger::warn(const char *msg){
    _root.warn(msg);
}

void MyLogger::info(const char *msg){
    _root.info(msg);
}

void MyLogger::debug(const char *msg){
    _root.debug(msg);
}

MyLogger* MyLogger::getInstance(){
    if(_mylogger == nullptr){
        _mylogger = new MyLogger();
        atexit(destroy);
    }
    return _mylogger;
}

void MyLogger::destroy(){
    if(_mylogger != nullptr){
        delete _mylogger;
        _mylogger = nullptr;
    }
}

MyLogger* MyLogger::_mylogger = MyLogger::getInstance();

}

