#include <bits/stdc++.h>

int N,M,Q;
int grid[1000][1000];


class EqCl {
private:
	std::vector<int> p_tree;
	std::vector<int> rank;
	int num_sets;

public:
	EqCl(int n) : num_sets{n} {
		p_tree.assign(n,0);
		rank.assign(n,0);
		for (int i = 0; i < n; ++i) p_tree[i] = i;
	}

	int find(int i) {
		std::stack<int, std::vector<int>> st;
		while (i != p_tree[i]) {
			st.push(i);
			i = p_tree[i];
		}
		while (!st.empty()) { p_tree[st.top()] = i; st.pop(); }
		return i;
	}

	void merge(int a, int b) {
		// printf("Merge (%d, %d) => [(%d, %d), (%d, %d)]\n", a, b, a%N, a/N, b%N, b/N);
		int p_A = find(a);
		int p_B = find(b);
		if (p_A != p_B) {
			if (rank[p_A] > rank[p_B]) {
				p_tree[p_B] = p_A;
			} else {
				p_tree[p_A] = p_B;
				if (rank[p_A] == rank[p_B]) ++p_B;
			}
			--num_sets;
		}
	}

	int getNumSets() {
		return num_sets;
	}

};

struct Stroke {
	int x1,y1,x2,y2;
};

int map(int x, int y) {
	return y*N + x;
}

int main() {

	scanf("%d %d %d", &N, &M, &Q);
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < N; ++j) {
			grid[i][j] = 0;
		}
	}

	std::vector<Stroke> strokes(Q);
	for (int i = 0; i < Q; ++i) {
		int x1,y1,x2,y2; scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		--x1; --y1; --x2; --y2;
		strokes[i] = {x1,y1,x2,y2};
		if (x1 == x2) {
			int lo = std::min(y1,y2);
			int hi = std::max(y1,y2);
			for (int j = lo; j <= hi; ++j) {
				++grid[j][x1];
			}
		} else {
			int lo = std::min(x1,x2);
			int hi = std::max(x1,x2);
			for (int j = lo; j <= hi; ++j) {
				++grid[y1][j];
			}
		}
	}

	EqCl eq(M*N);
	int black_cnts = 0;
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < N; ++j) {
			if (grid[i][j] == 0) {
				if (i+1 < M && grid[i+1][j] == 0) {
					eq.merge(map(j,i), map(j,i+1));
				}
				if (j+1 < N && grid[i][j+1] == 0) {
					eq.merge(map(j,i), map(j+1,i));
				}
			} else {
				++black_cnts;
			}
		}
	}


	// Handle each stroke in reverse order
	std::stack<int> ans;
	for (int i = Q-1; i > 0; --i) {
		ans.push(eq.getNumSets() - black_cnts);
		Stroke& curr = strokes[i];
		if (curr.x1 == curr.x2) {
			int lo = std::min(curr.y1, curr.y2);
			int hi = std::max(curr.y1, curr.y2);
			for (int j = lo; j <= hi; ++j) {
				if (--grid[j][curr.x1] == 0) {
					--black_cnts;

					int base_coord = map(curr.x1, j);

					if (j > 0 && grid[j-1][curr.x1] == 0) {
						eq.merge(base_coord, map(curr.x1, j-1));
					}

					if (j < M-1 && grid[j+1][curr.x1] == 0) {
						eq.merge(base_coord, map(curr.x1, j+1));
					}

					if (curr.x1 > 0 && grid[j][curr.x1-1] == 0) {
						eq.merge(base_coord, map(curr.x1-1,j));
					}

					if (curr.x1 < N-1 && grid[j][curr.x1+1] == 0) {
						eq.merge(base_coord, map(curr.x1+1,j));
					}
				}
			}

		} else {
			int lo = std::min(curr.x1, curr.x2);
			int hi = std::max(curr.x1, curr.x2);

			for (int j = lo; j <= hi; ++j) {
				if (--grid[curr.y1][j] == 0) {
					--black_cnts;

					int base_coord = map(j, curr.y1);

					if (curr.y1 > 0 && grid[curr.y1-1][j] == 0) {
						eq.merge(base_coord, map(j, curr.y1-1));
					}

					if (curr.y1 < M-1 && grid[curr.y1+1][j] == 0) {
						eq.merge(base_coord, map(j, curr.y1+1));
					}

					if (j > 0 && grid[curr.y1][j-1] == 0) {
						eq.merge(base_coord, map(j-1, curr.y1));
					}

					if (j < N-1 && grid[curr.y1][j+1] == 0) {
						eq.merge(base_coord, map(j+1, curr.y1));
					}
				}
			}
		}

	}

	ans.push(eq.getNumSets() - black_cnts);

	while (!ans.empty()) {
		printf("%d\n", ans.top());
		ans.pop();
	}

	
	return 0;
}
