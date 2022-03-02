#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <Windows.h>
#include <thread>

#include "Clicker.hpp"
#include "../Time/Time.hpp"
#include "../Task/Task.hpp"

using namespace std;

struct Int2 {
    int a[2];
};

Clicker::Clicker() {
    // Task task("Tache 1");
    // Click click(0, 0, MOUSEEVENTF_LEFTDOWN, false, 0);
    // task.setClick(click);
    // task.setIsInfiniteCycle(true);
    // task.setTimeInterval(1);
    // this->_tasks.push_back(task);
    mainMenu();
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
        cout << "Importer/Sauvegarder [I]\n";
        cout << "Consulter l'historique des taches [H]\n";
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
    else if (action == "H" || action == "h") {
        historyMenu();
        return true;
    }
    else if (action == "I" || action == "i") {
        saveTaskMenu();
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
        displayTasks();
        cout << "\nRetour au menu principal [R]\n";
        cout << "Quitter [Q]\n\n";
        cin >> action;
        valid = getActionWithoutInput(action);
    } while (!valid);
}

void Clicker::displayTasks() {
    for (int i = 0; i < this->_tasks.size(); i++) {
        cout << this->_tasks[i].getName() << ":" << endl;
        for (int j = 0; j < this->_tasks[i].getClicks().size(); j++) {
            cout << "Position du clique " << (j + 1) << ": (" << this->_tasks[i].getClicks()[j].getX() << ", " << this->_tasks[i].getClicks()[j].getY() << ")" << endl;
            if (this->_tasks[i].getClicks()[j].getIsHeld())
                cout << "Le temps de maintien du clique est de : " << this->_tasks[i].getClicks()[j].getDuration() << endl;
        }

        cout << "Nombres de repetions du cycle : ";
        if (this->_tasks[i].getIsInfiniteCycle())
            cout << "En boucle !" << endl;
        else
            cout << this->_tasks[i].getCycleRepetitions() << endl;
        cout << "Temps d'intervalle entre 2 cycles: " << this->_tasks[i].getTimeInterval() << " secondes\n";

        cout << "Heure d'execution : ";
        if (this->_tasks[i].getIsScheduled()) {
            int hour = this->_tasks[i].getHourTime();
            int minutes = this->_tasks[i].getMinutesTime();
            int seconds = this->_tasks[i].getSecondsTime();

            if (hour < 10) cout << "0" << hour << ":";
            else cout << hour << ":";
            if (minutes < 10) cout << "0" << minutes << ":";
            else cout << minutes << ":";
            if (seconds < 10) cout << "0" << seconds << endl;
            else cout << seconds << endl;
        }
        else
            cout << "lancement manuel\n";
        cout << endl;
    }
}

