#include <iostream>
#include <cmath>
#include <fstream>
#include <limits>
#include <stdexcept>
using namespace std;
void checkValidInput();
void checkValidParams(int n);
double find_y(double x, int n);
void inputData(double& a, double& b, double& h, int& n);
void inputFromKeyboard(double& a, double& b, double& h, int& n);
void inputFromFile(double& a, double& b, double& h, int& n);
void outputData(double a, double b, double h, int n);
void outputToFile(double a, double b, double h, int n, const string& fileName);
void outputToConsole(double a, double b, double h, int n);

int main() {
    double a, b, h;
    int n, q;

    cout << "*****************************************************************************************************************************************************" << endl;
    cout << "************************************************************* FIND EQUATION OF Y ********************************************************************" << endl;

    do
    {
        inputData(a, b, h, n);
        outputData(a, b, h, n);

        cout << "Continue? (yes=1/no=0): ";
        cin >> q;
    } while (q == 1);

    cout << "********************************************************************** END **************************************************************************" << endl;
    return 0;
}

double find_y(double x, int n)
{
    double y = 0.0;

    if (x < -5)
    {
        for (int i = -6; i <= n; i++)
        {
            y += i + x;
        }
        return 4 * x * y - 9;
    }
    else
    {
        for (int i = 0; i <= n + 1; i++)
        {
            double product = 1.0;
            for (int j = 0; j <= n - 3; j++)
            {
                product *= (i - 2 * j) / (4 + pow(x, 2));
            }
            y += product;
        }
        return y;
    }
}

// ¬в≥д даних
void inputData(double& a, double& b, double& h, int& n)
{
    char choice;
    bool validInput = false;

    while (!validInput)
    {
        try
        {
            cout << "Choose way of reading data (k = keyboard, f = file): ";
            cin >> choice;

            if (choice == 'f' || choice == 'F')
            {
                inputFromFile(a, b, h, n);
            }
            else if (choice == 'k' || choice == 'K')
            {
                inputFromKeyboard(a, b, h, n);
            }
            else
            {
                throw runtime_error("Invalid choice. Enter 'k' for keyboard or 'f' for file.");
            }

            validInput = true;
        }
        catch (const exception& e)
        {
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void inputFromKeyboard(double& a, double& b, double& h, int& n)
{
    while (true) {
        try {
            cout << "Enter a: ";
            cin >> a;
            checkValidInput();
            break;
        }
        catch (const exception& e)
        {
            cout << "Error: " << e.what() << ". Please try again." << endl;
        }
    }

    while (true)
    {
        try
        {
            cout << "Enter b (b > a): ";
            cin >> b;
            checkValidInput();
            if (b <= a) throw runtime_error("'b' must be greater than 'a'.");
            break;
        }
        catch (const exception& e)
        {
            cout << "Error: " << e.what() << ". Please try again." << endl;
        }
    }

    while (true)
    {
        try
        {
            cout << "Enter h (step > 0): ";
            cin >> h;
            checkValidInput();
            if (h <= 0) throw runtime_error("'h' must be greater than 0.");
            break;
        }
        catch (const exception& e)
        {
            cout << "Error: " << e.what() << ". Please try again." << endl;
        }
    }

    while (true)
    {
        try
        {
            double temp;
            cout << "Enter n (n >= 4, integer value): ";
            cin >> temp;
            checkValidInput();
            if (temp < 4 || floor(temp) != temp) throw runtime_error("'n' must be an integer greater than or equal to 4.");
            n = static_cast<int>(temp);
            break;
        }
        catch (const exception& e)
        {
            cout << "Error: " << e.what() << ". Please try again." << endl;
        }
    }
}
void inputFromFile(double& a, double& b, double& h, int& n)
{
    while (true)
    {
        try
        {
            string fileName;
            cout << "Enter file name: ";
            cin >> fileName;

            ifstream file(fileName);
            if (!file) throw runtime_error("Error opening file. Please check the file name.");

            file >> a >> b >> h >> n;
            checkValidInput();
            checkValidParams(n);
            file.close();
            break;
        }
        catch (const exception& e)
        {
            cout << "Error: " << e.what() << ". Please try again." << endl;
        }
    }
}

void outputData(double a, double b, double h, int n)
{
    char choice;
    while (true)
    {
        try
        {
            cout << "Do you want to save the result to a file? (y/n): ";
            cin >> choice;

            if (choice == 'y' || choice == 'Y')
            {
                string fileName;
                cout << "Enter file name: ";
                cin >> fileName;
                outputToFile(a, b, h, n, fileName);
                outputToConsole(a, b, h, n);
                break;
            }
            else if (choice == 'n' || choice == 'N')
            {
                outputToConsole(a, b, h, n);
                break;
            }
            else
            {
                throw runtime_error("Invalid choice. Please enter 'y' or 'n'.");
            }
        }
        catch (const exception& e)
        {
            cout << "Error: " << e.what() << ". Please try again." << endl;
        }
    }
}

void outputToFile(double a, double b, double h, int n, const string& fileName)
{
    ofstream outfile(fileName);
    if (!outfile)
    {
        cout << "Error: Could not open file for writing." << endl;
        return;
    }

    for (double x = a; x <= b; x += h)
    {
        double y = find_y(x, n);
        outfile << "|x = " << x << "| y = " << y << "|" << endl;
    }
    outfile.close();
    cout << "Results saved to " << fileName << endl;
}

void outputToConsole(double a, double b, double h, int n) {
    for (double x = a; x <= b; x += h) {
        double y = find_y(x, n);
        cout << "|x = " << x << "| y = " << y << "|" << endl;
    }
}

void checkValidInput() {
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw runtime_error("Incorrect input. Please enter numeric values.");
    }
}

void checkValidParams(int n)
{
    if (n < 4) {
        throw runtime_error("Invalid parameter 'n'. It must be greater than or equal to 4.");
    }
}