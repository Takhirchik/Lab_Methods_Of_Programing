#include <iostream>
#include <iomanip>
#include <thread>
#include <mutex>
#include <string>
#include <array>
#include <chrono>
#include <vector>

using namespace std;

mutex out;
const int Philosophers_count = 5;

struct fork {
	mutex mutex;
};

struct table {
	array<fork, Philosophers_count> forks;
};

class philosopher {
public:
	string name;
	fork& left_fork;
	fork& right_fork;
	thread thread;
	philosopher(string n, fork& l, fork& r) : name(n), left_fork(l), right_fork(r), thread(&philosopher::dinner, this) {}
	~philosopher() {
		thread.join();
	}
	void dinner() {
		out.lock();
		cout << name << " started dinner" << '\n';
		out.unlock();
		int k = 0;
		do {
			eat();
			k++;
		} while (k < 100);
	}
	
	void eat() {
		if (left_fork.mutex.try_lock()) {
			//left_fork.mutex.lock();
			if (right_fork.mutex.try_lock()) {
				//right_fork.mutex.lock();
				cout << name << " is eating" << '\n';
				this_thread::sleep_for(chrono::seconds(rand()%5 + 1));
				left_fork.mutex.unlock();
				right_fork.mutex.unlock();
				cout << name << " finished eating" << '\n';
			}
			else {
				left_fork.mutex.unlock();
				cout << name << " is waiting" << '\n';
				this_thread::sleep_for(chrono::seconds(rand() % 5 + 1));
				eat();
			}
		}
		else {
			cout << name << " is waiting" << '\n';
			this_thread::sleep_for(chrono::seconds(rand() % 5 + 1));
			eat();
		}
	}
};



int main() {
	setlocale(LC_ALL, "russian");
	table table;
	array<philosopher, Philosophers_count> philosophers
	{
	   {
		  { "Aristotel", table.forks[0], table.forks[1] },
		  { "Platon", table.forks[1], table.forks[2] },
		  { "Diogen", table.forks[2], table.forks[3] },
		  { "Sokrat", table.forks[3], table.forks[4] },
		  { "Confucius", table.forks[4], table.forks[0] },
	   }
	};
	//for (int i = 0; i < Philosophers_count; i++) {
	//	p[i].thread.join();
	//}

	return 0;
}