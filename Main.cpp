#include <iostream>
#include <string>
#include "Task/Task.hpp"
#include "Clicker/Clicker.hpp"
#include "Cycle/Cycle.hpp"

using namespace std;

Clicker SUPINFOAutoClicker;

void mainMenu();
bool getMainAction(string action);

void tasksListMenu();
bool getTasksListAction(char action);

void addTaskMenu();
bool getAddTaskAction();

bool isDigit(string input);

bool isDigit(string input) {
    for (int i = 0; i < input.size(); i++) {
        if (!isdigit(input[i]))
            return false;
    }
    return true;
}

void mainMenu() {
    string action;
    bool valid = false;

    do {
        system("cls");
        cout << "<------------ Bienvenue dans SUPINFO Auto Clicker ------------>\n\n";
        cout << "Voir la liste des taches [V]\n";
        cout << "Ajouter une tache [A]\n";
        cout << "Modifier une tache [M]\n";
        cout << "Lancer une tache [L]\n";
        cout << "Quitter [Q]\n";
        cin >> action;
        valid = getMainAction(action);
    } while (!valid);
}

bool getMainAction(string action) {

    if (action == "V" || action == "v") {
        tasksListMenu();
        return true;
    }
    else if (action == "A" || action == "a") {
        addTaskMenu();
        return true;
    }
    else if (action == "M" || action == "m") {
        return true;
    }
    else if (action == "L" || action == "l") {
        return true;
    }
    else if (action == "Q" || action == "q") {
        exit(0);
    }
    else {
        return true;
    }
}

void tasksListMenu() {
    char action;
    bool valid = false;
    do {
        system("cls");
        cout << "<------------ Voici la liste des taches ------------>\n\n";
        SUPINFOAutoClicker.displayTasks();
        cout << "\nRetour au menu principal [R]\n";
        cout << "Quitter [Q]\n\n";
        cin >> action;
        valid = getTasksListAction(action);
    } while (!valid);
}

bool getTasksListAction(char action) {
    system("cls");
    switch (action) {
    case 'r':
    case 'R':
        mainMenu();
        return true;
        break;
    case 'q':
    case 'Q':
        exit(0);
    default:
        return false;
    }
}

void addTaskMenu() {
    char action;
    bool valid = false;

    string taskName;
    string clickDuration;
    // string numberClicks;
    string clickHeld;
    bool isClickHeld;
    string cycleRepetitions = "0";
    string timeInterval;
    string pos[2];

    system("cls");
    cout << "<------------ Creation d'une tache ------------>\n\n";
    cout << "Retour au menu principal [R]\n";
    cout << "Quitter [Q]\n\n";
    cout << "Quel est le nom de la tache ?\n";
    do {
        getline(cin, taskName);
        if (taskName != "") valid = true;
    } while (!valid);

    // ------------------ Instructions pour un clique ------------------ //
    // system("cls");
    // cout << "Quel est le nombre de cliques que tu veux?\n";
    // do {
    //     valid = false;
    //     cin >> numberClicks;
    //     valid = isDigit(numberClicks);
    // } while (!valid);
    cout <<"Voulez vous maintenir votre click ? (oui/non)\n";
    do {
        valid = false;
        cin >> clickHeld;
        if (clickHeld == "oui" || clickHeld == "non") {
            if (clickHeld == "oui") isClickHeld = true;
            else isClickHeld = false;
            valid = true;
        }
    } while (!valid);

    if (isClickHeld) {
        cout << "Quel est la duree de ton clique (en secondes) ?\n";
        do {
            valid = false;
            cin >> clickDuration;
            valid = isDigit(clickDuration);
        } while (!valid);
    }    

    cout << "Quel est le nombre de repetitions de ton clique ?\n";
    do {
        valid = false;
        cin >> cycleRepetitions;
        valid = isDigit(cycleRepetitions);
    } while (!valid);

    cout << "Quel est le nombre de secondes entre 2 cliques ?\n";
    do {
        valid = false;
        cin >> timeInterval;
        valid = isDigit(timeInterval);
    } while (!valid);

    cout << "Quel est la position de ton clique ? (entre d'abord le x puis le y)\n";
    do {
        valid = false;
        cin >> pos[0];
        cin >> pos[1];
        valid = (isDigit(pos[0]) && isDigit(pos[1]));
    } while (!valid);

    Click click(2, stoi(pos[0]), stoi(pos[1]), isClickHeld);
    Cycle cycle;
    cycle.setClick(click);
    Task task(taskName, cycle, stoi(cycleRepetitions), stoi(timeInterval));
    SUPINFOAutoClicker.setTask(task);

    mainMenu();
}

bool getAddTaskAction(string name) {
    system("cls");
    if (name == "R" || name == "r") {
        mainMenu();
        return true;
    }
    else if (name == "Q" || name == "q") {
        exit(0);
    }
    else {
        return true;
    }
}

int main() {
    mainMenu();
    return 0;
}