bool Clicker::getActionWithoutInput(char action) {
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

int Clicker::keyPressed(int key){
    return (GetKeyState(key) & 1 != 0);
}

int Clicker::ClickType(){
    if(keyPressed(VK_LBUTTON)){
        return MOUSEEVENTF_LEFTDOWN;
    }
    if(keyPressed(VK_RBUTTON)){
        return MOUSEEVENTF_RIGHTDOWN;
    }
    return 0;
}

int Clicker::ClickType2(){
    if(keyPressed(VK_LBUTTON)){
        return MOUSEEVENTF_LEFTDOWN + 0x0002;
    }
    if(keyPressed(VK_RBUTTON)){
        return MOUSEEVENTF_RIGHTDOWN + 0x0002;
    }
    return 0;
}

bool Clicker::isHeld(int posx, int posy){
    if(keyPressed(VK_LBUTTON) || keyPressed(VK_RBUTTON)) {
        mouse_event(ClickType(), posx, posy, 0, 0);
        return true;
    }
    else {
        mouse_event(ClickType2(), posx, posy, 0, 0);
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
    string positionConsole[2];
    int positionClick[2];
    DWORD clickType;
    string typeClick;

    bool isScheduled;
    string scheduled;
    string hour;
    string minutes;
    string seconds;

    string consoleOrCapture;
    bool isClickCapturing;
    bool userClicked = false;

    system("cls");
    std::cout << "<------------ Creation d'une tache ------------>\n\n";
    std::cout << "Retour au menu principal [R]\n";
    std::cout << "Quitter [Q]\n\n";
    std::cout << "Quel est le nom de la tache ?\n";
    do {
        getline(std::cin, taskName);
        if (taskName != "")
            valid = true;
    } while (!valid);

    // ------------------ Instructions pour un clique ------------------ //
    std::cout << "Quel est le nombre de cliques que vous voulez dans votre cycle?\n";
    do {
        valid = false;
        std::cin >> numberClicks;
        steps = stoi(numberClicks);
        valid = isDigit(numberClicks);
    } while (!valid);

    Task task(taskName);

    std::cout << "Voulez vous entrer vos clicks a la console ou cliquer directement ? ([c]console/[d]directement)\n";
    do {
        valid = false;
        std::cin >> consoleOrCapture;
        if (consoleOrCapture == "c" || consoleOrCapture == "d") {
            if (consoleOrCapture == "c")
                isClickCapturing = false;
            else
                isClickCapturing = true;
            valid = true;
        }
    } while (!valid);

    do {

        if (consoleOrCapture == "c") {
            std::cout << "Voulez vous maintenir votre click ? ([o]oui/[N]non)\n";
            do {
                valid = false;
                std::cin >> clickHeld;
                if (clickHeld == "oui" || clickHeld == "o" || clickHeld == "O" || clickHeld == "non" || clickHeld == "n" || clickHeld == "N") {
                    if (clickHeld == "oui" || clickHeld == "o")
                        isClickHeld = true;
                    else
                        isClickHeld = false;
                    valid = true;
                }
            } while (!valid);

            if (isClickHeld) {
                std::cout << "Quel est la duree de votre clique (en secondes) ?\n";
                do {
                    valid = false;
                    std::cin >> clickDuration;
                    valid = isDigit(clickDuration);
                } while (!valid);
            }

            std::cout << "Quel est le type de votre clique ? ([g]gauche/[d]droit)\n";
            do {
                valid = false;
                std::cin >> typeClick;
                if (typeClick == "d" || typeClick == "g") {
                    if (typeClick == "d")
                        clickType = MOUSEEVENTF_RIGHTDOWN;
                    else
                        clickType = MOUSEEVENTF_LEFTDOWN;
                    valid = true;
                }
            } while (!valid);

            std::cout << "Quel est la position de votre clique ? (entrez d'abord le x puis le y)\n";
            do {
                valid = false;
                std::cin >> positionConsole[0];
                std::cin >> positionConsole[1];
                valid = (isDigit(positionConsole[0]) && isDigit(positionConsole[1]));
            } while (!valid);
        }
        else {
            std::cout << "Veuillez cliquer sur l'ecran pour enregistrer votre click !\n";
            vector<Int2> moves;
            bool hearing = true;
            POINT point;
            while(hearing) {
                int pos[2];
                if((keyPressed(VK_LBUTTON) || keyPressed(VK_RBUTTON)) && GetCursorPos(&point)) {
                    pos[0] = point.x;
                    pos[1] = point.y;
                    SetCursorPos(pos[0], pos[1]);
                    mouse_event(ClickType(), pos[0], pos[1], 0, 0);
                    mouse_event(ClickType2(), pos[0], pos[1], 0, 0);
                }
                do {
                    if (GetCursorPos(&point)) {
                        pos[0] = point.x;
                        pos[1] = point.y;
                    }
                } while(!keyPressed(VK_LBUTTON) || !keyPressed(VK_RBUTTON));
                int counter = 0;
                while(isHeld(pos[0], pos[1])){
                    if (GetCursorPos(&point)) {
                        moves.push_back({point.x, point.y});
                    }
                    Sleep(100);
                    counter += 100;
                }

                for (int i = 0; i < moves.size(); i++) {
                    int posi[2];
                    posi[0] = moves[i].a[0];
                    posi[1] = moves[i].a[1];
                    cout << posi[0] << "," << posi[1] << "\n";
                }
                
                cout << counter << endl;
                cout << "Click gauche\n";
                cout << pos[0] << "," << pos[1] << "\n";

                hearing = false;
            };
            
        }

        if (consoleOrCapture == "d") {
            Click click(positionClick[0], positionClick[1], clickType, isClickHeld, stoi(clickDuration));
            task.addClick(click);
        }
        else {
            Click click(stoi(positionConsole[0]), stoi(positionConsole[1]), clickType, isClickHeld, stoi(clickDuration));
            task.addClick(click);
        }
        steps--;
    } while (steps != 0);

    std::cout << "Voulez vous que le cycle se repete indefiniment? (oui/non)\n";
    do {
        valid = false;
        std::cin >> infiniteCycle;
        if (infiniteCycle == "oui" || infiniteCycle == "o" || infiniteCycle == "non" || infiniteCycle == "n" || infiniteCycle == "N") {
            if (infiniteCycle == "oui" || infiniteCycle == "o") {
                isInfiniteCycle = true;
                task.setIsInfiniteCycle(isInfiniteCycle);
                valid = true;
            }
            else {
                isInfiniteCycle = false;
                task.setIsInfiniteCycle(isInfiniteCycle);
                std::cout << "Combien de fois le cycle dois se répéter?\n";
                std::cin >> cycleRepetitions;
                valid = isDigit(cycleRepetitions);
            }
        }
    } while (!valid);
    std::cout << "Combien de secondes avant de recommencer un cycle ?\n";
    do {
        valid = false;
        std::cin >> timeInterval;
        valid = isDigit(timeInterval);
    } while (!valid);

    std::cout << "Voulez vous definir une heure d'execution pour cette tache ? ([o]oui/[n]non)\n";
    do {
        valid = false;
        std::cin >> scheduled;
        if (scheduled == "oui" || scheduled == "o" || scheduled == "O" || scheduled == "non" || scheduled == "n" || scheduled == "N") {
            if (scheduled == "oui" || scheduled == "o"|| scheduled == "O") {
                isScheduled = true;
                task.setIsScheduled(isScheduled);
            }
            else
                isScheduled = false;
            valid = true;
        }
    } while (!valid);

    if (isScheduled) {
        std::cout << "A quelle heure ?\n";
        do {
            valid = false;
            std::cin >> hour;
            if (isDigit(hour))
                if (stoi(hour) >= 0 && stoi(hour) < 24)
                    valid = true;
        } while (!valid);

        std::cout << "Minutes ?\n";
        do {
            valid = false;
            std::cin >> minutes;
            if (isDigit(minutes))
                if (stoi(minutes) >= 0 && stoi(minutes) < 60)
                    valid = true;
        } while (!valid);

        std::cout << "Secondes ?\n";
        do {
            valid = false;
            std::cin >> seconds;
            if (isDigit(seconds))
                if (stoi(seconds) >= 0 && stoi(seconds) < 60)
                    valid = true;
        } while (!valid);
        task.setTimeExecution(Time(stoi(hour), stoi(minutes), stoi(seconds)));
    }

    task.setCycleRepetitions(stoi(cycleRepetitions));
    task.setTimeInterval(stoi(timeInterval));
    this->_tasks.push_back(task);
    
    thread t1(runScheduledTask, task);
    // t1.join();

    mainMenu();
}

bool Clicker::isDigit(string input) {
    for (int i = 0; i < input.size(); i++) {
        if (!isdigit(input[i]))
            return false;
    }
    return true;
}

void runScheduledTask(Task task) {
	while (!task.getTimeExecution().isNow()) Sleep(1000);
	task.run();
}


// RENOMMER UNE TACHE

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

bool Clicker::validTaskIndex(int taskIndex) {
    if (taskIndex < 1 || taskIndex > this->_tasks.size())
        return false;
    return true;
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

    auto start = chrono::system_clock::now();
    this->_tasks[stoi(taskIndex) - 1].run();
    auto end = chrono::system_clock::now();
    time_t start_time = chrono::system_clock::to_time_t(start);
    time_t end_time = chrono::system_clock::to_time_t(end);
    History history(this->_tasks[stoi(taskIndex) - 1].getName(), start_time, end - start);
    this->_history.push_back(history);

    mainMenu();
}

// DUPLIQUER UNE TACHE

void Clicker::duplicateTaskMenu() {
    string taskIndex;
    Task newTask;
    string newTaskName;
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

// HISTORIQUE DES TACHES

void Clicker::historyMenu() {
    char action;
    bool valid = false;
    do {
        system("cls");
        cout << "<------------ HISTORIQUE DES TACHES ------------>\n\n";
        displayHistory();
        cout << "\nRetour au menu principal [R]\n";
        cout << "Quitter [Q]\n\n";
        cin >> action;
        valid = getActionWithoutInput(action);
    } while (!valid);
}

void Clicker::displayHistory() {
    for (int i = 0; i < this->_history.size(); i++) {
        time_t timeExecution = this->_history[i].getTimeExecution();

        cout << "Nom de la tache : " << this->_history[i].getName() << endl;
        cout << "Heure : " << ctime(&timeExecution);
        cout << "Duree : " << this->_history[i].getDuration().count() << " secondes\n\n";
    }
}

// IMPORTER/SAUVEGARDER TACHES

void Clicker::writeTasks(string fileName) {
    int tasks = this->_tasks.size();
    ofstream file(fileName);
    file << tasks << endl;
    for (int i = 0; i < tasks; i++) this->_tasks[i].write(&file);
    file.close();
}

bool Clicker::readTasks(string fileName) {
	ifstream file;
	file.open(fileName, ios::in);
    if (file.fail()) return false;
	int tasks;
	file >> tasks;
	for (int i = 0; i < tasks; i++) this->_tasks.push_back(Task::read(&file));
	file.close();
    return true;
}

void Clicker::saveTaskMenu() {
    bool valid = false;
    string saveOrImport;
    string fileName;

    system("cls");
    cout << "<------------ MENU DES SAUVEGARDES ------------>\n\n";
    cout << "Retour au menu principal [R]\n";
    cout << "Quitter [Q]\n\n";
    cout << "Voulez-vous sauvegarder ou importer une sauvegarde de taches ? (S/I)\n";
    do {
        valid = false;
        getline(cin, saveOrImport);
        if (saveOrImport == "I" || saveOrImport == "i" || saveOrImport == "S" || saveOrImport == "s")
            valid = true;
    } while (!valid);

    if (saveOrImport == "s" || saveOrImport == "S") {
        cout << "Quel est le nom du fichier dans lequel vous voulez sauvegarder ? \n";
        do {
            valid = false;
            getline(cin, fileName);
            if (isValidFileName(fileName)) valid = true;
        } while (!valid);
        fileName += ".txt";
        writeTasks(fileName);
    }

    else if (saveOrImport == "i" || saveOrImport == "I") {
        cout << "Quel est le nom du fichier dans lequel est votre sauvegarde ? \n";
        do {
            do {
                valid = false;
                getline(cin, fileName);
                if (fileName != "") valid = true;
            } while (!valid);
            valid = false;
            if (readTasks(fileName)) valid = true;            
        } while(!valid);       
    }

    mainMenu();
}

bool Clicker::isValidFileName(string nameFile) {
    for (int i; i<nameFile.size(); i++) {
        if (nameFile[i] == ' ' || nameFile[i] == '\\' ||
            nameFile[i] == '/' || nameFile[i] == ':' ||
            nameFile[i] == '*' || nameFile[i] == '?' ||
            nameFile[i] == '"' || nameFile[i] == '<' ||
            nameFile[i] == '>' || nameFile[i] == '|')
        return false;
    }
    return true;
}