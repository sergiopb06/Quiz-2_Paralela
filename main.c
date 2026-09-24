Dining · C
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
 

#define NUM_PHILS 5 //number of Philosophers
#define TIMES_TO_EAT 5 //number of times a Philosopher has to eat 

void *philosopher(void *num);
void think(int phil);
void eat(int phil);


sem_t room;
sem_t chopstick[NUM_PHILS];



int main(void){
    

}

void think(int phil) {
    printf("Philosopher %d is thinking\n", phil);
    sleep(1);
}

void eat(int phil) {
    printf("Philosopher %d is eating\n", phil);
    sleep(1);
}

void *philosopher(void *num){

    int phil = *(int *) num;

    int left = phil;
    int right = (phil + 1) % NUM_PHILS;
    int rounds;

    for (rounds = 0; rounds < TIMES_TO_EAT; rounds++) { //each philosopher eats exactly TIMES_TO_EAT times, then leaves the room.

        think(phil);
 
        sem_wait(&room); 

        printf("Philosopher %d entered the room\n", phil);
 
        sem_wait(&chopstick[left]); 
        sem_wait(&chopstick[right]);
 
        eat(phil);
        printf("Philosopher %d finished eating\n", phil);
 
        sem_post(&chopstick[right]);
        sem_post(&chopstick[left]);
 
        sem_post(&room); //finished eating, leave the room.
    }

    printf("Philosopher %d has eaten %d times and is leaving the table\n", phil, TIMES_TO_EAT);

    
    return NULL;
}
