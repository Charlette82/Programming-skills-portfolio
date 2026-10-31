#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <cctype>
using namespace std;


class Book {
public:
    string title, author, id;
    int pages;
    bool borrowed;

    Book(string t, string a, int p, string i, bool b)
        : title(t), author(a), pages(p), id(i), borrowed(b) {}
};

vector<Book> books;

string trim(string text) {
    size_t start = text.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    size_t end = text.find_last_not_of(" \t\r\n");
    return text.substr(start, end - start + 1);
}

void loadBooks() {
    ifstream file("bookData.txt");
    if (!file) {
        cout << "Error: Could not open bookData.txt\n";
        cout << "Place it in the program's working directory.\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        string title, author, pagesText, id, statusText;
        stringstream ss(line);

        if (!getline(ss, title, ',') ||
            !getline(ss, author, ',') ||
            !getline(ss, pagesText, ',') ||
            !getline(ss, id, ',') ||
            !getline(ss, statusText, ',')) {
            cout << "Skipping invalid line: " << line << '\n';
            continue;
        }

        try {
            title = trim(title);
            author = trim(author);
            int pages = stoi(trim(pagesText));
            id = trim(id);
            statusText = trim(statusText);

            transform(statusText.begin(), statusText.end(),
                      statusText.begin(),
                      [](unsigned char c) { return tolower(c); });

            bool borrowed = (statusText == "true" ||
                             statusText == "1");

            books.emplace_back(title, author, pages, id, borrowed);
        }
        catch (...) {
            cout << "Skipping invalid line: " << line << '\n';
        }
    }

    file.close();
    cout << books.size() << " book(s) loaded.\n";
}

void saveBooks() {
    ofstream file("bookData.txt");
    if (!file) {
        cout << "Error: Could not save book data.\n";
        return;
    }

    for (const Book& book : books) {
        file << book.title << ',' << book.author << ','
             << book.pages << ',' << book.id << ','
             << (book.borrowed ? "true" : "false") << '\n';
    }

    file.close();
}

void viewAllBooks() {
    if (books.empty()) {
        cout << "No books available.\n";
        return;
    }

    cout << "\n--- All Books ---\n";
    for (const Book& book : books) {
        cout << "ID: " << book.id
             << " | Title: " << book.title
             << " | Author: " << book.author
             << " | Pages: " << book.pages
             << " | Status: "
             << (book.borrowed ? "Borrowed" : "Available")
             << '\n';
    }
}

int findBook(string id) {
    id = trim(id);
    for (int i = 0; i < static_cast<int>(books.size()); i++) {
        if (books[i].id == id)
            return i;
    }
    return -1;
}

void viewBook() {
    string id;
    cout << "Enter book ID: ";
    cin >> id;

    int index = findBook(id);
    if (index == -1) {
        cout << "Book not found.\n";
        return;
    }

    Book b = books[index];
    cout << "\nTitle: " << b.title
         << "\nAuthor: " << b.author
         << "\nPages: " << b.pages
         << "\nID: " << b.id
         << "\nStatus: "
         << (b.borrowed ? "Borrowed" : "Available") << '\n';
}

void borrowBook() {
    string id;
    cout << "Enter book ID to borrow: ";
    cin >> id;

    int index = findBook(id);
    if (index == -1) {
        cout << "Book not found.\n";
    }
    else if (books[index].borrowed) {
        cout << "This book is already borrowed.\n";
    }
    else {
        books[index].borrowed = true;
        saveBooks();
        cout << "Book borrowed successfully!\n";
    }
}

void returnBook() {
    string id;
    cout << "Enter book ID to return: ";
    cin >> id;

    int index = findBook(id);
    if (index == -1) {
        cout << "Book not found.\n";
    }
    else if (!books[index].borrowed) {
        cout << "This book is not currently borrowed.\n";
    }
    else {
        books[index].borrowed = false;
        saveBooks();
        cout << "Book returned successfully!\n";
    }
}

int main() {
    loadBooks();

    if (books.empty()) {
        cout << "No book records loaded. Check bookData.txt.\n";
        return 1;
    }

    int choice;
    do {
        cout << "\n=== Library Management System ===\n"
             << "1. View all books\n"
             << "2. Search for a book\n"
             << "3. Borrow a book\n"
             << "4. Return a book\n"
             << "5. Save and exit\n"
             << "Enter choice: ";

        if (!(cin >> choice)) {
            cout << "Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: viewAllBooks(); break;
            case 2: viewBook(); break;
            case 3: borrowBook(); break;
            case 4: returnBook(); break;
            case 5:
                saveBooks();
                cout << "Data saved. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Choose 1 to 5.\n";
        }
    } while (choice != 5);

    return 0;
}