#include <iostream>
#include <conio.h> // for password input as *
#include <fstream>
#define maxlim 20 // The maximum data that will be stored in .txt file is set limit 20 rows
using namespace std;

string acc_in_use; // When user is authenticated, his account number will be stored in it and this can be used anywhere

string data[maxlim][4]; // Whole .txt file data will be stored in this when import_data() is called and this is global.
int rows = 0;           // rows are calculated and stored in this for later use in for loops in iterating 2D array
void import_data()
{
    data[maxlim][4]; // initializing array in which we will import data

    ifstream file;                      // it must be ifstream not fstream
    file.open("backend.txt", ios::app); // set file name and ios::app will not overwrite file while writing it again

    rows = 0;               // declaring rows
    while (file.eof() == 0) // reading file till end of file
    {
        string temp_row = "";
        getline(file, temp_row); // take line 1 of file as input in temp_row
        if (temp_row == "")      // if it is empty row you will skip to next row
        {
            rows++;
            continue;
        }
        int column = 0;
        string temp_col = "";
        for (int j = 0; j < temp_row.length(); j++) // breaking row that we input into different values
        {
            if (temp_row[j] != ',') // if , does not occur keep adding character in temp_row
            {
                temp_col += temp_row[j];
            }
            else // if , occur save temp_row into 2D array
            {
                data[rows][column] = temp_col;
                temp_col = ""; // empty temp_col
                column++;
            }
        }
        rows++;
        if (rows == maxlim) // if rows become equal to max limit, decrease row by one, show error message, break
        {
            rows--;
            cout << "%%%%% (Error) %%%%%%%%%%% (Maximum memory reached)%%%%%%%%%%%" << endl;
            break;
        }
    }
    file.close(); // closing file
}

template <typename T> // for input for every datatype except string with spaces
T input(string x);
string input(string x); // for input of string with spaces
string new_password();
int isAmount(int x);
void new_account();
void data_update();
void existing();
bool authentication();
string input_password(string x);
int show_balance();
int deposit();
int withdraw();
void balance_updation(int balance);

int main()
{
    int choice;
    cout << "\n%%%%%%%%%(Welcome to the Superior ATM system)%%%%%%%%%\n";
    cout << "\nPress Enter to Insert the ATM Card\n";
    cin.ignore(); // no matter what user enter, if he hit enter compiler will ignore everything and move on

    do
    {
        cin.clear();
        fflush(stdin);

        cout << "________________________________\n";
        cout << "|---------( Main Page )--------|\n";
        cout << "| Choose one of the following: |\n";
        cout << "********************************\n";
        cout << "| 1: Activate your card        |\n";
        cout << "| 2: Existing account          |\n";
        cout << "| 3: Eject your card           |\n";
        cout << "********************************\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            system("cls"); // to clear console
            new_account();
            break;
        case 2:
            system("cls");
            existing();
            break;
        case 3:
            system("cls");
            cout << "\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
            cout << "%% (Thanks for using our ATM service) %%\n";
            cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n\n";
            break;

        default:
            system("cls");
            cout << "Invalid Input\n";
            break;
        }

    } while (choice != 3);

    return 0;
}

void new_account()
{
    string account_number = input("Enter your account number: ");
    import_data(); // importing data in global 2D array

    for (int i = 0; i <= rows; i++)
    {
        int j = 0;

        if (data[i][j] == account_number)
        {
            cout << "Card is already activated\nPlease Enter Password instead\n";
            return; // to exit void function
        }
    }

    string name = input("Enter your name: ");
    string password = new_password();
    int balance = isAmount(input<int>("Enter the amount you want to deposite: Rs."));

    ofstream backend;
    backend.open("backend.txt", ios::app);
    backend << '\n' // this is necessary bcz otherwise data will be saved in the same line and you can't also put it at end of line
            << account_number << ',' << name << ',' << password << ',' << balance << ',';
}

template <typename T>
T input(string x)
{
    T y;
    cout << x;
    cin >> y;
    return y;
}
string input(string x)
{
    string y;
    cout << x;
    getline(cin >> ws, y);
    return y;
}
string new_password()
{
    string pass = "";
    string confirm_pass = "";
    do
    {
        pass = input_password("Set a new password: ");
        cout << endl;
        
        confirm_pass = input_password("Confirm password: ");
        cout << endl;
        if (pass == confirm_pass)
        {
            return pass; // if password match, get out of function
        }
        cout << "Incorrect password\n";

    } while (pass != confirm_pass);
    return ""; // it has nothing to do with code but I have just written it so that compiler does not give warning
}
int isAmount(int x)
{
    if (x < 0) // If user enter amount with negative sign
    {
        cout << "This is not a valid amount\n";
        return 0;
    }
    else
    {
        return x;
    }
}

