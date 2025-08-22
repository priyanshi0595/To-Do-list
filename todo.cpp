#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Task {
    string title;
    bool completed;

    string toString() const {
        return (completed ? "[X] " : "[ ] ") + title;
    }
};

// Global task list
vector<Task> tasks;

// Function to load tasks from file
void loadTasks() {
    ifstream file("todo.txt");
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        if (line.length() < 4) continue;
        Task task;
        task.completed = (line[1] == 'X');
        task.title = line.substr(4);
        tasks.push_back(task);
    }
    file.close();
}

// Function to save tasks to file
void saveTasks() {
    ofstream file("todo.txt");
    for (const auto& task : tasks) {
        file << (task.completed ? "[X] " : "[ ] ") << task.title << "\n";
    }
    file.close();
}

// Function to show all tasks
void showTasks() {
    cout << "\n--- To-Do List ---\n";
    if (tasks.empty()) {
        cout << "No tasks found.\n";
    } else {
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << i + 1 << ". " << tasks[i].toString() << "\n";
        }
    }
    cout << "------------------\n";
}

// Function to add a task
void addTask() {
    cin.ignore(); // clear newline
    string title;
    cout << "Enter task title: ";
    getline(cin, title);
    tasks.push_back({title, false});
    cout << "Task added.\n";
}

// Function to mark task as completed
void completeTask() {
    int index;
    cout << "Enter task number to mark as completed: ";
    cin >> index;
    if (index < 1 || index > tasks.size()) {
        cout << "Invalid task number.\n";
        return;
    }
    tasks[index - 1].completed = true;
    cout << "Task marked as completed.\n";
}

// Function to delete a task
void deleteTask() {
    int index;
    cout << "Enter task number to delete: ";
    cin >> index;
    if (index < 1 || index > tasks.size()) {
        cout << "Invalid task number.\n";
        return;
    }
    tasks.erase(tasks.begin() + index - 1);
    cout << "Task deleted.\n";
}

// Menu
void showMenu() {
    cout << "\nTo-Do List Menu:\n";
    cout << "1. Show Tasks\n";
    cout << "2. Add Task\n";
    cout << "3. Complete Task\n";
    cout << "4. Delete Task\n";
    cout << "5. Save & Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    loadTasks();
    int choice;

    while (true) {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: showTasks(); break;
            case 2: addTask(); break;
            case 3: completeTask(); break;
            case 4: deleteTask(); break;
            case 5:
                saveTasks();
                cout << "Tasks saved. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}