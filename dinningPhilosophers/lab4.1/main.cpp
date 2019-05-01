#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <fstream>
#include <conio.h>
using namespace std;

const int philosophersCount = 5;
bool isFreeForks[] = { true, true, true, true, true }; 
mutex mtx;


int GetNumberLeftFork(int number)
{
	return number == 0 ? philosophersCount - 1 : number - 1;
}


void Eat(int id) 
{
	while (!_kbhit())
	{
		int leftFork = GetNumberLeftFork(id);
		unique_lock<mutex> ul(mtx);

		if (isFreeForks[leftFork] == true && isFreeForks[id] == true)
		{
			isFreeForks[leftFork] = isFreeForks[id] = false;
			cout <<"������� "<< id << " ���! " << "�����: " << this_thread::get_id() << endl;
			ul.unlock();

			this_thread::sleep_for(chrono::milliseconds(rand() % 5001 + 1000));		// ���
			
			ul.lock();
			isFreeForks[leftFork] = isFreeForks[id] = true;
			cout << "������� " << id << " �������� ����! " << "�����: " << this_thread::get_id() << endl;
			ul.unlock();

			this_thread::sleep_for(chrono::milliseconds(rand() % 5001 + 2000));			//������
		}
	}
}


int main() 
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");

	thread philosophers[philosophersCount];
	for (int i = 0; i < philosophersCount; i++)
	{
		philosophers[i] = thread(Eat, i);
	}
	for (int i = 0; i < philosophersCount; i++)
	{
		philosophers[i].join();
	}

	system("pause");
}