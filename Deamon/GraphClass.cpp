#include "GraphClass.h"
std::unique_ptr<Graph> GraphClass::generateGraph()
{

    std::unique_ptr<Graph> Users = std::make_unique<Graph>();
    Vertex PizzaAlex = { 0,"Strada PizzaAlex", "07553623892" };

    Vertex ID1 = { 1, "Brasov, strada Mare nr 12", "0755632019" };
    Vertex ID2 = { 2, "Brasov, strada Lunga nr 12", "0762736273" };
    Vertex ID3 = { 3, "Brasov, Strada Mare nr 5", "0723626327" };
    Vertex ID4 = { 4, "Brasov, strada Lunga nr 7", "0762736273" };
    Vertex ID5 = { 5, "Brasov, Strada Mare nr 1", "0723626327" };
    Vertex ID6 = { 6, "Brasov, strada Lunga nr 9", "0762736273" };
    Vertex ID7 = { 7, "Brasov, Strada Mare nr 10", "0723626327" };
    Vertex ID8 = { 8, "Brasov, Strada Veche nr 4", "0723626327" };
    Vertex ID9 = { 9, "Brasov, Strada Veche nr 19", "0723626327" };
    Vertex ID10 = { 10, "Brasov, Strada Veche nr 12", "0723626327" };
    Vertex ID11 = { 11, "Brasov, Strada Veche nr 8", "0723626327" };
    Vertex ID12 = { 12, "Brasov, Strada Veche nr 5", "0723626327" };
    Vertex ID13 = { 13, "Brasov, Strada Veche nr 82", "0723626327" };
    Vertex ID14 = { 14, "Brasov, Strada Veche nr 83", "0723626327" };
    Vertex ID15 = { 15, "Brasov, Strada Veche nr 84", "0723626327" };
    Vertex ID16 = { 16, "Brasov, Strada Veche nr 100", "0723626327" };
    Vertex ID17 = { 17, "Brasov, Strada Veche nr 102", "0723626327" };
    Vertex ID18 = { 18, "Brasov, Strada Veche nr 106", "0723626327" };
    Vertex ID19 = { 19, "Brasov, Strada Veche nr 108", "0723626327" };
    Vertex ID20 = { 20, "Brasov, Strada Veche nr 110", "0723626327" };
    Vertex ID21 = { 21, "Brasov, Strada Veche nr 112", "0723626327" };
    Vertex ID22 = { 22, "Brasov, Strada Veche nr 126", "0723626327" };



    Edge  edgeTimeToDeliverId1 = { 120, 2.5 * 120 };
    Edge  edgeTimeToDeliverId3 = { 120, 2.5 * 120 };
    Edge  edgeTimeToDeliverId4 = { 400, 2.5 * 400 };
    Edge  edgeTimeToDeliverId5 = { 300, 2.5 * 200 };
    Edge  edgeTimeToDeliverId9 = { 170, 2.5 * 170 };
    Edge  edgeTimeToDeliverId13 = { 80, 2.5 * 80 };
    Edge  edgeTimeToDeliverId14 = { 140, 2.5 * 140 };
    Edge  edgeTimeToDeliverId16 = { 260, 2.5 * 260 };
    Edge  edgeTimeToDeliverId17 = { 170, 2.5 * 170 };
    Edge  edgeTimeToDeliverId18 = { 70, 2.5 * 70 };

    Edge edgeID1_ID2 = { 90, 2.5 * 90 };
    Edge edgeID2_ID3 = { 150, 2.5 * 150 };
    Edge edgeID6_ID7 = { 60, 2.5 * 60 };
    Edge edgeID4_ID6 = { 90, 2.5 * 90 };
    Edge edgeID3_ID8 = { 80, 2.5 * 80 }; 
    Edge edgeID6_ID8 = { 190, 2.5 * 190 };
    Edge edgeID5_ID10 = { 150, 2.5 * 150 };
    Edge edgeID7_ID10 = { 170, 2.5 * 170 };
    Edge edgeID9_ID10 = { 190, 2.5 * 190 };
    Edge edgeID5_ID7 = { 120, 2.5 * 120 };
    Edge edgeID5_ID9 = { 120, 2.5 * 120 };
    Edge edgeID1_ID9 = { 90, 2.5 * 90 };
    Edge edgeID2_ID8 = { 500, 2.5 * 500 };
    Edge edgeID3_ID6 = { 150, 2.5 * 150 };
    Edge edgeID8_ID11 = { 300, 2.5 * 300 };
    Edge edgeID2_ID11 = { 200, 2.5 * 200 };
    Edge edgeID1_ID12 = { 200, 2.5 * 200 };
    Edge edgeID9_ID12 = { 400, 2.5 * 400 };
    Edge edgeID11_ID12 = { 900, 2.5 * 900 };
    Edge edgeID2_ID13 = { 60, 2.5 * 60 };
    Edge edgeID1_ID13 = { 150, 2.5 * 150 };
    Edge edgeID3_ID13 = { 100, 2.5 * 100 };
    Edge edgeID14_ID15 = { 100, 2.5 * 100 };
    Edge edgeID4_ID14 = { 80, 2.5 * 80 };
    Edge edgeID4_ID15 = { 90, 2.5 * 90 };
    Edge edgeID5_ID14 = { 120, 2.5 * 120 };
    Edge edgeID5_ID15 = { 140, 2.5 * 140 };
    Edge edgeID7_ID15 = { 30, 2.5 * 30 };
    Edge edgeID4_ID16 = { 100, 2.5 * 100 };
    Edge edgeID6_ID16 = { 80, 2.5 * 80 };
    Edge edgeID5_ID17 = { 100, 2.5 * 100 };
    Edge edgeID9_ID17 = { 90, 2.5 * 90 };
    Edge edgeID9_ID18 = { 60, 2.5 * 60 };
    Edge edgeID1_ID18 = { 30, 2.5 * 30 };
    Edge edgeID2_ID19 = { 70, 2.5 * 70 };
    Edge edgeID8_ID19 = { 80, 2.5 * 80 };
    Edge edgeID11_ID19 = { 90, 2.5 * 90 };
    Edge edgeID2_ID20 = { 30, 2.5 * 30 };
    Edge edgeID11_ID20 = { 120, 2.5 * 120 };
    Edge edgeID20_ID21 = { 40, 2.5 * 40 };
    Edge edgeID1_ID21 = { 20, 2.5 * 20 };
    Edge edgeID12_ID21 = { 70, 2.5 * 70 };
    Edge edgeID12_ID22 = { 60, 2.5 * 60 };
    Edge edgeID1_ID22 = { 50, 2.5 * 50 };
    Edge edgeID9_ID22 = { 70, 2.5 * 70 };

    Graph::vertex_descriptor vPizzaAlex = boost::add_vertex(PizzaAlex, *Users);
    Graph::vertex_descriptor vID1 = boost::add_vertex(ID1, *Users);
    Graph::vertex_descriptor vID2 = boost::add_vertex(ID2, *Users);
    Graph::vertex_descriptor vID3 = boost::add_vertex(ID3, *Users);
    Graph::vertex_descriptor vID4 = boost::add_vertex(ID4, *Users);
    Graph::vertex_descriptor vID5 = boost::add_vertex(ID5, *Users);
    Graph::vertex_descriptor vID6 = boost::add_vertex(ID6, *Users);
    Graph::vertex_descriptor vID7 = boost::add_vertex(ID7, *Users);
    Graph::vertex_descriptor vID8 = boost::add_vertex(ID8, *Users);
    Graph::vertex_descriptor vID9 = boost::add_vertex(ID9, *Users);
    Graph::vertex_descriptor vID10 = boost::add_vertex(ID10, *Users);
    Graph::vertex_descriptor vID11 = boost::add_vertex(ID11, *Users);
    Graph::vertex_descriptor vID12 = boost::add_vertex(ID12, *Users);
    Graph::vertex_descriptor vID13 = boost::add_vertex(ID13, *Users);
    Graph::vertex_descriptor vID14 = boost::add_vertex(ID14, *Users);
    Graph::vertex_descriptor vID15 = boost::add_vertex(ID15, *Users);
    Graph::vertex_descriptor vID16 = boost::add_vertex(ID16, *Users);
    Graph::vertex_descriptor vID17 = boost::add_vertex(ID17, *Users);
    Graph::vertex_descriptor vID18 = boost::add_vertex(ID18, *Users);
    Graph::vertex_descriptor vID19 = boost::add_vertex(ID19, *Users);
    Graph::vertex_descriptor vID20 = boost::add_vertex(ID20, *Users);
    Graph::vertex_descriptor vID21 = boost::add_vertex(ID21, *Users);
    Graph::vertex_descriptor vID22 = boost::add_vertex(ID22, *Users);

    boost::add_edge(vPizzaAlex, vID1, edgeTimeToDeliverId1, *Users);
    boost::add_edge(vPizzaAlex, vID3, edgeTimeToDeliverId3, *Users);
    boost::add_edge(vPizzaAlex, vID4, edgeTimeToDeliverId4, *Users);
    boost::add_edge(vPizzaAlex, vID5, edgeTimeToDeliverId5, *Users);
    boost::add_edge(vPizzaAlex, vID9, edgeTimeToDeliverId9, *Users);
    boost::add_edge(vPizzaAlex, vID13, edgeTimeToDeliverId13, *Users);
    boost::add_edge(vPizzaAlex, vID14, edgeTimeToDeliverId14, *Users);
    boost::add_edge(vPizzaAlex, vID16, edgeTimeToDeliverId16, *Users);
    boost::add_edge(vPizzaAlex, vID17, edgeTimeToDeliverId17, *Users);
    boost::add_edge(vPizzaAlex, vID18, edgeTimeToDeliverId18, *Users);

   
    boost::add_edge(vID2, vID3, edgeID2_ID3, *Users);
    boost::add_edge(vID1, vID2, edgeID1_ID2, *Users);
    boost::add_edge(vID3, vID6, edgeID3_ID6, *Users);
    boost::add_edge(vID6, vID7, edgeID6_ID7, *Users);
    boost::add_edge(vID4, vID6, edgeID4_ID6, *Users);
    boost::add_edge(vID3, vID8, edgeID3_ID8, *Users);
    boost::add_edge(vID6, vID8, edgeID6_ID8, *Users);
    boost::add_edge(vID5, vID10, edgeID5_ID10, *Users);
    boost::add_edge(vID7, vID10, edgeID7_ID10, *Users);
    boost::add_edge(vID9, vID10, edgeID9_ID10, *Users);
    boost::add_edge(vID5, vID7, edgeID5_ID7, *Users);
    boost::add_edge(vID5, vID9, edgeID5_ID9, *Users);
    boost::add_edge(vID1, vID9, edgeID1_ID9, *Users);
    boost::add_edge(vID2, vID8, edgeID2_ID8, *Users);
    boost::add_edge(vID8, vID11, edgeID8_ID11, *Users);
    boost::add_edge(vID2, vID11, edgeID2_ID11, *Users);
    boost::add_edge(vID1, vID12, edgeID1_ID12, *Users);
    boost::add_edge(vID9, vID12, edgeID9_ID12, *Users);
    boost::add_edge(vID11, vID12, edgeID11_ID12, *Users);
    boost::add_edge(vID2, vID13, edgeID2_ID13, *Users);
    boost::add_edge(vID1, vID13, edgeID2_ID13, *Users);
    boost::add_edge(vID3, vID13, edgeID2_ID13, *Users);
    boost::add_edge(vID14, vID15, edgeID14_ID15, *Users);
    boost::add_edge(vID4, vID14, edgeID4_ID14, *Users);
    boost::add_edge(vID4, vID15, edgeID4_ID15, *Users);
    boost::add_edge(vID5, vID14, edgeID5_ID14, *Users);
    boost::add_edge(vID5, vID15, edgeID5_ID15, *Users);
    boost::add_edge(vID7, vID15, edgeID7_ID15, *Users);
    boost::add_edge(vID4, vID16, edgeID4_ID16, *Users);
    boost::add_edge(vID6, vID16, edgeID6_ID16, *Users);
    boost::add_edge(vID9, vID17, edgeID9_ID17, *Users);
    boost::add_edge(vID5, vID17, edgeID5_ID17, *Users);
    boost::add_edge(vID1, vID18, edgeID1_ID18, *Users);
    boost::add_edge(vID9, vID18, edgeID9_ID18, *Users);
    boost::add_edge(vID2, vID19, edgeID2_ID19, *Users);
    boost::add_edge(vID8, vID19, edgeID8_ID19, *Users);
    boost::add_edge(vID11, vID19, edgeID11_ID19, *Users);
    boost::add_edge(vID2, vID20, edgeID2_ID20, *Users);
    boost::add_edge(vID11, vID20, edgeID11_ID20, *Users);
    boost::add_edge(vID20, vID21, edgeID20_ID21, *Users);
    boost::add_edge(vID1, vID21, edgeID1_ID21, *Users);
    boost::add_edge(vID12, vID21, edgeID12_ID21, *Users);
    boost::add_edge(vID12, vID22, edgeID12_ID22, *Users);
    boost::add_edge(vID1, vID22, edgeID1_ID22, *Users);
    boost::add_edge(vID19, vID22, edgeID9_ID22, *Users);
    return Users;
    
}

