#include <iostream>

#include "Menu.hpp"

using namespace std;

// Affiche le menu d'accueil
void Menu::mainMenu() {
    system("cls");
    cout << "<------------ BIENVENUE DANS SUPINFO AUTO CLICKER ------------>\n\n";
    cout << "Voir la liste des tâches [V]\n";
    cout << "Ajouter une tâche [A]\n";
    cout << "Renommer une tâche [R]\n";
    cout << "Dupliquer une tâche [D]\n";
    cout << "Supprimer une tâche [S]\n";
    cout << "Lancer une tâche [L]\n";
    cout << "Importer/Sauvegarder [I]\n";
    cout << "Consulter l'historique des tâches [H]\n";
    cout << "Quitter [Q]\n";    
}

// Affiche tous les autres menus
void Menu::showMenu(string menuName) {
    system("cls");
    std::cout << "<------------ " + menuName +" ------------>\n\n";
    std::cout << "Retour au menu principal [R]\n";
    std::cout << "Quitter [Q]\n\n";
}