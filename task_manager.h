#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include "task.h"
#include <vector>

// Declarations for the task manager class/functions

//needed functions


//add update delete

//change progress

//list tasks that are done, not done, in progress all tasks


class TaskManager {
    public:
    TaskManager(const std::string& filepath);
    
    
    void addTask(const std::string& title, const std::string desc);
    void updateTask(int id, const std::string& title, const std::string desc);
    void deleteTask(int id);


    void markTask(int id, Progress progress);
    void listTasks(Progress filterProgress = Progress::NOT_STARTED, bool filer = false) const;

    void loadTasks();
    void saveTasks();

    private:
    std::string filePath;
    std::vector<Task> tasks;
    int nextId;

    int findTaskIndexById(int id) const;
};

#endif
