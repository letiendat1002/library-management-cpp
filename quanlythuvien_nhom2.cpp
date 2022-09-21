#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> // setw(), left, right, setfill
#include <cctype>  // toupper()

using namespace std;

struct Student
{
    long long idLib;
    string idStudent;
    string nameStudent;
    string classStudent;
};

struct Book
{
    long long idBook;
    string nameBook;
    string authorBook;
    string placeBook;
    bool isRent;
};

struct Date
{
    int day, month, year;
};
struct RentLib
{
    Student rentStudent;
    Book rentBook;
    int quantity;
    string total;
    Date rentDate;
    Date returnDate;
};

// Student node and tree
struct NodeSt
{
    Student st;
    NodeSt *left;
    NodeSt *right;
};
typedef NodeSt *studentTree;

// Book node and tree
struct NodeBk
{
    Book bk;
    NodeBk *left;
    NodeBk *right;
};
typedef NodeBk *bookTree;

// Rent node and tree
struct NodeRl
{
    RentLib rl;
    NodeRl *left;
    NodeRl *right;
};
typedef NodeRl *rentTree;

// Menu
void menuBase();
void menuStudent();
void menuBook();
void menuRent();

// Student main function
int student_CreateInsertNode(studentTree &, Student); // Create and Insert Data to Student Node
void readDataFile_StudentTree(studentTree &);         // Read data file to Student tree
void writeDataFile_StudentTree(studentTree &);        // Write Struct Student to data files
studentTree studentID_Find(studentTree &, string);    // Find Student ID
void studentAdd(studentTree &);                       // * Add Student to Student tree
int studentDelete(studentTree &, long long);          // Delete Student
void studentUpdate(studentTree &);                    // Update Student
studentTree studentFind(studentTree &, long long);    // ** Find Student
void view_studentFind(studentTree &);                 // ** View Student is found
void studentView(studentTree &);                      // View (Default)
void studentViewSortedByName(studentTree &);          // View (Sort By Student Name)
void studentProgram(studentTree &);                   // Program Student

// Book main function
int book_CreateInsertNode(bookTree &, Book);   // Create and Insert Data to Book Node
void readDataFile_BookTree(bookTree &);        // Read data file to book tree
void writeDataFile_BookTree(bookTree &);       // Write Struct book to data files
void bookAdd(bookTree &);                      // * Add book to book tree
int bookDelete(bookTree &, long long);         // Delete book
void bookUpdate(bookTree &);                   // Update book
bookTree bookFind_ByID(bookTree &, long long); // ** Find book
void view_bookFind_ByID(bookTree &);           // ** View book is found By ID
void view_bookFind_ByName(bookTree &);         // ** View book is found By Name
void bookView(bookTree &);                     // View (Default)
void bookViewSortedByName(bookTree &);         // View (Sort By Book Name)
void bookProgram(bookTree &);

// Rent main function
int rent_CreateInsertNode(rentTree &, RentLib);          // Create and Insert Data to Node
void readDataFile_RentTree(rentTree &);                  // Read data file to Rent tree
void writeDataFile_RentTree(rentTree &);                 // Write Struct Rent to data files
void rentAdd(studentTree &, bookTree &, rentTree &);     // * Add Rent info to Rent tree
int rentDelete(rentTree &, long long);                   // Delete rent
void rentUpdate(rentTree &);                             // Update rent
rentTree rentFind(rentTree &, long long);                // ** Find rent
void view_rentFind(rentTree &);                          // ** View rent is found
void rentView(rentTree &);                               // View (Default)
void bookViewSortedByName(rentTree);                     // view (Sort By Student Name)
void rentProgram(studentTree &, bookTree &, rentTree &); // Program rent

int pos = 0;
// Main Function
int main()
{
    studentTree rootSt = NULL;
    bookTree rootBk = NULL;
    rentTree rootRl = NULL;

    readDataFile_StudentTree(rootSt);
    readDataFile_BookTree(rootBk);
    readDataFile_RentTree(rootRl);
    int choice;
    int confirm;
    do
    {
    doagain:
        menuBase();
        cout << "\nInput your choice (1-3): ";
        cin >> choice;
        cin.ignore();
        if (cin.fail())
        {
            cout << "CAUTIONS: Invalid input -> Try again.\n\n";
            cin.clear();
            cin.ignore();
            goto doagain;
        }
        switch (choice)
        {
        case 1:
            studentProgram(rootSt);
            break;
        case 2:
            bookProgram(rootBk);
            break;
        case 3:
            rentProgram(rootSt, rootBk, rootRl);
            break;
        default:
            if (choice == 0)
            {
                cout << "\nApp shutdown successfully.\nMORE INFO: This program is created by Group 02..." << endl;
                exit(0);
            }
            else
            {
                cout << "Invalid choice -> Try again.\n\n";
                goto doagain;
            }
        }
    confirm_again:
        cout << "\nContinue with Program? Yes[1]/No[0]: ";
        cin >> confirm;
        cin.ignore();
        if (cin.fail())
        {
            cout << "CAUTIONS: Invalid input -> Try again.\n\n";
            cin.clear();
            cin.ignore();
            goto confirm_again;
        }
        if (confirm != 0 && confirm != 1)
        {
            cout << "Your choice is invalid. Try again please!\n\n";
            goto confirm_again;
        }
    } while (confirm == 1);
    cout << "\nApp shutdown successfully.\nMORE INFO: This program is created by Group 02..." << endl;
    return 0;
}

// Menu Function
void menuBase()
{
    cout << "*************************MENU BASE**************************\n";
    cout << "**  1) Student Management                                 **\n";
    cout << "**  2) Book Management                                    **\n";
    cout << "**  3) Rent Management                                    **\n";
    cout << "**  0) Exit                                               **\n";
    cout << "************************************************************\n";
}
void menuStudent()
{
    cout << "*************************MENU STUDENT***********************\n";
    cout << "**  1. Add Student                                        **\n";
    cout << "**  2. Delete Student                                     **\n";
    cout << "**  3. Update Student                                     **\n";
    cout << "**  4. Find Student                                       **\n";
    cout << "**  5. View Student List (Default)                        **\n";
    cout << "**  6. View Student List (Sorted By Student Name)         **\n";
    cout << "**  7. Save Student Data                                  **\n";
    cout << "**  0. Exit                                               **\n";
    cout << "************************************************************\n";
}
void menuBook()
{
    cout << "*************************MENU BOOK**************************\n";
    cout << "**  1. Add Book                                           **\n";
    cout << "**  2. Delete Book                                        **\n";
    cout << "**  3. Update Book                                        **\n";
    cout << "**  4. Find Book                                          **\n";
    cout << "**  5. View Book List (Default)                           **\n";
    cout << "**  6. View Book List (Sorted By Book Name)               **\n";
    cout << "**  7. Save Book Data                                     **\n";
    cout << "**  0. Exit                                               **\n";
    cout << "************************************************************\n";
}
void menuRent()
{
    cout << "*************************MENU RENT**************************\n";
    cout << "**  1. Add Rent Info                                      **\n";
    cout << "**  2. Delete Rent Info                                   **\n";
    cout << "**  3. Update Rent Info                                   **\n";
    cout << "**  4. Find Rent Info                                     **\n";
    cout << "**  5. View Rent List (Default)                           **\n";
    cout << "**  6. Save Rent Data                                     **\n";
    cout << "**  0. Exit                                               **\n";
    cout << "************************************************************\n";
}

