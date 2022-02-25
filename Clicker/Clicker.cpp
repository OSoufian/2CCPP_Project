#include <iostream>
#include "Clicker.hpp"

using namespace std;

Clicker::Clicker() {
    Task task("Tache 1");
    Click click(0, 0, MOUSEEVENTF_LEFTDOWN, false, 0);
    task.setClick(click);
    task.setIsInfiniteCycle(true);
    task.setTimeInterval(1);
    this->_tasks.push_back(task);
    mainMenu();
}

void Clicker::displayTasks() {
    for (int i = 0; i < this->_tasks.size(); i++)
    {
        cout << this->_tasks[i].getName() << ":" << endl;
        for (int j = 0; j < this->_tasks[i].getClicks().size(); j++){
            cout << "Position du clique " << (j+1) << ": (" << this->_tasks[i].getClicks()[j].getX() << ", " << this->_tasks[i].getClicks()[j].getY() << ")" << endl;
            if (this->_tasks[i].getClicks()[j].getIsHeld())
                cout << "Le temps de maintien du clique est de : " << this->_tasks[i].getClicks()[j].getDuration() << endl;
        }
        cout << "Nombres de repetions du cycle : ";
        if (this->_tasks[i].getIsInfiniteCycle())
            cout << "En boucle !" << endl;
        else 
            cout << this->_tasks[i].getCycleRepetitions() << endl;
        cout << "Temps d'intervalle entre 2 cycles: " << this->_tasks[i].getTimeInterval() << " secondes\n\n";
    }
}

bool Clicker::isDigit(string input) {
    for (int i = 0; i < input.size(); i++) {
        if (!isdigit(input[i]))
            return false;
    }
    return true;
}

// MENU PRINCIPAL

void Clicker::mainMenu() {
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

bool Clicker::getMainAction(string action) {

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
        return false;
    }
}

// LISTE DES TACHES
void Clicker::tasksListMenu() {
    char action;
    bool valid = false;
    do {
        system("cls");
        cout << "<------------ Voici la liste des taches ------------>\n\n";
        this->displayTasks();
        cout << "\nRetour au menu principal [R]\n";
        cout << "Quitter [Q]\n\n";
        cin >> action;
        valid = getTasksListAction(action);
    } while (!valid);
}

bool Clicker::getTasksListAction(char action) {
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

void Clicker::addTaskMenu() {
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
    this->_tasks.push_back(task);

    mainMenu();
}

// RENOMMER UNE TACHE

bool Clicker::validTaskIndex(int taskIndex) {
    if (taskIndex < 1 || taskIndex > this->_tasks.size())
        return false;
    return true;
}

void Clicker::renameTaskMenu() {
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

    this->_tasks[stoi(taskIndex) - 1].setName(newTaskName);

    mainMenu();
}

// SUPPRIMER UNE TACHE

void Clicker::deleteTaskMenu() {
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

    this->_tasks.erase(this->_tasks.begin() + stoi(taskIndex) - 1);

    mainMenu();
}

// LANCER UNE TACHE

void Clicker::runTaskMenu() {
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

    this->_tasks[stoi(taskIndex) - 1].run(); 

    mainMenu();
}

// DUPLIQUER UNE TACHE

void Clicker::duplicateTaskMenu() {
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

    newTask = this->_tasks[stoi(taskIndex) - 1];
    newTask.setName(newTaskName);
    this->_tasks.push_back(newTask);

    mainMenu();
}