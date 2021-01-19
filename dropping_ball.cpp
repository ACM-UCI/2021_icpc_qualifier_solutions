#include <bits/stdc++.h>

typedef long long LL;
typedef std::vector<std::string> Grid;
typedef std::vector<std::vector<bool>> Matrix;
typedef std::vector<std::vector<LL>> Cost;

const char EMPTY = '.';
const char OBSTA = 'X';
const char RIGHT = 'R';
const char LEFT = 'L';
const char CONVE = '?';

struct Cell {
	int r,c;
};


int R,C,K;

Grid g;
Matrix base;
Cost base_cost;
Cost curr_cost;
std::vector<LL> init_costs;


void bfs(int i) {
	std::vector<std::vector<bool>> visited(R, std::vector<bool>(C));
	std::queue<Cell> q;
	q.push({0,i});
	
	while (!q.empty()) {
		Cell curr = q.front(); q.pop();

		if (curr.r == R) {
			base[i][curr.c] = true;
			base_cost[i][curr.c] = init_costs[curr.c];
			continue;
		}
		
		if (visited[curr.r][curr.c]) {
			continue;
		}
		visited[curr.r][curr.c] = true;

		switch (g[curr.r][curr.c]) {
			case EMPTY:
				q.push({curr.r+1, curr.c});
				break;
			case OBSTA:
				break;
			case RIGHT:
				if (curr.c+1 < C) {
					q.push({curr.r, curr.c+1});
				}
				break;
			case LEFT:
				if (curr.c > 0) {
					q.push({curr.r, curr.c-1});
				}
				break;
			case CONVE:
				if (curr.c+1 < C) {
					q.push({curr.r, curr.c+1});
				}
				if (curr.c > 0) {
					q.push({curr.r, curr.c-1});
				}
				break;
		}

	}
}

void multiply(Matrix& a, Matrix& b, Matrix& out, Cost& c_a, Cost& c_b, Cost& c_out) {
	for (int r = 0; r < C; ++r) {
		for (int c = 0; c < C; ++c) {
			bool val = false;
			LL max = 0;
			for (int k = 0; k < C; ++k) {
				bool tmp = (a[r][k] & b[k][c]);
				val = (val | tmp);
				if (tmp) {
					max = std::max(max, c_a[r][k] + c_b[k][c]);
				}
			}
			out[r][c] = val;
			c_out[r][c] = max;
		}
	}
}


Matrix to_return;
Cost c_to_return;

void pow(int k) {
	if (k == 0) {
		to_return.assign(C, std::vector<bool>(C));
		for (int i = 0; i < C; ++i) to_return[i][i] = true;
		c_to_return.assign(C, std::vector<LL>(C,0));
		return;
	} else if (k == 1) {
		to_return = base;
		c_to_return = base_cost;
		return;
	} else {

		pow(k/2);
		Matrix copy = to_return;
		Cost c_copy = c_to_return;

		multiply(copy, copy, to_return, c_copy, c_copy, c_to_return);

		if (k%2) {
			Matrix copy = to_return;
			Cost c_copy = c_to_return;
			multiply(copy, base, to_return, c_copy, base_cost, c_to_return);
		}

		return;
	}
}

LL get_max_cost() {
	LL ans = 0;
	for (int r = 0; r < C; ++r) {
		for(int c = 0; c < C; ++c) {
			ans = std::max(ans, c_to_return[r][c]);
		}
	}
	return ans;
}


int main() {

	std::cin >> R >> C >> K;

	base.assign(C, std::vector<bool>(C));
	g.assign(R, "");
	init_costs.assign(C,0);
	base_cost.assign(C, std::vector<LL>(C));
	for (int i = 0; i < R; ++i) {
		std::cin >> g[i];
	}
	for (int i = 0; i < C; ++i) {
		std::cin >> init_costs[i];
	}


	// Build the base matrix
	for (int i = 0; i < C; ++i) {
		bfs(i);
	}


	// test
	Matrix res(C, std::vector<bool>(C));
	Cost c_res(C, std::vector<LL>(C));
	multiply(base, base, res, base_cost, base_cost, c_res);

	pow(K);
	LL ans = get_max_cost();
	printf("%lld\n", ans);


	return 0;
}
