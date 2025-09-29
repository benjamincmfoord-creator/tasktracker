#include "task.h"
#include <sstream>
#include <iostream>

// Convert Progress enum to string
std::string progressToString(Progress progress) {
    switch (progress) {
        case NOT_STARTED: return "NOT_STARTED";
        case IN_PROGRESS: return "IN_PROGRESS";
        case COMPLETED: return "COMPLETED";
        default: return "NOT_STARTED";
    }
}

// Convert string to Progress enum
Progress stringToProgress(const std::string& progressStr) {
    if (progressStr == "NOT_STARTED") return NOT_STARTED;
    if (progressStr == "IN_PROGRESS") return IN_PROGRESS;
    if (progressStr == "COMPLETED") return COMPLETED;
    return NOT_STARTED; // Default fallback
}

// Serialize Task to JSON-like string
std::string Task::toJson() const {
    std::ostringstream oss;
    oss << "{"
        << "\"id\":" << id << ","
        << "\"name\":\"" << name << "\","
        << "\"desc\":\"" << desc << "\","
        << "\"progress\":\"" << progressToString(progress) << "\""
        << "}";
    return oss.str();
}

// Parse Task from JSON-like string (very basic, not a full JSON parser)
Task Task::fromJson(const std::string& jsonStr) {
    Task task;

    size_t idPos = jsonStr.find("\"id\":");
    size_t namePos = jsonStr.find("\"name\":\"");
    size_t descPos = jsonStr.find("\"desc\":\"");
    size_t progressPos = jsonStr.find("\"progress\":\"");

    if (idPos == std::string::npos || namePos == std::string::npos ||
        descPos == std::string::npos || progressPos == std::string::npos) {
        throw std::runtime_error("Invalid JSON format for Task");
    }

    task.id = std::stoi(jsonStr.substr(idPos + 5, jsonStr.find(",", idPos) - idPos - 5));

    size_t nameStart = namePos + 8;
    task.name = jsonStr.substr(nameStart, jsonStr.find("\"", nameStart) - nameStart);

    size_t descStart = descPos + 8;
    task.desc = jsonStr.substr(descStart, jsonStr.find("\"", descStart) - descStart);

    size_t progressStart = progressPos + 11;
    task.progress = stringToProgress(jsonStr.substr(progressStart, jsonStr.find("\"", progressStart) - progressStart));

    return task;
}
