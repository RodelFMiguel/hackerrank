/* 
Given a string with alpha-numeric characters and parentheses, return a string with balanced parentheses by removing the fewest characters possible. You cannot add anything to the string.
Balanced parentheses means that each opening parenthesis has a corresponding closing parenthesis and the pairs of parentheses are properly nested

"()" -> "()"
"(())(" -> "(())"
"a(b)c)" -> "a(b)c"
")(" -> ""
"(((((" -> ""
"(()()(" -> "()()"
")(())(" -> "(())"
")())(()()(" -> "()()()"  

"())"
"(()" 
*/

#include <bits/stdc++.h>
using namespace std;

string balancedString(string s) {
    stack<int> index;
    
    for (int i=0; i < s.length(); i++) {
        if (s[i] == '(') {
            index.push(i);
        } else {
            if (s[i] == ')' && !index.empty())
                index.pop();
            else if (s[i] == ')')
                index.push(i);
        }
    }

    if (index.empty())
        return s;

    while(!index.empty()) {
        s[index.top()] = '*';
        cout << "index.top(): " << index.top() << endl;
        index.pop();
    }

    cout << "processing: " << s << endl;
    s.erase(remove(s.begin(), s.end(), '*'), s.end());
    return s;
}

int main()
{
    string s;
    cin >> s;

    cout << "balanced string: " << balancedString(s) << endl;
}
