#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_PHILOSOPHERS 5

sem_t forks[NUM_PHILOSOPHERS];
sem_t room;

void *philosopher(void *arg) {
  int id = *((int *)arg);
  int left_fork = id;
  int right_fork = (id + 1) % NUM_PHILOSOPHERS;

  while (1) {
    printf("Philosopher %d is thinking\n", id);
    usleep(500000);

    sem_wait(&room);
    sem_wait(&forks[left_fork]);
    sem_wait(&forks[right_fork]);

    printf("Philosopher %d is eating\n", id);
    usleep(500000);

    sem_post(&forks[right_fork]);
    sem_post(&forks[left_fork]);
    sem_post(&room);
  }
}

int main() {
  pthread_t philosophers[NUM_PHILOSOPHERS];
  int ids[NUM_PHILOSOPHERS];

  sem_init(&room, 0, NUM_PHILOSOPHERS - 1);
  for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
    sem_init(&forks[i], 0, 1);
  }

  for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
    ids[i] = i;
    pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
  }

  for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
    pthread_join(philosophers[i], NULL);
  }

  return 0;
}



