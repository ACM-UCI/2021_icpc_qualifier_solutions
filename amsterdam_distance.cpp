#include <bits/stdc++.h>

typedef long double LD;

const LD PI = std::acos(-1);

int main() {

	int M,N;
	LD R;
	scanf("%d %d %llf", &M, &N, &R);

	int aX,aY,bX,bY; scanf("%d %d %d %d", &aX, &aY, &bX, &bY);

	// Loop from min(aY,bY) to 0
	LD radial_unit = R/N;
	LD angular_unit = PI/M;
	LD ans = INFINITY;
	for (int i = 0; i <= std::min(aY,bY); ++i) {
		LD radius = i*radial_unit;
		LD theta = angular_unit * std::abs(aX-bX);
		LD circum = radius * theta;
		LD radial = (std::abs(aY-i) + std::abs(bY-i)) * radial_unit;

		LD tot = circum + radial;
		ans = std::min(tot, ans);
	}

	printf("%.7llf\n", ans);

	return 0;
}
