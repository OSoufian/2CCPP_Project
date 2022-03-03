#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <Windows.h>
#include <thread>

#include "Clicker.hpp"
#include "../Time/Time.hpp"
#include "../Task/Task.hpp"
#include "../Menu/Menu.hpp"

using namespace std;

Clicker::Clicker() {
    mainMenu();
}

void Clicker::mainMenu() {
    string action;
    bool valid = false;

    do {
        Menu::mainMenu();
        cin >> action;
        valid = getMainAction(action);
    } while (!valid);
}

bool Clicker::getMainAction(string action) {
    if (action == "V" || action == "v") {
        tasksList();
        return true;
    }
    else if (action == "A" || action == "a") {
        addTask();
        return true;
    }
    else if (action == "R" || action == "r") {
        renameTask();
        return true;
    }
    else if (action == "S" || action == "s") {
        deleteTask();
        return true;
    }
    else if (action == "D" || action == "d") {
        duplicateTask();
        return true;
    }
    else if (action == "L" || action == "l") {
        runTask();
        return true;
    }
    else if (action == "H" || action == "h") {
        history();
        return true;
    }
    else if (action == "I" || action == "i") {
        saveTask();
        return true;
    }
    else if (action == "Q" || action == "q") {
        exit(0);
    }
    else {
        return false;
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

void Clicker::tasksList() {
    char action;
    bool valid = false;
    do {
        Menu::showMenu("LISTE DES TÂCHES");
        displayTasks();
        cin >> action;
        valid = getActionWithoutInput(action);
    } while (!valid);
}

void Clicker::displayTasks() {
    for (int i = 0; i < this->_tasks.size(); i++) {
        Task task = this->_tasks[i];
        cout << task.getName() << ":" << endl;
        for (int j = 0; j < task.getClicks().size(); j++) {
            Click click = task.getClicks()[j];
            cout << "Position du clic " << (j + 1) << ": (" << click.getX() << ", " << click.getY() << ")" << endl;
            cout << "Type du clic: ";
            if (click.getType() == VK_LBUTTON) cout << "gauche\n";
            else cout << "droit\n";
            if (click.getIsHeld())
                cout << "Le temps de maintien du clic est de: " << click.getDuration() << " secondes\n";
        }

        cout << "Nombres de répétitions du cycle: ";
        if (this->_tasks[i].getIsInfiniteCycle())
            cout << "en boucle\n";
        else
            cout << this->_tasks[i].getCycleRepetitions() << endl;
        cout << "Temps d'intervalle entre 2 cycles: " << this->_tasks[i].getTimeInterval();
        if (this->_tasks[i].getTimeInterval() < 2) cout  << " seconde\n";
        else cout << " secondes\n";

        cout << "Heure d'exécution: ";
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
        else cout << "lancement manuel\n";
        cout << endl;
    }
}

int Clicker::keyPressed(int key) {
    return (GetKeyState(key) & 1 != 0);
}

DWORD Clicker::heldClickType(int key) {
    if (key == VK_LBUTTON)
        return 0x0002;
    if (key == VK_RBUTTON)
        return 0x0008;
    return 0;
}

DWORD Clicker::notHeldClickType(int key) {
    if (key == VK_LBUTTON)
        return 0x0004;
    if (key == VK_RBUTTON)
        return 0x0010;
    return 0;
}

bool Clicker::isHeld(int posx, int posy, int key) {
    if (keyPressed(key)) {
        mouse_event(heldClickType(key), posx, posy, 0, 0);
        return true;
    }
    if (!keyPressed(key)) {
        mouse_event(notHeldClickType(key), posx, posy, 0, 0);
        return false;
    }
    return false;
}

Click Clicker::captureClick(int key) {
    bool hearing = true;
    POINT point;
    int pos[2];
    while (hearing) {
        if (keyPressed(key) && GetCursorPos(&point)) {
            pos[0] = point.x;
            pos[1] = point.y;
            SetCursorPos(pos[0], pos[1]);
            mouse_event(heldClickType(key), pos[0], pos[1], 0, 0);
            mouse_event(notHeldClickType(key), pos[0], pos[1], 0, 0);
        }

        do {
            if (GetCursorPos(&point)) {
                pos[0] = point.x;
                pos[1] = point.y;
            }
        } while (!keyPressed(key));

        int counter = 0;

        while (isHeld(pos[0], pos[1], key)) {
            Sleep(50);
            counter += 50;
        }
        
        hearing = false;
        Click click(pos[0], pos[1], heldClickType(key), true, (counter / 1000));
        return click;
    }
    return Click();
}

// AJOUTER UNE TACHE

void Clicker::addTask() {
    bool valid = false;
    int steps;

    char consoleOrCapture;
    bool isClickCapturing;

    // Attribut des tâches
    string taskName;
    string numberClicks;
    string cycleRepetitions = "0";
    string infiniteCycle;
    bool isInfiniteCycle;
    string scheduled;
    bool isScheduled;
    string timeInterval;
    string hour;
    string minutes;
    string seconds;

    // Attribut des clics
    string position[2];    
    string typeClick;
    DWORD clickType;
    string clickHeld;
    bool isClickHeld;
    string clickDuration = "0";

    Menu::showMenu("AJOUTER UNE TÂCHE");
    std::cout << "Quel est le nom de la tâche ?\n";
    do {
        getline(std::cin, taskName);
        if (taskName != "")
            valid = true;
    } while (!valid);

    // ------------------ Instructions pour un clic ------------------ //
    std::cout << "Quel est le nombre de clics que vous voulez dans votre cycle?\n";
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
        if (consoleOrCapture == 'c' || consoleOrCapture == 'd') {
            if (consoleOrCapture == 'c')
                isClickCapturing = false;
            else
                isClickCapturing = true;
            valid = true;
        }
    } while (!valid);

    do {
        if (consoleOrCapture == 'c') {
            std::cout << "Voulez vous maintenir votre click ? ([o]oui/[N]non)\n";
            do {
                valid = false;
                std::cin >> clickHeld;
                if (clickHeld == "oui" || clickHeld == "o" || clickHeld == "O" || clickHeld == "non" || clickHeld == "n" || clickHeld == "N")
                {
                    if (clickHeld == "oui" || clickHeld == "o")
                        isClickHeld = true;
                    else
                        isClickHeld = false;
                    valid = true;
                }
            } while (!valid);

            if (isClickHeld) {
                std::cout << "Quel est la duree de votre clic (en secondes) ?\n";
                do
                {
                    valid = false;
                    std::cin >> clickDuration;
                    valid = isDigit(clickDuration);
                } while (!valid);
            }

            std::cout << "Quel est le type de votre clic ? ([g]gauche/[d]droit)\n";
            do {
                valid = false;
                std::cin >> typeClick;
                if (typeClick == "d" || typeClick == "g")
                {
                    if (typeClick == "d")
                        clickType = VK_RBUTTON;
                    else
                        clickType = VK_LBUTTON;
                    valid = true;
                }
            } while (!valid);

            std::cout << "Quel est la position de votre clic ? (entrez d'abord le x puis le y)\n";
            do {
                valid = false;
                std::cin >> position[0];
                std::cin >> position[1];
                valid = (isDigit(position[0]) && isDigit(position[1]));
            } while (!valid);
        }
        else {
            std::cout << "Veuillez cliquer sur l'écran pour enregistrer votre click !\n";
            bool clicked = false;
            while (!clicked) {
                if (keyPressed(VK_LBUTTON))
                {
                    task.addClick(captureClick(VK_LBUTTON));
                    clicked = true;
                }
                else if (keyPressed(VK_RBUTTON))
                {
                    task.addClick(captureClick(VK_RBUTTON));
                    clicked = true;
                }
            }
        }
        if (consoleOrCapture == 'c') {
            Click click(stoi(position[0]), stoi(position[1]), clickType, isClickHeld, stoi(clickDuration));
            task.addClick(click);
        }
        steps--;
    } while (steps != 0);

    std::cout << "Voulez vous que le cycle se répète indéfiniment? (oui/non)\n";
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

    std::cout << "Voulez vous definir une heure d'exécution pour cette tâche ? ([o]oui/[n]non)\n";
    do {
        valid = false;
        std::cin >> scheduled;
        if (scheduled == "oui" || scheduled == "o" || scheduled == "O" || scheduled == "non" || scheduled == "n" || scheduled == "N") {
            if (scheduled == "oui" || scheduled == "o" || scheduled == "O") {
                isScheduled = true;
                task.setIsScheduled(isScheduled);
            }
            else
                isScheduled = false;
            valid = true;
        }
    } while (!valid);

    if (isScheduled) {
        std::cout << "À quelle heure ?\n";
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
    while (!task.getTimeExecution().isNow())
        Sleep(1000);
    task.run();
}

void Clicker::renameTask() {
    char action;
    bool valid = false;

    string taskIndex;
    string newTaskName;

    Menu::showMenu("RENNOMER UNE TÂCHE");
    do {
        cin >> taskIndex;
        if (isDigit(taskIndex) && validTaskIndex(stoi(taskIndex)))
            valid = true;
    } while (!valid);

    cout << "Quel est le nouveau nom pour cette tâche ? \n";
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

void Clicker::deleteTask() {
    bool valid = false;

    string taskIndex;
    string newTaskName;

    Menu::showMenu("SUPPRIMER UNE TÂCHE");
    do {
        cin >> taskIndex;
        if (isDigit(taskIndex) && validTaskIndex(stoi(taskIndex)))
            valid = true;
    } while (!valid);

    this->_tasks.erase(this->_tasks.begin() + stoi(taskIndex) - 1);

    mainMenu();
}

// LANCER UNE TACHE

void Clicker::runTask() {
    bool valid = false;

    string taskIndex;

    Menu::showMenu("LANCER UNE TÂCHE");
    cout << "Quel est le numéro de la tâche ?\n";
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

void Clicker::duplicateTask() {
    string taskIndex;
    Task newTask;
    string newTaskName;
    bool valid = false;

    Menu::showMenu("DUPPLIQUER UNE TÂCHE");
    cout << "Quel est le numéro de la tâche que vous voulez ?\n";
    do {
        cin >> taskIndex;
        if (isDigit(taskIndex) && validTaskIndex(stoi(taskIndex)))
            valid = true;
    } while (!valid);

    cout << "Quel est le nom pour cette nouvelle tâche ? \n";
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

void Clicker::history() {
    char action;
    bool valid = false;
    do {
        Menu::showMenu("HISTORIQUE DES TÂCHES");
        displayHistory();
        cin >> action;
        valid = getActionWithoutInput(action);
    } while (!valid);
}

void Clicker::displayHistory() {
    for (int i = 0; i < this->_history.size(); i++) {
        time_t timeExecution = this->_history[i].getTimeExecution();

        cout << "Nom de la tâche : " << this->_history[i].getName() << endl;
        cout << "Heure : " << ctime(&timeExecution);
        cout << "Duree : " << this->_history[i].getDuration().count() << " secondes\n\n";
    }
}

// IMPORTER/SAUVEGARDER TACHES

void Clicker::writeTasks(string fileName) {
    int tasks = this->_tasks.size();
    ofstream file(fileName);
    file << tasks << endl;
    for (int i = 0; i < tasks; i++)
        this->_tasks[i].write(&file);
    file.close();
}

bool Clicker::readTasks(string fileName) {
    ifstream file;
    file.open(fileName, ios::in);
    if (file.fail())
        return false;
    int tasks;
    file >> tasks;
    for (int i = 0; i < tasks; i++)
        this->_tasks.push_back(Task::read(&file));
    file.close();
    return true;
}

void Clicker::saveTask() {
    bool valid = false;
    string saveOrImport;
    string fileName;

    Menu::showMenu("SAUVEGARDER UNE TÂCHE");
    cout << "Voulez-vous sauvegarder ou importer une sauvegarde de tâches ? (S/I)\n";
    do {
        valid = false;
        cin >> saveOrImport;
        if (saveOrImport == "I" || saveOrImport == "i" || saveOrImport == "S" || saveOrImport == "s")
            valid = true;
    } while (!valid);

    if (saveOrImport == "s" || saveOrImport == "S") {
        cout << "Quel est le nom du fichier dans lequel vous voulez sauvegarder ? \n";
        do {
            valid = false;
            getline(cin, fileName);
            if (isValidFileName(fileName))
                valid = true;
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
                if (fileName != "")
                    valid = true;
            } while (!valid);
            valid = false;
            if (readTasks(fileName))
                valid = true;
        } while (!valid);
    }

    mainMenu();
}

bool Clicker::isValidFileName(string nameFile) {
    for (int i; i < nameFile.size(); i++) {
        if (nameFile[i] == ' ' || nameFile[i] == '\\' ||
            nameFile[i] == '/' || nameFile[i] == ':' ||
            nameFile[i] == '*' || nameFile[i] == '?' ||
            nameFile[i] == '"' || nameFile[i] == '<' ||
            nameFile[i] == '>' || nameFile[i] == '|')
            return false;
    }
    return true;
}