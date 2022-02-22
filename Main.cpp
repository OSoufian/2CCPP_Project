#include <iostream>
#include <string>
#include "Task/Task.hpp"
#include "Clicker/Clicker.hpp"

using namespace std;

Clicker SUPINFOAutoClicker;

void mainMenu();
bool getMainAction(string action);

void tasksListMenu();
bool getTasksListAction();

void addTaskMenu();
bool getAddTaskAction();

bool isDigit(string input);

bool isDigit(string input)
{
    for (int i = 0; i < input.size(); i++)
    {
        if (!isdigit(input[i]))
            return false;
    }
    return true;
}

void mainMenu()
{
    string action;
    bool valid = false;

    string test = "44";
    int ee = stoi(test);
    cout << ee << endl;

    do
    {
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

bool getMainAction(string action)
{

    if (action == "V" || action == "v")
    {
        tasksListMenu();
        return true;
    }
    else if (action == "A" || action == "a")
    {
        addTaskMenu();
        return true;
    }
    else if (action == "M" || action == "m")
    {
        return true;
    }
    else if (action == "L" || action == "l")
    {
        return true;
    }
    else if (action == "Q" || action == "q")
    {
        exit(0);
    }
    else
    {
        return true;
    }
}

void tasksListMenu()
{
    char action;
    bool valid = false;
    do
    {
        system("cls");
        cout << "<------------ Voici la liste des taches ------------>\n\n";
        SUPINFOAutoClicker.displayTasks();
        cout << "Retour au menu principal [R]\n";
        cout << "Quitter [Q]\n\n";
        cin >> action;
        // valid = getTasksListAction();
    } while (!valid);
}

bool getTasksListAction(char action)
{
    system("cls");
    switch (action)
    {
    case 'r':
    case 'R':
        mainMenu();
        return true;
        break;
    default:
        return false;
    }
}

void addTaskMenu()
{
    char action;
    bool valid = false;

    string taskName;
    string duration;
    string numberClicks;
    string delay;
    string pos[2];

    system("cls");
    cout << "<------------ Création d'une tache ------------>\n\n";
    cout << "Retour au menu principal [R]\n";
    cout << "Quitter [Q]\n\n";
    cout << "Quel est le nom de la tâche ?\n";
    cin >> taskName;

    // ------------------ Instructions pour un clique ------------------ //
    system("cls");
    cout << "Quel est le nombre de cliques que tu veux?\n";
    do
    {
        cin >> numberClicks;
        valid = isDigit(numberClicks);
    } while (!valid);

    cout << "Quel est la durée de ton clique?\n";
    do
    {
        valid = false;
        cin >> duration;
        valid = isDigit(duration);
    } while (!valid);

    // cout << "Quel est le nombre de secondes entre 2 cliques?\n";
    // do
    // {
    //     valid = false;
    //     cin >> delay;
    //     valid = isDigit(delay);
    // } while (!valid);
    cout << "Quel est la position de ton clique? (en coordonnées x et y ( de gauche à droite de haut en bas ))\n";
    do
    {
        valid = false;
        cin >> pos[0];
        cin >> pos[1];
        valid = (isDigit(pos[0]) && isDigit(pos[1]));
    } while (!valid);

    
    Click click(stoi(duration), stoi(pos[0]), stoi(pos[1]));
    Cycle cycle;
    cycle.setClick(click);
    Task task(taskName, cycle);
    SUPINFOAutoClicker.setTask(task);

    mainMenu();
}

bool getAddTaskAction(string name)
{
    system("cls");
    if (name == "R" || name == "r")
    {
        mainMenu();
        return true;
    }
    else if (name == "Q" || name == "q")
    {
        exit(0);
    }
    else
    {
        return true;
    }
}

int main()
{
    mainMenu();
    return 0;
}