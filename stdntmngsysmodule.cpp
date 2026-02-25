#include"stdntmngsys.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<windows.h>
#include<string_view>
#include<algorithm>
#include<cctype>
#include<iomanip>

student::student(std::string_view name,std::string_view rollNumber,std::string_view marks)
    :name(name),rollNumber(rollNumber),marks(marks){}

studentManagementSystem::studentManagementSystem(std::string_view name,std::string_view rollNumber,std::string_view marks)
    :stdmngr(name,rollNumber,marks){}

student& student::setname(std::string_view name){
    this->name = name;
    return *this;
}

student& student::setrollnumber(std::string_view rollNumber){
    this->rollNumber=rollNumber;
    return *this;
}

student& student::setmarks(std::string_view marks){
    this->marks=marks;
    return *this;
}

int studentManagementSystem::mainMenu(){

    int choice{};

    const int boxWidth = 27; // total width inside the box

    std::string heading = "STUDENT DATABASE";

    // calculate left padding for centering
    int padding = (boxWidth - heading.length()) / 2;

    std::cout << "+===========================+\n";
    std::cout << "|"
         << std::setw(padding + heading.length()) << std::right << heading
         << std::setw(boxWidth - padding - heading.length()) << ""  // fill remaining space
         << "|\n";
    std::cout << "+===========================+\n";

    // menu options aligned left
    std::cout << "| " << std::left << std::setw(boxWidth) << "1 - Add Student" << "|\n";
    std::cout << "| " << std::left << std::setw(boxWidth) << "2 - View All Students" << "|\n";
    std::cout << "| " << std::left << std::setw(boxWidth) << "3 - Search Student" << "|\n";
    std::cout << "| " << std::left << std::setw(boxWidth) << "4 - Delete Student" << "|\n";
    std::cout << "| " << std::left << std::setw(boxWidth) << "5 - Update Student" << "|\n";
    std::cout << "| " << std::left << std::setw(boxWidth) << "6 - Exit" << "|\n";
    std::cout << "+===========================+\n";
    std::cin>>choice;

    return choice;
}

void studentManagementSystem::menuChoices(int& choice){
    studentManagementSystem sys1;

    switch (choice)
    {
    case 1:
    system("clear");
    sys1.addStudent();
    break;

    case 2:
    system("clear");
    sys1.viewStudent();
    break;

    case 3:
    system("clear");
    sys1.searchStudent();
    break;

    case 4:
    system("clear");
    sys1.deleteStudent();
    break;

    case 5:
    system("clear");
    sys1.updateStudent();
    break;
    
    case 6:
    system("clear");
    exit(0);
    break;

    default:
    system("clear");
    std::cout<<"ERROR! Invalid option"<<std::endl;
    break;
    }
}

int studentManagementSystem::addStudent(){

    std::string name{},rollNumber{},marks{};

    std::cout<<"Enter name: ";
    std::cin.ignore();
    std::getline(std::cin,name);
    setName(name);
    std::cout<<"Enter roll number: ";
    std::cin>>rollNumber;
    setRollnumber(rollNumber);
    std::cout<<"Enter marks: ";
    std::cin>>marks;
    setmarks(marks);
    std::cout<<"\n";

    std::fstream fileopen("Databasesystem.csv",std::ios::app);
    if(!fileopen){
        std::cout<<"ERROR!, unable to open file"<<std::endl;
        return 1;
    }

    fileopen<<name<<","<<rollNumber<<","<<marks<<std::endl;

    fileopen.close();

    return 0;
}

