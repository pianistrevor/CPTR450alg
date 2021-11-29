# CPTR450alg
An efficient algorithm designed for a senior class at WWU. A sample program is provided.

To call, define globals of 4 equally-sized double-precision arrays called ARRAYx (x is 1-4), int SIZE_N (the size of each array), double TARGET (the target to be searched for), and double EPSILON (the allowed error). In the future, I may add an update that includes these as parameters to avoid the globals problem, but it was the easiest implementation to start.

`void searchSum(std::vector<solution>, int)`

The `solution` struct is included in the algorithm and is a set of 4 integers representing indexes, one for each array.
The integer parameter is the number of comparisons done by the algorithm.
Both parameters are passed by reference.

The algorithm returns all solutions for which one element from each array adds to within EPSILON of TARGET.
The algorithm is recursive and includes a `boundSearch` to tackle the epsilon bracket problem with a binary search.
