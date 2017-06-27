//Brandon Duncan
//CSC 3430 - HW4
//Dijkstra Shortest Path Algorithm
// A C / C++ program for Dijkstra's single source shortest path algorithm.
// The program is for adjacency matrix representation of the graph
// Code used from http://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm/

#include <iostream>
#include <stdio.h>
#include <limits.h>

using namespace std;
#define V 9
int path[V];	//path array

int minDistance(int dist[], bool sptSet[]);
int printSolution(int dist[], int n);
void dijkstra(int graph[V][V], int src);
void pathOutput(int dest, int path[]);

int main()
{
	int graph[V][V] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
						{ 4, 0, 8, 0, 0, 0, 0, 11, 0 },
						{ 0, 8, 0, 7, 0, 4, 0, 0, 2 },
						{ 0, 0, 7, 0, 9, 14, 0, 0, 0 },
						{ 0, 0, 0, 9, 0, 10, 0, 0, 0 },
						{ 0, 0, 4, 14, 10, 0, 2, 0, 0 },
						{ 0, 0, 0, 0, 0, 2, 0, 1, 6 },
						{ 8, 11, 0, 0, 0, 0, 1, 0, 7 },
						{ 0, 0, 2, 0, 0, 0, 6, 7, 0 }
						};

	int vertex;
	cout << "Please enter your starting vertex: ";
	cin >> vertex;
	dijkstra(graph, vertex);

	return 0;
}


// Funtion that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(int graph[V][V], int src)
{
	int dist[V];     // The output array.  dist[i] will hold the shortest distance from src to i
	
	bool processedSet[V]; // processedSet[i] will true if vertex i is included in shortest
							// path tree or shortest distance from src to i is finalized

	// Initialize all distances as INFINITE and processedSet[] as false, set all values in path array to -1
	for (int i = 0; i < V; i++)
	{
		dist[i] = INT_MAX, processedSet[i] = false, path[i] = -1;
	}

	// Distance of source vertex from itself is always 0
	dist[src] = 0;

	// Find shortest path for all vertices
	for (int count = 0; count < V - 1; count++)
	{
		// Pick the minimum distance vertex from the set of vertices not
		// yet processed. u is always equal to src in first iteration.
		int u = minDistance(dist, processedSet);
	
		// Mark the picked vertex as processed
		processedSet[u] = true;

		// Update list value of the adjacent vertices of the picked vertex.
		for (int v = 0; v < V; v++)
		{
			// Update dist[v] only if is not in processedSet, there is an edge from 
			// u to v, and total weight of path from src to  v through u is 
			// smaller than current value of dist[v]
			if (!processedSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
			{
				dist[v] = dist[u] + graph[u][v];
				path[v] = u;		//add vertex to path array
			}	
		}
	}

	//Print the distances for each vertex
	printSolution(dist, V);
	//Print the paths to each vertex from the starting vertex
	cout << endl;
	cout << "Shortest paths from vertex " << src << ":" << endl << endl;
	int x = 0;
	while(x < V)	//Let x = destination vertex
	{
		cout << x << " = ";
		pathOutput(x, path);
		cout << endl;
		x++;
	}

}

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], bool processedSet[])
{
	// Initialize min value
	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++)
		if (processedSet[v] == false && dist[v] <= min)
		{
			min = dist[v], min_index = v;
		}

	return min_index;
}


int printSolution(int dist[], int n)
{
	printf("Vertex   Distance from Source\n");
	for (int i = 0; i < V; i++)
	{
		printf("%d \t\t %d\n", i, dist[i]);
	}

	return 0;
}
//A recursive function to print out the shortest path for all of the nodes
void pathOutput(int dest, int path[])
{
	if (path[dest] != -1)
	{ 
		pathOutput(path[dest], path);	//recursively call print function again
		cout << " --> ";
	}
	cout << dest;
}

