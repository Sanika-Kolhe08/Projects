#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int bookID[100];
string title[100];

int countBooks = 0;
void SaveBooks()
{
    ofstream file("books.txt");

    for(int i = 0; i < countBooks; i++)
    {
        file << bookID[i] << endl;
        file << title[i] << endl;
    }

    file.close();
}

void LoadBooks()
{
    ifstream file("books.txt");

    while(file >> bookID[countBooks])
    {
        file.ignore();

        getline(file, title[countBooks]);

        countBooks++;
    }

    file.close();
}

int main()
{
    int choice;

    LoadBooks();

    do
    {
        cout << "\n1. Add Book";
        cout << "\n2. Display Books";
        cout << "\n3. Search Book";
        cout << "\n4. Delete Book";
        cout << "\n5. Exit";

        cout << "\nEnter choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
            {
                int newID;
                bool exists = false;

                cout << "\nEnter Book ID: ";
                cin >> newID;

                for(int i = 0; i < countBooks; i++)
                {
                    if(bookID[i] == newID)
                    {
                        exists = true;
                        break;
                     }
                }

                if(exists)
                {
                    cout << "\nBook ID already exists!\n";
                }
                else
                {
                    bookID[countBooks] = newID;

                    cin.ignore();

                    cout << "Enter Book Title: ";
                    getline(cin, title[countBooks]);

                    countBooks++;
                    SaveBooks();

                    cout << "\nBook Added Successfully!\n";
                }

                break;
            }

            case 2:
            {
            if(countBooks == 0)
            {
                 cout << "\nNo Books Available.\n";
            }
            else
            {
                cout << "\n----- BOOK LIST -----\n";

                for(int i = 0; i < countBooks; i++)
                {
                         cout << "\nBook ID: " << bookID[i];
                        cout << "\nBook Title: " << title[i] << endl;
            }
            }
            break;
            }
            case 3:
            {
                int searchID;
                bool found = false;

                cout << "\nEnter Book ID to Search: ";
                cin >> searchID;

                for(int i = 0; i < countBooks; i++)
                {
                    if(bookID[i] == searchID)
                    {
                        cout << "\nBook Found!";
                        cout << "\nBook ID: " << bookID[i];
                        cout << "\nBook Title: " << title[i] << endl;

                        found = true;
                        break;
                    }
                }

                if(found == false)
                {
                    cout << "\nBook Not Found!\n";
                }

                break;
                }

            case 4:
            {
                int deleteID;
                bool found = false;

                cout << "\nEnter Book ID to Delete: ";
                cin >> deleteID;

                for(int i = 0; i < countBooks; i++)
                {
                    if(bookID[i] == deleteID)
                    {
                        for(int j = i; j < countBooks - 1; j++)
                        {
                            bookID[j] = bookID[j + 1];
                            title[j] = title[j + 1];
                        }

                        countBooks--;
                        SaveBooks();
                        found = true;

                        cout << "\nBook Deleted Successfully!\n";
                        break;
                        }
                }

                if(found == false)
                {
                    cout << "\nBook Not Found!\n";
                }

                break;
            }

            case 5:
            {
                cout << "\nThank You\n";
                break;
            }


            default:
                cout << "\nInvalid Choice\n";
        }

    } while(choice != 5);

    return 0;
}
