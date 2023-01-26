#include <bits/stdc++.h>
using namespace std;

set<int> hash_table;

bool insertToTable(int i)
{
    cout << "inserting " << i << endl; 
    set<int>::iterator it = hash_table.find(i);
    if (it != hash_table.end())
        return false;
    else {
        hash_table.insert(i);
        return true;
    }
}

bool storeDigitProducts(vector<int> numbers)
{
    for (int i=0,j=1; j < numbers.size(); i++,j++) {
        int result = numbers[i] * numbers[j];
        cout << "inserting " << numbers[i] << " * " << numbers[j] << " = " << endl;
        if (!insertToTable(result))
            return false;
    }
    return true;
}

bool isColorful(string &number)
{
    for (int digits=1; digits < number.length(); digits++) {
        vector<int> digit_set;
        for (int i=0; i+digits <= number.length(); i++) {
            string num = number.substr(i, digits);
            digit_set.push_back(stoi(num));
            if (!insertToTable(stoi(num)))
                return false;
        }
        if (!storeDigitProducts(digit_set))
            return false;
    }
    return true;
}

int main()
{
    string test;
    getline(cin, test);

    cout << test << " is " << (isColorful(test) ? "colorful" : "not colorful");
    cout << endl;
    return 0;
}



