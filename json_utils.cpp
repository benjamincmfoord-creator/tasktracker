//Functions to read/write JSON to file manually
#include "json_utils.h"
#include <fstream>
#include <sstream>
#include <iostream>


std::string progressToString(Progress progress) {
    switch (progress) {
        case Progress::NOT_STARTED: return "TODO";
        case Progress::IN_PROGRESS: return "IN_PROGRESS";
        case Progress::COMPLETED: return "DONE";
        default: return "TODO";
    }
}


Progress stringToProgress(const std::string& progressStr) {
    if (progressStr == "NOT_STARTED") return Progress::NOT_STARTED;
    if (progressStr == "IN_PROGRESS") return Progress::IN_PROGRESS;
    if (progressStr == "COMPLETED") return Progress::COMPLETED;
    return Progress::NOT_STARTED;
}

std::string Task::toJson() const {
    std::ostringstream oss;
    oss << "{"
        << "\"id\":" << id << ","
        << "\"name\":\"" << name << "\","
        << "\"description\":\"" << desc << "\","
        << "\"status\":\"" << progressToString(progress) << "\""
        << "}";
    return oss.str();
}


Task Task::fromJson(const std::string& jsonStr) {
    Task task;
    size_t idPos = jsonStr.find("\"id\":");
    size_t namePos = jsonStr.find("\"name\":\"");
    size_t descPos = jsonStr.find("\"description\":\"");
    size_t progressPos = jsonStr.find("\"progress\":\"");

    if (idPos == std::string::npos || namePos == std::string::npos || descPos == std::string::npos || progressPos == std::string::npos) {
        throw std::runtime_error("Invalid JSON format");
    }

    task.id = std::stoi(jsonStr.substr(idPos + 5, jsonStr.find(",", idPos) - idPos - 5));

    size_t nameStart = namePos + 9;
    task.name = jsonStr.substr(nameStart, jsonStr.find("\"", nameStart) - nameStart);

    size_t descStart = descPos + 15;
    task.desc = jsonStr.substr(descStart, jsonStr.find("\"", descStart) - descStart);

    size_t progressStart = progressPos + 10;
    task.progress = stringToProgress(jsonStr.substr(progressStart, jsonStr.find("\"", progressStart) - progressStart));

    return task;
}

std::vector<Task> readTasksFromFile(const std::string& filePath) {
    std::vector<Task> tasks;
    std::ifstream file(filePath);
    if (!file.is_open()) return tasks;

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    // Basic parsing: assume file contains an array of task objects
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

