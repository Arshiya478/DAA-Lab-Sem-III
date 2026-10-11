#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000

int n;
int dist[20][20];
int dp[1 << 20][20];

int tsp(int mask, int u) {
    if (mask == (1 << n) - 1) {
        if (dist[u][0] != -1) {
            return dist[u][0];
        }
        return INF;
    }

    if (dp[mask][u] != -1) {
        return dp[mask][u];
    }

    int min_cost = INF;

    for (int v = 0; v < n; v++) {
        if (!(mask & (1 << v)) && dist[u][v] != -1) {
            int new_cost = dist[u][v] + tsp(mask | (1 << v), v);
            if (new_cost < min_cost) {
                min_cost = new_cost;
            }
        }
    }

    return dp[mask][u] = min_cost;
}

int main() {
    if (scanf("%d", &n) != 1) return 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &dist[i][j]);
        }
    }

    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = -1;
        }
    }

    int ans = tsp(1, 0);

    printf("%d\n", ans);

    return 0;
}
