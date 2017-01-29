#ifndef _COMMAND_MANAGER_H_
#define _COMMAND_MANAGER_H_

#include <string>
#include <vector>
#include <map>
#include "Command.h"

/*
命令管理类
*/
class CommandManager {
public:
    static CommandManager* getInstance();

    void add(std::string key,Command* command);
    void remove(std::string key);
    Command* get(std::string key);
    void execute(std::string key);
    void release();

private:
    static CommandManager* manager;
    std::map<std::string, Command*> m_commands;

private:
    CommandManager();
    virtual ~CommandManager();

};
#endif //_COMMAND_MANAGER_H_