void menuFind()
{
    cout << "*************************MENU FIND BOOK*********************\n";
    cout << "**  1. Find Book By ID                                    **\n";
    cout << "**  2. Find Book By Name                                  **\n";
    cout << "**  0. Exit                                               **\n";
    cout << "************************************************************\n";
}
// =================================================================
// STUDENT MANAGEMENT

// Student Tree function
int student_CreateInsertNode(studentTree &rootSt, Student x) // Create and Insert Node
{
    if (rootSt != NULL)
    {
        if (rootSt->st.idLib == x.idLib)
            return -1; // Node existed
        else if (rootSt->st.idLib > x.idLib)
            return student_CreateInsertNode(rootSt->left, x); // Chen node left
        else
            return student_CreateInsertNode(rootSt->right, x); // Chen node right
    }
    rootSt = new NodeSt[1];
    if (rootSt == NULL)
        return 0; // Bo nho Full
    rootSt->st = x;
    rootSt->left = rootSt->right = NULL;
    return 1;
}
// Input and output Student Info
studentTree studentID_Find(studentTree &rootSt, string x) // Find Student ID
{
    NodeSt *p = rootSt;
    if (p != NULL)
    {
        if (x.compare(p->st.idStudent) == 0)
            return p; // Found node p with key x
        if (x.compare(p->st.idStudent) < 0)
            return studentID_Find(p->left, x); // Find next at left
        if (x.compare(p->st.idStudent) > 0)
            return studentID_Find(p->right, x); // Find next at right

        return NULL;
    }
    else
        return NULL; // Node with key x not found
}

Student studentInput(studentTree &rootSt)
{
    Student x;
again_idLib:
    cout << "Library ID (Input -1 to cancel): ";
    cin >> x.idLib;
    cin.ignore();
    if (cin.fail())
    {
        cout << "CAUTIONS: Invalid input -> Try again.\n\n";
        cin.clear();
        cin.ignore();
        goto again_idLib;
    }
    if (x.idLib == -1)
    {
        cout << "*Cancel successfully!*\n";
        return x; // Cancel input
    }
    if (studentFind(rootSt, x.idLib) != NULL) // Id Library found
    {
        cout << "\n*This Library ID is already existed in Student List*. Try again\n";
        goto again_idLib;
    }

    if (x.idLib < 0 && x.idLib != -1)
    {
        cout << "Invalid library ID. Try again\n\n";
        goto again_idLib;
    }

again_idStudent:
    cout << "Student ID: ";
    cin >> x.idStudent;
    cin.ignore();
    if (studentID_Find(rootSt, x.idStudent) != NULL) // ID Student is existed
    {
        cout << "\n*This Student ID is already existed in Student List*. Try again\n";
        goto again_idStudent;
    }
    cout << "Student name: ";
    getline(cin, x.nameStudent);
    cout << "Student class: ";
    cin >> x.classStudent;
    cin.ignore();
    return x;
}
void studentOutput(Student x)
{
    cout << setw(15) << left << x.idLib;
    cout << setw(20) << left << x.idStudent;
    cout << setw(30) << left << x.nameStudent;
    cout << setw(15) << right << x.classStudent << endl;
}
// Read and write between Student Tree and student.txt
void readDataFile_StudentTree(studentTree &rootSt)
{
    Student x;
    fstream St("D:\\student.txt", ios::in); // Mo file o dang read
    char c;
    if (St)
    {
        while (!St.eof())
        {
            St >> x.idLib;
            St >> x.idStudent;
            St.get(c);
            getline(St, x.nameStudent, ',');
            St >> x.classStudent;
            St.get(c);
            student_CreateInsertNode(rootSt, x);
        }
        St.close(); // dong file
    }
}
void writeDataFile_StudentTree(studentTree &rootSt)
{
    if (rootSt != NULL) // cây có DATA
    {
        fstream St("D:\\student.txt", ios::out | ios::app); // Mở file ở MODE write
        St << rootSt->st.idLib << ' ' << rootSt->st.idStudent << ' ' << rootSt->st.nameStudent << ',' << rootSt->st.classStudent << '\n';
        St.close();
        writeDataFile_StudentTree(rootSt->left); // rootSt gọi là gốc, sau khi đệ quy rootSt->left gọi là node con LEFT, rootSt->right gọi là node con RIGHT
        writeDataFile_StudentTree(rootSt->right);
    }
}
// Copy Data from Student Tree to Struct Array
void studentTree_toArray(studentTree &rootSt, Student a[])
{
    if (rootSt == NULL)
        return;

    a[pos++] = rootSt->st;
    studentTree_toArray(rootSt->left, a);
    studentTree_toArray(rootSt->right, a);
}
int studentTree_Size(studentTree &rootSt)
{
    if (rootSt == NULL)
        return 0;
    else
        return studentTree_Size(rootSt->left) + studentTree_Size(rootSt->right) + 1;
}
// Bubble Sort
void student_bubbleSort(Student arr[], int n)
{
    int i, j;
    bool haveSwap = false;
    for (i = 0; i < n - 1; i++)
    {
        haveSwap = false;
        for (j = n - 1; j > i; j--)
        {
            if (arr[j].nameStudent.compare(arr[j - 1].nameStudent) < 0)
            {
                swap(arr[j], arr[j - 1]);
                haveSwap = true;
            }
        }
        if (haveSwap == false)
        {
            break;
        }
    }
}

