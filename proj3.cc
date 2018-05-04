/**********************************************************************
 *
 * CISC 4080: Computer Algorithms
 * Project 3: Topological Sorting
 *
 * Author: Philip Tenteromano
 * Date:   3/1/2018
 *
 * DFS algorithm for sorting DAGs in topological order
 * Read-in from file
 *
 **********************************************************************/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

// misc datatypes

template <typename VertexType> struct Edge {
   VertexType from;
   VertexType to;
};

template <typename VertexType> struct Graph {
   vector<VertexType> vertices;
   vector<Edge<VertexType>> edges;
};

// function declarations
template <typename VertexType>
istream& operator>>(istream& is, Edge<VertexType>& e);

template <typename VertexType>
ostream& operator<<(istream& is, const Edge<VertexType>& e);

template <typename VertexType> Graph<VertexType> getData(string fileName);

template <typename VertexType> vector<VertexType> topSort(Graph<VertexType> g);

int main(int argc, char** argv)
{
   /*
    * get the data
    */
   if (argc != 2) {
      cerr << "Usage: " << argv[0] << " datafile\n";
      return 1;
   }
   Graph<char> g = getData<char>(argv[1]);

   /*
    * do the topological sort
    */
   vector<char> tSort = topSort(g);

   /*
    * report results
    */
   for (auto vertex: tSort)
      cout << vertex << " ";
   cout << endl;

   return 0;
}

/*
 * function definitions
 */

// input operator: read an edge from an input stream
// edge has form (v,w) where vertices v and w are of type VertexType
template <typename VertexType>
istream& operator>>(istream& is, Edge<VertexType>& e)
{
   VertexType initial, terminal;
   char lparen, comma, rparen;
   is >> lparen >> initial >> comma >> terminal >> rparen;
   if (!is) return is;
   if (lparen != '(' || comma != ',' || rparen != ')') {
      cerr << "Bad format " << lparen <<  initial << comma 
           <<  terminal <<  rparen
           << " ... edge ignored\n";
      return is;
   }
   e.from = initial;
   e.to = terminal;
   return is;
}

// output operator: write an edge to an output stream
// edge has form (v,w) where vertices v and w are of type VertexType
template <typename VertexType> 
ostream& operator<<(ostream& os, const Edge<VertexType>& e)
{
   os<< '(' << e.from << ',' << e.to << ')';
   return os;
}

// read graph data from a file
template <typename VertexType> Graph<VertexType> getData(string fileName)
{
   ifstream dataStream(fileName.c_str());
   if (!dataStream) {
      cerr << "can't open " << fileName << endl;
      exit(1);
   }

   Edge<VertexType> e;
   Graph<VertexType> g;

   // vertices
   char ch;
   while (dataStream >> ch && !(isspace(ch) || ch == '(')) {
      dataStream.putback(ch);
      VertexType temp;
      dataStream >> temp;
      g.vertices.push_back(temp);
   }
   dataStream.putback(ch);

   // edges
   while (dataStream >> e) 
      g.edges.push_back(e);

   return g;
}

// return a vector consisting of all the vertices appearing in the
// graph g (in lexicographic order)
// 
// Using method number 2:
// Map Indegrees, pop sources, remove source node + outbound edges, repeat
template <typename VertexType> vector<VertexType> topSort(Graph<VertexType> g)
{
    vector<VertexType> ts;					// returned list
	map<VertexType, int> indegree;			// indegree map
	int numV = 0;							// counting |V|

	for (auto vertex: g.vertices) {			// store the vertices in the map
		indegree[vertex] = 0;
		numV++;
	}

   	for (auto edge: g.edges)				// increment indegree for
	  	indegree[edge.to]++;				// non-source nodes

	while ( numV > 0 ) {					// find Sources
		for (auto &source: indegree) 		// add to OUTPUT list
			if (source.second == 0) {
				ts.push_back(source.first);
				source.second = -1;			// sentinel value for deletion
				for (auto edge: g.edges) 	// delete appropriate edges
					if (edge.from == source.first)
						indegree[edge.to]--;
			}
		numV--;
	}
   	return ts;
}



