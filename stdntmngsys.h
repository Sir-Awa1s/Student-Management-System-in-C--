#ifndef STDNTMNGSYS_H
#define STDNTMNGSYS_H

#include<string_view>
#include<string>

class student{
private:
    std::string name{},rollNumber{},marks{};

public:
    student() = default;
    student(std::string_view name,std::string_view rollNumber,std::string_view marks);

    const std::string& getname()const{
        return name;
    }

    const std::string& getrollnumber()const{
        return rollNumber;
    }

    const std::string& getmarks()const{
        return marks;
    }

    student& setname(std::string_view name);
    student& setrollnumber(std::string_view rollNumber);
    student& setmarks(std::string_view marks);
};

class studentManagementSystem{
    private:
    student stdmngr;

    public:
    studentManagementSystem() = default;
    studentManagementSystem(std::string_view name,std::string_view rollNumber,std::string_view marks);

    studentManagementSystem& setName(std::string_view name){
        stdmngr.setname(name);
        return *this;
    }

    studentManagementSystem& setRollnumber(std::string_view rollnumber){
        stdmngr.setrollnumber(rollnumber);
        return *this;
    }

    studentManagementSystem& setmarks(std::string_view marks){
        stdmngr.setmarks(marks);
        return *this;
    }

    int mainMenu();
    void menuChoices(int& choice);
    int addStudent();
    int viewStudent();
    int searchStudent();
    int deleteStudent();
    int updateStudent();
};

int searchUpdatestudent(int choice,std::string& search);

int modifyUpdatestudent(int choice,std::string& singleinput,std::string& search);

static inline void trim(std::string &s);

#endif