void showGraph(const Graph& g) {
    for (auto vd = boost::vertices(g); vd.first != vd.second; ++vd.first) {
        Graph::vertex_descriptor current_vd = *vd.first;

        std::cout << "Vertex descriptor: " << current_vd << std::endl;
        std::cout << "Vertex info: ";
        std::cout << g[current_vd].id << " ";
        std::cout << g[current_vd].address << " ";
        std::cout << g[current_vd].phone << std::endl;
    }
}

double GraphClass::goToUser(Graph& g, int userId)
{
    Graph::vertex_descriptor pizzaAlex = boost::vertex(0, g);;
    Graph::vertex_descriptor user = boost::vertex(0, g);

    for (auto vd = boost::vertices(g); vd.first != vd.second; ++vd.first) {
        Graph::vertex_descriptor current_vd = *vd.first;
        

        if (g[current_vd].id == 0) {
            pizzaAlex = current_vd;
        }
        else if(g[current_vd].id == userId) {
            user = current_vd;
        }
   }
    if (pizzaAlex == boost::graph_traits<Graph>::null_vertex() || user == boost::graph_traits<Graph>::null_vertex()) {
        return 0; 
    }

    Graph::edge_descriptor edge;
    bool found;
    std::tie(edge, found) = boost::edge(pizzaAlex, user, g);

    if (!found) {
        return 0; 
    }

    return g[edge].distance;
}

