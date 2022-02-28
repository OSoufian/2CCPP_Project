// RECUPERER LES CLICKS

#include <iostream>
#include <ctime>
#include <Windows.h>

using namespace std;

int keyPressed(int key){
    return (GetAsyncKeyState(key) & 0x8000 != 0);
}

int main(){
    while(true){
        POINT point;

        if(keyPressed(VK_LBUTTON)) {
            cout << "Click gauche\n";            
            if (GetCursorPos(&point)) {
            cout << point.x << "," << point.y << "\n";
            }
        }

        if(keyPressed(VK_RBUTTON)) {
            cout << "Click droit\n";   
        }
    }
    return 0;
}