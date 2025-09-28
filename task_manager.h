#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include "task.h"
#include <vector>

class TaskManager {
    public:
    TaskManager(const std::string& filepath);
    
    
    void addTask(const std::string& name, const std::string& desc);
    void updateTask(int id, const std::string& name, const std::string& desc);
    void deleteTask(int id);


    void markTask(int id, Progress progress);
    void listTasks(Progress filterProgress = Progress::NOT_STARTED, bool filer = false) const;

    void loadTasks();
    void saveTasks() const;

    private:
    std::string filePath;
    std::vector<Task> tasks;
    int nextId;

    int findTaskIndexById(int id) const;
};

#endif
