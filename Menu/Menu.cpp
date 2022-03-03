#include <iostream>

#include "Menu.hpp"

using namespace std;

// MENU PRINCIPAL

void Menu::mainMenu() {
    system("cls");
    cout << "<------------ BIENVENUE DANS SUPINFO AUTO CLICKER ------------>\n\n";
    cout << "Voir la liste des taches [V]\n";
    cout << "Ajouter une tache [A]\n";
    cout << "Renommer une tache [R]\n";
    cout << "Dupliquer une tache [D]\n";
    cout << "Supprimer une tache [S]\n";
    cout << "Lancer une tache [L]\n";
    cout << "Importer/Sauvegarder [I]\n";
    cout << "Consulter l'historique des taches [H]\n";
    cout << "Quitter [Q]\n";    
}

void Menu::tasksListMenu() {
    system("cls");
    cout << "<------------ Voici la liste des taches ------------>\n";        
    cout << "\nRetour au menu principal [R]\n";
    cout << "Quitter [Q]\n\n";
}

void Menu::addTaskMenu() {
    system("cls");
    std::cout << "<------------ CREATION d'UNE TACHE ------------>\n\n";
    std::cout << "Retour au menu principal [R]\n";
    std::cout << "Quitter [Q]\n\n";
}

void Menu::renameTaskMenu() {
    system("cls");
    cout << "<------------ RENOMMER UNE TACHE ------------>\n\n";
    cout << "Retour au menu principal [R]\n";
    cout << "Quitter [Q]\n\n";
}

void Menu::deleteTaskMenu() {
    system("cls");
    cout << "<------------ RENOMMER UNE TACHE ------------>\n\n";
    cout << "Retour au menu principal [R]\n";
    cout << "Quitter [Q]\n\n";
}

void Menu::runTaskMenu() {
    system("cls");
    cout << "<------------ EXECUTER UNE TACHE ------------>\n\n";
    cout << "Retour au menu principal [R]\n";
    cout << "Quitter [Q]\n\n";
}

void Menu::duplicateTaskMenu() {
    system("cls");
    cout << "<------------ DUPLIQUER UNE TACHE ------------>\n\n";
    cout << "Retour au menu principal [R]\n";
    cout << "Quitter [Q]\n\n";
}

void Menu::saveTaskMenu() {
    system("cls");
    cout << "<------------ DUPLIQUER UNE TACHE ------------>\n\n";
    cout << "Retour au menu principal [R]\n";
    cout << "Quitter [Q]\n\n";
}

void Menu::historyTaskMenu() {
    system("cls");
    cout << "<------------ MENU DES SAUVEGARDES ------------>\n\n";
    cout << "Retour au menu principal [R]\n";
    cout << "Quitter [Q]\n\n";
}