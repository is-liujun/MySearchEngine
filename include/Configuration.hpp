#ifndef __CONFIGURATION_HPP__
#define __CONFIGURATION_HPP__

#include <string>
#include <unordered_map>

namespace MySearchEngine
{
class Configuration
{
public:
    // 单例模式的初始化
    static Configuration *getInstance();
    // 单例模式的销毁
    static void destroy();

    std::unordered_map<std::string, std::string> &getConfig();

private:
    void loadFile();

private:
    Configuration();
    ~Configuration();

private:
    static Configuration *_pInstance;
    std::string _filename = "../conf/myconf.conf";
    std::unordered_map<std::string, std::string> _config;
};

} // namespace MySearchEngine

#endif
