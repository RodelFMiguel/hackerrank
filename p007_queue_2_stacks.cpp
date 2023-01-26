#include <cmath>
#include <cstdio>
#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>
using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

stack<int> s1; // <- 1 2 3 4 5 + 6
stack<int> s2; // <- 5 4 3 2 1

void enqueue(int x)
{
    s1.push(x);
}

void repopulate_queue()
{
    if (s1.empty() && s2.empty())
        return;

    if (s2.empty()) {
        while(!s1.empty()) {
            s2.push(s1.top());
            s1.pop();
        }
    }
}

void dequeue()
{
    repopulate_queue();
    s2.pop();
}

void print_head()
{
    repopulate_queue();
    cout << s2.top() << endl;   
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
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
            case 1: // enqueue
                enqueue(ops[1]);
                break;
            
            case 2: // dequeue
                dequeue();
                break;

            case 3: // print element at the front of queue
                print_head();
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