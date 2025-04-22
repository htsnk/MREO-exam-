#include "QueueSystem.h"

int main() {
    QueueSystem system;
    int choice;

    while (true) {
        cout << "\n--- MENU ---" << endl;
        cout << "1. Add user to queue" << endl;
        cout << "2. Start processing queue" << endl;
        cout << "3. Show passed users" << endl;
        cout << "4. Show failed users" << endl;
        cout << "5. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            system.addUser();
            break;
        case 2:
            system.startProcessing();
            break;
        case 3:
            system.showUsersFromFile("passed.txt");
            break;
        case 4:
            system.showUsersFromFile("failed.txt");
            break;
        case 5:
            return 0;
        default:
            cout << "Invalid option!" << endl;
        }
    }
}