double GraphClass::dijkstraShortestPathGetDistance(Graph& g, int userIdA, int userIdB)
{
    Graph::vertex_descriptor userA, userB;
    bool foundUserA = false, foundUserB = false;

    for (auto vd : boost::make_iterator_range(boost::vertices(g))) {
        if (!foundUserA && g[vd].id == userIdA) {
            userA = vd;
            foundUserA = true;
        }
        if (!foundUserB && g[vd].id == userIdB) {
            userB = vd;
            foundUserB = true;
        }
    }

    if (!foundUserA || !foundUserB) {
        // std::cerr << userIdA << " || " << userIdB;
      //   std::cerr << "User ID not found.\n";
        return -1.0;
    }
    std::vector<Graph::vertex_descriptor> predecessors(boost::num_vertices(g));
    std::vector<double> distances(boost::num_vertices(g));

    auto predecessor_map = boost::make_iterator_property_map(predecessors.begin(), boost::get(boost::vertex_index, g));
    auto distance_map = boost::make_iterator_property_map(distances.begin(), boost::get(boost::vertex_index, g));
    auto weight_map = boost::get(&Edge::distance, g);

    dijkstra_shortest_paths(g, userA,
        boost::predecessor_map(predecessor_map)
        .distance_map(distance_map)
        .weight_map(weight_map)
    );

    std::vector<Graph::edge_descriptor> path;

    for (auto v = userB; v != userA; v = predecessor_map[v])
    {
        auto edge = boost::edge(predecessor_map[v], v, g);
        path.push_back(edge.first);

    }

    std::reverse(path.begin(), path.end());

    double totalDistance = 0;
    for (const auto& edge : path)
    {
        totalDistance += g[edge].distance;
    }

    return totalDistance;
}
std::string GraphClass::dijkstraShortestPathGetPath(Graph& g, int userIdA, int userIdB)
{
    Graph::vertex_descriptor userA, userB;
    bool foundUserA = false, foundUserB = false;

    for (auto vd : boost::make_iterator_range(boost::vertices(g))) {
        if (!foundUserA && g[vd].id == userIdA) {
            userA = vd;
            foundUserA = true;
        }
        if (!foundUserB && g[vd].id == userIdB) {
            userB = vd;
            foundUserB = true;
        }
    }

    if (!foundUserA || !foundUserB) {
        return "";
    }

    std::vector<Graph::vertex_descriptor> predecessors(boost::num_vertices(g));
    std::vector<double> distances(boost::num_vertices(g));

    auto predecessor_map = boost::make_iterator_property_map(predecessors.begin(), boost::get(boost::vertex_index, g));
    auto distance_map = boost::make_iterator_property_map(distances.begin(), boost::get(boost::vertex_index, g));
    auto weight_map = boost::get(&Edge::distance, g);

    dijkstra_shortest_paths(g, userA,
        boost::predecessor_map(predecessor_map)
        .distance_map(distance_map)
        .weight_map(weight_map)
    );

    std::vector<Graph::vertex_descriptor> path;

    for (auto v = userB; v != userA; v = predecessor_map[v])
    {
        path.push_back(v);
    }

    path.push_back(userA);

    std::reverse(path.begin(), path.end());
    std::string pathString;

    for (const auto& vertex : path)
    {
        pathString += std::to_string(g[vertex].id) + " -> ";
    }

    pathString = pathString.substr(0, pathString.length() - 4);
    return pathString;
}

