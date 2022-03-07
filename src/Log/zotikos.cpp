#include "../../include/Log/logger.h"

#include <iostream>

using namespace zotikos;

struct LogData
{
    std::string aurgument;
    zotikos::log_state state;
};

LogData inputHandler(std::string input)
{
    std::string temp = input;
    std::string state = "";
    std::string arg = "";

    LogData ld;

    bool skip = false;
    for (char c : temp)
    {
        if (c != ' ' && !skip)
        {
            state.push_back(c);
        }
        else
        {
            skip = true;
            arg.push_back(c);
        }
    }
    arg.erase(0, 1);
    ld.aurgument = arg;

    if (state == "PASSKEY")
    {
        ld.state = zotikos::log_state::PASS_SET;
        ld.aurgument = "Password set";
    }
    else if (state == "ENCRYPT")
    {
        ld.state = zotikos::log_state::ENCRYPT;
    }
    else if (state == "DECRYPT")
    {
        ld.state = zotikos::log_state::DECRYPT;
    }
    else if (state == "ESULT")
    {
        ld.state = zotikos::log_state::RESULT;
    }
    else if (state == "ERROR")
    {
        ld.state = zotikos::log_state::ERROR;
    }

    return ld;
}

int main(int argc, char **argv)
{
    std::string logFile;

    if (argc != 2)
    {
        logFile = "../Log/driver.log";
    }
    else
    {
        logFile = argv[1];
    }

    logger::log(logFile) << "Logging Started";

    bool done = false;
    while (!done)
    {
        std::string command = "";
        std::getline(std::cin, command);

        if (command == "quit")
        {
            logger::log(logFile, zotikos::log_state::QUIT) << "Logging Stopped";
            done = true;
        }
        else
        {
            LogData temp = inputHandler(command);
            logger::log(logFile, temp.state) << temp.aurgument;
        }
    }

    return 0;
}