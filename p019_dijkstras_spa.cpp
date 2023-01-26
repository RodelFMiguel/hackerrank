#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <map>
#include <limits>
#include <algorithm>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'shortestReach' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. 2D_INTEGER_ARRAY edges
 *  3. INTEGER s
 */


#if 1
class Node {
    int id; // node id
    int distance; // distance from source
    bool visited; // is visited

public:
    multimap<Node *, int> adjacent;
    Node *previous;
    Node(int id) {
        this->id = id;
        this->distance = INT_MAX;
        this->visited = false;
        this->previous = NULL;
    };

    Node() {
        this->distance = INT_MAX;
        this->visited = false;
        this->previous = NULL;
    };

    int getId() {
        return id;
    };

    void setId(int id) {
        this->id = id;
    }

    int getDistance() {
        return distance;
    }

    void setDistance(int d) {
        this->distance = d;
    }

    bool isVisited() {
        return this->visited;
    }

    void setVisited(bool v) {
        this->visited = v;
    }

    bool operator<(const Node &node) const {
        return (this->distance < node.distance);
    }

};

void printNodes(vector<Node *> &nodes, Node *source) {

    vector<Node *>::iterator itNodes;
    for (itNodes = nodes.begin(); itNodes != nodes.end(); itNodes++) {
        if ((*itNodes) == source) cout << "(S) ";
        cout << (*itNodes)->getId() << " adjacent nodes: ";
        multimap<Node *, int>::iterator itChild;
        for (itChild = (*itNodes)->adjacent.begin(); itChild != (*itNodes)->adjacent.end(); itChild++) {
            cout << "(" << (*itChild).first->getId() << ":" << (*itChild).second << ") ";
        }
        cout << endl;
    }
}

void addAdjacents(Node *source, Node *destination, int weight) {
    source->adjacent.insert(pair<Node *, int>(destination, weight));
    destination->adjacent.insert(pair<Node *, int>(source, weight));
}

Node *get_min_node(vector<Node *> &nodes, Node *source) {
    int min = INT_MAX;
    int vertices = nodes.size();
    Node *min_node = NULL;

    for (int i = 0; i < vertices; i++) {
        if (nodes[i]->isVisited() == false && nodes[i]->getDistance() <= min) {
            min = nodes[i]->getDistance();
            min_node = nodes[i];
        }
    }

    return min_node;
}

void dijkstras_shortest_path(vector<Node *> &nodes, Node *source, vector<int> &distances) {
    int vertices = nodes.size();
    
    for (int i = 0; i < vertices; i++) {
        // Get the minimum distance from the source; note: source distance = 0
        Node *minNode  = get_min_node(nodes, source);

        // Mark the min vertex as visited
        minNode->setVisited(true);
        distances[minNode->getId()-1] = minNode->getDistance() == INT_MAX ? -1 : minNode->getDistance();
        
        multimap<Node *, int>::iterator it;
        for (it = minNode->adjacent.begin(); it != minNode->adjacent.end(); it++) {
            if (!it->first->isVisited() && it != minNode->adjacent.end() && minNode->getDistance() != INT_MAX &&
                minNode->getDistance() + it->second < it->first->getDistance())
                it->first->setDistance(minNode->getDistance() + it->second);
        }
    }
}

vector<int> shortestReach(int n, vector< vector<int> > edges, int s) {
    // 1. Populate the nodes
    vector<Node *> nodes;
    vector<int> distances;
    Node *source;
    
    for (int i = 1; i <= n; i++) {
        Node *node = new Node(i);
        nodes.push_back(node);
        distances.push_back(-1);
        if (i == s)
            source = node;
    }

    // 2. Traverse the vector and populate the edges
    for (int i = 0; i < edges.size(); i++) {
        int start = edges[i][0];
        int end = edges[i][1];
        int weight = edges[i][2];
        vector<Node *>::iterator itStart, itEnd;
        for (itEnd = nodes.begin(); itEnd != nodes.end(); itEnd++)
            if ((*itEnd)->getId() == end) break;

        if (itEnd != nodes.end()) {
            for (itStart = nodes.begin(); itStart != nodes.end(); itStart++) {
                if ((*itStart)->getId() == start) {
                    addAdjacents(*itStart, *itEnd, weight);
                }
            }
        }
    }
    // printNodes(nodes, source);

    // 3. Calculate the distances
    
    source->setDistance(0);
    distances[source->getId()-1] = 0;
    dijkstras_shortest_path(nodes, source, distances);

    /* for (int i = 0; i < n; i++) {
        if (nodes[i] == source)
            continue;
        distances.push_back(nodes[i]->getDistance() == INT_MAX ? -1 : nodes[i]->getDistance());
    } */
   
    distances.erase(distances.begin()+source->getId()-1);
    return distances;
}

#else
class Node {
    int id; // node id
    int distance; // distance from source
    bool visited; // is visited

public:
    multimap<int, int> adjacent; // index and weight
    Node *previous;
    Node(int id) {
        this->id = id;
        this->distance = INT_MAX;
        this->visited = false;
        this->previous = NULL;
    };

    Node() {
        this->distance = INT_MAX;
        this->visited = false;
        this->previous = NULL;
    };

    int getId() {
        return id;
    };

    void setId(int id) {
        this->id = id;
    }

    int getDistance() {
        return distance;
    }

    void setDistance(int d) {
        this->distance = d;
    }

    bool isVisited() {
        return this->visited;
    }

