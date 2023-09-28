#pragma once
#pragma warning(disable:4239) 
#pragma warning(push)
#include <iostream>
#include "boost/graph/dijkstra_shortest_paths.hpp"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/graph_traits.hpp>
#include <vector>
#include <limits>

struct Vertex {
	int id = 0;
	std::string address;
	std::string phone;
};

struct Edge {
	double distance = 0.0;
	double time = 0.0;
};

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,Vertex, Edge> Graph;

class GraphClass
{
public:
	struct EdgeInfo {
		std::unique_ptr<Graph>::element_type::vertex_descriptor source;
		std::unique_ptr<Graph>::element_type::vertex_descriptor target;
		double distance;
	};
	 std::unique_ptr<Graph> Users;
	 std::unique_ptr<Graph> generateGraph();
	 double goToUser(Graph& g, int userId);
	 double dijkstraShortestPathGetDistance(Graph& h, int userIdA, int userIdB);
	 std::string dijkstraShortestPathGetPath(Graph& g, int userIdA, int userIdB);
	 std::vector<double> dijkstraShortestPathGetDistanceEachEdge(Graph& g, int userIdA, int userIdB);
	 std::vector<Graph::edge_descriptor> dijkstraShortestPathGetEachEdge(Graph& g, int userIdA, int userIdB);

};