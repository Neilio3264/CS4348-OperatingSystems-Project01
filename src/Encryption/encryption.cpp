#include "../../include/Encryption/encryption.h"

#include <iostream>

namespace krypto
{
    encryption::encryption()
    {
    }

    encryption::~encryption()
    {
    }

    void encryption::inputHandler(std::string input)
    {
        std::string temp = input;
        std::string state = "";
        std::string arg = "";
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
        _argument = arg;

        if (state == "PASSKEY")
        {
            _current_state = encryption_states::PASSKEY;
        }
        else if (state == "ENCRYPT")
        {
            _current_state = encryption_states::ENCRYPT;
        }
        else if (state == "DECRYPT")
        {
            _current_state = encryption_states::DECRYPT;
        }
        else if (state == "RESULT")
        {
            _current_state = encryption_states::RESULT;
        }
        else if (state == "ERROR")
        {
            _current_state = encryption_states::ERROR;
        }
        else if (state == "QUIT")
        {
            _current_state = encryption_states::QUIT;
        }
    }

    bool passCheck(std::string arg)
    {
        std::string temp = arg;
        for (char c : temp)
        {
            if (c == ' ')
            {
                return false;
            }
        }

        return true;
    }

    void encryption::passkey(std::string arg)
    {
        if (_current_state != encryption_states::PASSKEY)
            return;

        std::string temp = arg;

        if (passCheck(temp))
        {
            _password = temp;
            _current_state = encryption_states::RESULT;
            result("Password set");
            _current_state = encryption_states::IDLE;
        }
        else
        {
            _current_state = encryption_states::ERROR;
            error("Password input contains a space");
            _current_state = encryption_states::IDLE;
        }

        return;
    }

    std::string extend_key(std::string arg, std::string key)
    {
        std::string temp = arg;
        std::string extendKey = key;
        if (extendKey.size() >= temp.size())
            return extendKey;
        else
        {
            int psize = temp.size() - extendKey.size();
            int ksize = extendKey.size();
            while (psize >= ksize)
            {
                extendKey += extendKey;
                psize -= ksize;
            }

            extendKey += extendKey.substr(0, psize);
            return extendKey;
        }
    }

    void encryption::encrypt(std::string arg)
    {
        if (_current_state != encryption_states::ENCRYPT)
            return;

        std::string key = extend_key(arg, _encryption_key);

        if (!_password.empty())
        {
            std::string decrypted = "";
            for (int i = 0; i < arg.size(); i++)
                decrypted += (char)((((int)arg[i] - 'A' - (key[i] - 'A')) + 26) % 26) + 'A';

            _current_state = encryption_states::RESULT;
            result(decrypted);
            _current_state = encryption_states::IDLE;
        }
        else
        {
            _current_state = encryption_states::ERROR;
            error("Password not set");
            _current_state = encryption_states::IDLE;
        }

        return;
    }

    void encryption::decrypt(std::string arg)
    {
        if (_current_state != encryption_states::DECRYPT)
            return;

        std::string key = extend_key(arg, _encryption_key);

        if (!_password.empty())
        {
            std::string encrypted = "";
            for (int i = 0; i < arg.size(); i++)
                encrypted += (char)(((int)arg[i] - 'A' + (int)key[i] - 'A') % 26) + 'A';

            _current_state = encryption_states::RESULT;
            result(encrypted);
            _current_state = encryption_states::IDLE;
        }
        else
        {
            _current_state = encryption_states::ERROR;
            error("Password not set");
            _current_state = encryption_states::IDLE;
        }

        return;
    }

    void encryption::result(std::string arg)
    {
        if (_current_state != encryption_states::RESULT)
            return;

        std::string output = "RESULT " + arg;
        std::cout << output << std::endl;
        return;
    }

    void encryption::error(std::string arg)
    {
        if (_current_state != encryption_states::ERROR)
            return;

        std::string output = "ERROR " + arg;
        std::cout << output << std::endl;
        return;
    }
}