#include <stdio.h>
#include <stdlib.h>

#define MAX_N 20
#define MAX_SUBSETS 1050000 // 2^20 maximum possible subsets

int weights[MAX_N];
int n;
int target_sum;

int solutions[MAX_SUBSETS][MAX_N + 1]; 
int solution_count = 0;

int current_subset[MAX_N];
int current_size = 0;

void find_subsets(int index, int current_sum) {
    if (current_sum == target_sum) {
        solutions[solution_count][0] = current_size;
        for (int i = 0; i < current_size; i++) {
            solutions[solution_count][i + 1] = current_subset[i];
        }
        solution_count++;
        return;
    }

    if (index == n || current_sum > target_sum) {
        return;
    }

    current_subset[current_size] = weights[index];
    current_size++;
    find_subsets(index + 1, current_sum + weights[index]);
    current_size--;

    find_subsets(index + 1, current_sum);
}

int main() {
    if (scanf("%d", &n) != 1) return 0;
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &weights[i]) != 1) return 0;
    }
    if (scanf("%d", &target_sum) != 1) return 0;

    find_subsets(0, 0);

    if (solution_count == 0) {
        printf("-1\n");
    } else {
        for (int i = solution_count - 1; i >= 0; i--) {
            int size = solutions[i][0];
            for (int j = 0; j < size; j++) {
                printf("%d ", solutions[i][j + 1]);
            }
            printf("\n");
        }
    }
    return 0;
}
