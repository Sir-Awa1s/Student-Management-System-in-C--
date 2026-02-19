#include"stdntmngsys.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<windows.h>

int mainMenu(){

    int choice{};

    std::cout<<"-----Menu-----"<<std::endl;
    std::cout<<"1-Add Student"<<std::endl;
    std::cout<<"2-view all students"<<std::endl;
    std::cout<<"3-Search"<<std::endl;
    std::cout<<"Enter choice: "<<std::endl;
    std::cin>>choice;

    return choice;
}

void menuChoices(int& choice){
    switch (choice)
    {
    case 1:
    system("clear");
    addStudent();
    break;

    case 2:
    system("clear");
    viewStudent();
    break;

    case 3:
    system("clear");
    searchStudent();
    break;
    
    default:
    system("clear");
    std::cout<<"ERROR! Invalid option"<<std::endl;
    break;
    }
}

int addStudent(){

    std::string name{},rollNumber{},marks{};

    std::cout<<"Enter name: ";
    std::cin>>name;
    std::cout<<"Enter roll number: ";
    std::cin>>rollNumber;
    std::cout<<"Enter marks: ";
    std::cin>>marks;
    std::cout<<"\n";

    std::fstream fileopen("Databasesystem.txt",std::ios::app);
    if(!fileopen){
        std::cout<<"ERROR!, unable to open file"<<std::endl;
        return 1;
    }

    fileopen<<name<<" "<<rollNumber<<" "<<marks<<std::endl;

    fileopen.close();

    return 0;
}

int viewStudent(){
    
    std::string container{};

    std::ifstream fileopen("Databasesystem.txt");
    if(!fileopen){
        std::cout<<"ERROR!, Cannot open file"<<std::endl;
        return 1;
    }

    while(std::getline(fileopen,container)){
        std::cout<<container<<std::endl;
    }
    std::cout<<"\n";

    fileopen.close();

    return 0;
}

int searchStudent(){

    std::string search{};
    std::string temp;

    std::cout<<"Enter the roll number: ";
    std::cin>>search;

    std::ifstream fileopen("Databasesystem.txt");
    if(!fileopen){
        std::cout<<"ERROR!, cannot open file"<<std::endl;
        return 1;
    }
    
    while(std::getline(fileopen,temp)){
        if(temp.find(search) != std::string::npos){
            std::cout<<temp<<std::endl;
        }
    }
    std::cout<<"\n";

    fileopen.close();
    
    return 0;
}
