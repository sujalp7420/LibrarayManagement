#include <bits/stdc++.h>
using namespace std;

struct Book
{
    string id;
    string title;
    string author;
    bool issued;
    string issuedTo; // Student ID if issued, empty otherwise

    Book(string _id, string _title, string _author, bool _issued = false, string _issuedTo = "")
        : id(_id), title(_title), author(_author), issued(_issued), issuedTo(_issuedTo) {}
};

struct Student
{
    string id;
    string name;

    Student(string _id, string _name) : id(_id), name(_name) {}
};

class Library
{
private:
    vector<Book> books;
    vector<Student> students;
    const string bookFile = "books.txt";
    const string studentFile = "students.txt";

    Book *findBookById(const string &id)
    {
        for (auto &b : books)
        {
            if (b.id == id)
                return &b;
        }
        return nullptr;
    }

    Student *findStudentById(const string &id)
    {
        for (auto &s : students)
        {
            if (s.id == id)
                return &s;
        }
        return nullptr;
    }

    void saveBooks()
    {
        ofstream out(bookFile);
        for (auto &b : books)
        {
            out << b.id << "|" << b.title << "|" << b.author << "|"
                << b.issued << "|" << b.issuedTo << "\n";
        }
    }

    void saveStudents()
    {
        ofstream out(studentFile);
        for (auto &s : students)
        {
            out << s.id << "|" << s.name << "\n";
        }
    }

    void loadBooks()
    {
        ifstream in(bookFile);
        books.clear();
        string line;
        while (getline(in, line))
        {
            stringstream ss(line);
            string id, title, author, issuedStr, issuedTo;
            getline(ss, id, '|');
            getline(ss, title, '|');
            getline(ss, author, '|');
            getline(ss, issuedStr, '|');
            getline(ss, issuedTo);
            bool issued = (issuedStr == "1");
            books.emplace_back(id, title, author, issued, issuedTo);
        }
    }

    void loadStudents()
    {
        ifstream in(studentFile);
        students.clear();
        string line;
        while (getline(in, line))
        {
            stringstream ss(line);
            string id, name;
            getline(ss, id, '|');
            getline(ss, name);
            students.emplace_back(id, name);
        }
    }

public:
    Library()
    {
        loadBooks();
        loadStudents();
    }

    void addBook()
    {
        string id, title, author;
        cout << "Enter Book ID: ";
        cin >> id;
        if (findBookById(id))
        {
            cout << "Book ID already exists!\n";
            return;
        }
        cin.ignore();
        cout << "Enter Title: ";
        getline(cin, title);
        cout << "Enter Author: ";
        getline(cin, author);
        books.emplace_back(id, title, author);
        saveBooks();
        cout << "Book added!\n";
    }

    void addStudent()
    {
        string id, name;
        cout << "Enter Student ID: ";
        cin >> id;
        if (findStudentById(id))
        {
            cout << "Student ID already exists!\n";
            return;
        }
        cin.ignore();
        cout << "Enter Student Name: ";
        getline(cin, name);
        students.emplace_back(id, name);
        saveStudents();
        cout << "Student added!\n";
    }

    void displayBooks()
    {
        if (books.empty())
        {
            cout << "No books in library!\n";
            return;
        }
        for (auto &b : books)
        {
            cout << "ID: " << b.id << " | Title: " << b.title << " | Author: " << b.author
                 << " | Status: " << (b.issued ? "Issued to " + b.issuedTo : "Available") << "\n";
        }
    }

    void displayStudents()
    {
        if (students.empty())
        {
            cout << "No students registered!\n";
            return;
        }
        for (auto &s : students)
        {
            cout << "ID: " << s.id << " | Name: " << s.name << "\n";
        }
    }

    void issueBook()
    {
        string bookId, studentId;
        cout << "Enter Book ID to issue: ";
        cin >> bookId;
        Book *book = findBookById(bookId);
        if (!book)
        {
            cout << "Book not found!\n";
            return;
        }
        if (book->issued)
        {
            cout << "Book already issued!\n";
            return;
        }
        cout << "Enter Student ID: ";
        cin >> studentId;
        Student *student = findStudentById(studentId);
        if (!student)
        {
            cout << "Student not found!\n";
            return;
        }
        book->issued = true;
        book->issuedTo = studentId;
        saveBooks();
        cout << "Book issued to " << student->name << "!\n";
    }

    void returnBook()
    {
        string bookId, studentId;
        cout << "Enter Book ID to return: ";
        cin >> bookId;
        Book *book = findBookById(bookId);
        if (!book)
        {
            cout << "Book not found!\n";
            return;
        }
        if (!book->issued)
        {
            cout << "Book was not issued!\n";
            return;
        }
        cout << "Enter Student ID returning the book: ";
        cin >> studentId;
        if (book->issuedTo != studentId)
        {
            cout << "This student didn't issue this book!\n";
            return;
        }
        book->issued = false;
        book->issuedTo = "";
        saveBooks();
        cout << "Book returned!\n";
    }

    void removeBook()
    {
        string id;
        cout << "Enter Book ID to remove: ";
        cin >> id;
        Book *book = findBookById(id);
        if (!book)
        {
            cout << "Book not found!\n";
            return;
        }
        if (book->issued)
        {
            cout << "Cannot remove — book is currently issued!\n";
            return;
        }
        books.erase(remove_if(books.begin(), books.end(),
                              [&](Book &b)
                              { return b.id == id; }),
                    books.end());
        saveBooks();
        cout << "Book removed!\n";
    }
};

int main()
{
    Library lib;
    int choice;
    do
    {
        cout << "\n=== Library Management System ===\n";
        cout << "1. Add Book\n";
        cout << "2. Add Student\n";
        cout << "3. Display Books\n";
        cout << "4. Display Students\n";
        cout << "5. Issue Book\n";
        cout << "6. Return Book\n";
        cout << "7. Remove Book\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            lib.addBook();
            break;
        case 2:
            lib.addStudent();
            break;
        case 3:
            lib.displayBooks();
            break;
        case 4:
            lib.displayStudents();
            break;
        case 5:
            lib.issueBook();
            break;
        case 6:
            lib.returnBook();
            break;
        case 7:
            lib.removeBook();
            break;
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 0);
    return 0;
}