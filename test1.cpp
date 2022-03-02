// RECUPERER LES CLICKS

#include <iostream>
#include <ctime>
#include <Windows.h>
#include <vector>

using namespace std;

struct Int2 {
    int a[2];
};

int keyPressed(int key){
    return (GetKeyState(key) & 1 != 0);
}

// DWORD ClickType(){
//     if(keyPressed(VK_LBUTTON)){
//         return 0x0002;
//     }
//     if(keyPressed(VK_RBUTTON)){
//         return 0x0008;
//     }
//     return 0;
// }

// DWORD ClickType2(){
//     if(keyPressed(VK_LBUTTON)){
//         return 0x0004;
//     }
//     if(keyPressed(VK_RBUTTON)){
//         return 0x0010;
//     }
//     return 0;
// }

bool isHeld(int posx, int posy, int key){
    if(keyPressed(key)) {
        mouse_event(0x0002, posx, posy, 0, 0);
        return true;
    }
    if(!keyPressed(key)) {
        mouse_event(0x0004, posx, posy, 0, 0);
        return false;
    }
    return false;
}

int main() {
    vector<Int2> moves;
    bool hearing = true;
    POINT point;
    int pos[2];
    while(hearing) {

        if(keyPressed(VK_LBUTTON) && GetCursorPos(&point)) {
            pos[0] = point.x;
            pos[1] = point.y;
            SetCursorPos(pos[0], pos[1]);
            mouse_event(0x0002, pos[0], pos[1], 0, 0);
            mouse_event(0x0004, pos[0], pos[1], 0, 0);
        }

        do {
            if (GetCursorPos(&point)) {
                pos[0] = point.x;
                pos[1] = point.y;
            }
        } while(!keyPressed(VK_LBUTTON));

        int counter = 0;

        while(isHeld(pos[0], pos[1], VK_LBUTTON)){
            if (GetCursorPos(&point)) {
                moves.push_back({point.x, point.y});
            }
            if(keyPressed(VK_LBUTTON)) cout << "Click gauche\n";
            Sleep(50);
            counter += 50;
        }

        for (int i = 0; i < moves.size(); i++)
        {
            int posi[2];
            posi[0] = moves[i].a[0];
            posi[1] = moves[i].a[1];
            cout << posi[0] << "," << posi[1] << "\n";
        }
        
        cout << counter << endl;
        cout << "Click gauche\n";
        cout << pos[0] << "," << pos[1] << "\n";

        hearing = false;
    }
    return 0;
}