    void setVisited(bool v) {
        this->visited = v;
    }

    bool operator<(const Node &node) const {
        return (this->distance < node.distance);
    }

    bool operator== (const Node &node) const {
        return (this->id == node.id);
    }
};

void printNodes(vector<Node> &nodes, int source) {
    vector<Node>::iterator itNodes;
    for (itNodes = nodes.begin(); itNodes != nodes.end(); itNodes++) {
        if ((*itNodes).getId() == source) cout << "(S) ";
        cout << (*itNodes).getId() << " adjacent nodes: " << flush;
        multimap<int, int>::iterator itChild;
        for (itChild = (*itNodes).adjacent.begin(); itChild != (*itNodes).adjacent.end(); itChild++) {
            cout << "(" << nodes[(*itChild).first].getId() << ":" << (*itChild).second << ") " << flush;
        }
        cout << endl;
    }
}

void addAdjacents(vector<Node> &nodes, int source, int destination, int weight) {
    // cout << "source: " << source << "; destination: " << destination << "; weight: " << weight << endl;
    nodes[source].adjacent.insert(pair<int, int>(destination, weight));
    nodes[destination].adjacent.insert(pair<int, int>(source, weight));
}

int get_min_node(vector<Node> &nodes, int source_idx, int &start_index) {
    int vertices = nodes.size();
    int min_node = source_idx;

    sort(nodes.begin(), nodes.end());

    for (int i = start_index; i < vertices; i++) {
        if (nodes[i].isVisited() == false) {
            min_node = i;
            start_index = i;
            break;
        }
    }

    return min_node;
}

void dijkstras_shortest_path(vector<Node> &nodes, int source_idx, vector<int> &distances) {
    int vertices = nodes.size();
    int start_index = 0;
    vector<Node> sorted_nodes = nodes;
    
    for (int i = 0; i < vertices; i++) {
        int minNodeIdx = get_min_node(sorted_nodes, source_idx, start_index);

        // Mark the min vertex as visited
        sorted_nodes[minNodeIdx].setVisited(true);
        distances[sorted_nodes[minNodeIdx].getId()] = \
            nodes[sorted_nodes[minNodeIdx].getId()].getDistance() == INT_MAX ? -1 : \
            nodes[sorted_nodes[minNodeIdx].getId()].getDistance();

        multimap<int, int>::iterator it;
        for (it = sorted_nodes[minNodeIdx].adjacent.begin(); it != sorted_nodes[minNodeIdx].adjacent.end(); it++) {
            if (!nodes[it->first].isVisited() && it != sorted_nodes[minNodeIdx].adjacent.end() && 
                sorted_nodes[minNodeIdx].getDistance() != INT_MAX &&
                sorted_nodes[minNodeIdx].getDistance() + it->second < nodes[it->first].getDistance()) {
                    nodes[it->first].setDistance(sorted_nodes[minNodeIdx].getDistance() + it->second);
                    vector<Node>::iterator it_sn = find(sorted_nodes.begin(), sorted_nodes.end(), nodes[it->first]);
                    it_sn->setDistance(sorted_nodes[minNodeIdx].getDistance() + it->second);
                }
        }
    }
}

vector<int> shortestReach(int n, vector< vector<int> > edges, int s) {

    // cout << "1. Populate the nodes with size " << n << endl;
    vector<Node> nodes;
    vector<int> distances;
    int source_idx = 0;
    
    for (int i = 0; i < n; i++) {
        Node node(i);
        nodes.push_back(node);
        distances.push_back(-1);
        if (i == s-1)
            source_idx = i;
    }

    // cout << "2. Traverse the vector and populate the edges with size: " << edges.size() << endl;
    for (int i = 0; i < edges.size(); i++) {
        int start = edges[i][0] - 1;
        int end = edges[i][1] - 1;
        int weight = edges[i][2];
        vector<Node>::iterator itStart, itEnd;
        for (itEnd = nodes.begin(); itEnd != nodes.end(); itEnd++)
            if (itEnd->getId() == end)
                break;

        if (itEnd != nodes.end()) {
            for (itStart = nodes.begin(); itStart != nodes.end(); itStart++) {
                if (itStart->getId() == start) {
                    addAdjacents(nodes, itStart->getId(), itEnd->getId(), weight);
                }
            }
        }
    }
    // printNodes(nodes, source_idx);

    // 3. Calculate the distances
    nodes[source_idx].setDistance(0);
    distances[source_idx] = 0;
    dijkstras_shortest_path(nodes, source_idx, distances);

    distances.erase(distances.begin() + source_idx);
    return distances;
}

#endif

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int n = stoi(first_multiple_input[0]);

        int m = stoi(first_multiple_input[1]);

        vector< vector<int> > edges(m);

        for (int i = 0; i < m; i++) {
            edges[i].resize(3);

            string edges_row_temp_temp;
            getline(cin, edges_row_temp_temp);

            vector<string> edges_row_temp = split(rtrim(edges_row_temp_temp));

            for (int j = 0; j < 3; j++) {
                int edges_row_item = stoi(edges_row_temp[j]);

                edges[i][j] = edges_row_item;
            }
        }

        string s_temp;
        getline(cin, s_temp);

        int s = stoi(ltrim(rtrim(s_temp)));

        vector<int> result = shortestReach(n, edges, s);

        for (size_t i = 0; i < result.size(); i++) {
            fout << result[i];

            if (i != result.size() - 1) {
                fout << " ";
            }
        }

        fout << "\n";
    }

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
