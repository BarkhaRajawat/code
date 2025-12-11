#include <iostream>
#include <string>
#include <ctime>
using namespace std;

struct Book {
    int id;
    string name;
    string author;

    string issueDate;
    string dueDate;
    bool isIssued;

    Book* next;
};

class HashTable {
private:
    static const int SIZE = 10;
    Book* table[SIZE];

public:
    HashTable() {
        for (int i = 0; i < SIZE; i++)
            table[i] = NULL;
    }

    int hashFunction(int id) {
        return id % SIZE;
    }

    void addBook(int id, string name, string author) {
        int index = hashFunction(id);

        Book* newBook = new Book;
        newBook->id = id;
        newBook->name = name;
        newBook->author = author;
        newBook->isIssued = false;
        newBook->next = NULL;

        if (table[index] == NULL) {
            table[index] = newBook;
        } else {
            Book* temp = table[index];
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newBook;
        }

        cout << "Book added successfully!\n";
    }

    void displayBooks() {
        cout << "\n---- Library Books ----\n";
        for (int i = 0; i < SIZE; i++) {
            Book* temp = table[i];
            while (temp != NULL) {
                cout << "ID: " << temp->id;
                cout << " | Name: " << temp->name;
                cout << " | Author: " << temp->author;

                if (temp->isIssued)
                    cout << " | Status: Issued";
                else
                    cout << " | Status: Available";

                cout << endl;
                temp = temp->next;
            }
        }
    }

    string getCurrentDate() {
        time_t now = time(0);
        tm* ltm = localtime(&now);

        int day = ltm->tm_mday;
        int month = 1 + ltm->tm_mon;
        int year = 1900 + ltm->tm_year;

        return to_string(day) + "-" + to_string(month) + "-" + to_string(year);
    }

    string calculateDueDate() {
        time_t now = time(0);
        now += 14 * 24 * 60 * 60; // add 14 days in seconds

        tm* ltm = localtime(&now);

        int day = ltm->tm_mday;
        int month = 1 + ltm->tm_mon;
        int year = 1900 + ltm->tm_year;

        return to_string(day) + "-" + to_string(month) + "-" + to_string(year);
    }

    void issueBook(int id) {
        int index = hashFunction(id);
        Book* temp = table[index];

        while (temp != NULL) {
            if (temp->id == id) {
                if (temp->isIssued) {
                    cout << "Book is already issued!\n";
                    return;
                }

                temp->issueDate = getCurrentDate();
                temp->dueDate = calculateDueDate();
                temp->isIssued = true;

                cout << "\nBook Issued Successfully!\n";
                cout << "Issue Date: " << temp->issueDate << endl;
                cout << "Due Date: " << temp->dueDate << endl;
                return;
            }
            temp = temp->next;
        }

        cout << "Book not found.\n";
    }

    void showIssueDetails(int id) {
        int index = hashFunction(id);
        Book* temp = table[index];

        while (temp != NULL) {
            if (temp->id == id) {
                if (!temp->isIssued) {
                    cout << "Book is not issued.\n";
                    return;
                }

                cout << "\n---- Issue Details ----\n";
                cout << "Issue Date: " << temp->issueDate << endl;
                cout << "Due Date: " << temp->dueDate << endl;
                return;
            }
            temp = temp->next;
        }

        cout << "Book not found.\n";
    }
};

int main() {
    HashTable lib;
    int choice, id;
    string name, author;

    while (true) {
        cout << "\n===== Library Management System =====\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Issue Book\n";
        cout << "4. Show Issue Details\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Book ID: ";
            cin >> id;
            cout << "Enter Book Name: ";
            cin >> name;
            cout << "Enter Author Name: ";
            cin >> author;
            lib.addBook(id, name, author);
            break;

        case 2:
            lib.displayBooks();
            break;

        case 3:
            cout << "Enter Book ID to Issue: ";
            cin >> id;
            lib.issueBook(id);
            break;

        case 4:
            cout << "Enter Book ID: ";
            cin >> id;
            lib.showIssueDetails(id);
            break;

        case 5:
            cout << "Exiting program...\n";
            return 0;

        default:
            cout << "Invalid choice! Try again.\n";
        }
    }
}
