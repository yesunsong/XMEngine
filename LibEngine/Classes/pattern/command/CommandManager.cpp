#include "CommandManager.h"
#include <iostream>

CommandManager* CommandManager::manager = nullptr;

CommandManager::CommandManager() {
    manager = this;
}

CommandManager::~CommandManager() {
    manager = nullptr;
}

CommandManager* CommandManager::getInstance() {
    return manager;
}

void CommandManager::add(std::string key, Command* command) {
    if (m_commands.find(key) != m_commands.end()) {
        std::cout << "add duplicated command~~~(key=" << key <<")" << std::endl;
        return;
    }
    m_commands.insert(std::pair<std::string, Command*>(key, command));
}

void CommandManager::remove(std::string key) {
    m_commands.erase(key);
}

Command* CommandManager::get(std::string key) {
    return m_commands.at(key);
}

void CommandManager::execute(std::string key) {
    Command* command = get(key);
    if (command) {
        command->execute();
    }
}

void CommandManager::release() {
    m_commands.clear();
}
