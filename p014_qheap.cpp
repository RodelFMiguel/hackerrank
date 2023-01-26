#include <bits/stdc++.h>
using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

set<int> heap;

int main() {
    string test_count_str;
    getline(cin, test_count_str);
    int test_count = stoi(ltrim(rtrim(test_count_str)));

    for (int i = 0; i < test_count; i++) {
        string op_line;
        getline(cin, op_line);

        vector<string> ops_temp = split(rtrim(op_line));
        vector<int> ops(ops_temp.size());

        ops[0] = stoi(ops_temp[0]);
        if (ops_temp.size() > 1)
            ops[1] = stoi(ops_temp[1]);

        switch (ops[0]) {
            case 1: // add an element
                heap.insert(ops[1]);
                break;
            
            case 2: // delete an element
                {
                    set<int>::iterator it = heap.find(ops[1]);
                    heap.erase(it);
                }
                break;

            case 3: // print element at the front of queue
                cout << *heap.begin() << endl;
                break;
            
            default:
                break;
        }
    }

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