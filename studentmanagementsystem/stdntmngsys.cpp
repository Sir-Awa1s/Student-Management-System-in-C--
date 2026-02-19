#include<iostream>
#include"stdntmngsys.h"
#include<windows.h>

int main(){

    int programchoice{}; 

    do{
    int choice = mainMenu();
    std::cout<<choice<<std::endl;

    menuChoices(choice);

    std::cout<<"1-Continue"<<std::endl;
    std::cout<<"2-Exit"<<std::endl;
    std::cin>>programchoice;
    system("clear");

    }while(programchoice != 2);

    return 0;
}

