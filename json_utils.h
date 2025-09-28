#ifndef JSON_UTILS_H
#define JSON_UTILS_H

#include <string>
#include <vector>
#include "task.h"

std::vector<Task> readTasksFromFile(const std::string& filePath);
void writeTasksToFile(const std::string& filePath, const std::vector<Task> tasks);

#endif