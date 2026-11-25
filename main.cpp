#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int SIZE = 50000;

struct customList {
    int id;
    customList *next;
};

void readFromFile(customList *&l) {
    ifstream file("data.txt");
    customList *last = nullptr;
    int val;

    while (file >> val) {
        customList *temp = new customList{val, nullptr};
        if (last == nullptr)
            l = temp;
        else
            last->next = temp;
        last = temp;
    }
    cout << "Data read from file.\n";
}
void displayList(customList *l) {
    if (l == nullptr) {
        cout << "No data available.\n";
        return;
    }

    int i = 1;
    customList *temp = l;
    while (temp != nullptr) {
        cout << i << " | " << temp->id << endl;
        temp = temp->next;
        i++;
    }
}
void findMax(customList *l) {
    int highest = l->id;
    customList *temp = l->next;

    while (temp != nullptr) {
        if (temp->id > highest)
            highest = temp->id;
        temp = temp->next;
    }
    cout << "Highest value: " << highest << endl;
}
void sortList(customList *l) {
    for (customList *i = l; i != nullptr && i->next != nullptr; i = i->next) {
        customList *max_id = i;

        for (customList *j = i->next; j != nullptr; j = j->next) {
            if (j->id > max_id->id)
                max_id = j;
        }
        swap(i->id, max_id->id);
    }
}
void truncateList(customList *&l) {
    while (l != nullptr) {
        customList *temp = l;
        l = l->next;
        delete temp;
    }
}
void sortArray(int arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        int max_id = i;

        for (int j = i + 1; j < n; ++j) {
            if (arr[j] > arr[max_id]) {
                max_id = j;
            }
        }
        swap(arr[i], arr[max_id]);
    }
}
void compareSorting() {
    int arr[SIZE];
    customList *l = nullptr;
    customList *last = nullptr;

    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 1000000;

        customList *temp = new customList{arr[i], nullptr};
        if (last == nullptr)
            l = temp;
        else
            last->next = temp;
        last = temp;
    }

    time_t startList = time(nullptr);
    sortList(l);
    time_t endList = time(nullptr);

    time_t startArray = time(nullptr);
    sortArray(arr, SIZE);
    time_t endArray = time(nullptr);


    cout << "Sorting " << SIZE << " numbers.\n";
    cout << "List:  " << endList - startList << " ms\n";
    cout << "Array: " << endArray - startArray << " ms\n";

    truncateList(l);
}
int main() {
    srand(time(NULL));
    customList *l = nullptr;
    int choice = 0;

    do {
        cout << "\n1 | Load data from file\n";
        cout << "2 | Display list\n";
        cout << "3 | Find highest value\n";
        cout << "4 | Sort list (highest to lowest)\n";
        cout << "5 | Compare sorting time (list vs array)\n";
        cout << "6 | Exit and Free Memory\n\n";
        cin >> choice;
        cout << "\n";

        switch (choice) {
            case 1:
                readFromFile(l);
                break;
            case 2:
                displayList(l);
                break;
            case 3:
                if (l == nullptr)
                    cout << "List is empty.\n";
                else
                    findMax(l);
                break;
            case 4:
                if (l == nullptr)
                    cout << "List is empty.\n";
                else
                    sortList(l);
                break;
            case 5:
                compareSorting();
                break;
            case 6:
                truncateList(l);
                break;
        }
    } while (choice != 6);
    return 0;
}
