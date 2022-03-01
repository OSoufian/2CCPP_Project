// RECUPERER LES CLICKS

#include <iostream>
#include <ctime>
#include <Windows.h>

using namespace std;

int keyPressed(int key){
    return (GetAsyncKeyState(key) & 0x8000 != 0);
}

int main() {
    while(!keyPressed(VK_LBUTTON)) {
        POINT point;
        if(keyPressed(VK_LBUTTON)) {
            cout << "Click gauche\n";
            if (GetCursorPos(&point)) cout << point.x << "," << point.y << "\n";
            return 0;
        }

        if(keyPressed(VK_RBUTTON)) {
            cout << "Click droit\n";
            if (GetCursorPos(&point)) cout << point.x << "," << point.y << "\n";  
        }
    }
    return 0;
}

// #include <windows.h>

// #define WINDOW_POS_X   0
// #define WINDOW_POS_Y   0
// #define CLIENT_SIZE_X  400
// #define CLIENT_SIZE_Y  300
// #define COLOR_BACK     RGB(   0,   0,  80 )
// #define COLOR_FORE     RGB( 200, 200,  50 )

// HBRUSH hbrBack;
// BOOL do_mouse_move = FALSE;

// void wmLButtonDblClk( HWND hwnd, WPARAM wp, LPARAM lp )
// {
//     InvalidateRect( hwnd, NULL, TRUE ); // erase window
// }

// void wmLButtonDown( HWND hwnd, WPARAM wp, LPARAM lp )
// {
//     do_mouse_move = true;
//     SetCapture( hwnd ); // so we'll get the button-up msg even
//                         // if the cursor is off of the window
// }

// void wmLButtonUp( HWND hwnd, WPARAM wp, LPARAM lp )
// {
//     do_mouse_move = false;
//     ReleaseCapture();
// }

// void wmMouseMove( HWND hwnd, WPARAM wp, LPARAM lp )
// {
//     POINT p;
//     HDC hdc;
//     if( !do_mouse_move ) return;
//     p = (POINT) { LOWORD( lp ), HIWORD( lp ) }; // x-pos, y-pos
//     hdc = GetDC( hwnd );
//     ReleaseDC( hwnd, hdc );
// }

// void wmDestroy( HWND hwnd, WPARAM wp, LPARAM lp )
// {
//     PostQuitMessage( 0 );
// }

// LRESULT CALLBACK wndproc( HWND hwnd, UINT msg, WPARAM wp, LPARAM lp )
// {
//     switch( msg )
//     {
//     case WM_MOUSEMOVE:     wmMouseMove(     hwnd, wp, lp );  break;
//     case WM_LBUTTONDOWN:   wmLButtonDown(   hwnd, wp, lp );  break;
//     case WM_LBUTTONUP:     wmLButtonUp(     hwnd, wp, lp );  break;
//     case WM_LBUTTONDBLCLK: wmLButtonDblClk( hwnd, wp, lp );  break;
//     case WM_DESTROY:       wmDestroy(       hwnd, wp, lp );  break;
//     default:        return DefWindowProc(   hwnd, msg, wp, lp );
//     }
//     return 0;
// }

// int WINAPI WinMain( HINSTANCE hinst, HINSTANCE unused,
//                     PSTR cmd, int show )
// {
//     MSG msg;
//     while( GetMessage( &msg, NULL, 0, 0 ))
//     {
//         TranslateMessage( &msg );
//         DispatchMessage( &msg );
//     }

//     DeleteObject( hbrBack );
//     return msg.wParam;
// }