// Student Main Function
void studentAdd(studentTree &rootSt) // Add Struct Student to 1 node in Student tree
{
    Student x;
    while (true)
    {
        cout << "\nInput Student Info\n";
        x = studentInput(rootSt);
        if (x.idLib == -1)
            break; // Cancel Add Student
        int check = student_CreateInsertNode(rootSt, x);
        if (check == -1)
            cout << "***This ID Library is already existed in Student Tree***\n\n";
        else if (check == 0)
            cout << "***Memory is full***" << endl;
        else
            cout << "***Add Student Successfully***\n\n";
    }
}
int studentDelete(studentTree &rootSt, long long x)
{
    if (rootSt == NULL)
    {
        return 0;
    }
    else if (rootSt->st.idLib > x)
        return studentDelete(rootSt->left, x);
    else if (rootSt->st.idLib < x)
        return studentDelete(rootSt->right, x);
    else // rootSt->st.idLib == x (found). This is the note to be deleted.
    {
        NodeSt *p = rootSt;
        if (rootSt->left == NULL)
            rootSt = rootSt->right; // Node only have right subtree
        else if (rootSt->right == NULL)
            rootSt = rootSt->left; // Node only have left subtree

        else // Node have 2 subtree
        {
            NodeSt *s = rootSt, *q = s->left;
            // s is parent of q, q->right is rightest node of left subtree of p
            while (q->right != NULL)
            {
                s = q;
                q = q->right;
            }
            p->st = q->st;
            s->right = q->left;
            delete q;
        }
    }
    return 1;
}
void studentUpdate(studentTree &rootSt, long long lib) // Update student
{
    studentTree p = studentFind(rootSt, lib);
    string keyword;

    if (p != NULL)
    {
        cout << "Student is found!\n"
             << endl;
        cout << "Input keyword to update:\n";
        cout << "1. mssv\n2. name\n3. class\n\nInput keyword: ";

        cin >> keyword;
        cin.ignore();
        if (keyword == "mssv")
        {
            cout << "\nStudent ID before change: " << p->st.idStudent << "\n\n";
            cout << "Re-Input Student ID: ";
            cin >> p->st.idStudent;
            cin.ignore();
            cout << "\n*Update Student ID successfully.*\n";
        }
        else if (keyword == "name")
        {
            cout << "\nStudent Name before change: " << p->st.nameStudent << "\n\n";
            cout << "Re-Input Student Name: ";
            getline(cin, p->st.nameStudent);
            cout << "\n*Update Student Name successfully.*\n";
        }
        else if (keyword == "class")
        {
            cout << "\nStudent Class before change: " << p->st.classStudent << "\n\n";
            cout << "Re-Input Student Class: ";
            cin >> p->st.classStudent;
            cin.ignore();
            cout << "\n*Update Student Class successfully.*\n";
        }
        else
        {
            cout << "*Invalid keyword*\n";
        }
    }
    else
    {
        cout << "*ID library not found!*" << endl;
    }
}
studentTree studentFind(studentTree &rootSt, long long x) // Find Student
{
    NodeSt *p = rootSt;
    if (p != NULL)
    {
        if (x == p->st.idLib)
            return p; // Found node p with key x
        if (x < p->st.idLib)
            return studentFind(p->left, x); // Find next at left
        if (x > p->st.idLib)
            return studentFind(p->right, x); // Find next at right

        return NULL;
    }
    else
        return NULL; // Node with key x not found
}
void view_studentFind(studentTree &rootSt) // View Student is found
{
    long long lib;
tryagain:
    cout << "Input ID Library to find (-1 to cancel): ";
    cin >> lib;
    cin.ignore();
    if (cin.fail())
    {
        cout << "CAUTIONS: Invalid input -> Try again.\n\n";
        cin.clear();
        cin.ignore();
        goto tryagain;
    }
    if (lib < 0 && lib != -1)
    {
        cout << "*Invalid library ID. Try again*\n\n";
        goto tryagain;
    }
    if (lib == -1)
    {
        cout << "*Cancel successfully!*\n";
        return; // Cancel input
    }
    studentTree temp = studentFind(rootSt, lib);
    if (temp != NULL)
    {
        cout << setw(15) << left << "Library ID";
        cout << setw(20) << left << "Student ID";
        cout << setw(30) << left << "Student Name";
        cout << setw(15) << right << "Student Class" << endl;
        cout << setfill('-');
        cout << setw(80) << '-' << endl;
        // reset fill
        cout << setfill(' ');
        studentOutput(temp->st);
    }
    else
    {
        cout << "\n*ID library not found!*\n";
    }
}
// View Student List (Default)
void studentView(studentTree &rootSt) // NLR - Node left right - PreOrder
{
    if (rootSt != NULL)
    {
        studentOutput(rootSt->st);
        studentView(rootSt->left);
        studentView(rootSt->right);
    }
}
// View Student List (Sorted by Student Name)
void studentViewSortedByName(studentTree &rootSt)
{
    if (rootSt != NULL)
    {
        int st_size = studentTree_Size(rootSt);
        Student *a = new Student[st_size];
        studentTree_toArray(rootSt, a);
        student_bubbleSort(a, st_size);
        for (int i = 0; i < st_size; i++)
            studentOutput(a[i]);
        delete[] a;
    }
    else
    {
        cout << "\n*There is no Student Info to view*\n";
    }
}
void studentProgram(studentTree &rootSt)
{
    system("cls");
    Student x;

    int choice;
    int confirm;
    do
    {
        system("cls");
    doagain_student:
        menuStudent();
        cout << "\nInput your choice (1-7): ";
        cin >> choice;
        cin.ignore();
        if (cin.fail())
        {
            cout << "CAUTIONS: Invalid input -> Try again.\n\n";
            cin.clear();
            cin.ignore();
            goto doagain_student;
        }
        if (choice == 1)
        {
            studentAdd(rootSt);
        }
        else if (choice == 2)
        {
            long long x;
        inputagain:
            cout << "Input ID Library to delete (-1 to cancel): ";
            cin >> x;
            cin.ignore();
            if (cin.fail())
            {
                cout << "CAUTIONS: Invalid input -> Try again.\n\n";
                cin.clear();
                cin.ignore();
                goto inputagain;
            }
            if (x < 0 && x != -1)
            {
                cout << "*Invalid library ID. Try again*\n\n";
                goto inputagain;
            }

            if (x == -1)
            {
                cout << "*Cancel successfully!*\n";
            }
            if (x >= 0 && x != -1)
            {
                studentTree p = studentFind(rootSt, x);
                if (p != NULL)
                {
                    int del = 1;
                    while (del)
                    {
                        if (p != NULL)
                        {
                            del = studentDelete(rootSt, x);
                        }
                        else
                        {
                            cout << "*No data!*" << endl;
                            del = 0;
                        }
                    }
                    cout << "*Student is deleted successfully!*" << endl;
                }
                else
                {
                    cout << "*ID library not found!*" << endl;
                }
            }
        }
        else if (choice == 3)
        {
            long long lib;
            cout << "\n*Update Student Info*\n";
        reinput:
            cout << "Input ID Library to update (-1 to cancel): ";
            cin >> lib;
            cin.ignore();
            if (cin.fail())
            {
                cout << "CAUTIONS: Invalid input -> Try again.\n\n";
                cin.clear();
                cin.ignore();
                goto reinput;
            }
            if (lib < 0 && lib != -1)
            {
                cout << "*Invalid library ID. Try again*\n\n";
                goto reinput;
            }
            if (lib == -1)
            {
                cout << "*Cancel successfully!*\n";
            }
            if (lib >= 0 && lib != -1)
                studentUpdate(rootSt, lib);
        }
        else if (choice == 4)
        {
            view_studentFind(rootSt);
        }
        else if (choice == 5)
        {
            cout << "***Student list (Default By ID Library)***\n";
            cout << setw(15) << left << "Library ID";
            cout << setw(20) << left << "Student ID";
            cout << setw(30) << left << "Student Name";
            cout << setw(15) << right << "Student Class" << endl;
            cout << setfill('-');
            cout << setw(80) << '-' << endl;
            // reset fill
            cout << setfill(' ');
            studentView(rootSt);
        }
        else if (choice == 6)
        {
            pos = 0;
            cout << "***Student list (Sort By Student Name)***\n";
            cout << setw(15) << left << "Library ID";
            cout << setw(20) << left << "Student ID";
            cout << setw(30) << left << "Student Name";
            cout << setw(15) << right << "Student Class" << endl;
            cout << setfill('-');
            cout << setw(80) << '-' << endl;
            // reset fill
            cout << setfill(' ');
            studentViewSortedByName(rootSt);
        }
        else if (choice == 7)
        {
            remove("D:\\student.txt");
            writeDataFile_StudentTree(rootSt);
            cout << "\n*Save data successfully!*" << endl;
        }
        else if (choice == 0)
        {
            cout << "*Exit successfully!*\n";
        }
        else
        {
            cout << "*Invalid choice -> Try again.*\n\n";
            goto doagain_student;
        }
    confirm_again:
        cout << "\nContinue with Student? Yes[1]/No[0]: ";
        cin >> confirm;
        cin.ignore();
        if (cin.fail())
        {
            cout << "CAUTIONS: Invalid input -> Try again.\n\n";
            cin.clear();
            cin.ignore();
            goto confirm_again;
        }
        if (confirm != 0 && confirm != 1)
        {
            cout << "*Your choice is invalid. Try again please!*\n\n";
            goto confirm_again;
        }
    } while (confirm == 1);
}

