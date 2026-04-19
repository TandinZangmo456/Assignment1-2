#include <iostream>
#include <vector>
using namespace std;
 
int main() {
    int N;
    cout << "Enter N: ";
    cin >> N;
 
    vector<int> arr(N);
    cout << "Enter " << N << " integers: ";
    for (int i = 0; i < N; i++) cin >> arr[i];
 
    int K;
    cout << "Enter K (divisor): ";
    cin >> K;
 
    int totalSubsets = (1 << N); 
    int count = 0;
 
    cout << "\n All Subsets \n";
 
    for (int mask = 0; mask < totalSubsets; mask++) {
        vector<int> subset;
        int sum = 0;
 
        for (int i = 0; i < N; i++) {
            if (mask & (1 << i)) { 
                subset.push_back(arr[i]);
                sum += arr[i];
            }
        }
 
        cout << "Mask " << mask << " → { ";
        for (int x : subset) cout << x << " ";
        cout << "} | Sum = " << sum;
 
        if (sum % K == 0) {
            cout << " ✓ (divisible by " << K << ")";
            count++;
        }
        cout << "\n";
    }
 
    cout << "\nTotal subsets         : " << totalSubsets << "\n";
    cout << "Subsets divisible by " << K << ": " << count << "\n";
 
    return 0;
}


/*
 * HOW BITMASKING WORKS:
 *   For N=3, masks go from 0 (000) to 7 (111)
 *   mask=5 → binary 101 → include arr[0] and arr[2]
 *   mask & (1<<i) checks if the i-th bit is set
 *
 * COMPLEXITY:
 *   Time  : O(2^N × N)  — feasible for N ≤ 20
 *   Space : O(N) for the current subset
 */