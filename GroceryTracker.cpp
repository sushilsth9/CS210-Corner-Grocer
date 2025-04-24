/*
Name:Sushil Shrestha
Date:April 20,2025.

 */


// For input/output operations
#include <iostream>
// For file handling operations
#include <fstream>
// For storing item frequencies
#include <map>
//for handling and manipulating strings efficiently
#include <string>
// For formatting output
#include <iomanip>
// For input validation
#include <limits>
//to avoid writing std::
using namespace std;


class GroceryTracker {
private:
    // Map to store
    map<string, int> itemFrequency;

    // Filenames for input and output operations
    string inputFilename;
    string outputFilename;

public:
    GroceryTracker(const string &inputFile = "CS210_Project_Three_Input_File.txt",
                   const string &outputFile = "frequency.dat") {
        // Initializing filenames
        inputFilename = inputFile;
        outputFilename = outputFile;


        loadData();


        createBackupFile();
    }


    void loadData() {
        // Opening the input file
        ifstream inputFile(inputFilename);

        // Checking  if file opened successfully
        if (!inputFile.is_open()) {
            cout << "Cannot able to open inputfile " << inputFilename << endl;
            return;
        }

        string item;

        // Reading in the map
        while (getline(inputFile, item)) {
            if (!item.empty()) {
                itemFrequency[item]++;
            }
        }


        inputFile.close();
    }


    void createBackupFile() {
        // Opening the output file for writing
        ofstream outputFile(outputFilename);

        // Check if file opened successfully
        if (!outputFile.is_open()) {
            cerr << "Cann't able to create backup file " << outputFilename << std::endl;
            return;
        }


        for (const auto &pair: itemFrequency) {
            outputFile << pair.first << " " << pair.second << endl;
        }


        outputFile.close();
    }


    int getItemFrequency(const string &item) {
        if (itemFrequency.find(item) != itemFrequency.end()) {
            return itemFrequency[item];
        }
        return 0;
    }


    void printAllFrequencies() {
        cout << "\nAll Items Purchased Today (with frequencies):" << endl;
        cout<<endl;


        //Printing  its name and frequency
        for (const auto &pair: itemFrequency) {
            cout << setw(15) << left << pair.first << " " << pair.second << endl;
        }
        cout << endl;
    }


    void printHistogram() {
        cout << "\nPurchase Frequency Histogram:" << endl;


        //  printing its name followed by asterisks representing frequency
        for (const auto &pair: itemFrequency) {
            cout << setw(15) << left << pair.first << " ";

            // Print asterisks
            for (int i = 0; i < pair.second; i++) {
                cout << "*";
            }
            cout << endl;
        }
        cout << endl;
    }
};


void displayMenu() {
    cout << "\n*** Corner Grocer Item-Tracking Menu ***" << endl;
    cout << "1. Look up an item's purchased frequency" << endl;
    cout << "2. Print the list with numbers that represent the frequency of all items purchased" << endl;
    cout << "3. Print purchased item frequencies in the form of a histogram"<< endl;
    cout << "4. Exit " << endl;
    cout << "Enter your number (1-4): ";
}


int getValidChoice() {
    int choice;

    // While loop to get valid input until successful
    while (!(cin >> choice)) {
        cin.clear();


        cin.ignore(numeric_limits<streamsize>::max(), '\n');


        cout << "Invalid input. Please enter a number (1-4): ";
    }


    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return choice;
}


int main() {
    //Dispalying
    cout << "*** Corner Grocery Item-Tracking Program ***" << endl;
    cout << "This program helps to see purchase records " << endl;

    //  GroceryTracker object
    GroceryTracker tracker;

    // Declaring Variables
    int choice;
    bool running = true;

    //while  loop for display menu
    while (running) {
        displayMenu();
        choice = getValidChoice();

        switch (choice) {
            case 1: {
                string item;
                cout << "\nEnter the item name: ";
                getline(cin, item);


                int frequency = tracker.getItemFrequency(item);
                if (frequency > 0) {
                    cout << "'" << item << "' was purchased " << frequency << " time(s) today." << endl;
                } else {
                    cout << "'" << item << "' was not purchased today." << endl;
                }
                break;
            }
            case 2:

                tracker.printAllFrequencies();
                break;
            case 3:

                tracker.printHistogram();
                break;
            case 4:

                cout << " Thank you and Goodbye!" << endl;
                running = false;
                break;
            default:

                cout << "Invalid number. Please enter a number between 1 and 4." << endl;
        }
    }
    return 0;
}