int studentManagementSystem::viewStudent(){
    
    std::string container{};

    std::ifstream fileopen("Databasesystem.csv");
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

int studentManagementSystem::searchStudent(){

    std::string search{};
    std::string temp;

    std::cout<<"Enter the roll number: ";
    std::cin>>search;

    std::ifstream fileopen("Databasesystem.csv");
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

int studentManagementSystem::deleteStudent(){

    int choice{};
    std::string search{};
    std::string tokenizer;

    std::cout<<"Do you want to search by name or roll number?\n1-Name\n2-Roll number"<<std::endl;
    std::cin>>choice;

    searchUpdatestudent(choice,search);

    std::ofstream tempfile("temp.csv");
    std::ifstream openfile("Databasesystem.csv");
    if(!tempfile || !openfile){
        std::cout<<"Error!, cannot open tempfile || openfile ||"<<std::endl;
        }

    while(std::getline(openfile,tokenizer)){
        if(tokenizer.find(search) == std::string::npos){
            tempfile<<tokenizer<<std::endl;
        }
    }
    
    openfile.close();
    tempfile.close();

    std::ofstream delfilecont("Databasesystem.csv");
    
    delfilecont.close();

    tokenizer={};

    std::ifstream tempfiletransfer("temp.csv");
    std::fstream mainfile("Databasesystem.csv");
    if(!tempfiletransfer || !mainfile){
        std::cout<<"Error! cannot openv tempfile || mainfile "<<std::endl;
    }

    while(std::getline(tempfiletransfer,tokenizer)){
        mainfile<<tokenizer<<std::endl;
        }

    std::cout<<"Line deleted!"<<std::endl;

    mainfile.close();
    tempfiletransfer.close();
    std::ofstream deltemp("temp.csv");
    deltemp.close();

    return 0;
}

int studentManagementSystem::updateStudent(){

    int choice{},choiceTwo{};
    std::string search{};
    std::string tokenizer{},tokenizerTwo{};
    std::string newinput{};
    bool firstLine=true;

    std::cout<<"Modify \n1-Name\n2-Roll number"<<std::endl;
    std::cin>>choiceTwo;
    if(modifyUpdatestudent(choiceTwo,newinput,search) != 0){
        std::cout<<"modify update student function error!"<<std::endl;
        return 1;
    }
    // g++ stdntmngsys.cpp stdntmngsysmodule.cpp -o stdntmngsys//
    std::ifstream openfile("Databasesystem.csv");
    if(!openfile){
        std::cout<<"Error!, cannot open tempfile || openfile ||"<<std::endl;
    }

    std::ofstream tempfile("temfile.csv");
    if(!tempfile){
        std::cout<<"ERROR! failed to open temporary file"<<std::endl;
        return 1;
    }
     std::string buf1{},buf2{},buf3{};

    while(std::getline(openfile,tokenizer)){
        std::stringstream stringtoken(tokenizer);

        std::getline(stringtoken,buf1,',');
        std::getline(stringtoken,buf2,',');
        std::getline(stringtoken,buf3);

            if(search == buf1){
                buf1 = newinput;
            }else if(search == buf2){
                buf2 = newinput;
            }else{
                int errchoice{};
                std::cout<<"ERROR!, unable to find token!"<<std::endl;
                std::cout<<"Try again?\n1-Yes\n2-Exit"<<std::endl;
                std::cin>>errchoice;
                if(errchoice == 1){
                    system("clear");
                    mainMenu();
                }else if(errchoice == 2){
                    exit(0);
                }else{
                    std::cout<<"ERROR"<<std::endl;
                    return 1;
                }
            }
            std::string reconstructed = buf1 + ',' + buf2 + ',' + buf3;
            tempfile<<reconstructed<<std::endl;
        }

    openfile.close();
    tempfile.close();

    std::ifstream test("temfile.csv");
        if(!test){
            std::cout << "Error: temp file was never created\n";
            return 1;
        }
    test.close();

    // Remove original database
        if(std::remove("Databasesystem.csv") != 0){
            std::cout << "Error deleting original file\n";
            return 1;
        }

    // Rename temp file to original
        if(std::rename("temfile.csv", "Databasesystem.csv") != 0){
            std::cout << "Error renaming temp file\n";
            return 1;
        }

    std::cout << "Modified successfully!" << std::endl;
    return 0;

}

int searchUpdatestudent(int choice,std::string& search){
    if(choice < 1 || choice > 2){
        std::cout<<"Error! undefined choice for update-student (switch 1)"<<std::endl;
        return 1;
        }

    switch(choice){
        case 1:
        std::cout<<"Enter name of student: "<<std::endl;
        std::cin.ignore();
        std::getline(std::cin,search);
        break;

        case 2:
        std::cout<<"Enter roll number: "<<std::endl;
        std::cin>>search;
        break;

        default:
        std::cout<<"Error! invalid switch choice, out-of-bounds"<<std::endl;
        return 1;
        }

        return 0;
}

int modifyUpdatestudent(int choice,std::string& singleinput,std::string& search){


     if(choice < 1 || choice > 3 ){
            std::cout<<"Modifying choice out-of-bounds!"<<std::endl;
            return 1;
        }

        switch(choice){
            case 1:
            std::cout<<"Enter name you want to modify: ";
            std::cin.ignore();
            std::getline(std::cin,search);
            std::cout<<"Enter new name: ";
            std::getline(std::cin,singleinput);
            break;

            case 2:
            std::cout<<"Enter roll number you want to modify :";
            std::cin>>search;
            std::cout<<"Enter new roll number: ";
            std::cin>>singleinput;
            break;

            default:
            std::cout<<"ERROR!, invalid modification-option"<<std::endl;
            return 1;
        }
        return 0;
}

