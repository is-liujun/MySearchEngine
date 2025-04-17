#include "../include/MyLogger.hpp"

using namespace MyLog;

int main()
{
    MyLogger::getInstance()->error("this is an error msg");
    MyLogger::getInstance()->warn("this is a warn msg");
    MyLogger::getInstance()->info("this is an info msg");
    MyLogger::getInstance()->debug("this is a debug msg");

    LogError("an error message");
    LogWarn("a warn msg");
    LogInfo("an info msg");
    LogDebug("a debug msg");

}
