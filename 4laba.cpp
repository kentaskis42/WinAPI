#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <stdio.h>
#include <string>
#include <wchar.h>
#define DIV 1024
#define WIDTH 7
//#pragma warning(disable:4996)

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("MainFrame");
HWND hWnd;
int WINAPI _tWinMain(HINSTANCE This,		 // Дескриптор текущего приложения 
	HINSTANCE Prev, 	// В современных системах всегда 0 
	LPTSTR cmd, 		// Командная строка 
	int mode) 		// Режим отображения окна
{
	// Дескриптор главного окна программы 
	MSG msg; 		// Структура для хранения сообщения 
	WNDCLASS wc; 	// Класс окна
	// Определение класса окна 
	wc.hInstance = This;
	wc.lpszClassName = WinName; 				// Имя класса окна 
	wc.lpfnWndProc = WndProc; 					// Функция окна 
	wc.style = CS_HREDRAW | CS_VREDRAW; 			// Стиль окна 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		// Стандартная иконка 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// Стандартный курсор 
	wc.lpszMenuName = NULL; 					// Нет меню 
	wc.cbClsExtra = 0; 						// Нет дополнительных данных класса 
	wc.cbWndExtra = 0; 						// Нет дополнительных данных окна 
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); 	// Заполнение окна белым цветом 


	// Регистрация класса окна
	if (!RegisterClass(&wc)) return 0;

	// Создание окна 
	hWnd = CreateWindow(WinName,			// Имя класса окна 
		_T("4"), 		// Заголовок окна 
		WS_OVERLAPPEDWINDOW, 		// Стиль окна 
		CW_USEDEFAULT,				// x 
		CW_USEDEFAULT, 				// y	 Размеры окна 
		CW_USEDEFAULT, 				// width 
		CW_USEDEFAULT, 				// Height 
		HWND_DESKTOP, 				// Дескриптор родительского окна 
		NULL, 						// Нет меню 
		This, 						// Дескриптор приложения 
		NULL); 					// Дополнительной информации нет 

	ShowWindow(hWnd, mode); 				// Показать окно

	//HMENU WINAPI a;
	HMENU MainMenu = CreateMenu();
	HMENU hPopupMenu = CreatePopupMenu();
	HMENU hPopupMenu2 = CreatePopupMenu();
	AppendMenu(MainMenu, MF_STRING | MF_POPUP, (UINT)hPopupMenu, L"&Поток 1");
	{
		AppendMenu(hPopupMenu, MF_STRING, 1001, L"Включить");
		AppendMenu(hPopupMenu, MF_STRING, 1002, L"Выключить");
	}
	AppendMenu(MainMenu, MF_STRING | MF_POPUP, (UINT)hPopupMenu2, L"&Поток 2");
	{
		AppendMenu(hPopupMenu2, MF_STRING, 1003, L"Включить");
		AppendMenu(hPopupMenu2, MF_STRING, 1004, L"Выключить");
	}
	SetMenu(hWnd, MainMenu);

	// Цикл обработки сообщений 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 		// Функция трансляции кодов нажатой клавиши 
		DispatchMessage(&msg); 		// Посылает сообщение функции WndProc() 
	}
	return 0;
}
HANDLE hThread1;
HANDLE hThread2;
DWORD WINAPI Thread1(LPVOID t);
DWORD WINAPI Thread2(LPVOID t);

int a = 0;
BOOL fin1 = true;
BOOL fin2 = true;

// Оконная функция вызывается операционной системой
// и получает сообщения из очереди для данного приложения

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)		 // Обработчик сообщений
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break; 			// Завершение программы 
	default: 			// Обработка сообщения по умолчанию 
		return DefWindowProc(hWnd, message, wParam, lParam);
	case WM_COMMAND:
		switch (wParam)
		{
		case 1001:
		{
			fin1 = true;
			hThread1 = CreateThread(NULL, 0, Thread1, hWnd, 0, NULL);
			break;
		}
		case 1002:
		{
			TerminateThread(hThread1, 0);
			CloseHandle(hThread1);
			fin1 = FALSE;
			break;
		}
		case 1003:
		{
			fin2 = TRUE;
			hThread2 = CreateThread(NULL, 0, Thread2, hWnd, 0, NULL);
			break;
		}
		case 1004:
		{
			TerminateThread(hThread2, 0);
			CloseHandle(hThread2);
			fin2 = FALSE;
			break;
		}
		}
	}
	return 0;
}

DWORD WINAPI Thread1(LPVOID t)
{
	RECT rect;
	int f = 0;
	int g = 0;
	int d = 0;
	int k = 0;
	int h = 0;
	while (fin1)
	{
		GetWindowRect(HWND(t), &rect);
		HDC hdc = GetDC(HWND(t));
		HBRUSH hBrush;
		hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		SelectObject(hdc, hBrush);
		d = rand() % 20;
		//h = rand() % 10,
		f = rand() % 10,
			g = rand() % 30,
			Ellipse(hdc, f * d, g * d, 20 + f * d, 20 + g * d);
		Sleep(2000);
	}
	return (0);


}

DWORD WINAPI Thread2(LPVOID t)
{
	int width = 0;
	int height = 0;
	RECT rect;
	TCHAR buff[300];
	HPEN hPen;
	HPEN myPen;
	MEMORYSTATUSEX statex;
	while (fin2)
	{
		int a;
		int x = 0;
		a = 0;
		while (fin2)
		{
			GetWindowRect(HWND(t), &rect);
			if (a == 0)
			{
				HDC hdc = GetDC(HWND(t));
				HBRUSH hBrush;
				HPEN hPen;
				for (int i = 750; i < 951; i++)
				{
					//if (x == 0)
					{
						MoveToEx(hdc, 850, 50, NULL);
						myPen = CreatePen(PS_SOLID, 10, RGB(255, 255, 255));
						SelectObject(hdc, myPen);
						LineTo(hdc, i - 1, 200); //Sleep(10);
						//InvalidateRect(hWnd, NULL, TRUE);

						MoveToEx(hdc, 850, 50, NULL);
						myPen = CreatePen(PS_SOLID, 10, RGB(rand() % 255, rand() % 255, rand() % 255));
						SelectObject(hdc, myPen);
						LineTo(hdc, i, 200); Sleep(10);
						//InvalidateRect(hWnd , NULL, TRUE);

						//x = 1;
					}


				}
				for (int i = 951; i > 749; i--)
				{
					MoveToEx(hdc, 850, 50, NULL);
					myPen = CreatePen(PS_SOLID, 10, RGB(255, 255, 255));
					SelectObject(hdc, myPen);
					LineTo(hdc, i + 1, 200); //Sleep(10);
					//InvalidateRect(hWnd, NULL, TRUE);

					MoveToEx(hdc, 850, 50, NULL);
					myPen = CreatePen(PS_SOLID, 10, RGB(rand() % 255, rand() % 255, rand() % 255));
					SelectObject(hdc, myPen);
					LineTo(hdc, i, 200); Sleep(10);
					//InvalidateRect(hWnd, NULL, TRUE);

				}


			}


		}

	}
	return 0;
}