#include <bits/stdc++.h>

typedef std::vector<std::vector<int>> AdjList;
typedef long long LL;


int N;
AdjList adj;
std::vector<int> p_tree;
std::vector<std::vector<int>> child_counts;

LL best;
int best_root;

LL count_pairs(std::vector<int>& child_sizes) {
	LL children_remaining = N;

	LL pairs = 0;
	for (int i = 0; i < child_sizes.size(); ++i) {
		children_remaining -= child_sizes[i];
		pairs += child_sizes[i] * children_remaining;
	}

	return pairs;
}

int dfs(int u) {

	int num_children = 0;
	for (const int v : adj[u]) if (p_tree[v] < 0) {
		p_tree[v] = u;
		int tmp = dfs(v);
		num_children += tmp;
		child_counts[u].push_back(tmp);
	}

	child_counts[u].push_back(N-num_children);
	std::sort(child_counts[u].begin(), child_counts[u].end());

	LL pairs = count_pairs(child_counts[u]);

	if (pairs > best) {
		best = pairs;
		best_root = u;
	}

	return num_children + 1;
}


int main() {
	
	scanf("%d", &N);
	adj.assign(N+1, std::vector<int>());
	p_tree.assign(N+1,-1);
	child_counts.assign(N+1, std::vector<int>());
	best = -1;
	best_root = 0;

	for (int i = 0; i < N; ++i) {
		int u,v; scanf("%d %d", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	// Find a leaf node
	int root = 0;
	for (int i = 0; i <= N; ++i) {
		if (adj[i].size() == 1) {
			root = i;
			break;
		}
	}

	p_tree[root] = root;

	dfs(root);

	// printf("%d %d\n", best, best_root);

	int tmp = child_counts[best_root].back();
	child_counts[best_root].pop_back();
	child_counts[best_root][child_counts[best_root].size()-1] += tmp;

	int better = count_pairs(child_counts[best_root]);
	printf("%d %d\n", best, better);



	return 0;
}
