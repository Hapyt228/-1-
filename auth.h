#ifndef AUTH_H
#define AUTH_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const string USERS_FILE = "user.txt";
const int MAX_USERS = 100;

struct User {
    string username;
    string password;
    bool isAdmin;
};

extern User* currentUser;


void loadUsers();
void saveUsers();
void registerUser();
void loginUser();
string getCurrentUser();
bool checkIfAdmin();

#endif