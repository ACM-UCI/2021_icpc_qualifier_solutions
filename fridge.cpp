#include <bits/stdc++.h>

int main() {

	int counts[10];
	memset(counts, 0, sizeof counts);
	std::string s; std::cin >> s;

	for (int i = 0; i < s.length(); ++i) {
		++counts[s[i] - '0'];
	}

	int min_seen = s.length() + 1;
	int min_char = -1;
	for (int i = 1; i < 10; ++i) {
		if (counts[i] < min_seen) {
			min_seen = counts[i];
			min_char = i;
		}
	}

	int zeros = counts[0];
	if (zeros < min_seen) {
		std::string ans = "1";
		for (int i = 0; i <= zeros; ++i) {
			ans += '0';
		}
		std::cout << ans << std::endl;

	} else {
		std::string ans;
		for (int i = 0; i <= min_seen; ++i) {
			ans += (min_char + '0');
		}
		std::cout << ans << std::endl;
	}
	

	return 0;
}
