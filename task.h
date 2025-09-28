#ifndef TASK_H
#define TASK_H

#include<string>
//Struct for Task representation

//tasks have id, title, desc and progress
//progress enum not started, in progress or completed

enum Progress{
    NOT_STARTED,
    IN_PROGRESS,
    COMPLETED
};

struct Task{
    int id;
    std::string name;
    std::string desc;
    Progress progress;

    std::string toJson() const;

    static Task fromJson(const std::string& jsonStr);
    
};

std::string progressToString(Progress progress);

Progress progressToString(const std::string& statusStr);

#endif