#pragma once
#include <queue>
#include <string>
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <sstream>
using namespace std;

struct User {
    std::string id;
    std::string name;
    std::string surname;
    int age;
    std::string testType;
};

class QueueSystem {
private:
    std::queue<User> users;
    int theoryCounter = 1;
    int practiceCounter = 1;

public:
    void addUser();
    void startProcessing();
    void showUsersFromFile(const std::string& filename);

private:
    bool simulateExam(const std::string& testType);
    void saveToFile(const std::string& filename, const User& user, const std::string& status);
    std::string generateTime();
};
