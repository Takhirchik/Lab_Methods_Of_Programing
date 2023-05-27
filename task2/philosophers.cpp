
#include <iostream>
#include <thread>
#include <vector>
#include <ctime>
#include <pthread.h>
#include <sys/wait.h>
#include <unistd.h>
// #define Sleep(X) sleep(X)
// #define wait() scanf("1")

using namespace std;


#define PHT_SIZE 5
 
// int const phil_count = 5;

// Философы
typedef struct philosopher{
    const char *name;
    unsigned left_fork;
    unsigned right_fork;
} phil_t;

// Стол 
typedef struct table{
    pthread_mutex_t forks[PHT_SIZE];
}table_t;

// Делаем единый объект
typedef struct philosopher_args_tag {
    const phil_t *philosopher;
    table_t *table;
} philosopher_args_t;

pthread_mutex_t entry_point = PTHREAD_MUTEX_INITIALIZER;

// инициализируем объекты
void init_philosopher(phil_t *philosopher, const char *name, unsigned left_fork, unsigned right_fork) {
    philosopher->name = name;
    philosopher->left_fork = left_fork;
    philosopher->right_fork = right_fork;
}

// заполняем массив вилок
void init_table(table_t *table){
    for (size_t i = 0; i < PHT_SIZE ; ++i){
        pthread_mutex_init(&table->forks[i], NULL);
    }
}

int k = 0, phil = 0;

int f1 = 0, f2 = 2;

void mod(){
    f1 = f1 % 5;
    f2 = f2 % 5;
}

void * eat(void * args) {
    philosopher_args_t *arg = (philosopher_args_t *) args;
    const phil_t *philosopher = arg->philosopher;
    table_t *table = arg->table;
    do{ 
        if ((phil == f1) || (phil == f2)){
            printf("%s started\n", philosopher->name);

            pthread_mutex_lock(&table->forks[philosopher->left_fork]);
            pthread_mutex_lock(&table->forks[philosopher->right_fork]);

            printf("%s is eating\n", philosopher->name);
            
            sleep(5);

            pthread_mutex_unlock(&table->forks[philosopher->right_fork]);
            pthread_mutex_unlock(&table->forks[philosopher->left_fork]);
            
            printf("%s finished\n", philosopher->name);
        }
        else {
            printf("%s wait\n", philosopher->name);
            sleep(5);
        }
        k++;
        ++f1;
        ++f2;
        mod();
        phil++;
    } while (k < 30);
}


int main() {
    pthread_t threads[PHT_SIZE];
 
    phil_t philosophers[PHT_SIZE];
    philosopher_args_t args[PHT_SIZE];
    table_t table;
 
    init_table(&table);
 
    init_philosopher(&philosophers[0], "Aristotel", 0, 1);
    init_philosopher(&philosophers[1], "Diogen", 1, 2);
    init_philosopher(&philosophers[2], "Platon", 2, 3);
    init_philosopher(&philosophers[3], "Sokrat", 3, 4);
    init_philosopher(&philosophers[4], "Confucius", 4, 0);
    
    for (size_t i = 0; i < PHT_SIZE; i++) {
        args[i].philosopher = &philosophers[i];
        args[i].table = &table;
    }

    for (size_t i = 0; i < PHT_SIZE; i++)
        pthread_create(&threads[i], NULL, eat, &args[i]);
 
    for (size_t i = 0; i < PHT_SIZE; i++)
       pthread_join(threads[i], NULL);

    pid_t wait(int *status);
    return 0;
}


