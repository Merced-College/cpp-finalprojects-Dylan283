
// === File: Task.h ===
#ifndef TASK_H
#define TASK_H

#include <string>

class Task {
public:
    std::string name;
    std::string dueDate; // Format: YYYY-MM-DD
    int priority; // 1 = High, 2 = Medium, 3 = Low
    bool completed;

    Task(std::string n, std::string d, int p);
    void markComplete();
};

#endif

// === File: Task.cpp ===
//#include "Task.h"

Task::Task(std::string n, std::string d, int p)
    : name(n), dueDate(d), priority(p), completed(false) {}

void Task::markComplete() {
    completed = true;
}

// === File: TaskManager.h ===
#ifndef TASKMANAGER_H
#define TASKMANAGER_H

//#include "Task.h"
#include <vector>
#include <map>
#include <queue>

class TaskManager {
private:
    std::map<std::string, std::vector<Task>> tasksByDate;
    std::priority_queue<Task*> priorityTasks;

public:
    void addTask(Task t);
    void listTasks();
    void sortTasksByPriority();
    void generateWeeklySchedule();
    void markTaskComplete(const std::string& name);
};

#endif

// === File: TaskManager.cpp ===
//#include "TaskManager.h"
#include <iostream>
#include <algorithm>

void TaskManager::addTask(Task t) {
    tasksByDate[t.dueDate].push_back(t);
    priorityTasks.push(&tasksByDate[t.dueDate].back());
}

void TaskManager::listTasks() {
    for (const auto& [date, tasks] : tasksByDate) {
        std::cout << "Due: " << date << "\n";
        for (const auto& task : tasks) {
            std::cout << "  - " << task.name << (task.completed ? " [Done]" : "") << "\n";
        }
    }
}

void TaskManager::sortTasksByPriority() {
    for (auto& [_, taskList] : tasksByDate) {
        std::sort(taskList.begin(), taskList.end(), [](Task& a, Task& b) {
            return a.priority < b.priority;
        });
    }
}

void TaskManager::generateWeeklySchedule() {
    std::cout << "Weekly Schedule:\n";
    for (const auto& [date, taskList] : tasksByDate) {
        std::cout << date << ":\n";
        for (const Task& task : taskList) {
            std::cout << "  * " << task.name << " (Priority: " << task.priority << ")\n";
        }
    }
}

void TaskManager::markTaskComplete(const std::string& name) {
    for (auto& [_, taskList] : tasksByDate) {
        for (auto& task : taskList) {
            if (task.name == name) {
                task.markComplete();
                return;
            }
        }
    }
}

// === File: main.cpp ===
//#include "TaskManager.h"
#include <iostream>

void showMenu() {
    std::cout << "\nStudy Planner App\n";
    std::cout << "1. Add Task\n";
    std::cout << "2. List Tasks\n";
    std::cout << "3. Sort Tasks by Priority\n";
    std::cout << "4. Generate Weekly Schedule\n";
    std::cout << "5. Mark Task Complete\n";
    std::cout << "6. Exit\n";
}

int main() {
    TaskManager manager;
    int choice;

    do {
        showMenu();
        std::cout << "Enter choice: ";
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1) {
            std::string name, due;
            int priority;
            std::cout << "Task Name: ";
            std::getline(std::cin, name);
            std::cout << "Due Date (YYYY-MM-DD): ";
            std::getline(std::cin, due);
            std::cout << "Priority (1=High, 2=Medium, 3=Low): ";
            std::cin >> priority;
            manager.addTask(Task(name, due, priority));
        } else if (choice == 2) {
            manager.listTasks();
        } else if (choice == 3) {
            manager.sortTasksByPriority();
        } else if (choice == 4) {
            manager.generateWeeklySchedule();
        } else if (choice == 5) {
            std::string name;
            std::cout << "Enter task name to mark complete: ";
            std::getline(std::cin >> std::ws, name);
            manager.markTaskComplete(name);
        }
    } while (choice != 6);

    return 0;
}

/*
 * Code written by Dylan Hamilton, May 2025.
 * Cited lines: All logic in TaskManager.cpp, sorting algorithm, priority queue, and weekly schedule generator.
 * These algorithms were designed manually and follow class standards.
 */
