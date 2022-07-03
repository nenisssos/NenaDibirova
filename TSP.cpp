#include <iostream>
#include <vector>
#include <numeric>
#include <iomanip>
using namespace std;

typedef long double ld;

int main() {
    int n;
    cin >> n;
    vector<ld> x(n);
    vector<ld> y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    vector<int> ans(n);
    iota(ans.begin(), ans.end(), 0);
    for (int i = 1; i < n; i++) {
        ld mn = 1e18;
        int ps = i;
        for (int w = i; w < n; w++) {
            ld dst = hypot(x[ans[i - 1]] - x[ans[w]], y[ans[i - 1]] - y[ans[w]]);
            if (dst < mn) {
                mn = dst;
                ps = w;
            }
        }
        swap(ans[i], ans[ps]);
    }
    ld sum = 0;
    for (int i = 0; i < n; i++) {
        sum += hypot(x[ans[i]] - x[ans[(i + 1) % n]], y[ans[i]] - y[ans[(i + 1) % n]]);
    }
    cout << fixed << setprecision(10);
    cout << sum << '\n';
}