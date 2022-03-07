#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

bool passSet = false;
bool error = false;

string commandMap(string input, vector<string> &history)
{
    error = false;
    string select = "";
    if (input == "password")
    {
        int temp;
        cout << "Enter 0 for new string or 1 to select from history" << endl;
        cout << ">> ";
        cin >> temp;

        if (temp == 1)
        {
            cout << "Select from history:" << endl;
            int index = 0;
            for (string str : history)
            {
                cout << "   (" << index << ") " << str << endl;
                index++;
            }

            int selection = 0;
            cin >> selection;

            select = "PASSKEY " + history.at(selection);
            passSet = true;
        }
        else if (temp == 0)
        {
            string newPass;
            cout << "Enter new passcode:" << endl;
            cout << ">> ";
            cin >> newPass;
            history.push_back(newPass);

            select = "PASSKEY " + newPass;
            passSet = true;
        }
        else
        {
            cout << "INVALID INPUT" << endl;
            cout << endl;
        }
    }
    else if (input == "encrypt")
    {
        if (!passSet)
        {
            error = true;
        }
        int temp;
        cout << "Enter 0 for new string or 1 to select from history" << endl;
        cout << ">> ";
        cin >> temp;
        cout << endl;

        if (temp == 1)
        {
            cout << "Select from history:" << endl;
            int index = 0;
            for (string str : history)
            {
                cout << "   (" << index << ") " << str << endl;
                index++;
            }

            int selection = 0;
            cin >> selection;

            select = "ENCRYPT " + history.at(selection);
        }
        else if (temp == 0)
        {
            string newPass;
            cout << "Enter new encrypt string:" << endl;
            cout << ">> ";
            cin >> newPass;
            history.push_back(newPass);

            select = "ENCRYPT " + newPass;
        }
        else
        {
            cout << "INVALID INPUT" << endl;
            cout << endl;
        }
    }
    else if (input == "decrypt")
    {
        if (!passSet)
        {
            error = true;
        }
        int temp;
        cout << "Enter 0 for new string or 1 to select from history" << endl;
        cout << ">> ";
        cin >> temp;
        cout << endl;

        if (temp == 1)
        {
            cout << "Select from history:" << endl;
            int index = 0;
            for (string str : history)
            {
                cout << "   (" << index << ") " << str << endl;
                index++;
            }

            int selection = 0;
            cin >> selection;

            select = "DECRYPT " + history.at(selection);
        }
        else if (temp == 0)
        {
            string newPass;
            cout << "Enter new decrypt string:" << endl;
            cout << ">> ";
            cin >> newPass;
            history.push_back(newPass);

            select = "DECRYPT " + newPass;
        }
        else
        {
            cout << "INVALID INPUT" << endl;
            cout << endl;
        }
    }
    else if (input == "history")
    {
        int index = 0;
        for (string str : history)
        {
            cout << " --- " << str << endl;
            index++;
        }
    }
    else if (input == "quit")
    {
        select = "quit";
    }

    return select;
}

string inputHandler(std::string input)
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

    return arg;
}

int main(int argc, char **argv)
{
    string logFile = "";

    if (argc != 2)
    {
        cout << "ERROR: not the correct cmd arguments: ./[exe] [log filename]" << endl;
        return -1;
    }
    else
    {
        logFile = argv[1];
    }

    // To store pipe identifiers
    // p1[0] - read from pipe
    // p1[1] - write to pipe
    int p2[2], p4[2], p5[2];
    pid_t log_pid, encrypt_pid; // To store the process id

    if (pipe(p2) == -1)
    {
        cerr << "Unable to create first pipe" << endl;
        exit(-1);
    }

    if (pipe(p4) == -1)
    {
        cerr << "Unable to create third pipe" << endl;
        exit(-1);
    }

    if (pipe(p5) == -1)
    {
        cerr << "Unable to create forth pipe" << endl;
        exit(-1);
    }

    (log_pid = fork()) && (encrypt_pid = fork());

    if (log_pid == -1)
    {
        cerr << "Error forking" << endl;
        exit(-1);
    }
    else if (encrypt_pid == -1)
    {
        cerr << "Error forking" << endl;
        exit(-1);
    }

    if (log_pid == 0)
    {
        close(p2[1]); // p1 is for reading
        close(p4[0]);
        close(p4[1]);
        close(p5[0]);
        close(p5[1]);
        dup2(p2[0], 0); // map pipe to stdin

        char *cstr = new char[logFile.length() + 1];
        strcpy(cstr, logFile.c_str());

        char *args[] = {strdup("./zotikos"), cstr, NULL};
        execvp(args[0], args);

        delete[] cstr;
    }
    else if (encrypt_pid == 0)
    {
        close(p2[0]);
        close(p2[1]);
        close(p4[1]);   // p1 is for reading
        close(p5[0]);   // p2 is for writing
        dup2(p4[0], 0); // map pipe to stdin
        dup2(p5[1], 1);

        char *args[] = {strdup("./krypto"), NULL};
        execvp(args[0], args);
    }
    else
    {
        close(p2[0]);
        close(p4[0]);
        close(p5[1]);

        bool done = false;
        vector<string> historyInput;

        while (!done)
        {
            string input = "";
            cout << "Enter a command (type [menu] for help)" << endl;
            cout << ">> ";
            this_thread::sleep_for(chrono::nanoseconds(30));
            getline(cin, input);
            historyInput.push_back(input);
            cout << endl;

            if (input == "menu")
            {
                cout << "COMMANDS: " << endl;
                cout << "   password" << endl;
                cout << "   encrypt" << endl;
                cout << "   decrypt" << endl;
                cout << "   history" << endl;
                cout << "   quit" << endl;
            }
            else
            {
                string command = commandMap(input, historyInput);
                if (!command.empty())
                {
                    if (error)
                    {
                        string er = "ERROR Password not set\n";
                        cout << er << endl;
                        write(p2[1], er.c_str(), er.size());
                        continue;
                    }

                    if (command == "quit")
                    {
                        done = true;

                        command += "\n";

                        write(p2[1], command.c_str(), command.size());
                        write(p4[1], command.c_str(), command.size());
                        this_thread::sleep_for(chrono::nanoseconds(30));
                        close(p2[1]);
                        close(p4[1]);
                        close(p5[0]);
                    }
                    else
                    {
                        command += "\n";

                        write(p4[1], command.c_str(), command.size());
                        write(p2[1], command.c_str(), command.size());
                        this_thread::sleep_for(chrono::nanoseconds(30));

                        string result = "";
                        read(p5[0], (char *)&result, 1024);

                        string s = "";
                        for (char c : result)
                        {
                            if (c == '\n')
                            {
                                break;
                            }
                            else
                            {
                                s += c;
                            }
                        }

                        cout << s << endl;

                        historyInput.push_back(inputHandler(s));
                        s += "\n";

                        write(p2[1], s.c_str(), s.size());
                        this_thread::sleep_for(chrono::nanoseconds(60));
                    }
                }
            }
            cout << endl;
        }
    }

    wait(NULL);
    return 0;
}