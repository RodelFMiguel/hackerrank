#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

class Edge
{
private:
    int source;
    int target;
    int weight;
    
public:
    Edge() {}
    Edge(const int w) { weight = w; }
    void set_source(const int s) { source = s; }
    void set_target(const int t) { target = t; }
    void set_weight(const int w) { weight = w; }
    int get_source(void) { return source; }
    int get_target(void) { return target; }
    int get_weight(void) { return weight; }
};

class Vertex
{
private:
    int id;
    int value;
    vector<Vertex*> neighbors;
    vector<Edge*> edges;
    
public:
    Vertex() {}
    Vertex(const int id) { this->id = id; }
    void add_neighbor(Vertex *v) { neighbors.push_back(v); }
    void add_edge(Edge *e) { edges.push_back(e); }
    void set_id(const int id) { this->id = id; }
    void set_value(const int v) { value = v; }
    vector<Vertex*> get_neighbors(void) { return neighbors; }
    vector<Edge*> get_edges(void) { return edges; }
    int get_id(void) { return id; }
    int get_value(void) { return value; }
    void print(void) { cout << "node: " << id << endl;}
};

class Graph
{
private:
    vector<Vertex*> nodes;
    vector<Edge*> edges;
    Vertex *root;
    
public:
    Graph() { root = NULL; }
    ~Graph() {
        for (int i = 0; i < nodes.size(); i++) {
            delete nodes[i];
        }
        for (int i = 0; i < edges.size(); i++) {
            delete edges[i];
        }
    }
    void add_node(int id) {
        Vertex *v = new Vertex;
        v->set_id(id);
        nodes.push_back(v);
    }
    vector<Vertex*> get_nodes(void) {
        vector<Vertex*> res;
        for (int i = 0; i < nodes.size(); i++) {
            res.push_back(nodes[i]);
        }
        return res; 
    }
    Vertex *get_node(int id) {
        for (int i = 0; i < nodes.size(); i++) {
            if (id == nodes[i]->get_id()) {
                return nodes[i];
            }
        }
        return NULL;
    }
    void add_edge(const int source, const int target, const int weight) {
        Vertex *s = get_node(source);
        Vertex *t = get_node(target);
        Edge *e1 = new Edge;
        s->add_neighbor(t);
        e1->set_target(target);
        e1->set_source(source);
        e1->set_weight(weight);
        edges.push_back(e1);
        s->add_edge(e1);
        // non directed
        t->add_neighbor(s);
        t->add_edge(e1);
    }
    vector<Edge*> get_connecting_edges(Vertex *s, Vertex *t) {
        vector<Edge*> res;
        vector<Edge*> localedges = s->get_edges();
        for (int i = 0; i < localedges.size(); i++) {
            Edge *e = localedges[i];
            if (e->get_source() == s->get_id() && e->get_target() == t->get_id()) {
                res.push_back(e);
            }
            // non directed
            if (e->get_source() == t->get_id() && e->get_target() == s->get_id()) {
                res.push_back(e);
            }
        }
        return res;
    }
    int min_edge_weight(Vertex *s, Vertex *t) {
        vector<Edge*> edges = get_connecting_edges(s, t);
        int minedge = INT_MAX;
        for (int i = 0; i < edges.size(); i++) {
            int w = edges[i]->get_weight();
            if (w < minedge) {
                minedge = w;
            }
        }
        return minedge;
    }
    void set_root(int id) { root = get_node(id); }
    Vertex * get_root(void) { return root; }
    
    void print(void) {
        if (root != NULL) {
            cout << "Root: " << root->get_id() << endl;
        }
        cout << "Nodes: ";
        for (int i = 0; i < nodes.size(); i++) {
            cout << nodes[i]->get_id() << " ";
        }
        cout << endl;
        
        cout << "Edges:" << endl;
        for (int i = 0; i < edges.size(); i++) {
            cout << i << " source: " << edges[i]->get_source() << " target: "
                << edges[i]->get_target() << " Weight: " << edges[i]->get_weight() << endl;
        }
    }
};

Vertex *
min_node(vector<Vertex*> &q)
{
    int minval = INT_MAX;
    int val;
    Vertex * res = NULL;
    
    for (int i = 0; i < q.size(); i++) {
        val = q[i]->get_value();
        if (val < minval) {
            minval = val;
            res = q[i];
        }
    }
    return res;
}

void
dijkstra(Graph *graph)
{
    Vertex * root = graph->get_root();
    vector<Vertex*> nodes = graph->get_nodes();
    vector<Vertex*> q;
    
    for (int i = 0; i < nodes.size(); i++) {
        nodes[i]->set_value(INT_MAX);
        q.push_back(nodes[i]);
    }
    root->set_value(0);
    
    while (!q.empty()) {
        Vertex *u = min_node(q);
        if (u == NULL) {
            // these nodes are not reachable
            break;
        }
        int uid = u->get_id();
        vector<Vertex*> neighbors = u->get_neighbors();
        //cout << "Removing: " << uid << endl;
        q.erase(remove(q.begin(), q.end(), u), q.end());
        
        //cout << "num of neighbors: " << neighbors.size() << endl;
        for (int i = 0; i < neighbors.size(); i++) {
            int minedge;
            int vid = neighbors[i]->get_id();
            Vertex *v = graph->get_node(vid);
            int alt;
            //cout << "source: " << u->get_id() << " target: " << vid << endl;
            minedge = graph->min_edge_weight(u, v);
            alt = u->get_value() + minedge;
            if (alt < v->get_value()) {
                v->set_value(alt);
            }    
        }
    }
    
    for (int i = 0; i < nodes.size(); i++) {
        if (root->get_id() == nodes[i]->get_id()) {
            continue;
        }
        if (nodes[i]->get_value() == INT_MAX) {
            cout << -1 << " ";
        }
        else {
            cout << nodes[i]->get_value() << " ";
        }
    }
    cout << endl;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int cases;
    int n, m;
    int id;
    Graph *graph;
    cin >> cases;
    while (cases--) {
        graph = new Graph;
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            graph->add_node(i);
        }
        for (int i = 0; i < m; i++) {
            int source, target, weight;
            cin >> source >> target >> weight;
            graph->add_edge(source, target, weight);
        }
        cin >> id;
        graph->set_root(id);
        //graph->print();
        dijkstra(graph);
        delete graph;
    }
    return 0;
}