// =================================================================
// BOOK MANAGEMENT

// Book Tree function
int book_CreateInsertNode(bookTree &rootBk, Book x) // Create and Insert Node
{
    if (rootBk != NULL)
    {
        if (rootBk->bk.idBook == x.idBook)
            return -1; // Node existed
        else if (rootBk->bk.idBook > x.idBook)
            return book_CreateInsertNode(rootBk->left, x); // Chen node left
        else
            return book_CreateInsertNode(rootBk->right, x); // Chen node right
    }
    rootBk = new NodeBk[1];
    if (rootBk == NULL)
        return 0; // Bo nho Full
    rootBk->bk = x;
    rootBk->left = rootBk->right = NULL;
    return 1;
}
// Input and output Book Info
Book bookInput(bookTree &rootBk)
{
    Book x;
again_idBook:
    cout << "Book ID (Input -1 to cancel): ";
    cin >> x.idBook;
    cin.ignore();
    if (cin.fail())
    {
        cout << "CAUTIONS: Invalid input -> Try again.\n\n";
        cin.clear();
        cin.ignore();
        goto again_idBook;
    }
    if (x.idBook == -1)
    {
        cout << "*Cancel successfully!*\n";
        return x; // Cancel input
    }
    if (bookFind_ByID(rootBk, x.idBook) != NULL) // Id Book found
    {
        cout << "\n*This Book ID is already existed in Book List. Try again*\n";
        goto again_idBook;
    }
    if (x.idBook < 0 && x.idBook != -1)
    {
        cout << "*Invalid Book ID. Try again*\n\n";
        goto again_idBook;
    }

    cout << "Book Name: ";
    getline(cin, x.nameBook);
    cout << "Author Name: ";
    getline(cin, x.authorBook);
    cout << "Book Location: ";
    cin >> x.placeBook;
    cin.ignore();
    cout << "Rented? : ";
    cin >> x.isRent;
    cin.ignore();
    return x;
}
void bookOutput(Book x)
{
    cout << setw(15) << left << x.idBook;
    cout << setw(30) << left << x.nameBook;
    cout << setw(30) << left << x.authorBook;
    cout << setw(20) << left << x.placeBook;
    cout << setw(15) << right << ((x.isRent) ? "Yes" : "No") << endl;
}
// Read and write between Book Tree and book.txt
void readDataFile_BookTree(bookTree &rootBk)
{
    Book x;
    fstream Bk("D:\\book.txt", ios::in);
    char c;
    if (Bk)
    {
        while (!Bk.eof())
        {
            Bk >> x.idBook;
            Bk.get(c);
            getline(Bk, x.nameBook, ',');
            getline(Bk, x.authorBook, ',');
            Bk >> x.placeBook;
            Bk >> x.isRent;
            book_CreateInsertNode(rootBk, x);
        }
        Bk.close();
    }
}
void writeDataFile_BookTree(bookTree &rootBk)
{
    if (rootBk != NULL)
    {
        fstream Bk("D:\\book.txt", ios::out | ios::app);
        Bk << rootBk->bk.idBook << ' ' << rootBk->bk.nameBook << ',' << rootBk->bk.authorBook << ','
           << rootBk->bk.placeBook << ' ' << rootBk->bk.isRent << '\n';
        Bk.close();
        writeDataFile_BookTree(rootBk->left);
        writeDataFile_BookTree(rootBk->right);
    }
}
// Copy data from tree to Struct array

void bookTree_toArray(bookTree &rootBk, Book a[])
{
    if (rootBk == NULL)
    {
        return;
    }

    a[pos++] = rootBk->bk;
    bookTree_toArray(rootBk->left, a);
    bookTree_toArray(rootBk->right, a);
}
int bookTree_Size(bookTree &rootBk)
{
    if (rootBk == NULL)
        return 0;
    else
        return bookTree_Size(rootBk->left) + bookTree_Size(rootBk->right) + 1;
}
// Bubble Sort
void book_bubbleSort(Book arr[], int n)
{
    int i, j;
    bool haveSwap = false;
    for (i = 0; i < n - 1; i++)
    {
        haveSwap = false;
        for (j = n - 1; j > i; j--)
        {
            if (arr[j].nameBook.compare(arr[j - 1].nameBook) < 0)
            {
                swap(arr[j], arr[j - 1]);
                haveSwap = true;
            }
        }
        if (haveSwap == false)
        {
            break;
        }
    }
}

bool compareChar(char &c1, char &c2)
{
    if (c1 == c2)
        return true;
    else if (toupper(c1) == toupper(c2))
        return true;
    return false;
}
/*
 * Case Insensitive String Comparision
 */
bool caseInSensStringCompare(string &str1, string &str2)
{
    return ((str1.size() == str2.size()) &&
            equal(str1.begin(), str1.end(), str2.begin(), &compareChar));
}

