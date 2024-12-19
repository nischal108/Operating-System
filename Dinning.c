#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

// Semaphores for chopsticks
sem_t chopsticks[NUM_PHILOSOPHERS];

// Function for philosophers' actions
void* philosopher(void* num) {
    int id = *(int*)num;

    while (1) {
        // Thinking
        printf("Philosopher %d is thinking.\n", id);
        sleep(1);

        // Hungry and trying to pick up chopsticks
        printf("Philosopher %d is hungry.\n", id);

        // Picking up left chopstick
        sem_wait(&chopsticks[id]);
        printf("Philosopher %d picked up left chopstick.\n", id);

        // Picking up right chopstick
        sem_wait(&chopsticks[(id + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d picked up right chopstick.\n", id);

        // Eating
        printf("Philosopher %d is eating.\n", id);
        sleep(1);

        // Putting down chopsticks
        sem_post(&chopsticks[id]);
        printf("Philosopher %d put down left chopstick.\n", id);

        sem_post(&chopsticks[(id + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d put down right chopstick.\n", id);
    }
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    // Initialize semaphores (one for each chopstick)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&chopsticks[i], 0, 1);
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Wait for all philosopher threads to complete (in this example, they run indefinitely)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy semaphores (not reachable in this example)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&chopsticks[i]);
    }

    return 0;
}

