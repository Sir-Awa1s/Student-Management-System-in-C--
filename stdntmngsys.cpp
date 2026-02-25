#include<iostream>
#include"stdntmngsys.h"
#include<windows.h>

int main(){

    studentManagementSystem mainsys;

    int programchoice{}; 

    do{
    int choice = mainsys.mainMenu();
    std::cout<<choice<<std::endl;

    mainsys.menuChoices(choice);

    std::cout<<"1-Continue"<<std::endl;
    std::cout<<"2-Exit"<<std::endl;
    std::cin>>programchoice;
    system("clear");

    }while(programchoice != 2);

    return 0;
}

