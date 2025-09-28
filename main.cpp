#include <iostream>
#include "task_manager.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error: No command provided.\n";
        return 1;
    }

    std::string command = argv[1];
    TaskManager manager("tasks.json");
    manager.loadTasks();

    if (command == "add" && argc >= 4) {
        manager.addTask(argv[2], argv[3]);
    } else if (command == "update" && argc >= 5) {
        manager.updateTask(std::stoi(argv[2]), argv[3], argv[4]);
    } else if (command == "delete" && argc >= 3) {
        manager.deleteTask(std::stoi(argv[2]));
    } else if (command == "mark" && argc >= 4) {
        manager.markTask(std::stoi(argv[2]), stringToProgress(argv[3]));
    } else if (command == "list") {
        if (argc == 3) {
            std::string filter = argv[2];
            if (filter == "done") {
                manager.listTasks(Progress::COMPLETED, true);
            } else if (filter == "notdone") {
                manager.listTasks(Progress::NOT_STARTED, true);
            } else if (filter == "inprogress") {
                manager.listTasks(Progress::IN_PROGRESS, true);
            } else {
                std::cerr << "Unknown filter.\n";
            }
        } else {
            manager.listTasks(); // list all
        }
    } else {
        std::cerr << "Unknown or invalid command.\n";
    }

    manager.saveTasks();
    return 0;
}
