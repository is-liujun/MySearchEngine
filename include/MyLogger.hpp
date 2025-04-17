#include <iostream>
#include <string>

#include <log4cpp/PatternLayout.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>

namespace MyLog
{
 class MyLogger
    {
        // 由于log4cpp的warn、error等函数只能接受一个参数，
        // 这样的话还需要借助第三方库将多个参数转换成一个参数再传给log4cpp的成员函数，很麻烦，就不做了
        // template<typename ...Args>
        // void error(const char *msg, Args ...args);
        //
        // template<typename ...Args>
        // void warn(const char *msg, Args ...args);
        //
        // template<typename ...Args>
        // void info(const char *msg, Args ...args);
        //
        // template<typename ...Args>
        // void debug(const char *msg, Args ...args);

        public:
        static MyLogger *getInstance();
        static void destroy();

        void warn(const char *msg); //MyLog.cc中实现了这4个函数，上面的四个好像没有用到；；；；
        void error(const char *msg);
        void debug(const char *msg);
        void info(const char *msg);



        private:
            MyLogger();
            ~MyLogger();

        private:
            static MyLogger* _mylogger;
            log4cpp::Category& _root;
    };

    //日志信息的宏定义
    #define INFO(msg) std::string("[") \
        .append(__FILE__).append(": ")  \
        .append(__FUNCTION__).append(": ")  \
        .append(std::to_string(__LINE__))    \
        .append("]")    \
        .append(msg).c_str()

    #define LogInfo(msg) MyLogger::getInstance()->info(INFO(msg));
    #define LogWarn(msg) MyLogger::getInstance()->warn(INFO(msg));
    #define LogDebug(msg) MyLogger::getInstance()->debug(INFO(msg));
    #define LogError(msg) MyLogger::getInstance()->error(INFO(msg));
}
