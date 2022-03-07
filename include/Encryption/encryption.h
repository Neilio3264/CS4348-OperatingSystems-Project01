#ifndef KRYPTO_ENCRYPTION_H
#define KRYPTO_ENCRYPTION_H

#include "./encryption_states.h"

#include <string>
#include <iostream>

namespace krypto
{
    class encryption
    {
        encryption_states _current_state = encryption_states::IDLE;
        std::string _argument = "";
        bool first = true;

        std::string _password = "";
        const std::string _encryption_key = "NEIL";

        void passkey(std::string arg);
        void encrypt(std::string arg);
        void decrypt(std::string arg);

        void result(std::string arg);
        void error(std::string arg);

        void inputHandler(std::string input);

        encryption();
        ~encryption();

    public:
        encryption(encryption const &) = delete;
        void operator=(encryption const &) = delete;

        static void runCommand(std::string input)
        {
            static encryption _instance;
            _instance.inputHandler(input);

            switch (_instance._current_state)
            {
            case encryption_states::PASSKEY:
                _instance.passkey(_instance._argument);
                _instance.first = false;
                break;

            case encryption_states::ENCRYPT:
                _instance.encrypt(_instance._argument);
                break;

            case encryption_states::DECRYPT:
                _instance.decrypt(_instance._argument);
                break;

            case encryption_states::RESULT:
                _instance.result(_instance._argument);
                _instance._current_state = encryption_states::IDLE;
                break;

            case encryption_states::ERROR:
                _instance.error(_instance._argument);
                _instance._current_state = encryption_states::IDLE;
                break;

            default:
                break;
            }
        }
    };
}

#endif