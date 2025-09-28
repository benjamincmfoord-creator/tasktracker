//Contains logic for add, update, delete, list, etc.
#include "task_manager.h"
#include "json_utils.h"
#include <iostream>

TaskManager::TaskManager(const std::string& filePath) : filePath(filePath), nextId(1) {}

void TaskManager::loadTasks(){
    tasks = readTasksFromFile(filePath);

    nextId = 1;
    for(const auto& task : tasks){
        if(task.id >= nextId){
            nextId = task.id + 1;
        }
    }

}

void TaskManager::saveTasks() const{
    writeTasksToFile(filePath, tasks);
}

void TaskManager::addTask(const std::string& name, const std::string& desc){
    Task task;
    task.id = nextId++;
    task.name = name;
    task.desc = desc;
    task.progress = Progress::NOT_STARTED;
    tasks.push_back(task);
    std::cout << "Task added with ID:" << task.id << "/n";
}

void TaskManager::updateTask(int id, const std::string& name, const std::string& desc){
    int idx = findTaskIndexById(id);
    if (idx == -1){
        std::cerr << "TASK ID NOT FOUND. \n";
        return;
    }
    tasks[idx].name = name;
    tasks[idx].desc = desc;
    std::cout << "Task Updated.\n";
}

void TaskManager::deleteTask(int id){
    int idx = findTaskIndexById(id);
    if (idx == -1){
        std::cerr << "TASK ID NOT FOUND. \n";
        return;
    }
    tasks.erase(tasks.begin() + idx);
    std::cout << "Tasks deleted.\n";
}

void TaskManager::markTask(int id, Progress progress){
    int idx = findTaskIndexById(id);
    if (idx == -1){
        std::cerr << "TASK ID NOT FOUND. \n";
        return;
    }
    tasks[idx].progress = progress;
    std::cout << tasks[idx].name << " Progress updated to " << tasks[idx].progress << "\n";
}

void TaskManager::listTasks(Progress filterProgress, bool filter) const{
    if(tasks.empty()) {
        std::cout << "NO TASKS";
        return;
    }

    for (const auto& task: tasks){
        if(!filter || task.progress == filterProgress){
            std::cout << "ID: " << task.id << "\n";
            std::cout << "Title: " << task.name << "\n";
            std::cout << "Description: " << task.desc << "\n";
            std::cout << "Status: " << statusToString(task.progress) << "\n";
            std::cout << "-----------------------\n";
        }
    }

}


int TaskManager::findTaskIndexById(int id) const{
    for(size_t i = 0; i < tasks.size(); ++i){
        if(tasks[i].id == id) return static_cast<int>(i);
    }
    return -1;

}
