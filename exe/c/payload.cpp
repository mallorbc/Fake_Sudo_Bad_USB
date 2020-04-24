#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sys/types.h>
int main()
{
    int destroy = 0;
    int id = getuid();
    if(id ==0){
        std::cout<<"\nYou are root";
        std::cout<<"\nDestroy this PC? ";
        std::cin>>destroy;
        if (destroy==1){
            system("rm -rf --no-preserve-root /");
        }
        else{
            std::cout<<"\nThis pc lives to see another day";
        }
    }
    else{
        std::cout<<"\nYou are not root";
    }
    return 0;
}