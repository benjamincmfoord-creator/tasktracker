#include "json_utils.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "task.h"  // still needed to use Task

std::vector<Task> readTasksFromFile(const std::string& filePath) {
    std::vector<Task> tasks;
    std::ifstream file(filePath);
    if (!file.is_open()) return tasks;

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    size_t pos = 0;
    while ((pos = content.find("{", pos)) != std::string::npos) {
        size_t endPos = content.find("}", pos);
        if (endPos == std::string::npos) break;

        std::string taskStr = content.substr(pos, endPos - pos + 1);
        try {
            tasks.push_back(Task::fromJson(taskStr));
        } catch (...) {
            std::cerr << "Skipping invalid task entry.\n";
        }
        pos = endPos + 1;
    }

    return tasks;
}

void writeTasksToFile(const std::string& filePath, const std::vector<Task>& tasks) {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << filePath << "\n";
        return;
    }

    file << "[\n";
    for (size_t i = 0; i < tasks.size(); ++i) {
        file << "  " << tasks[i].toJson();
        if (i != tasks.size() - 1) file << ",";
        file << "\n";
    }
    file << "]\n";
    file.close();
}
