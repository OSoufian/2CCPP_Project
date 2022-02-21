#include <iostream>
#include "Task/Task.hpp"
#include "Clicker/Clicker.hpp"

using namespace std;

char mainMenu();
// char tasksListMenu();
// void getTasksListAction(char action);
void getMainAction(char action);

char mainMenu() {
    char action;
    cout << "<------------ Bienvenue dans SUPINFO Auto Clicker ------------>\n\n";
    cout << "Voir la liste des taches [V]\n";
    cout << "Modifier une tache [M]\n";
    cout << "Lancer une tache [L]\n";
    cin >> action;
    return action;
}

// char tasksListMenu() {
//     char action;
//     cout << "<------------ Voici la liste des tâches ------------>\n\n";
//     // SUPINFOAutoClicker.displayTasks()
//     cout << "Retour [R]";
//     cin >> action;
//     return action;
// }

// void getTasksListAction(char action) {
//     system("cls");
//     switch (action) {
//         case 'R':
//             char action = mainMenu();    
//             getMainAction(action);
//             break;    
//     }
// }

void getMainAction(char action) {
    system("cls");
    switch (action) {
        case 'V':
            // char action = tasksListMenu();
            // getTasksListAction(action);
            cout << "Vous avez appuye sur V";
            break;
        
        case 'M':            
            // 
            break;

        case 'L':
            // 
            break;        
    }

}



int main() {
    Clicker SUPINFOAutoClicker();
    char action = mainMenu();    
    getMainAction(action);
    return 0;
}

