# 2021 UCI ICPC Qualifier Solutions

## A - Inlation
* Greedy Sorting

## B - Amsterdam Distance
* Geometry + search for radius of traversal

## C - Fridge
* Ad Hoc
	* count occurences of each digit
	* min occurence of digit implies answer will consist entirely of that digit
	* edge case for handling 0

## D - Cent Savings
* Dynamic Programming
	* Can be solved in O(N^2 * D) but requires efficient memoization
		* either do bottom up or use a fixed 2D array for memoization
	* Can also be solved in O(N*D)

## E - Letter Wheels
* Ad Hoc
	* Precompute possible rotations between all pairs of rows O(N^2)
	* Attempt every possible combination of rotation for all 3 rows using the precomputations to achieve an O(1) check
		* This is O(N^2)

## F - On Track
* DFS + Tree knowledge
	* root the tree at every node and compute the number of nodes in each of its children's tree
		* number of pair is the product of this
	* Greedily connect the two maximal sized sub trees of the critical point with greatest number of pairs

## G - Abstract Painting
* Dynamic Programming or Combinatorics
* The number of possibilities for a certain square can completely be determined based on what the above and left border must be. 
	* If there is no limit on either - the case R=C=1 - there are 18 combinations ( 3nCr2 * 4nCr2 ).
	* If one border is determined there are 6 combinations ( 2nCr1 * 3nCr2 )
	* If two borders are determined there are 2 combinations ( 2nCr 1 )

## H - Artwork
* Union Find
	* Key realization is you can apply strokes in reverse order

## I - Dropping Balls
* Divide & Conquer + BFS + Adjacency Matrix + Matrix Exponentiation
	* Key realization is that if the solution can be found for K=1 you can use that solution to compute K=2, then K=4, then K=8, etc
	* Can map start columns to end columns as an adjacency matrix using a bfs search O(R*C^2)
	* apply matrix exponentiation, in sync with point calculations to find the adjency matrix to the power of K
		* multiplication is O(C^3)
		* entire process is O(C^3 * log(K))

## J - Pokegene
* Longest Common Prefix (LCP) + Lowest Common Ancestor (LCA) + Prefix Trie
	* If you sort a list of strings it is always the case that for any two strings A and B any third string C in between A and B in the sorted list will have any LCP(A,C) >= LCP(A,B) and LCP(B,C) >= LCP(A,B).
	* Hence it is sufficient to find the difference between LCP(s[i], s[i+L-1]) - max(LCP(s[i-1], s[i]), LCP(s[i], s[i+L])) where s is the array of strings
	* To efficiently compute the LCP between any two strings requires constructing a prefix trie and computing the LCA on that prefix trie
		* This can be done in several ways including range minimum query(RMQ) or binary lift

