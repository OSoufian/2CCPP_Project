#include <iostream>

#include "Menu.hpp"

using namespace std;

// MENU PRINCIPAL

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

void Menu::tasksListMenu() {
    system("cls");
    cout << "<------------ LISTE DES TÂCHES ------------>\n";        
    cout << "\nRetour au menu principal [R]\n";
    cout << "Quitter [Q]\n\n";
}

void Menu::addTaskMenu() {
    system("cls");
    std::cout << "<------------ CREATION D'UNE TÂCHE ------------>\n\n";
    std::cout << "Retour au menu principal [R]\n";
    std::cout << "Quitter [Q]\n\n";
}

void Menu::renameTaskMenu() {
    system("cls");
    cout << "<------------ RENOMMER UNE TÂCHE ------------>\n\n";
    cout << "Retour au menu principal [R]\n";
    cout << "Quitter [Q]\n\n";
}

void Menu::deleteTaskMenu() {
    system("cls");
    cout << "<------------ SUPPRIMER UNE TÂCHE ------------>\n\n";
    cout << "Retour au menu principal [R]\n";
    cout << "Quitter [Q]\n\n";
}

void Menu::runTaskMenu() {
    system("cls");
    cout << "<------------ EXECUTER UNE TÂCHE ------------>\n\n";
    cout << "Retour au menu principal [R]\n";
    cout << "Quitter [Q]\n\n";
}

void Menu::duplicateTaskMenu() {
    system("cls");
    cout << "<------------ DUPLIQUER UNE TÂCHE ------------>\n\n";
    cout << "Retour au menu principal [R]\n";
    cout << "Quitter [Q]\n\n";
}

void Menu::saveTaskMenu() {
    system("cls");
    cout << "<------------ SAUVEGARDER UNE TÂCHE ------------>\n\n";
    cout << "Retour au menu principal [R]\n";
    cout << "Quitter [Q]\n\n";
}

void Menu::historyTaskMenu() {
    system("cls");
    cout << "<------------ MENU DES SAUVEGARDES ------------>\n\n";
    cout << "Retour au menu principal [R]\n";
    cout << "Quitter [Q]\n\n";
}