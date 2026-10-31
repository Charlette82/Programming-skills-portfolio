#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

int main() {
    vector<string> jokes;
    string line, input;

    // Open the jokes file
    ifstream file("randomJokes.txt");

    if (!file) {
        cout << "Error: Cannot open jokes.txt" << endl;
        return 1;
    }

    // Read jokes from the file
    while (getline(file, line)) {
        if (line.find('?') != string::npos)
            jokes.push_back(line);
    }
    file.close();

    if (jokes.empty()) {
        cout << "No jokes found in the file." << endl;
        return 1;
    }

    srand(static_cast<unsigned int>(time(nullptr)));

    cout << "Type 'Alexa, tell me a joke' for a joke."
         << endl;
    cout << "Type 'quit' to exit." << endl;

    while (true) {
        cout << "\nEnter your request: ";
        getline(cin, input);

        if (input == "quit" || input == "Quit")
            break;

        if (input == "Alexa, tell me a joke") {
            string joke = jokes[rand() % jokes.size()];
            size_t pos = joke.find('?');

            cout << "\n" << joke.substr(0, pos + 1);
            cout << "\nPress Enter to reveal the punchline...";
            getline(cin, input);

            cout << joke.substr(pos + 1) << endl;
        } else {
            cout << "Invalid request. Please try again." << endl;
        }
    }

    cout << "Goodbye!" << endl;
    return 0;
}