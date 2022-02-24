#include <iostream>
#include <string>
#include <windows.h>
#include "Task/Task.hpp"
#include "Clicker/Clicker.hpp"
#include "Cycle/Cycle.hpp"
#include "Click/Click.hpp"

using namespace std;

Clicker SUPINFOAutoClicker;

void mainMenu();
bool getMainAction(string action);

void tasksListMenu();
bool getTasksListAction(char action);

void addTaskMenu();

void renameTaskMenu();

void deleteTaskMenu();

void duplicateTaskMenu();

void runTaskMenu();

bool isDigit(string input) {
    for (int i = 0; i < input.size(); i++) {
        if (!isdigit(input[i]))
            return false;
    }
    return true;
}

// MENU PRINCIPAL

void mainMenu() {
    string action;
    bool valid = false;

    do {
        system("cls");
        cout << "<------------ Bienvenue dans SUPINFO Auto Clicker ------------>\n\n";
        cout << "Voir la liste des taches [V]\n";
        cout << "Ajouter une tache [A]\n";
        cout << "Renommer une tache [R]\n";
        cout << "Dupliquer une tache [D]\n";
        cout << "Supprimer une tache [S]\n";
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
    else if (action == "R" || action == "r") {
        renameTaskMenu();
        return true;
    }
    else if (action == "S" || action == "s") {
        deleteTaskMenu();
        return true;
    }
    else if (action == "D" || action == "d") {
        duplicateTaskMenu();
        return true;
    }
    else if (action == "L" || action == "l") {
        runTaskMenu();
        return true;
    }
    else if (action == "Q" || action == "q") {
        exit(0);
    }
    else {
        return true;
    }
}

// LISTE DES TACHES

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

// AJOUTER UNE TACHE

void addTaskMenu() {
    // char action;
    bool valid = false;
    int steps;

    string taskName;
    string clickDuration = "0";
    string numberClicks;
    string clickHeld;
    bool isClickHeld;
    string infiniteCycle;
    bool isInfiniteCycle;
    string cycleRepetitions = "0";
    string timeInterval;
    string pos[2];
    DWORD clickType;

    system("cls");
    cout << "<------------ Creation d'une tache ------------>\n\n";
    cout << "Retour au menu principal [R]\n";
    cout << "Quitter [Q]\n\n";
    cout << "Quel est le nom de la tache ?\n";
    do {
        getline(cin, taskName);
        if (taskName != "")
            valid = true;
    } while (!valid);

    // ------------------ Instructions pour un clique ------------------ //
    system("cls");
    cout << "Quel est le nombre de cliques que vous voulez dans votre cycle?\n";
    do {
        valid = false;
        cin >> numberClicks;
        steps = stoi(numberClicks);
        valid = isDigit(numberClicks);
    } while (!valid);
    Task task(taskName);
    do {

        cout << "Quel est le type de votre clique ? ([d]droit/[g]gauche)\n";
        do {
            valid = false;
            cin >> clickHeld;
            if (clickHeld == "d" || clickHeld == "g") {
                if (clickHeld == "d") clickType = MOUSEEVENTF_RIGHTDOWN;
                else clickType = MOUSEEVENTF_LEFTDOWN;
                valid = true;
            }
        } while (!valid);


        cout << "Voulez vous maintenir votre click ? ([o]oui/[N]non)\n";
        do {
            valid = false;
            cin >> clickHeld;
            if (clickHeld == "oui" || clickHeld == "o" || clickHeld == "O" || clickHeld == "non" || clickHeld == "n" || clickHeld == "N") {
                if (clickHeld == "oui" || clickHeld == "o")
                    isClickHeld = true;
                else
                    isClickHeld = false;
                valid = true;
            }
        } while (!valid);

        if (isClickHeld) {
            cout << "Quel est la duree de votre clique (en secondes) ?\n";
            do {
                valid = false;
                cin >> clickDuration;
                valid = isDigit(clickDuration);
            } while (!valid);
        }

        cout << "Quel est la position de votre clique ? (entrez d'abord le x puis le y)\n";
        do {
            valid = false;
            cin >> pos[0];
            cin >> pos[1];
            valid = (isDigit(pos[0]) && isDigit(pos[1]));
        } while (!valid);

        Click click(stoi(pos[0]), stoi(pos[1]), clickType, isClickHeld, stoi(clickDuration));
        task.setClick(click);

        steps--;
    } while (steps != 0);

    cout << "Voulez vous que le cycle se répète indéfiniment? (oui/non)\n";
    do {
        valid = false;
        cin >> infiniteCycle;
        if (infiniteCycle == "oui" || infiniteCycle == "o" || infiniteCycle == "non" || infiniteCycle == "n" || infiniteCycle == "N") {
            if (infiniteCycle == "oui" || infiniteCycle == "o") {
                isInfiniteCycle = true;
                task.setIsInfiniteCycle(isInfiniteCycle);
                valid = true;
            }
            else {
                isInfiniteCycle = false;
                task.setIsInfiniteCycle(isInfiniteCycle);
                cout << "Combien de fois le cycle dois se répéter?\n";
                cin >> cycleRepetitions;
                valid = isDigit(cycleRepetitions);
            }
        }
    } while (!valid);
    cout << "Quel est le nombre de cliques par secondes entre 2 cycles ?\n";
    do {
        valid = false;
        cin >> timeInterval;
        valid = isDigit(timeInterval);
    } while (!valid);

    task.setCycleRepetitions(stoi(cycleRepetitions));
    task.setTimeInterval(stoi(timeInterval));
    SUPINFOAutoClicker.setTask(task);

    mainMenu();
}

// RENOMMER UNE TACHE

bool validTaskIndex(int taskIndex) {
    if (taskIndex < 1 || taskIndex > SUPINFOAutoClicker.getTasks().size())
        return false;
    return true;
}

void renameTaskMenu() {
    char action;
    bool valid = false;

    string taskIndex;
    string newTaskName;

    system("cls");
    cout << "<------------ Renommer une tache ------------>\n\n";
    cout << "Retour au menu principal [R]\n";
    cout << "Quitter [Q]\n\n";
    cout << "Quel est le numéro de la tache ?\n";
    do {
        cin >> taskIndex;
        if (isDigit(taskIndex) && validTaskIndex(stoi(taskIndex)))
            valid = true;
    } while (!valid);

    cout << "Quel est le nouveau nom pour cette tache ? \n";
    do {
        valid = false;
        getline(cin, newTaskName);
        if (newTaskName != "")
            valid = true;
    } while (!valid);

    SUPINFOAutoClicker.setTaskName(stoi(taskIndex), newTaskName);

    mainMenu();
}

// SUPPRIMER UNE TACHE

void deleteTaskMenu() {
    bool valid = false;

    string taskIndex;
    string newTaskName;

    system("cls");
    cout << "<------------ SUPPRIMER une tache ------------>\n\n";
    cout << "Retour au menu principal [R]\n";
    cout << "Quitter [Q]\n\n";
    cout << "Quel est le numéro de la tache ?\n";
    do {
        cin >> taskIndex;
        if (isDigit(taskIndex) && validTaskIndex(stoi(taskIndex)))
            valid = true;
    } while (!valid);

    SUPINFOAutoClicker.deleteTask(stoi(taskIndex));

    mainMenu();
}

// LANCER UNE TACHE

void runTaskMenu() {
    bool valid = false;

    string taskIndex;

    system("cls");
    cout << "<------------ Lancer une tache ------------>\n\n";
    cout << "Retour au menu principal [R]\n";
    cout << "Quitter [Q]\n\n";
    cout << "Quel est le numéro de la tache ?\n";
    do {
        cin >> taskIndex;
        if (isDigit(taskIndex) && validTaskIndex(stoi(taskIndex)))
            valid = true;
    } while (!valid);

    SUPINFOAutoClicker.runTask(stoi(taskIndex));

    mainMenu();
}

// DUPLIQUER UNE TACHE

void duplicateTaskMenu() {
    string taskIndex;
    Task newTask;
    std::string newTaskName;
    bool valid = false;

    system("cls");
    cout << "<------------ DUPLIQUER une tache ------------>\n\n";
    cout << "Retour au menu principal [R]\n";
    cout << "Quitter [Q]\n\n";
    cout << "Quel est le numéro de la tache que vous voulez ?\n";
    do {
        cin >> taskIndex;
        if (isDigit(taskIndex) && validTaskIndex(stoi(taskIndex)))
            valid = true;
    } while (!valid);

    cout << "Quel est le nom pour cette nouvelle tache ? \n";
    do {
        valid = false;
        getline(cin, newTaskName);
        if (newTaskName != "")
            valid = true;
    } while (!valid);

    newTask = SUPINFOAutoClicker.getTask(stoi(taskIndex));
    newTask.setName(newTaskName);
    SUPINFOAutoClicker.setTask(newTask);

    mainMenu();
}

int main() {
    mainMenu();
    return 0;
}