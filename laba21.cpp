#include "framework.h"
#include "laba21.h"

#include <Windows.h>
#include <tchar.h>

TCHAR WinName[] = _T("Окно 1");

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); // Оконная функция

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
	wc.hbrBackground = CreateSolidBrush(RGB(100, 200, 200)); // Заполнение окна цветом

	if (!RegisterClass(&wc)) return 0; // Регистрация класса окна

	hWnd = CreateWindow(WinName, _T("Окно 1"), WS_OVERLAPPEDWINDOW, 50, 50, 300, 300, HWND_DESKTOP, NULL, This, NULL);    	// Создание окна

	ShowWindow(hWnd, mode); // Показать окно

	// Цикл обработки сообщений
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); // Функция, которая транслирует код нажатой клавиши в клавиатурные сообщения WM_CHAR
		DispatchMessage(&msg); 	// Посылает сообщение функции WndProc() (Возврат преобразованного сообщения операционной системе)
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) { // Оконная функция

	HWND hChildWnd = FindWindow(_T("Окно 2"), _T("Окно 2")); // Извлекает дискриптор окна верхнего уровня
	HDC hdc;
	PAINTSTRUCT ps;
	static HBRUSH brush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
	static int x = 0;

	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		if (hChildWnd == NULL)
		{
			x = 1;
			brush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
			InvalidateRect(hWnd, NULL, false);
		}
		else
		{
			MessageBox(NULL, _T("Окно 2 найдено"), _T("Сообщение"), NULL);

			SendMessage(hChildWnd, WM_USER + 1, WPARAM(hWnd), NULL);  // Отправляет заданное сообщение окну
		}
		break;
	}

	case WM_RBUTTONDOWN:
		SendMessage(hChildWnd, WM_USER + 2, WPARAM(hWnd), NULL); // Отправляет заданное сообщение окну
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
				//brush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
				//FillRect(hdc, &ps.rcPaint, brush);
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
