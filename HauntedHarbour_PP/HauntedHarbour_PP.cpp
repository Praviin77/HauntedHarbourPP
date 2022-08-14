// HauntedHarbour_PP.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "HauntedHarbour_PP.h"
#include "GraphicsObject.h"
#include "PlayerObject.h"
#include "BackgroundObject.h"
#include "EnemyObject.h"
#include "GroundEnemy.h"
#include "FlyingEnemy.h"
#include "LightHouseKeeper.h"
#include "HungrySailor.h"
#include "LifeBar.h"
#include "LifeBarEnemy.h"
#include <stdio.h>
#include <iostream>
#include <string>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HDC offScreenDC;        // buffer

int mapPosition = 0;
int windowWidth = 700;
int windowHeight = 580;
int numBlocks = 0;
int numEnemies = 0;
int level = 1;

bool bStartGame = false;
bool bPauseGame = false;
bool gameOver = false;

// Create our objects
PlayerObject viktor;
BackgroundObject backdrop("../Pics/Background3.jpg", 0, 0, 5118, 800, 0.2);
BackgroundObject ground("../Pics/Ground.bmp", 0, GROUND, 774, 128, 1);
BackgroundObject startScreen("../Pics/TitleScreen.jpg", 0, 0, windowWidth, 550, 0);
BackgroundObject pauseScreen("../Pics/Pause.jpg", 0, 0, 700, 550, 0);
BackgroundObject gameOverScreen("../Pics/GameOver.jpg", 0, 0, 700, 550, 0);
GraphicsObject* crateArray[100];
EnemyObject* enemyArray[100];
LifeBar lifeBar(&viktor);

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void SetScreen();
void DrawScreen(HWND hWnd);
void LoadMap();
void nextLevel();


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_HAUNTEDHARBOURPP, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HAUNTEDHARBOURPP));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HAUNTEDHARBOURPP));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_HAUNTEDHARBOURPP);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, windowWidth, windowHeight, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   LoadMap();

   SetScreen();

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_RIGHT:
        case 'D':
            if (viktor.IsJumping() == true)
            {
                viktor.picY = 86;
                viktor.xSpeed = 10;
                viktor.state = JUMP_RIGHT;
            }
            else
            {
                viktor.setMoveRight();
            }
            viktor.bIsStoppedRight = false;
            break;

        case VK_LEFT:
        case 'A':
            if (viktor.IsJumping() == true)
            {
                viktor.picY = 146;
                viktor.xSpeed = -10;
                viktor.state = JUMP_LEFT;
            }
            else
            {
                viktor.setMoveLeft();
            }
            viktor.bIsStoppedLeft = false;
            break;

        case VK_UP:
        case 'W':
            if (viktor.state == MOVE_RIGHT || viktor.state == STAND_RIGHT)
            {
                viktor.setJumpRight();
            }
            else if (viktor.state == MOVE_LEFT || viktor.state == STAND_LEFT)
            {
                viktor.setJumpLeft();
            }
            break;

        case 'P':
            bPauseGame = !bPauseGame;
            break;

        case VK_SPACE:
            if (viktor.state == STAND_RIGHT)
            {
                viktor.setShootRight();
            }
            else if (viktor.state == STAND_LEFT)
            {
                viktor.setShootLeft();
            }
            if (viktor.state == STAND_RIGHT ||
                viktor.state == MOVE_RIGHT || 
                viktor.state == JUMP_RIGHT ||
                viktor.state == SHOOT_RIGHT)
            {
                viktor.FireBullet(viktor.xPos + viktor.width - 15, viktor.yPos + 10, 20 + viktor.xSpeed, 0);
            }
            if (viktor.state == STAND_LEFT ||
                viktor.state == MOVE_LEFT ||
                viktor.state == JUMP_LEFT ||
                viktor.state == SHOOT_LEFT)
            {
                viktor.FireBullet(viktor.xPos, viktor.yPos + 10, -20 + viktor.xSpeed, 0);
            }
            break;

        case VK_RETURN:
            if (bStartGame == false)
            {
                bStartGame = true;
                SetTimer(hWnd, 1, 50, NULL);
            }
            break;
        }
    }
    break;

    case WM_KEYUP:
    {
        switch (wParam)
        {
        case VK_RIGHT:
        case 'D':
            if (viktor.IsJumping() == false)
            {
                viktor.setStandRight();
            }
            viktor.bIsStoppedRight = true;
            break;
        case VK_LEFT:
        case 'A':
            if (viktor.IsJumping() == false)
            {
                viktor.setStandLeft();
            }
            viktor.bIsStoppedLeft = true;
            break;
        }
        case VK_SPACE:
            if (viktor.state == SHOOT_RIGHT)
            {
                viktor.setStandRight();
            }
            else if (viktor.state == SHOOT_LEFT)
            {
                viktor.setStandLeft();
            }
            break;
    }
    break;

    case WM_TIMER:
    {
        if (viktor.lives <= 0)
        {
            gameOver = true;
        }
        if (bPauseGame == false && gameOver == false)
        {
            viktor.Move();
            viktor.MoveBullets();

            for (int i = 0; i < numBlocks; i++)
            {
                viktor.CheckPlayerCollisionWithEntity(crateArray[i]);
                viktor.CheckBulletCollisionWithCrate(crateArray[i]);
            }

            for (int i = 0; i < numEnemies; i++)
            {
                enemyArray[i]->Move(&viktor);
                enemyArray[i]->MoveBullets();

                if (enemyArray[i]->bIsAlive == true)
                {
                    viktor.CheckBulletCollisionWithEntity(enemyArray[i]);
                }
                enemyArray[i]->CheckBulletCollisionWithEntity(&viktor);

                for (int j = 0; j < numBlocks; j++)
                {
                    enemyArray[i]->CheckCollisionWithCrate(crateArray[j]);
                }
            }

            nextLevel();
        }
        PostMessage(hWnd, WM_PAINT, 0, 0); // refresh screen
    }
    break;

    case WM_PAINT:
    {
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            
            if (bStartGame == true)
            {
                backdrop.Draw(offScreenDC);
                ground.Draw(offScreenDC);

                for (int i = 0; i < numBlocks; i++)
                {
                    crateArray[i]->Draw(offScreenDC);
                }

                for (int i = 0; i < numEnemies; i++)
                {
                    enemyArray[i]->Draw(offScreenDC);
                    enemyArray[i]->DrawBullet(offScreenDC);
                }
                viktor.Draw(offScreenDC);
                viktor.DrawBullet(offScreenDC);
                lifeBar.Draw(offScreenDC);
            }
            else
            {
                startScreen.Draw(offScreenDC);
            }
            
            if (bPauseGame == true)
            {
                pauseScreen.Draw(offScreenDC);
            }

            if (gameOver == true)
            {
                gameOverScreen.Draw(offScreenDC);
            }

            DrawScreen(hWnd);
            EndPaint(hWnd, &ps);
        }
    }
    break;
    case WM_DESTROY:
    {
        // Delete block and enemy array after instantiation

        for (int i = 0; i < numEnemies; i++)
        {
            delete enemyArray[i];
        }

        for (int i = 0; i < numBlocks; i++)
        {
            delete crateArray[i];
        }

        PostQuitMessage(0);
    }
    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void SetScreen()
{
    HDC _hTempDC;           // Replacing screen
    HBITMAP _offScreenBMP;  // Replacing image

    _hTempDC = GetDC(0);

    // Initalize buffer image
    offScreenDC = CreateCompatibleDC(_hTempDC);
    _offScreenBMP = CreateCompatibleBitmap(_hTempDC, 800, 600);

    SelectObject(offScreenDC, _offScreenBMP);

    ReleaseDC(0, _hTempDC);
}