std::vector<double> GraphClass::dijkstraShortestPathGetDistanceEachEdge(Graph& g, int userIdA, int userIdB)
{
    Graph::vertex_descriptor userA, userB;
    bool foundUserA = false, foundUserB = false;

    for (auto vd : boost::make_iterator_range(boost::vertices(g))) {
        if (!foundUserA && g[vd].id == userIdA) {
            userA = vd;
            foundUserA = true;
        }
        if (!foundUserB && g[vd].id == userIdB) {
            userB = vd;
            foundUserB = true;
        }
    }

    if (!foundUserA || !foundUserB) {
        // std::cerr << userIdA << " || " << userIdB;
        // std::cerr << "User ID not found.\n";
        return std::vector<double>(); // Return an empty vector to indicate failure.
    }

    std::vector<Graph::vertex_descriptor> predecessors(boost::num_vertices(g));
    std::vector<double> distances(boost::num_vertices(g));

    auto predecessor_map = boost::make_iterator_property_map(predecessors.begin(), boost::get(boost::vertex_index, g));
    auto distance_map = boost::make_iterator_property_map(distances.begin(), boost::get(boost::vertex_index, g));
    auto weight_map = boost::get(&Edge::distance, g);

    dijkstra_shortest_paths(g, userA,
        boost::predecessor_map(predecessor_map)
        .distance_map(distance_map)
        .weight_map(weight_map)
    );

    std::vector<Graph::edge_descriptor> path;

    for (auto v = userB; v != userA; v = predecessor_map[v])
    {
        auto edge = boost::edge(predecessor_map[v], v, g);
        path.push_back(edge.first);
    }

    std::reverse(path.begin(), path.end());

    std::vector<double> distancesOfEdges;
    for (const auto& edge : path)
    {
        distancesOfEdges.push_back(g[edge].distance);
    }

    return distancesOfEdges;
}

