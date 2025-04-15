#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono; // using std::chrono here for accurate task sort timing

// development of Task data type starts here

struct Task {
    string description;
    int priority;
};

// function prototypes

void addTask(vector<Task*>& tasks);
void deleteTask(vector<Task*>& tasks);
void displayTasks(const vector<Task*>& tasks);
void bubbleSort(vector<Task*>& tasks);
void selectionSort(vector<Task*>& tasks);
void insertionSort(vector<Task*>& tasks);

int main() {
    vector<Task*> tasks; // rather than using arrays, I am going to do something new and use vectors to store tasks
    int choice;
    do {
        cout << "\nSmart To-Do List Manager\n";
        cout << "1. Add Task" << endl;
        cout << "2. Delete Task" << endl;
        cout << "3. Display Tasks" << endl;
        cout << "4. Bubble Sort Tasks" << endl;
        cout << "5. Selection Sort Tasks" << endl;
        cout << "6. Insertion Sort Tasks" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
            {
            		addTask(tasks);
            		break;
            }
            case 2:
			{
					deleteTask(tasks);
					break;
			}
            case 3:
            {
            	displayTasks(tasks);
            	break;
            }
            case 4:
            {
            	bubbleSort(tasks);
            	break;
            }
            case 5:
            {
            	selectionSort(tasks);
            	break;
            }
            case 6:
            {
            	insertionSort(tasks);
            	break;
            }
            case 7:
            {
            	cout << "Exiting program..." << endl;
            	break;
            }
            default:
            {
            	cout << "Invalid choice! Try again." << endl;
            }
        }
    } while (choice != 7);

    for (Task* task : tasks) {
        delete task; // deleting tasks to avoid memory leak
    }
    return 0;
}

void addTask(vector<Task*>& tasks) { // this function uses the vector of tasks to add tasks
    Task* newTask = new Task;
    cout << "Enter task description: ";
    cin.ignore();
    getline(cin, newTask->description); // using the -> syntax to send newTask to description variable
    cout << "Enter task priority (higher number = higher priority): ";
    cin >> newTask->priority; // using the -> syntax to send newTask to priority variable
    tasks.push_back(newTask); // using push_back to add an element to a vector (CS1 technique)
}

void deleteTask(vector<Task*>& tasks) { // this function uses the vector of tasks to delete tasks
    int index;
    cout << "Enter task index to delete: ";
    cin >> index;
    if (index < 0 || index >= tasks.size()) { // this is the first draft of the if statement that I am using to check if this is the proper index that can be deleted from the vector list of tasks
        cout << "Invalid index!" << endl;
        return;
    }
    delete tasks[index];
    for (int i = index; i < tasks.size() - 1; i++) { // after task(s) has been deleted we will then use this for loop to reorder the indexes (not the priority)
        tasks[i] = tasks[i + 1];
    }
    tasks.pop_back(); // using pop_back to delete an element to a vector (CS1 technique)
    cout << "Task deleted successfully." << endl;
}

void displayTasks(const vector<Task*>& tasks) { // this function uses the vector of tasks to display tasks and uses const to keep it intact
    cout << "\nTasks:\n";
    for (int i = 0; i < static_cast<int>(tasks.size()); i++) {
    	cout << i << ". " << tasks[i]->description << " (Priority: " << tasks[i]->priority << ")\n"; // using the -> syntax to send tasks to priority/description variables
    }
}

void bubbleSort(vector<Task*>& tasks) { // this function uses the vector of tasks to sort inputted tasks using bubble sort
	auto start = high_resolution_clock::now(); // start the timer to check sorting time
    int n = tasks.size();
    for (int i = 0; i < n - 1; i++) { // used the Module 3 bubble sort lecture notes to help me write this algorithm
        for (int j = 0; j < n - i - 1; j++) {
            if (tasks[j]->priority < tasks[j + 1]->priority) { // using the -> syntax to send task index to priority variable and checks to see if it's less than the j + 1 task variable
                Task* temp = tasks[j]; // variable temp and the pointer variable of tasks is crucial for the bubble sorting process
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }
    auto end = high_resolution_clock::now(); // ends the timer to check sorting time
    duration<double> elapsed = end - start; // calculates the elapsed time and returns as doubled
    cout << "Bubble Sort completed in " << elapsed.count() << " seconds." << endl;
}

void selectionSort(vector<Task*>& tasks) { // this function uses the vector of tasks to sort inputted tasks using selection sort
	auto start = high_resolution_clock::now(); // start the timer to check sorting time
    int n = tasks.size();
    for (int i = 0; i < n - 1; i++) { // used the Module 3 selection sort lecture notes to help me write this algorithm
        int maxIndex = i; // initialization of i as the largest index
        for (int j = i + 1; j < n; j++) {
            if (tasks[j]->priority > tasks[maxIndex]->priority) { // using the -> syntax to send task index to priority variable and checks to see if it's greater than the largest index
                maxIndex = j;
            }
        }
        Task* temp = tasks[i]; // to help with selection sort process, variable temp and the pointer variable of tasks implemented
        tasks[i] = tasks[maxIndex];
        tasks[maxIndex] = temp;
    }
    auto end = high_resolution_clock::now(); // ends the timer to check sorting time
    duration<double> elapsed = end - start; // calculates the elapsed time and returns as doubled
    cout << "Selection Sort completed in " << elapsed.count() << " seconds." << endl;
}

void insertionSort(vector<Task*>& tasks) { // this function uses the vector of tasks to sort inputted tasks using insertion sort
	auto start = high_resolution_clock::now(); // start the timer to check sorting time
    int n = tasks.size();
    for (int i = 1; i < n; i++) {
        Task* key = tasks[i]; // from research; key is used as a temporary variable that holds the current element for an already sorted element from the vector
        int j = i - 1;
        while (j >= 0 && tasks[j]->priority < key->priority) { // using the -> syntax to send task and key variable to priority variable and checks to see if it's less than the key
            tasks[j + 1] = tasks[j]; // key is acted as a temp variable and this is crucial for the insertion sort algorithim
            j--;
        }
        tasks[j + 1] = key;
    }
    auto end = high_resolution_clock::now(); // end the timer to check sorting time
    duration<double> elapsed = end - start; // calculates the elapsed time and returns as doubled
    cout << "Insertion Sort completed in " << elapsed.count() << " seconds." << endl;
}