// Book Main Function
void bookAdd(bookTree &rootBk) // Add Struct Student to 1 node in Student tree
{
    Book x;
    while (true)
    {
        cout << "*Input Book Info*\n";
        x = bookInput(rootBk);
        if (x.idBook == -1)
            break; // Cancel Add Book
        int check = book_CreateInsertNode(rootBk, x);
        if (check == -1)
            cout << "***This ID Book is already existed in Book List***\n\n";
        else if (check == 0)
            cout << "***Memory is full***" << endl;
        else
            cout << "***Add Book Successfully***\n\n";
    }
}
int bookDelete(bookTree &rootBk, long long x) // Delete Book
{
    if (rootBk == NULL)
    {
        return 0;
    }
    // Leaf node
    else if (rootBk->bk.idBook > x)
        return bookDelete(rootBk->left, x);
    else if (rootBk->bk.idBook < x)
        return bookDelete(rootBk->right, x);
    else // rootBk->bk.idBook == x (found)
    {
        NodeBk *p = rootBk;
        if (rootBk->left == NULL)
            rootBk = rootBk->right; // Node only have right subtree
        else if (rootBk->right == NULL)
            rootBk = rootBk->left; // Node only have left subtree

        else // Node have 2 subtree
        {
            NodeBk *s = rootBk, *q = s->left;
            // s is parent of q, q is rightest node of left subtree of p
            while (q->right != NULL)
            {
                s = q;
                q = q->right;
            }
            p->bk = q->bk;
            s->right = q->left;
            delete q;
        }
    }
    return 1;
}
void bookUpdate(bookTree &rootBk, long long x) // Update Book
{
    bookTree p = bookFind_ByID(rootBk, x);
    string keyword;

    if (p != NULL)
    {
        cout << "*Book is found!*" << endl;
        cout << "Input keyword to update:\n";
        cout << "1. name\n2. author\n3. location\n4. rent\nInput keyword: ";

        cin >> keyword;
        cin.ignore();
        if (keyword == "name")
        {
            cout << "\nBook Name before change: " << p->bk.nameBook << "\n\n";
            cout << "Re-Input Book Name: ";
            getline(cin, p->bk.nameBook);
            cout << "\n*Update Book Name successfully.*\n";
        }
        else if (keyword == "author")
        {
            cout << "\nBook Author before change: " << p->bk.authorBook << "\n\n";
            cout << "Re-Input Author Name: ";
            getline(cin, p->bk.authorBook);
            cout << "\n*Update Author Name successfully.*\n";
        }
        else if (keyword == "location")
        {
            cout << "\nBook Location before change: " << p->bk.placeBook << "\n\n";
            cout << "Re-Input Book Location: ";
            cin >> p->bk.placeBook;
            cin.ignore();
            cout << "\n*Update Book Location successfully.*\n";
        }
        else if (keyword == "rent")
        {
            cout << "\nBook Status before change: " << p->bk.isRent << "\n\n";
            cout << "Re-Input Rent Status: ";
            cin >> p->bk.isRent;
            cin.ignore();
            cout << "\n*Update Rent Status successfully.*\n";
        }
        else
        {
            cout << "*Invalid keyword*\n";
        }
    }
    else
    {
        cout << "*ID book not found!*" << endl;
    }
}
bookTree bookFind_ByID(bookTree &rootBk, long long x) // Find Book By ID
{
    NodeBk *p = rootBk;
    if (p != NULL)
    {
        if (x == p->bk.idBook)
            return p; // Found node p with key x
        if (x < p->bk.idBook)
            return bookFind_ByID(p->left, x); // Find next at left
        if (x > p->bk.idBook)
            return bookFind_ByID(p->right, x); // Find next at right

        return NULL;
    }
    else
        return NULL; // Node with key x not found
}

void view_bookFind_ByID(bookTree &rootBk) // View Book is found By ID
{
    long long x;
tryagain:
    cout << "Input ID Book to find (-1 to cancel): ";

    cin >> x;
    cin.ignore();
    if (cin.fail())
    {
        cout << "CAUTIONS: Invalid input -> Try again.\n\n";
        cin.clear();
        cin.ignore();
        goto tryagain;
    }
    if (x < 0 && x != -1)
    {
        cout << "*Invalid Book ID. Try again*\n\n";
        goto tryagain;
    }
    if (x == -1)
    {
        cout << "*Cancel successfully!*\n";
        return; // Cancel input
    }
    bookTree temp = bookFind_ByID(rootBk, x);
    if (temp != NULL)
    {
        cout << setw(15) << left << "Book ID";
        cout << setw(30) << left << "Book Name";
        cout << setw(30) << left << "Book Author";
        cout << setw(20) << left << "Book Location";
        cout << setw(15) << right << "Rent Status" << endl;

        cout << setfill('-');
        cout << setw(110) << '-' << endl;
        // reset fill
        cout << setfill(' ');
        bookOutput(temp->bk);
    }
    else
    {
        cout << "*ID Book not found!*\n";
    }
}
void view_bookFind_ByName(bookTree &rootBk) // View Book is found by name
{
    if (rootBk != NULL)
    {
        string x;
    tryagain:
        cout << "Input Book Name to find (\"exit\" to cancel): ";
        getline(cin, x);
        cout << endl;
        if (cin.fail())
        {
            cout << "CAUTIONS: Invalid input -> Try again.\n\n";
            cin.clear();
            cin.ignore();
            goto tryagain;
        }
        if (x.compare("exit") == 0)
        {
            cout << "*Cancel successfully!*\n";
            return; // Cancel input
        }
        int bk_size = bookTree_Size(rootBk);
        Book *a = new Book[bk_size];
        bookTree_toArray(rootBk, a);
        bool check_print = true, check_notfound = true;
        for (int i = 0; i < bk_size; i++)
        {
            bool result = caseInSensStringCompare((a + i)->nameBook, x);
            if (result)
            {
                if (check_print)
                {
                    cout << setw(15) << left << "Book ID";
                    cout << setw(30) << left << "Book Name";
                    cout << setw(30) << left << "Book Author";
                    cout << setw(20) << left << "Book Location";
                    cout << setw(15) << right << "Rent Status" << endl;

                    cout << setfill('-');
                    cout << setw(110) << '-' << endl;
                    // reset fill
                    cout << setfill(' ');
                }
                bookOutput(a[i]);
                check_print = false;
                check_notfound = false;
            }
        }
        if (check_notfound)
        {
            cout << "\n*Book Name not found!*\n";
        }
        delete[] a;
    }
    else
    {
        cout << "\n*There is no Book Info to find*\n";
    }
}
// View Book List (Default)
void bookView(bookTree &rootBk) // NLR - Node left right - PreOrder
{
    if (rootBk != NULL)
    {
        bookOutput(rootBk->bk);
        bookView(rootBk->left);
        bookView(rootBk->right);
    }
}
// View Book List (Sorted by Book Name)
void bookViewSortedByName(bookTree &rootBk)
{
    if (rootBk != NULL)
    {
        int bk_size = bookTree_Size(rootBk);
        Book *a = new Book[bk_size];
        bookTree_toArray(rootBk, a);
        book_bubbleSort(a, bk_size);
        cout << "***Book list (Sorted by Book Name)***\n";
        for (int i = 0; i < bk_size; i++)
            bookOutput(a[i]);
        delete[] a;
    }
    else
    {
        cout << "\n*There is no Book Info to view*\n";
    }
}
void bookProgram(bookTree &rootBk)
{
    system("cls");
    Book x;

    int choice;
    int confirm;
    do
    {
        system("cls");
    doagain_book:
        menuBook();
        cout << "\nInput your choice (1-7): ";
        cin >> choice;
        cin.ignore();
        if (cin.fail())
        {
            cout << "CAUTIONS: Invalid input -> Try again.\n\n";
            cin.clear();
            cin.ignore();
            goto doagain_book;
        }
        if (choice == 1)
        {
            bookAdd(rootBk);
        }
        else if (choice == 2)
        {
            long long x;
        inputagain:
            cout << "Input ID Book to delete (-1 to cancel): ";
            cin >> x;
            cin.ignore();
            if (cin.fail())
            {
                cout << "CAUTIONS: Invalid input -> Try again.\n\n";
                cin.clear();
                cin.ignore();
                goto inputagain;
            }
            if (x < 0 && x != -1)
            {
                cout << "*Invalid Book ID. Try again*\n\n";
                goto inputagain;
            }

            if (x == -1)
            {
                cout << "*Cancel successfully!*\n";
            }
            if (x >= 0 && x != -1)
            {
                bookTree p = bookFind_ByID(rootBk, x);
                if (p != NULL)
                {
                    int del = 1;
                    while (del)
                    {
                        if (p != NULL)
                        {
                            del = bookDelete(rootBk, x);
                        }
                        else
                        {
                            cout << "No data!" << endl;
                            del = 0;
                        }
                    }
                    cout << "*Book is deleted successfully!*" << endl;
                }
                else
                {
                    cout << "*ID Book not found!*" << endl;
                }
            }
        }
        else if (choice == 3)
        {
            long long lib;
            cout << "Update Book Info\n";
        reinput:
            cout << "Input ID Book to update (-1 to cancel): ";
            cin >> lib;
            cin.ignore();
            if (cin.fail())
            {
                cout << "CAUTIONS: Invalid input -> Try again.\n\n";
                cin.clear();
                cin.ignore();
                goto reinput;
            }
            if (lib == -1)
            {
                cout << "*Cancel successfully!*\n";
            }
            if (lib < 0 && lib != -1)
            {
                cout << "*Invalid Book ID. Try again*\n\n";
                goto reinput;
            }
            if (lib >= 0 && lib != -1)
                bookUpdate(rootBk, lib);
        }
        else if (choice == 4)
        {
            system("cls");
            int opt_find;
        doagain_find:
            menuFind();
            cout << "\nInput your choice (1-2): ";
            cin >> opt_find;
            cin.ignore();
            if (cin.fail())
            {
                cout << "CAUTIONS: Invalid input -> Try again.\n\n";
                cin.clear();
                cin.ignore();
                goto doagain_find;
            }
            if (opt_find == 1)
            {
                view_bookFind_ByID(rootBk);
            }
            else if (opt_find == 2)
            {
                pos = 0;
                view_bookFind_ByName(rootBk);
            }
            else if (opt_find == 0)
            {
                cout << "*Exit successfully!*\n";
            }
            else
            {
                cout << "*Your choice is invalid. Try again please!*\n\n";
                goto doagain_find;
            }
        }
        else if (choice == 5)
        {
            cout << "***Book list (Default By Book ID)***\n";
            cout << setw(15) << left << "Book ID";
            cout << setw(30) << left << "Book Name";
            cout << setw(30) << left << "Book Author";
            cout << setw(20) << left << "Book Location";
            cout << setw(15) << right << "Rent Status" << endl;

            cout << setfill('-');
            cout << setw(110) << '-' << endl;
            // reset fill
            cout << setfill(' ');
            bookView(rootBk);
        }
        else if (choice == 6)
        {
            pos = 0;
            cout << "***Book list (Sort By Book Name)***\n";
            cout << setw(15) << left << "Book ID";
            cout << setw(30) << left << "Book Name";
            cout << setw(30) << left << "Book Author";
            cout << setw(20) << left << "Book Location";
            cout << setw(15) << right << "Rent Status" << endl;

            cout << setfill('-');
            cout << setw(110) << '-' << endl;
            // reset fill
            cout << setfill(' ');
            bookViewSortedByName(rootBk);
        }
        else if (choice == 7)
        {
            remove("D:\\book.txt");
            writeDataFile_BookTree(rootBk);
            cout << "\n*Save data successfully*" << endl;
        }
        else if (choice == 0)
        {
            cout << "*Exit successfully!*\n";
        }
        else
        {
            cout << "*Invalid choice -> Try again.*\n\n";
            goto doagain_book;
        }
    confirm_again:
        cout << "\nContinue with Book? Yes[1]/No[0]: ";
        cin >> confirm;
        cin.ignore();
        if (cin.fail())
        {
            cout << "CAUTIONS: Invalid input -> Try again.\n\n";
            cin.clear();
            cin.ignore();
            goto confirm_again;
        }
        if (confirm != 0 && confirm != 1)
        {
            cout << "*Your choice is invalid. Try again please!*\n\n";
            goto confirm_again;
        }
    } while (confirm == 1);
}

