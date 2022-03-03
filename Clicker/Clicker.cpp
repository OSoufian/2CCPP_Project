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

struct Int2 {
    int a[2];
};

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
        Menu::tasksListMenu();
        displayTasks();
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
                cout << "Le temps de maintien du clique est de : " << this->_tasks[i].getClicks()[j].getDuration() << " secondes"<< endl;
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

            if (hour < 10)
                cout << "0" << hour << ":";
            else
                cout << hour << ":";
            if (minutes < 10)
                cout << "0" << minutes << ":";
            else
                cout << minutes << ":";
            if (seconds < 10)
                cout << "0" << seconds << endl;
            else
                cout << seconds << endl;
        }
        else
            cout << "lancement manuel\n";
        cout << endl;
    }
}

int Clicker::keyPressed(int key) {
    return (GetKeyState(key) & 1 != 0);
}

DWORD Clicker::ClickType(int key) {
    if (key == VK_LBUTTON)
        return 0x0002;
    if (key == VK_RBUTTON)
        return 0x0008;
    return 0;
}

DWORD Clicker::ClickType2(int key) {
    if (key == VK_LBUTTON)
        return 0x0004;
    if (key == VK_RBUTTON)
        return 0x0010;
    return 0;
}

bool Clicker::isHeld(int posx, int posy, int key) {
    if (keyPressed(key)) {
        mouse_event(ClickType(key), posx, posy, 0, 0);
        return true;
    }
    if (!keyPressed(key)) {
        mouse_event(ClickType2(key), posx, posy, 0, 0);
        return false;
    }
    return false;
}

Click Clicker::captureClick(int key) {
    vector<Int2> moves;
    bool hearing = true;
    POINT point;
    int pos[2];
    while (hearing) {
        if (keyPressed(key) && GetCursorPos(&point)) {
            pos[0] = point.x;
            pos[1] = point.y;
            SetCursorPos(pos[0], pos[1]);
            mouse_event(ClickType(key), pos[0], pos[1], 0, 0);
            mouse_event(ClickType2(key), pos[0], pos[1], 0, 0);
        }

        do {
            if (GetCursorPos(&point)) {
                pos[0] = point.x;
                pos[1] = point.y;
            }
        } while (!keyPressed(key));

        int counter = 0;

        while (isHeld(pos[0], pos[1], key)) {
            if (GetCursorPos(&point))
                moves.push_back({point.x, point.y});
            Sleep(50);
            counter += 50;
        }

        for (int i = 0; i < moves.size(); i++) {
            int posi[2];
            posi[0] = moves[i].a[0];
            posi[1] = moves[i].a[1];
        }
        
        hearing = false;
        Click click(pos[0], pos[1], ClickType(key), true, (counter / 1000));
        return click;
    }
    return Click();
}

// AJOUTER UNE TACHE

void Clicker::addTask() {
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

    Menu::addTaskMenu();

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
                std::cout << "Quel est la duree de votre clique (en secondes) ?\n";
                do
                {
                    valid = false;
                    std::cin >> clickDuration;
                    valid = isDigit(clickDuration);
                } while (!valid);
            }

            std::cout << "Quel est le type de votre clique ? ([g]gauche/[d]droit)\n";
            do {
                valid = false;
                std::cin >> typeClick;
                if (typeClick == "d" || typeClick == "g")
                {
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
        if (consoleOrCapture == "c") {
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
    while (!task.getTimeExecution().isNow())
        Sleep(1000);
    task.run();
}

// RENOMMER UNE TACHE

void Clicker::renameTask() {
    char action;
    bool valid = false;

    string taskIndex;
    string newTaskName;

    Menu::renameTaskMenu();
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

void Clicker::deleteTask() {
    bool valid = false;

    string taskIndex;
    string newTaskName;

    Menu::deleteTaskMenu();
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

    Menu::runTaskMenu();
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

void Clicker::duplicateTask() {
    string taskIndex;
    Task newTask;
    string newTaskName;
    bool valid = false;

    Menu::duplicateTaskMenu();
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

void Clicker::history() {
    char action;
    bool valid = false;
    do {
        Menu::historyTaskMenu();
        displayHistory();
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

    Menu::saveTaskMenu();
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