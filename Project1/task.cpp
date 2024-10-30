#include <iostream>
#include <cmath>
#include <fstream>
#include <limits>
using namespace std;

double find_y(double x, int n);
int inputData(double& a, double& b, double& h, int& n);
void outputData(double a, double b, double h, int n);

int main() {
    double x;
    double y;
    double a, b, h;
    int n;
    int q;
    cout << "*****************************************************************************************************************************************************" << endl;
    cout << "***************************************************************FIND EQUATION OF Y********************************************************************" << endl;

    do {
        if (inputData(a, b, h, n) != 0) {

            return 1;
        }
        //inputData (x,n);

        //y=find_y(x, n);
        outputData(a, b, h, n);
        //cout<<"Result: "<<y<<endl;
        cout << "Continue? (yes=1/no=0): ";
        cin >> q;
    } while (q == 1);
    cout << "**********************************************************************END****************************************************************************";
    cout << "*****************************************************************************************************************************************************";
    return 0;

}
double find_y(double x, int n)
{
    long double y = 0.00;

    if (x < -5) {

        for (int i = -6; i <= n; i++) {
            y += i + x;

        }
        return 4 * x * y - 9;
    }
    else {
        //double product=1;
        for (int i = 0; i <= n + 1; i++) {
            double product = 1;

            for (int j = 0; j <= n - 3; j++) {
                product *= (i - 2 * j) / (4 + pow(x, 2));

            }
            y += product;
        }
        return y;
    }
}
int inputData(double& a, double& b, double& h, int& n)
{
    string FileName;
    char choice;
    string input;

    cout << "Choose way of reading data k/f:" << endl;
    cin >> choice;
    while (!(choice == 'f' || choice == 'F' || choice == 'k' || choice == 'K')) {
        cout << "Invalid choice. Please enter 'f' or 'F' for file, or 'k' or 'K' for keyboard: ";
        cin.clear(); // Clear error state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        cin >> choice;
    }

    if (choice == 'f' || choice == 'F')
    {
        while (true) {  // Додаємо цикл для повторного запиту назви файлу
            cout << "Enter file name: ";
            cin >> FileName;

            ifstream file;
            file.open(FileName);
            if (file.fail())
            {
                cout << "Error opening file! Try again." << endl;
            }
            else
            {
                file >> a >> b >> h >> n;
                cout << a << " " << b << " " << h << " " << n << endl;
                file.close();
                break;  // Виходимо з циклу, якщо файл успішно відкрився
            }
        }
    }
    else if (choice == 'k' || choice == 'K')
    {
        while (true) {
            cout << "Enter a: ";
            cin >> a;
            if (cin.fail()) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                cout << "Invalid input. Please enter a numeric value for a." << endl;
            }
            else {
                break;
            }
        }


        // Input validation for b
        while (true) {
            cout << "Enter b: ";
            cin >> b;
            if (cin.fail() || b <= a) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. 'b' must be an integer  value and greater than 'a'." << endl;
            }
            else {
                break;
            }
        }

        while (true) {
            cout << "Enter h (step): ";
            cin >> h;
            if (cin.fail() || h <= 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. 'h' must be a positive integer value." << endl;
            }
            else {
                break;
            }
        }

        while (true) {
            cout << "Enter n(>3): ";
            cin >> n;
            if (cin.fail() || n <= 3 || cin.peek() != '\n') {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. 'n' must be a positive integer greater than 3." << endl;
            }
            else {
                break;
            }
        }


    }
    else
    {
        cout << "Wrong data!" << endl;
        return 1;
    }
    return 0;
}
void outputData(double a, double b, double h, int n)
{
    string FileName;
    char choice;
    cout << "Do you want to save result?y/n" << endl;
    cin >> choice;
    while (!(choice == 'y' || choice == 'F' || choice == 'n' || choice == 'C' || choice == 'E')) {
        cout << "Invalid choice. Please enter 'y' or 'Y' if you want to save in file or 'N' or 'n' . ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> choice;
    }
    if (choice == 'E')
    {
        exit(1);
    }

    if (choice == 'y' || choice == 'Y')
    {
        cout << "Enter file name: ";
        cin >> FileName;

        ofstream outfile(FileName);

        if (outfile.is_open())
        {
            for (double x = a; x <= b; x += h)
            {
                double y = find_y(x, n);

                outfile << "|x = " << x << "|" << "| y = " << y << "|" << endl;
                cout << "|x = " << x << "|" << "| y = " << y << "|" << endl;
            }
            outfile.close();
            cout << "this result saved in file " << FileName << endl;

        }
        else
        {
            cout << "error";
        }

    }
    else if (choice == 'n' || choice == 'N')
    {
        for (double x = a; x <= b; x += h) {
            double y = find_y(x, n);
            cout << "|x = " << x << "|" << "| y = " << y << "|" << endl;
            //cout<<"Result: "<<y<<endl;
        }
    }
}