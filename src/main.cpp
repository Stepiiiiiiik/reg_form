#include <bits/stdc++.h>

#define ERROR -1
#define OK 0
#define SIGN_IN 1
#define SIGN_UP 2

using std::string;
using std::cin;
using std::ifstream;
using std::ofstream;
int parsingArgs(int argc, char* argv[]) {
    if (argc != 2) {
        return ERROR;
    } else {
        const char* flag = argv[1];
        if (!strcmp(flag, "-sign-in") || !strcmp(flag, "-sign-up")) {
            if (!strcmp(flag, "-sign-in")) {
                return SIGN_IN;
            } else {
                return SIGN_UP;
            }
        } else {
            return ERROR;
        }
    }
}

string login(string& userData) {
    int i = 0;
    string login;
    while (userData[i] != ' ') {
        login.push_back(userData[i++]);
    }
    return login;
}

string password(string& userData) {
    int i = 0;
    string password;
    while (userData[i] != ' ') {
        ++i;
    }
    ++i;
    while (userData[i]) {
        password.push_back(userData[i++]);
    }
    return password;
}

int signIn() {
    fprintf(stdout, "Please enter your login: ");
    string inputLogin;
    getline(cin, inputLogin);

    ifstream in("reg_list.txt");
    if(in.is_open()) {
        string userData;
        bool isLogin = false;
        while (getline(in, userData)) {
            if (login(userData) == inputLogin) {
                isLogin = true;
                break;
            }
        }

        if (isLogin) {
            fprintf(stdout, "Please enter your password: ");
            string inputPassword;
            getline(cin, inputPassword);
            if (inputPassword == password(userData)) {
                return OK;
            } else {
                fprintf(stderr, "Invalid password!\n");
                return ERROR;
            }
        } else {
            fprintf(stderr, "Invalid login\n");
            return ERROR;
        }
    } else {
        fprintf(stderr, "Database error\n");
        return ERROR;
    }
}

int signUp() {

}


int main(int argc, char* argv[]) {
    int mode = parsingArgs(argc, argv);
    switch(mode) {
        case (ERROR):
            fprintf(stderr, "Incorrect option!\n");
            return ERROR;
        case (SIGN_IN):
            if(signIn() == ERROR) return ERROR;
                fprintf(stdout, "Sign in successful!\n");
                return OK;
        case (SIGN_UP):
            if(signUp() == ERROR) return ERROR;
            fprintf(stdout, "Sign up successful!\n");
            return OK;
    }
}