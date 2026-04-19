#include <iostream>
#include <vector>
#include <deque>
#include <array>
#include <numeric>
#include <algorithm>
#include <string>
using namespace std;

int main() {

    int N;
    cout << "Enter N: ";
    cin >> N;

    vector<int> v(N);
    cout << "Enter " << N << " integers: ";
    for (int i = 0; i < N; i++) cin >> v[i];

    reverse(v.begin(), v.end());

    cout << "Reversed: ";
    for (int x : v) cout << x << " ";
    cout << "\n";


    cout << "\n--- Part B: deque ---\n";
    deque<int> dq;
    int Q;
    cout << "Enter number of operations: ";
    cin >> Q;

    cout << "Operations: push_front <x>, push_back <x>, pop_front\n";
    while (Q--) {
        string op;
        cin >> op;
        if (op == "push_back") {
            int x; cin >> x;
            dq.push_back(x);
        } else if (op == "push_front") {
            int x; cin >> x;
            dq.push_front(x);
        } else if (op == "pop_front") {
            if (!dq.empty()) dq.pop_front();
            else cout << "Deque is empty, cannot pop.\n";
        }
    }

    cout << "Deque contents: ";
    for (int x : dq) cout << x << " ";
    cout << "\n";

    cout << "\n--- Part C: std::array ---\n";
    const int SIZE = 5;
    array<int, SIZE> arr;

    cout << "Enter " << SIZE << " integers: ";
    for (int i = 0; i < SIZE; i++) cin >> arr[i];

    int sum    = accumulate(arr.begin(), arr.end(), 0);
    int maxVal = *max_element(arr.begin(), arr.end());
    int minVal = *min_element(arr.begin(), arr.end());

    cout << "Array size : " << arr.size() << "\n";
    cout << "Sum        : " << sum << "\n";
    cout << "Max element: " << maxVal << "\n";
    cout << "Min element: " << minVal << "\n";

    return 0;
}

/*

 * COMPLEXITY:
 *   reverse()       → O(N)
 *   push/pop deque  → O(1) amortized
 *   accumulate()    → O(N)
 */