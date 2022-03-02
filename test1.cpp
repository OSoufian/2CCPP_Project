// RECUPERER LES CLICKS

#include <iostream>
#include <ctime>
#include <Windows.h>
#include <vector>

using namespace std;

struct Int2
{
    int a[2];
};

int keyPressed(int key)
{
    return (GetKeyState(key) & 1 != 0);
}

DWORD ClickType(int key)
{
    if (key == VK_LBUTTON)
        return 0x0002;
    if (key == VK_RBUTTON)
        return 0x0008;
    return 0;
}

DWORD ClickType2(int key)
{
    if (key == VK_LBUTTON)
        return 0x0004;
    if (key == VK_RBUTTON)
        return 0x0010;
    return 0;
}

bool isHeld(int posx, int posy, int key)
{
    if (keyPressed(key))
    {
        mouse_event(ClickType(key), posx, posy, 0, 0);
        return true;
    }
    if (!keyPressed(key))
    {
        mouse_event(ClickType2(key), posx, posy, 0, 0);
        return false;
    }
    return false;
}

void captureClick(int key)
{
    vector<Int2> moves;
    bool hearing = true;
    POINT point;
    int pos[2];
    while (hearing)
    {
        if (keyPressed(key) && GetCursorPos(&point))
        {
            pos[0] = point.x;
            pos[1] = point.y;
            SetCursorPos(pos[0], pos[1]);
            mouse_event(ClickType(key), pos[0], pos[1], 0, 0);
            mouse_event(ClickType2(key), pos[0], pos[1], 0, 0);
        }

        do
        {
            if (GetCursorPos(&point))
            {
                pos[0] = point.x;
                pos[1] = point.y;
            }
        } while (!keyPressed(key));

        int counter = 0;

        while (isHeld(pos[0], pos[1], key))
        {
            if (GetCursorPos(&point))
                moves.push_back({point.x, point.y});
            if (key == VK_LBUTTON)
                cout << "Click gauche\n";
            else
                cout << "Click droit\n";
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
        cout << pos[0] << "," << pos[1] << "\n";

        hearing = false;
    }
}

int main()
{
    bool clicked = false;
    while (!clicked)
    {
        if (keyPressed(VK_LBUTTON))
        {
            captureClick(VK_LBUTTON);
            clicked = true;
        }
        else if (keyPressed(VK_RBUTTON))
        {
            captureClick(VK_RBUTTON);
            clicked = true;
        }
    }
    return 0;
}