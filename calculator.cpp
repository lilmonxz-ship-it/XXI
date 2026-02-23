#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define ID_BTN_PLUS 1
#define ID_BTN_MINUS 2
#define ID_BTN_MUL 3
#define ID_BTN_DIV 4


HWND hEdit1, hEdit2;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch(Message) {
        
        
        case WM_CREATE: {
            
            CreateWindow("STATIC", "Please input two numbers", 
                         WS_VISIBLE | WS_CHILD | SS_CENTER,
                         25, 20, 180, 20, hwnd, NULL, NULL, NULL);

            
            hEdit1 = CreateWindow("EDIT", "", 
                                  WS_VISIBLE | WS_CHILD | WS_BORDER,
                                  50, 50, 130, 20, hwnd, NULL, NULL, NULL);

            
            hEdit2 = CreateWindow("EDIT", "", 
                                  WS_VISIBLE | WS_CHILD | WS_BORDER,
                                  50, 80, 130, 20, hwnd, NULL, NULL, NULL);

            
            CreateWindow("BUTTON", "+", WS_VISIBLE | WS_CHILD, 
                         45, 115, 30, 30, hwnd, (HMENU)ID_BTN_PLUS, NULL, NULL);
            CreateWindow("BUTTON", "-", WS_VISIBLE | WS_CHILD, 
                         85, 115, 30, 30, hwnd, (HMENU)ID_BTN_MINUS, NULL, NULL);
            CreateWindow("BUTTON", "*", WS_VISIBLE | WS_CHILD, 
                         125, 115, 30, 30, hwnd, (HMENU)ID_BTN_MUL, NULL, NULL);
            CreateWindow("BUTTON", "/", WS_VISIBLE | WS_CHILD, 
                         165, 115, 30, 30, hwnd, (HMENU)ID_BTN_DIV, NULL, NULL);
            break;
        }

        
        case WM_COMMAND: {
            int wmId = LOWORD(wParam);
            
            
            if (wmId >= ID_BTN_PLUS && wmId <= ID_BTN_DIV) {
                char text1[100], text2[100], resultText[100];
                
                
                GetWindowText(hEdit1, text1, 100);
                GetWindowText(hEdit2, text2, 100);

                
                double num1 = atof(text1);
                double num2 = atof(text2);
                double result = 0.0;

                
                switch(wmId) {
                    case ID_BTN_PLUS: result = num1 + num2; break;
                    case ID_BTN_MINUS: result = num1 - num2; break;
                    case ID_BTN_MUL: result = num1 * num2; break;
                    case ID_BTN_DIV: 
                        if (num2 == 0) {
                            MessageBox(hwnd, "Cannot divide by zero!", "Error", MB_OK | MB_ICONERROR);
                            return 0;
                        }
                        result = num1 / num2; 
                        break;
                }

                
                sprintf(resultText, "%f", result);
                MessageBox(hwnd, resultText, "Result", MB_OK);
            }
            break;
        }
        
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
        
        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc; 
    HWND hwnd; 
    MSG msg; 

    memset(&wc,0,sizeof(wc));
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.lpfnWndProc   = WndProc; 
    wc.hInstance     = hInstance;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    
    
    wc.hbrBackground = CreateSolidBrush(RGB(205, 0, 100)); 
    wc.lpszClassName = "WindowClass";
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION); 
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION); 

    if(!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
        return 0;
    }

    
    hwnd = CreateWindowEx(
        0, 
        "WindowClass", 
        "My Calculator",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE, 
        CW_USEDEFAULT, CW_USEDEFAULT, 
        250, 200,
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
        return 0;
    }

    while(GetMessage(&msg, NULL, 0, 0) > 0) { 
        TranslateMessage(&msg); 
        DispatchMessage(&msg); 
    }
    return msg.wParam;
}
