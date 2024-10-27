#include <bits/stdc++.h>
#include <termios.h>

#define ERROR -1
#define OK 0
#define SIGN_IN 1
#define SIGN_UP 2
#define MIN_PASSWORD_LENGTH 8

using std::string;
using std::cin;
using std::ifstream;
using std::ofstream;
using std::ios;

int parsingArgs(int argc, char* argv[]) {
    if (argc != 2) {
        return ERROR;
    } else {
        const char* flag = argv[1];
        if (!strcmp(flag, "--sign-in") || !strcmp(flag, "--sign-up")) {
            if (!strcmp(flag, "--sign-in")) {
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

int loginCheck(string& login) {
    int i = 0;
    while (login[i]) {
        if (login[i] == ' ') {
            fprintf(stderr, "Invalid login.\n");
            return ERROR;
        }
        ++i;
    }
    return OK;
}

int passChesk(string& password) {
    int i = 0;
    bool isCapital = false;
    bool isSpecial = false;
    bool isLittle = false;
    bool isDigits = false;

    while (password[i]) {
        if (password[i] >= 'A' && password[i] <= 'Z') {
            isCapital = true;
        } else {
            if (password[i] >= 'a' && password[i] <= 'z') {
                isLittle = true;
            } else {
                if (password[i] >= '0' && password[i] <= '9') {
                    isDigits = true;
                } else {
                    isSpecial = true;
                }
            }
        }
        if (password[i] == ' ') {
            fprintf(stderr, "Your password contains invalid characters!\n");
            return ERROR;
        }
        ++i;
    }
    if (i >= 8 && isCapital && isSpecial && isLittle && isDigits) {
        return OK;
    }
    fprintf(stderr, "Your password is not strong enough!\n");
    return ERROR;
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
            struct termios oldTermios, newTermios;
            tcgetattr(STDIN_FILENO, &oldTermios);

            newTermios = oldTermios;
            newTermios.c_lflag &= ~(ECHO | ECHONL);
            tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);


            string inputPassword;
            getline(cin, inputPassword);
            printf("\n");

            tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);
            if (inputPassword == password(userData)) {
                in.close();
                return OK;
            } else {
                fprintf(stderr, "Invalid password!\n");
                in.close();
                return ERROR;
            }
        } else {
            fprintf(stderr, "Invalid login\n");
            in.close();
            return ERROR;
        }
    } else {
        fprintf(stderr, "Database error\n");
        in.close();
        return ERROR;
    }
}

int signUp() {
    fprintf(stdout, "Please enter your login: ");
    string inputLogin;
    getline(cin, inputLogin);
    if (loginCheck(inputLogin) == ERROR) {
        return ERROR;
    }
    ifstream in("reg_list.txt");
    if (in.is_open()) {
        string userData;
        bool isLogin = false;

        while (getline(in, userData)) {
            if (login(userData) == inputLogin) {
                isLogin = true;
                break;
            }
        }

        if (!isLogin) {
            fprintf(stdout, "Please enter your password: ");
            struct termios oldTermios, newTermios;
            tcgetattr(STDIN_FILENO, &oldTermios);

            newTermios = oldTermios;
            newTermios.c_lflag &= ~(ECHO | ECHONL);
            tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);


            string inputPassword;
            getline(cin, inputPassword);
            printf("\n");

            tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);

            if (passChesk(inputPassword) == ERROR) {
                in.close();
                return ERROR;
            }

            ofstream out("reg_list.txt", ios::app);
            if (out.is_open()) {
                out << inputLogin << " " << inputPassword << std::endl;
                out.close();
                in.close();
                return OK;
            } else {
                fprintf(stderr, "Database error\n");
                out.close();
                in.close();
                return ERROR;
            }


        } else {
            fprintf(stdout, "This login have been used by other user\n");
            in.close();
            return ERROR;
        }
    } else {
        fprintf(stderr, "Database error\n");
        in.close();
        return ERROR;
    }
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
            fprintf(stdout, "Sign up successful! Now you can sign in.\n");
            return OK;
    }
}