// =================================================================
// RENT MANAGEMENT
int rent_CreateInsertNode(rentTree &rootRl, RentLib x) // Create and Insert Node
{
    if (rootRl != NULL)
    {
        if (rootRl->rl.rentStudent.idLib == x.rentStudent.idLib)
            return -1; // Node existed
        else if (rootRl->rl.rentStudent.idLib > x.rentStudent.idLib)
            return rent_CreateInsertNode(rootRl->left, x); // Chen node left
        else
            return rent_CreateInsertNode(rootRl->right, x); // Chen node right
    }
    rootRl = new NodeRl[1];
    if (rootRl == NULL)
        return 0; // Bo nho Full
    rootRl->rl = x;
    rootRl->left = rootRl->right = NULL;
    return 1;
}

// Input and output Rent info
int dateValidate(int dd, int mm, int yy)
{
    if (mm >= 1 && mm <= 12 && yy > 0 && dd > 0)
    {
        if ((dd >= 1 && dd <= 31) && (mm == 1 || mm == 3 || mm == 5 || mm == 7 || mm == 8 || mm == 10 || mm == 12))
            ;
        else if ((dd >= 1 && dd <= 30) && (mm == 4 || mm == 6 || mm == 9 || mm == 11))
            ;
        else if ((dd >= 1 && dd <= 28) && (mm == 2))
            ;
        else if (dd == 29 && mm == 2 && (yy % 400 == 0 || (yy % 4 == 0 && yy % 100 != 0)))
            ;
        else
            return 0;
        return 1;
    }
    else
    {
        return 0;
    }
}
RentLib rentInput(studentTree &rootSt, bookTree &rootBk, rentTree &rootRl)
{
    RentLib x;
again_idLib:
    cout << "Library ID (-1 to cancel): ";
    cin >> x.rentStudent.idLib;
    cin.ignore();
    if (cin.fail())
    {
        cout << "CAUTIONS: Invalid input -> Try again.\n\n";
        cin.clear();
        cin.ignore();
        goto again_idLib;
    }
    if (x.rentStudent.idLib == -1)
    {
        cout << "*Cancel successfully!*\n";
        return x; // Cancel input
    }
    if (studentFind(rootSt, x.rentStudent.idLib) == NULL) // Not existed in Student List
    {
        cout << "\n***This ID Library is not existed in Student List. Try again.\n";
        goto again_idLib;
    }
    if (rentFind(rootRl, x.rentStudent.idLib) != NULL)
    {
        cout << "\n***This ID Library is existed in Rent List."
             << "\n***System recommends you using Update instead\n***Please try again or cancel.\n";
        goto again_idLib;
    }
    if (x.rentStudent.idLib < 0 && x.rentStudent.idLib != -1)
    {
        cout << "***\nInvalid library ID. Try again\n\n";
        goto again_idLib;
    }

again_quantity:
    cout << "Quantity: ";
    cin >> x.quantity;
    if (x.quantity <= 0)
    {
        cout << "\n***Quantity must > 0. Try again.\n";
        goto again_quantity;
    }
    for (int i = 0; i < x.quantity; i++)
    {
    again_book:
        cout << "ID Book " << i + 1 << " (-1 to cancel): ";
        cin >> x.rentBook.idBook;
        cin.ignore();
        if (cin.fail())
        {
            cout << "CAUTIONS: Invalid input -> Try again.\n\n";
            cin.clear();
            cin.ignore();
            goto again_book;
        }
        if (x.rentBook.idBook == -1)
        {
            cout << "*Cancel successfully!*\n";
            return x; // Cancel input
        }
        bookTree p = bookFind_ByID(rootBk, x.rentBook.idBook);
        if (p == NULL)
        {
            cout << "\n***This ID Book is not existed in Book List. Try again.\n";
            goto again_book;
        }
        else
        {
            if (p->bk.isRent != 0)
            {
                cout << "\n*This book is already rented. Try again.*\n\n";
                goto again_book;
            }
            else
            {
                p->bk.isRent = 1;
                remove("D:\\book.txt");
                writeDataFile_BookTree(rootBk);
            }
        }

        if (i == x.quantity - 1)
            x.total += to_string(x.rentBook.idBook);
        else
            x.total += to_string(x.rentBook.idBook) + "-";
    }
again_dateRent:
    cout << "Date rent: ";
    cin >> x.rentDate.day >> x.rentDate.month >> x.rentDate.year;
    cin.ignore();
    if (dateValidate(x.rentDate.day, x.rentDate.month, x.rentDate.year) == 0)
    {
        cout << "\n*Invalid date rent. Try again.*\n";
        goto again_dateRent;
    }
again_dateReturn:
    cout << "Date return: ";
    cin >> x.returnDate.day >> x.returnDate.month >> x.returnDate.year;
    cin.ignore();
    if (dateValidate(x.returnDate.day, x.returnDate.month, x.returnDate.year) == 0)
    {
        cout << "\n*Invalid date return. Try again.*\n";
        goto again_dateReturn;
    }
    if (x.returnDate.day <= x.rentDate.day || x.returnDate.month < x.rentDate.month || x.returnDate.year < x.rentDate.year)
    {
        cout << "\n*Date return must > date rent. Try again.*\n";
        goto again_dateReturn;
    }
    return x;
}
void rentOutput(RentLib x)
{
    cout << setw(15) << left << x.rentStudent.idLib;
    cout << setw(15) << left << x.quantity;
    cout << setw(30) << left << x.total;
    cout << setw(15) << left << to_string(x.rentDate.day) + '/' + to_string(x.rentDate.month) + '/' + to_string(x.rentDate.year);
    cout << setw(15) << right << to_string(x.returnDate.day) + '/' + to_string(x.returnDate.month) + '/' + to_string(x.returnDate.year) << endl;
}

