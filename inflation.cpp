#include <bits/stdc++.h>

int main() {

	int N; scanf("%d", &N);
	std::vector<int> canisters(N);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &canisters[i]);
	}

	std::sort(canisters.begin(), canisters.end());

	double min_frac = 1;
	bool possible = true;
	for (int i = 0; i < N; ++i) {
		if (canisters[i] > i+1) {
			possible = false;
			break;
		}

		min_frac = std::min(min_frac, canisters[i]/(1.0 + i));
	}

	if (possible)
		printf("%.7lf\n", min_frac);
	else
		printf("impossible\n");

	return 0;
}
