// laba22.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "laba22.h"

#include <Windows.h>	
#include <tchar.h>		

TCHAR str[128];
int width = 300, height = 300;

int xPos, yPos;
int xStep = 10; int yStep = 10;
int DesktopWeidht;
int DesktopHight;
void WindowStep(HWND hWnd);

TCHAR WinName[] = _T("Окно 2");
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI _tWinMain(HINSTANCE This, HINSTANCE Prev, LPTSTR cmd, int mode)
{
	HWND     hWnd;
	MSG      msg;
	WNDCLASS wc;

	wc.hInstance = This;                                   // Дескриптор текущего приложения
	wc.lpszClassName = WinName; 				           // Имя класса окна
	wc.lpfnWndProc = WndProc; 					           // Функция окна
	wc.style = CS_HREDRAW | CS_VREDRAW; 		           // Стиль окна
	wc.hIcon = LoadIcon(NULL, IDI_INFORMATION);            // Стандартная иконка
	wc.hCursor = LoadCursor(NULL, IDC_HAND); 	           // Стандартный курсор
	wc.lpszMenuName = NULL; 					           // Нет меню
	wc.cbClsExtra = 0; 						               // Нет дополнительных данных класса
	wc.cbWndExtra = 0; 						               // Нет дополнительных данных окна
	wc.hbrBackground = CreateSolidBrush(RGB(100, 100, 100)); // Заполнение окна цветом

	if (!RegisterClass(&wc)) return 0; // Регистрация класса окна

	hWnd = CreateWindow(WinName, _T("Окно 2"), WS_OVERLAPPEDWINDOW, 1200, 100, 300, 300, HWND_DESKTOP, NULL, This, NULL);       	// Создание окна 

	ShowWindow(hWnd, mode); // Показать окно

	// Цикл обработки сообщений 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) { // Оконная функция

	HDC hdc;
	PAINTSTRUCT ps;
	static HBRUSH brush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
	static int x = 0;
	switch (message)
	{

	case WM_USER + 1:
		MessageBox(NULL, _T("В первом окне нажата левая кнопка мыши"), _T("Сообщение"), NULL);
	{
			x = 1;
			//brush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
			//InvalidateRect(hWnd, NULL, false);
	}
		break;

	case WM_USER + 2:
	{
		double a = 1200; int b = 100;
		while (a > 0)
		{
			MoveWindow(hWnd, a - 0.5, b, width, height, 0);
			a = a - 0.5;
			Sleep(10);
		}
	}
	break;



	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		if (x == 1)
		{
			{
				brush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
				FillRect(hdc, &ps.rcPaint, brush);
				InvalidateRect(hWnd, NULL, false);
				Sleep(3000);

			}
		}

		EndPaint(hWnd, &ps);
		break;
	}

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	} return 0;
}