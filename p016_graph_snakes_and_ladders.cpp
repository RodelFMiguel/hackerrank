#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'quickestWayUp' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. 2D_INTEGER_ARRAY ladders
 *  2. 2D_INTEGER_ARRAY snakes
 */

int getMinDistance(vector<int> nodes) {
    set<int> visited;
    list<int> nextToVisit;
    int distance = 0;
    
    nextToVisit.push_back(nodes[0]); // visit the first node
    while(!nextToVisit.empty()) {
        int level = nextToVisit.size();
        while (level-- > 0) {
            int node = nextToVisit.front();
            nextToVisit.pop_front();
            
            if (node == nodes.size()-1) {
                return distance;
            }
            
            if (visited.find(node) != visited.end()) {
                continue;
            }
            visited.insert(node);

            for (int i = node+1; i <= (node+6) && i < nodes.size(); i++) {
                if (nodes[i] == -1)
                    nodes[i] = i;
                nextToVisit.push_back(nodes[i]);
            }
        }
        distance += 1;
    }
    return -1;
}


int quickestWayUp(vector< vector<int> > ladders, vector< vector<int> > snakes) {
    
    vector<int> nodes;
    
    for (int i = 0; i < 100; i++) {
        nodes.push_back(-1);
    }
    nodes[0] = 0; // initialize the starting node
    
    for (int i = 0; i < ladders.size(); i++) {
//        cout << "ladders: " << ladders[i][0] << " " << ladders[i][1] << endl;
        nodes[(ladders[i][0]) - 1] = ladders[i][1] - 1;
//        cout << "new node @ index " << (ladders[i][0]) - 1 << ": " << nodes[(ladders[i][0]) - 1] << endl;
    }

    for (int i = 0; i < snakes.size(); i++) {
//        cout << "snakes: " << snakes[i][0] << " " << snakes[i][1] << endl;
        nodes[(snakes[i][0]) - 1] = snakes[i][1] - 1;
//        cout << "new node @ index " << (snakes[i][0]) - 1 << ": " << nodes[(snakes[i][0]) - 1] << endl;
    }

/*
    for (int i = 0; i < 100; i++) {
        if (i%10 == 0) cout << endl;
        cout << nodes[i] << " ";
    }
    cout << endl;
*/
    return getMinDistance(nodes);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string n_temp;
        getline(cin, n_temp);

        int n = stoi(ltrim(rtrim(n_temp)));

        vector< vector<int> > ladders(n);

        for (int i = 0; i < n; i++) {
            ladders[i].resize(2);

            string ladders_row_temp_temp;
            getline(cin, ladders_row_temp_temp);

            vector<string> ladders_row_temp = split(rtrim(ladders_row_temp_temp));

            for (int j = 0; j < 2; j++) {
                int ladders_row_item = stoi(ladders_row_temp[j]);

                ladders[i][j] = ladders_row_item;
            }
        }

        string m_temp;
        getline(cin, m_temp);

        int m = stoi(ltrim(rtrim(m_temp)));

        vector< vector<int> > snakes(m);

        for (int i = 0; i < m; i++) {
            snakes[i].resize(2);

            string snakes_row_temp_temp;
            getline(cin, snakes_row_temp_temp);

            vector<string> snakes_row_temp = split(rtrim(snakes_row_temp_temp));

            for (int j = 0; j < 2; j++) {
                int snakes_row_item = stoi(snakes_row_temp[j]);

                snakes[i][j] = snakes_row_item;
            }
        }

        int result = quickestWayUp(ladders, snakes);

        fout << result << "\n";
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
