#include <bits/stdc++.h>

int N,D;
std::vector<int> prices;
std::vector<int> cum_prices;
std::vector<std::vector<int>> cache;

int round(int p) {
	if (p%10 < 5) {
		// round down
		return (p/10)*10;
	} else {
		// round up
		return ((p/10)+1)*10;
	}
}


int solve(int i, int d) {

	if (i >= N) {
		return 0;
	} else if (d == 0) {
		int tot = cum_prices[N]-cum_prices[i];
		return round(tot);
	}

	if (cache[d][i] >= 0) {
		return cache[d][i];
	}

	int best = 20000000;
	for (int j = i+1; j <= N; ++j) {
		int res = solve(j, d-1) + round(cum_prices[j]-cum_prices[i]);
		best = std::min(res, best);
	}
	return cache[d][i] = best;
}

int main() {

	scanf("%d %d", &N, &D);
	prices.assign(N, 0);
	cum_prices.assign(N+1,0);
	cache.assign(D+1, std::vector<int>(N, -1));
	for (int i = 0; i < N; ++i) {
		scanf("%d", &prices[i]);
		cum_prices[i+1] = cum_prices[i] + prices[i];
	}

	int ans = solve(0, D);
	printf("%d\n", ans);


	return 0;
}