// Read and write between Rent Tree and renLib.txt
void readDataFile_RentTree(rentTree &rootRl)
{
    RentLib x;
    fstream Rl("D:\\rentLib.txt", ios::in);
    char c;
    if (Rl)
    {
        while (!Rl.eof())
        {
            Rl >> x.rentStudent.idLib;
            Rl >> x.quantity;
            Rl >> x.total;
            Rl >> x.rentDate.day >> x.rentDate.month >> x.rentDate.year;
            Rl >> x.returnDate.day >> x.returnDate.month >> x.returnDate.year;
            Rl.get(c);
            rent_CreateInsertNode(rootRl, x);
        }
        Rl.close();
    }
}
void writeDataFile_RentTree(rentTree &rootRl)
{
    if (rootRl != NULL)
    {
        fstream Rl("D:\\rentLib.txt", ios::out | ios::app);
        Rl << rootRl->rl.rentStudent.idLib << ' ' << rootRl->rl.quantity << ' '
           << rootRl->rl.total << ' '
           << rootRl->rl.rentDate.day << ' '
           << rootRl->rl.rentDate.month << ' '
           << rootRl->rl.rentDate.year << ' '
           << rootRl->rl.returnDate.day << ' '
           << rootRl->rl.returnDate.month << ' '
           << rootRl->rl.returnDate.year << '\n';
        Rl.close();
        writeDataFile_RentTree(rootRl->left);
        writeDataFile_RentTree(rootRl->right);
    }
}
void rentAdd(studentTree &rootSt, bookTree &rootBk, rentTree &rootRl) // Add Struct rent to 1 node in rent tree
{
    RentLib x;
    while (true)
    {
        cout << "Input Rent Info\n";
        x = rentInput(rootSt, rootBk, rootRl);
        if (x.rentStudent.idLib == -1 || x.rentBook.idBook == -1)
            break; // Cancel Add Rent
        int check = rent_CreateInsertNode(rootRl, x);
        if (check == -1)
            cout << "***This ID Library is already existed in Rent List***\n\n";
        else if (check == 0)
            cout << "***Memory is full***" << endl;
        else
            cout << "***Add Rent Successfully***\n\n";
    }
}
int rentDelete(rentTree &rootRl, long long x) // Delete Rent
{
    if (rootRl == NULL)
    {
        // cout << "ID Book not found!\n";
        return 0;
    }
    // Leaf node
    else if (rootRl->rl.rentStudent.idLib > x)
        return rentDelete(rootRl->left, x);
    else if (rootRl->rl.rentStudent.idLib < x)
        return rentDelete(rootRl->right, x);
    else
    {
        NodeRl *p = rootRl;
        if (rootRl->left == NULL)
            rootRl = rootRl->right; // Node only have right subtree
        else if (rootRl->right == NULL)
            rootRl = rootRl->left; // Node only have left subtree

        else // Node have 2 subtree
        {
            NodeRl *s = rootRl, *q = s->left;
            // s is parent of q, q is rightest node of left subtree of p
            while (q->right != NULL)
            {
                s = q;
                q = q->right;
            }
            p->rl = q->rl;
            s->right = q->left;
            delete q;
        }
    }
    return 1;
}
void rentUpdate(rentTree &rootRl, long long lib) // Update Rent
{
    rentTree p = rentFind(rootRl, lib);
    string keyword;

    if (p != NULL)
    {
        cout << "Rent is found!" << endl;
        cout << "Input keyword to update:\n";
        cout << "1. idLib\n2. qtotal (quantity & total)\n3. drent\n4. dreturn\n\nInput keyword:";
        cout << "Keyword: ";

        cin >> keyword;
        cin.ignore();
        if (keyword == "idLib")
        {
            cout << "ID library before change: " << p->rl.rentStudent.idLib << "\n\n";
            cout << "Re-Input ID Library: ";
            cin >> p->rl.rentStudent.idLib;
            cin.ignore();
            cout << "\n*Update ID Library successfully.*\n";
        }
        else if (keyword == "qtotal")
        {
            cout << "Quantity before change: " << p->rl.quantity
                 << "\nTotal Book Rented before change: " << p->rl.total << "\n\n";
            cout << "Re-Input Quantity: ";
            cin >> p->rl.quantity;
            cout << "Re-Input Total Book Rented: ";
            cin >> p->rl.total;
            cout << "\n*Update Quantity & Total Book Rent successfully.*\n";
        }
        else if (keyword == "drent")
        {
            cout << "Date Rent before change: " << p->rl.rentDate.day << ' '
                 << p->rl.rentDate.month << ' ' << p->rl.rentDate.year << "\n\n";
            cout << "Re-Input Date Rent: ";
            cin >> p->rl.rentDate.day >> p->rl.rentDate.month >> p->rl.rentDate.year;
            cout << "\n*Update Date Rent successfully.*\n";
        }
        else if (keyword == "dreturn")
        {
            cout << "Date Return before change: " << p->rl.returnDate.day << ' '
                 << p->rl.returnDate.month << ' ' << p->rl.returnDate.year << "\n\n";
            cout << "Re-Input Date Return: ";
            cin >> p->rl.returnDate.day >> p->rl.returnDate.month >> p->rl.returnDate.year;
            cout << "\n*Update Date Return successfully.*\n";
        }
        else
        {
            cout << "*Invalid keyword*\n";
        }
    }
    else
    {
        cout << "*ID library not found!*" << endl;
    }
}
rentTree rentFind(rentTree &rootRl, long long x) // Find Rent
{
    NodeRl *p = rootRl;
    if (p != NULL)
    {
        if (x == p->rl.rentStudent.idLib)
            return p; // Found node p with key x
        if (x < p->rl.rentStudent.idLib)
            return rentFind(p->left, x); // Find next at left
        if (x > p->rl.rentStudent.idLib)
            return rentFind(p->right, x); // Find next at right

        return NULL;
    }
    else
        return NULL; // Node with key x not found
}
void view_rentFind(rentTree &rootRl) // View Rent is found
{
    long long x;
tryagain:
    cout << "Input ID Library to find (-1 to cancel): ";
    cin >> x;
    cin.ignore();
    if (cin.fail())
    {
        cout << "CAUTIONS: Invalid input -> Try again.\n\n";
        cin.clear();
        cin.ignore();
        goto tryagain;
    }
    if (x < 0 && x != -1)
    {
        cout << "*Invalid Library ID. Try again*\n\n";
        goto tryagain;
    }
    if (x == -1)
    {
        cout << "*Cancel successfully!*\n";
        return; // Cancel input
    }
    rentTree temp = rentFind(rootRl, x);
    if (temp != NULL)
    {
        cout << setw(15) << left << "Library ID";
        cout << setw(15) << left << "Quantity";
        cout << setw(30) << left << "Total Book ID Rented";
        cout << setw(15) << left << "Date Rent";
        cout << setw(15) << right << "Date Return" << endl;

        cout << setfill('-');
        cout << setw(90) << '-' << endl;
        // reset fill
        cout << setfill(' ');
        rentOutput(temp->rl);
    }
    else
    {
        cout << "\n*ID Library not found!*\n";
    }
}
// View Rent List (Default)
void rentView(rentTree &rootRl) // NLR - Node left right - PreOrder
{
    if (rootRl != NULL)
    {
        rentOutput(rootRl->rl);
        rentView(rootRl->left);
        rentView(rootRl->right);
    }
}
void rentProgram(studentTree &rootSt, bookTree &rootBk, rentTree &rootRl)
{
    system("cls");
    RentLib x;

    int choice;
    int confirm;
    do
    {
        system("cls");
    doagain_rent:
        menuRent();
        cout << "\nInput your choice (1-6): ";
        cin >> choice;
        cin.ignore();
        if (cin.fail())
        {
            cout << "CAUTIONS: Invalid input -> Try again.\n\n";
            cin.clear();
            cin.ignore();
            goto doagain_rent;
        }
        if (choice == 1)
        {
            rentAdd(rootSt, rootBk, rootRl);
        }
        else if (choice == 2)
        {
            long long x;
        inputagain:
            cout << "Input ID Library to delete (-1 to cancel): ";
            cin >> x;
            cin.ignore();
            if (cin.fail())
            {
                cout << "CAUTIONS: Invalid input -> Try again.\n\n";
                cin.clear();
                cin.ignore();
                goto inputagain;
            }
            if (x < 0 && x != -1)
            {
                cout << "*Invalid Library ID. Try again*\n\n";
                goto inputagain;
            }

            if (x == -1)
            {
                cout << "*Cancel successfully!*\n";
            }
            if (x >= 0 && x != -1)
            {
                rentTree p = rentFind(rootRl, x);
                if (p != NULL)
                {
                    int del = 1;
                    while (del)
                    {
                        if (p != NULL)
                        {
                            del = rentDelete(rootRl, x);
                        }
                        else
                        {
                            cout << "*No data!*" << endl;
                            del = 0;
                        }
                    }
                    cout << "*Rent Student is deleted successfully!*" << endl;
                }
                else
                {
                    cout << "*ID Library not found!*" << endl;
                }
            }
        }
        else if (choice == 3)
        {
            long long lib;
            cout << "*Update Rent Info*\n";
        reinput:
            cout << "Input ID Library to update (-1 to cancel): ";
            cin >> lib;
            cin.ignore();
            if (cin.fail())
            {
                cout << "CAUTIONS: Invalid input -> Try again.\n\n";
                cin.clear();
                cin.ignore();
                goto reinput;
            }
            if (lib == -1)
            {
                cout << "*Cancel successfully!*\n";
            }
            if (lib < 0 && lib != -1)
            {
                cout << "*Invalid Library ID. Try again*\n\n";
                goto reinput;
            }
            if (lib >= 0 && lib != -1)
                rentUpdate(rootRl, lib);
        }
        else if (choice == 4)
        {
            view_rentFind(rootRl);
        }
        else if (choice == 5)
        {
            cout << "***Rent list (Default By Library ID)***\n";
            cout << setw(15) << left << "Library ID";
            cout << setw(15) << left << "Quantity";
            cout << setw(30) << left << "Total Book ID Rented";
            cout << setw(15) << left << "Date Rent";
            cout << setw(15) << right << "Date Return" << endl;

            cout << setfill('-');
            cout << setw(90) << '-' << endl;
            // reset fill
            cout << setfill(' ');
            rentView(rootRl);
        }
        else if (choice == 6)
        {
            remove("D:\\rentLib.txt");
            writeDataFile_RentTree(rootRl);
            cout << "\n*Save data successfully*" << endl;
        }
        else if (choice == 0)
        {
            cout << "*Exit successfully!*\n";
        }
        else
        {
            cout << "*Invalid choice -> Try again.*\n\n";
            goto doagain_rent;
        }
    confirm_again:
        cout << "\nContinue with Rent? Yes[1]/No[0]: ";
        cin >> confirm;
        cin.ignore();
        if (cin.fail())
        {
            cout << "CAUTIONS: Invalid input -> Try again.\n\n";
            cin.clear();
            cin.ignore();
            goto confirm_again;
        }
        if (confirm != 0 && confirm != 1)
        {
            cout << "*Your choice is invalid. Try again please!*\n\n";
            goto confirm_again;
        }
    } while (confirm == 1);
}