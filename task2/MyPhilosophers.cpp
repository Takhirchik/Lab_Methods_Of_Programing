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
		printStatus(" started dinner");
		int k = 0;
		do {
			eat();
			k++;
		} while (k < 100);
	}
	
	void printStatus(string message) {
		out.lock();
		cout << name << message << '\n';
		out.unlock();
	}

	void eat() {
		if (left_fork.mutex.try_lock()) {
			//left_fork.mutex.lock();
			if (right_fork.mutex.try_lock()) {
				//right_fork.mutex.lock();
				printStatus(" is eating");
				this_thread::sleep_for(chrono::seconds(rand()%5 + 1));
				left_fork.mutex.unlock();
				right_fork.mutex.unlock();
				printStatus(" finished eating");
			}
			else {
				left_fork.mutex.unlock();
				printStatus(" is waiting");
				this_thread::sleep_for(chrono::seconds(rand() % 5 + 1));
				eat();
			}
		}
		else {
			printStatus(" is waiting");
			this_thread::sleep_for(chrono::seconds(rand() % 5 + 1));
			eat();
		}
	}
};



int main() {
	setlocale(LC_ALL, "russian");
	table table;
	array<philosopher, Philosophers_count> p
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
