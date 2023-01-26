#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'bfs' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER m
 *  3. 2D_INTEGER_ARRAY edges
 *  4. INTEGER s
 */


#if 1
class Node {
    int id;
    int distance;

public:
    set<Node *> adjacent;
    Node(int id) {
        this->id = id;
        this->distance = 0;
    };

    int getId() {
        return id;
    };

    int getDistance() {
        return distance;
    }

    void setDistance(int d) {
        this->distance = d;
    }

};

int isReachable(Node *source, Node *destination) {
    list<Node *> nextToVisit;
    set<int> visited;
    int distance = 0;
    nextToVisit.push_back(source);
    while(!nextToVisit.empty()) {
        int level = nextToVisit.size();

        while (level-- > 0) {
            Node *node = nextToVisit.front();
            nextToVisit.pop_front();

            if (node == destination) {
                return distance;
            }
            
            if (visited.find(node->getId()) != visited.end()) {
                continue;
            }
            visited.insert(node->getId());

            set<Node *>::iterator itChild;
            for (itChild = node->adjacent.begin(); itChild != node->adjacent.end(); itChild++) {
                nextToVisit.push_back(*itChild);
                if (!(*itChild)->getDistance())
                    (*itChild)->setDistance(distance+6);
            }
        }

        distance += 6;
    }

    return -1;
}

void printNodes(list<Node *> &nodes, Node *source) {

    list<Node *>::iterator itNodes;
    for (itNodes = nodes.begin(); itNodes != nodes.end(); itNodes++) {
        if ((*itNodes) == source) cout << "(S) ";
        cout << (*itNodes)->getId() << " adjacent nodes: ";
        set<Node *>::iterator itChild;
        for (itChild = (*itNodes)->adjacent.begin(); itChild != (*itNodes)->adjacent.end(); itChild++) {
            cout << (*itChild)->getId() << " ";
        }
        cout << endl;
    }
}

void addAdjacents(Node *source, Node *destination) {
    source->adjacent.insert(destination);
    destination->adjacent.insert(source);
}

vector<int> bfs(int n, int m, vector< vector<int> > edges, int s) {
    
    // 1. Populate the nodes
    list<Node *> nodes;
    Node *source;
    
    for (int i = 1; i <= n; i++) {
        Node *node = new Node(i);
        nodes.push_back(node);
        if (i == s)
            source = node;
    }

    // 2. Traverse the vector and populate the edges
    for (int i = 0; i < m; i++) {
        int start = edges[i][0];
        int end = edges[i][1];
        list<Node *>::iterator itStart, itEnd;
        for (itEnd = nodes.begin(); itEnd != nodes.end(); itEnd++)
            if ((*itEnd)->getId() == end) break;

        if (itEnd != nodes.end()) {
            for (itStart = nodes.begin(); itStart != nodes.end(); itStart++) {
                if ((*itStart)->getId() == start) {
                    addAdjacents(*itStart, *itEnd);
                }
            }
        }
    }
    printNodes(nodes, source);

    // 3. Calculate the distances
    vector<int> distances;
    
    list<Node *>::iterator itNodes;
    for (itNodes = nodes.begin(); itNodes != nodes.end(); itNodes++) {
        if (*itNodes == source)
            continue;
        int distance = (*itNodes)->getDistance() != 0 ? (*itNodes)->getDistance() : isReachable(source, *itNodes);
        distances.push_back(distance);
    }

    return distances;
}

#else
class Node {
    int id;

public:
    list<Node *> adjacent;
    Node(int id) {
        this->id = id;
    };

    int getId() {
        return id;
    };
};

int isReachable(Node *source, Node *destination) {
    list<Node *> nextToVisit;
    set<int> visited;
    int distance = 0;
    nextToVisit.push_back(source);
    while(!nextToVisit.empty()) {
        int level = nextToVisit.size();

        while (level-- > 0) {
            Node *node = nextToVisit.front();
            nextToVisit.pop_front();

            if (node == destination) {
                return distance;
            }
            
            if (visited.find(node->getId()) != visited.end()) {
                continue;
            }
            visited.insert(node->getId());

            list<Node *>::iterator itChild;
            for (itChild = node->adjacent.begin(); itChild != node->adjacent.end(); itChild++) {
                nextToVisit.push_back(*itChild);
            }
        }

        distance += 6;
    }

    return -1;
}

void printNodes(list<Node *> &nodes, Node *source) {

    list<Node *>::iterator itNodes;
    for (itNodes = nodes.begin(); itNodes != nodes.end(); itNodes++) {
        if ((*itNodes) == source) cout << "(S) ";
        cout << (*itNodes)->getId() << " adjacent nodes: ";
        list<Node *>::iterator itChild;
        for (itChild = (*itNodes)->adjacent.begin(); itChild != (*itNodes)->adjacent.end(); itChild++) {
            cout << (*itChild)->getId() << " ";
        }
        cout << endl;
    }
}

void addAdjacents(Node *source, Node *destination) {

    list<Node *>::iterator itChild;
    bool exists = false;

    // 1. Add the destination to the source adjacents
    for (itChild = source->adjacent.begin(); itChild != source->adjacent.end(); itChild++) {
        if ((*itChild)->getId() == destination->getId()) {
            exists = true;
            break;
        }
    }
    if (!exists)
        source->adjacent.push_back(destination);

    // 2. Add source to the destination adjacents
    exists = false; // reset flag
    for (itChild = destination->adjacent.begin(); itChild != destination->adjacent.end(); itChild++) {
        if ((*itChild)->getId() == source->getId()) {
            exists = true;
            break;
        }
    }
    if (!exists)
        destination->adjacent.push_back(source);
}

vector<int> bfs(int n, int m, vector< vector<int> > edges, int s) {
    
    // 1. Populate the nodes
    list<Node *> nodes;
    Node *source;
    
    for (int i = 1; i <= n; i++) {
        Node *node = new Node(i);
        nodes.push_back(node);
        if (i == s)
            source = node;
    }

    // 2. Traverse the vector and populate the edges
    for (int i = 0; i < m; i++) {
        int start = edges[i][0];
        int end = edges[i][1];
        list<Node *>::iterator itStart, itEnd;
        for (itEnd = nodes.begin(); itEnd != nodes.end(); itEnd++)
            if ((*itEnd)->getId() == end) break;

        if (itEnd != nodes.end()) {
            for (itStart = nodes.begin(); itStart != nodes.end(); itStart++) {
                if ((*itStart)->getId() == start) {
                    addAdjacents(*itStart, *itEnd);
                }
            }
        }
    }
    printNodes(nodes, source);

    // 3. Calculate the distances
    vector<int> distances;
    
    list<Node *>::iterator itNodes;
    for (itNodes = nodes.begin(); itNodes != nodes.end(); itNodes++) {
        if (*itNodes == source)
            continue;
        int distance = isReachable(source, *itNodes);
        distances.push_back(distance);
    }

    return distances;
}
#endif

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int n = stoi(first_multiple_input[0]);

        int m = stoi(first_multiple_input[1]);

        vector< vector<int> > edges(m);

        for (int i = 0; i < m; i++) {
            edges[i].resize(2);
 
            string edges_row_temp_temp;
            getline(cin, edges_row_temp_temp);

            vector<string> edges_row_temp = split(rtrim(edges_row_temp_temp));

            for (int j = 0; j < 2; j++) {
                int edges_row_item = stoi(edges_row_temp[j]);

                edges[i][j] = edges_row_item;
            }
        }

        string s_temp;
        getline(cin, s_temp);

        int s = stoi(ltrim(rtrim(s_temp)));

        vector<int> result = bfs(n, m, edges, s);

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
