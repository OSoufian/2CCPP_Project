#include <iostream>
#include "Task/Task.hpp"
#include "Clicker/Clicker.hpp"

using namespace std;

void mainMenu();
bool getMainAction(char action);

void tasksListMenu();
bool getTasksListAction(char action);

void mainMenu()
{
    char action;
    bool valid = false;
    do
    {
        system("cls");
        cout << "<------------ Bienvenue dans SUPINFO Auto Clicker ------------>\n\n";
        cout << "Voir la liste des taches [V]\n";
        cout << "Ajouter une tache [A]\n";
        cout << "Modifier une tache [M]\n";
        cout << "Lancer une tache [L]\n";
        cin >> action;
        valid = getMainAction(action);
    } while (!valid);
}

bool getMainAction(char action)
{
    switch (action)
    {
    case 'v':
    case 'V':
    {
        tasksListMenu();
        // cout << "Vous avez appuye sur V";
        return true;
        break;
    }

    case 'a':
    case 'A':
        return true;
        break;

    case 'm':
    case 'M':
        return true;
        break;

    case 'l':
    case 'L':
        return true;
        break;

    default:
        return false;
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
        // SUPINFOAutoClicker
        cout << "Retour [R]\n";
        cin >> action;
        valid = getTasksListAction(action);
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

int main()
{
    Clicker SUPINFOAutoClicker();
    mainMenu();
    return 0;
}