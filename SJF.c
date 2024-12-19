#include <stdio.h>

int main() {
    int bt[20], tat[20], wt[20], p[20];
    int total = 0, n, pos, temp;
    float avtat, avwt;

    printf("Enter the number of processes: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    printf("Enter the burst times for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("P[%d]: ", i + 1);
        if (scanf("%d", &bt[i]) != 1 || bt[i] < 0) {
            printf("Invalid burst time.\n");
            return 1;
        }
        p[i] = i + 1; // Initialize process IDs
    }

    // Sorting based on burst time (SJF Scheduling)
    for (int i = 0; i < n - 1; i++) {
        pos = i;
        for (int j = i + 1; j < n; j++) {
            if (bt[j] < bt[pos]) {
                pos = j;
            }
        }
        // Swap burst times
        temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;

        // Swap process IDs
        temp = p[i];
        p[i] = p[pos];
        p[pos] = temp;
    }

    // Waiting time calculation
    wt[0] = 0; // First process has no waiting time
    total = 0;
    for (int i = 1; i < n; i++) {
        wt[i] = bt[i - 1] + wt[i - 1];
        total += wt[i];
    }
    avwt = (float)total / n; // Average waiting time

    // Turnaround time calculation
    total = 0;
    for (int i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
        total += tat[i];
    }
    avtat = (float)total / n; // Average turnaround time

    // Print results
    printf("\nProcess\t\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P[%d]\t\t%d\t\t%d\t\t%d\n", p[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", avwt);
    printf("Average Turnaround Time: %.2f\n", avtat);

    return 0;
}