void DrawScreen(HWND hWnd)
{
    HDC _screenDC = GetDC(hWnd); //The screen

    // Draw on the screen
    TransparentBlt(_screenDC,   //Destination Device Context 
        0,                      // x position of the destination DC
        0,                      // y position of the destination DC
        windowWidth,            // width of the dest DC
        windowHeight,           // height of the dest DC
        offScreenDC,            //Source Device Context
        0,                      // x position of the source DC
        0,                      // y position of the destination DC
        windowWidth,            // width of the src DC
        windowHeight,           // height of the src DC
        RGB(255,174,201));      // Pink transparency            
}

void LoadMap()
{
    FILE* _level1;

    char _fnameBuf[25];
    sprintf_s(_fnameBuf, _countof(_fnameBuf), "../Levels/Level%d.txt", level);

    /*std::string levelFile = "../Levels/Level" + std::to_string(level) + ".txt";
    char* c = const_cast<char*>(levelFile.c_str());*/

    // check for errrs, then read the text file
    errno_t chkErr = fopen_s(&_level1, _fnameBuf, "r");


    char _section[80];
    int _index = 0;
    int _x = 0;
    int _y = 0;

    while (true)
    {
        // read string from the text file labelled as section
        fscanf_s(_level1, "%s", _section, _countof(_section));
        
        // read each section and set each entitiy position based on there index number
        if (strcmp(_section, "[Viktor]") == 0)
        {
            while (true)
            {
                // read the numerical values from the txt file labelled respectively as index, x pos, ypos
                fscanf_s(_level1, "%d %d %d", &_index, &_x, &_y);

                if (_index == -1)
                {
                    break;
                }

                viktor.xPos = _x;
                viktor.yPos = _y;
            }
        }

        if (strcmp(_section, "[Little-Block]") == 0)
        {
            while (true)
            {
                // read the numerical values from the txt file labelled respectively as index, x pos, ypos
                fscanf_s(_level1, "%d %d %d", &_index, &_x, &_y);

                if (_index == -1)
                {
                    break;
                }

                crateArray[numBlocks] = new GraphicsObject("../Pics/SmallCrate.bmp", _x, _y, 32, 32);
                numBlocks++;
            }
        }

        if (strcmp(_section, "[Big-Block]") == 0)
        {
            while (true)
            {
                // read the numerical values from the txt file labelled respectively as index, x pos, ypos
                fscanf_s(_level1, "%d %d %d", &_index, &_x, &_y);

                if (_index == -1)
                {
                    break;
                }

                crateArray[numBlocks] = new GraphicsObject("../Pics/Crate.bmp", _x, _y, 64, 64);
                numBlocks++;
            }
        }

        if (strcmp(_section, "[Flying-Enemy]") == 0)
        {
            while (true)
            {
                // read the numerical values from the txt file labelled respectively as index, x pos, ypos
                fscanf_s(_level1, "%d %d %d", &_index, &_x, &_y);

                if (_index == -1)
                {
                    break;
                }

                enemyArray[numEnemies] = new FlyingEnemy(&viktor, _x, _y);
                enemyArray[numEnemies]->xPos = _x;
                enemyArray[numEnemies]->yPos = _y;
                numEnemies++;
            }
        }

        if (strcmp(_section, "[Ground-Enemy]") == 0)
        {
            while (true)
            {
                // read the numerical values from the txt file labelled respectively as index, x pos, ypos
                fscanf_s(_level1, "%d %d %d", &_index, &_x, &_y);

                if (_index == -1)
                {
                    break;
                }

                enemyArray[numEnemies] = new GroundEnemy;
                enemyArray[numEnemies]->xPos = _x;
                enemyArray[numEnemies]->yPos = _y;
                numEnemies++;
            }
        }

        if (strcmp(_section, "[LightHouse-Keeper]") == 0)
        {
            while (true)
            {
                // read the numerical values from the txt file labelled respectively as index, x pos, ypos
                fscanf_s(_level1, "%d %d %d", &_index, &_x, &_y);

                if (_index == -1)
                {
                    break;
                }

                enemyArray[numEnemies] = new LightHouseKeeper;
                enemyArray[numEnemies]->xPos = _x;
                enemyArray[numEnemies]->yPos = _y;
                numEnemies++;
            }
        }

        if (strcmp(_section, "[HungrySailor]") == 0)
        {
            while (true)
            {
                // read the numerical values from the txt file labelled respectively as index, x pos, ypos
                fscanf_s(_level1, "%d %d %d", &_index, &_x, &_y);

                if (_index == -1)
                {
                    break;
                }

                enemyArray[numEnemies] = new HungrySailor;
                enemyArray[numEnemies]->xPos = _x;
                enemyArray[numEnemies]->yPos = _y;
                numEnemies++;
            }
        }

        if (strcmp(_section, "[End]") == 0)
        {
            break;
        }
    }

    fclose(_level1);
}
void nextLevel()
{
    for (int i = 0; i < numEnemies; i++)
    {
        if (enemyArray[i]->bIsAlive == false)
        {
            gameOver = true;
        }
        else
        {
            gameOver = false;
            break;
        }
    }
    if (gameOver == true)
    {
        level += 1;
        gameOver = false;
        LoadMap();
        mapPosition = 0;
    }
}
