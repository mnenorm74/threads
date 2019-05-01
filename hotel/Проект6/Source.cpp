#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <process.h>
using namespace std;

int ID = 0;
HANDLE semaphor;
const int numbersCount = 3;
mutex console_mutex;


DWORD WINAPI doing(LPVOID param)
{
	WaitForSingleObject(semaphor, INFINITE);

	console_mutex.lock();
	cout << "Клиент поселился. Поток: " << this_thread::get_id() << endl;
	ID++;
	console_mutex.unlock();

	Sleep(rand() % 8001 + 7000);

	console_mutex.lock();
	cout << "Клиент выселился. Поток: " << this_thread::get_id() << endl;
	console_mutex.unlock();

	ReleaseSemaphore(semaphor, 1, NULL);
	return 0;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	semaphor = CreateSemaphore(NULL, numbersCount, numbersCount, NULL);
	
	
	while (!GetAsyncKeyState(VK_RETURN))
	{
		CreateThread(NULL, 0, doing, NULL, 0, NULL);
		Sleep(rand() % 1001 + 1000);
	}

	
	getchar();
	getchar();
}