void existing()
{
    if (authentication() == false)
    {
        return; // this is used to escape void function
    }
    int balance;
    int choice;
    do
    {
        cin.clear();
        fflush(stdin);

        for (int i = 0, j = 0; i < rows; i++) // printing username
        {
            if (data[i][j] == acc_in_use)
            {
                cout << "Welcome " << data[i][1] << endl;
            }
        }

        cout << "________________________________\n";
        cout << "|-----( Transaction Page )-----|\n";
        cout << "| Choose one of the following: |\n";
        cout << "********************************\n";
        cout << "| 1: Cash deposite             |\n";
        cout << "| 2: Cash withdrawal           |\n";
        cout << "| 3: Show Balance              |\n";
        cout << "| 4: Exit                      |\n";
        cout << "********************************\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            system("cls");
            import_data();
            balance = show_balance();
            balance += deposit();
            balance_updation(balance);
            data_update();

            break;
        case 2:
            system("cls");
            import_data();
            balance = show_balance();
            balance -= withdraw();
            balance_updation(balance);
            data_update();

            break;
        case 3:
            system("cls");
            import_data();
            cout << "Balance: Rs." << show_balance() << endl;
            break;

        case 4:
            system("cls");
            break;

        default:
            system("cls");
            cout << "Invalid Input\n";
            break;
        }

    } while (choice != 4);
}

bool authentication()
{
    import_data();
    string acc_num = input("Enter your account number: ");
    int acc_check = 0;
    for (int i = 0, j = 0; i < rows; i++)
    {
        if (data[i][j] == acc_num)
        {
            acc_in_use = data[i][j];
            acc_check++;
        }
    }
    if (acc_check == 0)
    {
        system("cls");
        cout << "Record not found!\nPlease activate your card instead\n";
        return false;
    }
    else if (acc_check == 1)
    {
        string pass = input_password("Enter your password: ");
        cout << endl;
        int pass_check = 0;
        for (int i = 0, j = 2; i < rows; i++)
        {
            if (data[i][j] == pass)
            {
                pass_check++;
            }
        }
        if (pass_check == 1)
        {
            system("cls");
            return true;
        }
        else if (pass_check == 0)
        {
            system("cls");
            cout << "Invalid Password\n";
            return false;
        }
    }
    return true;
}

string input_password(string x)
{
    char password[15];
    int i = 0;
    char ch;
    cout << x;
    // Loop to read characters until Enter (ASCII 13) is pressed
    while ((ch = _getch()) != 13)
    {
        // Backspace (ASCII 8) handling
        if (ch == 8 && i > 0)
        {
            cout << "\b \b"; // Move the cursor back, print a space to erase the character, move the cursor back again
            i--;
        }
        else
        {
            password[i] = ch;
            i++;
            cout << "*"; // Display an asterisk (*) instead of the actual character
        }
    }
    password[i] = '\0'; // Null-terminate the password string

    return password;
}

int show_balance()
{
    int balance;
    for (int i = 0, j = 0; i < rows; i++)
    {
        if (data[i][j] == acc_in_use)
        {
            balance = stoi(data[i][3]);
        }
    }
    return balance;
}
int deposit()
{
    int balance = show_balance();
    cout << "Current balance: " << balance << endl;

    int money_dep = input<int>("Enter the amount you want to deposite: Rs.");
    if (money_dep < 0)
    {
        cout << "Invalid amount\n";
        return 0;
    }
    else
    {
        return money_dep;
    }
}
int withdraw()
{
    int balance = show_balance();
    cout << "Current balance: " << balance << endl;

    int withdrawal = input<int>("Enter the amount you want to withdraw: Rs.");
    if (withdrawal < 0)
    {
        cout << "Invalid amunt\n";
        return 0;
    }
    else if (withdrawal > balance)
    {
        cout << "You have insufficient balance\n";
        return 0;
    }
    else
    {
        return withdrawal;
    }
}
void balance_updation(int balance)
{
    for (int i = 0, j = 0; i < rows; i++)
    {
        if (data[i][j] == acc_in_use)
        {
            data[i][3] = to_string(balance);
        }
    }
}

void data_update() // export global 2D array to .txt file
{
    ofstream backend;
    backend.open("backend.txt");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            backend << data[i][j] << ',';
        }
        if (i < rows - 1) // if we dont do this after last row, an empty row will be added
        {
            backend << endl;
        }
    }
}
