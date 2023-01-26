#include <bits/stdc++.h>
using namespace std;

void print_array(int n, vector<int> arr)
{
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void quickSort(vector <int> &arr) 
{
    if (arr.size() <= 1)
        return;

	vector<int> left;
    vector<int> right;

    int pivot = arr[0];
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] < pivot)
            left.push_back(arr[i]);
        else
            right.push_back(arr[i]);
    }

    quickSort(left);
    quickSort(right);
    
    int i = 0;
    for (; i < left.size(); i++)
        arr[i] = left[i];
    
    arr[left.size()] = pivot;
    i++;

    for (int j = 0; j < right.size(); i++, j++)
        arr[i] = right[j];

    print_array(arr.size(), arr);
}


int main()
{
    int n;
    cin >> n;

    vector <int> arr(n);
    for(int i = 0; i < (int)n; ++i) {
        cin >> arr[i];
    }

    quickSort(arr);

    return 0;
}