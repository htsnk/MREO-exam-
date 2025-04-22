#include "QueueSystem.h"

void QueueSystem::addUser() {
    User user;
    cout << "\n--- Add User ---" << endl;
    cout << "First name: ";
    cin >> user.name;
    cout << "Last name: ";
    cin >> user.surname;
    cout << "Age: ";
    cin >> user.age;
    cout << "Test type (theory/practice): ";
    cin >> user.testType;

    if (user.testType == "theory") {
        user.id = "T" + to_string(theoryCounter++);
    }
    else {
        user.id = "P" + to_string(practiceCounter++);
    }

    users.push(user);
}

void QueueSystem::startProcessing() {
    while (!users.empty()) {
        User current = users.front();
        users.pop();

        cout << "\nNow serving: " << current.name << " " << current.surname << " [" << current.id << "]" << endl;
        cout << "Please come to the window. You have 5 seconds to confirm attendance (press 'y'): ";

        bool came = false;
        auto start = chrono::steady_clock::now();
        char response = '\0';

        while (chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - start).count() < 5) {
            if (cin.rdbuf()->in_avail()) {
                cin >> response;
                if (response == 'y' || response == 'Y') {
                    came = true;
                }
                break;
            }
            this_thread::sleep_for(chrono::milliseconds(100));
        }

        if (!came) {
            cout << "\nTime expired. User did not show up. Saved to failed.txt\n";
            saveToFile("failed.txt", current, "No-show");
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        bool passed = simulateExam(current.testType);
        if (passed) {
            cout << "Result: PASSED\n";
            saveToFile("passed.txt", current, "Passed");
        }
        else {
            cout << "Result: FAILED\n";
            saveToFile("failed.txt", current, "Failed");
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

bool QueueSystem::simulateExam(const string& testType) {
    srand(time(0));
    int totalQuestions = (testType == "theory") ? 20 : 10;
    int maxMistakes = (testType == "theory") ? 2 : 3;
    int mistakes = rand() % (totalQuestions + 1);

    cout << "\nMistakes made: " << mistakes << endl;
    return mistakes <= maxMistakes;
}

void QueueSystem::saveToFile(const string& filename, const User& user, const string& status) {
    ofstream file(filename, ios::app);
    file << user.id << " - " << user.name << " " << user.surname
        << ", Age: " << user.age << ", Test: " << user.testType
        << ", Status: " << status << ", Time: " << generateTime() << endl;
    file.close();
}

void QueueSystem::showUsersFromFile(const string& filename) {
    ifstream file(filename);
    string line;
    cout << "\n--- Users from " << filename << " ---" << endl;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

string QueueSystem::generateTime() {
    int startHour = 8;
    int endHour = 18;
    int hour = rand() % (endHour - startHour + 1) + startHour;
    int minute = rand() % 60;

    ostringstream oss;
    oss << setfill('0') << setw(2) << hour << ":" << setw(2) << minute;
    return oss.str();
}