std::vector<Graph::edge_descriptor> GraphClass::dijkstraShortestPathGetEachEdge(Graph& g, int userIdA, int userIdB)
{
    Graph::vertex_descriptor userA, userB;
    bool foundUserA = false, foundUserB = false;

    for (auto vd : boost::make_iterator_range(boost::vertices(g))) {
        if (!foundUserA && g[vd].id == userIdA) {
            userA = vd;
            foundUserA = true;
        }
        if (!foundUserB && g[vd].id == userIdB) {
            userB = vd;
            foundUserB = true;
        }
    }

    if (!foundUserA || !foundUserB) {
        return std::vector<Graph::edge_descriptor>();
    }

    std::vector<Graph::vertex_descriptor> predecessors(boost::num_vertices(g));
    std::vector<double> distances(boost::num_vertices(g));

    auto predecessor_map = boost::make_iterator_property_map(predecessors.begin(), boost::get(boost::vertex_index, g));
    auto distance_map = boost::make_iterator_property_map(distances.begin(), boost::get(boost::vertex_index, g));
    auto weight_map = boost::get(&Edge::distance, g);

    dijkstra_shortest_paths(g, userA,
        boost::predecessor_map(predecessor_map)
        .distance_map(distance_map)
        .weight_map(weight_map)
    );

    std::vector<Graph::vertex_descriptor> path;
    for (auto v = userB; v != userA; v = predecessor_map[v])
    {
        path.push_back(v);
    }
    path.push_back(userA);

    std::reverse(path.begin(), path.end());

    std::vector<Graph::edge_descriptor> edges;
    for (std::size_t i = 0; i < path.size() - 1; ++i)
    {
        auto edge = boost::edge(path[i], path[i + 1], g);
        if (edge.second) 
        {
            edges.push_back(edge.first);
        }
        else
        {
            std::cerr << "Edge not found between vertices " << path[i] << " and " << path[i + 1] << std::endl;
            return std::vector<Graph::edge_descriptor>();
        }
    }

    return edges;
}