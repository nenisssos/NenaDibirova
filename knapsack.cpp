#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> p(n);
    vector<int> w(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i] >> w[i];
    }
    vector<int> f(m + 1, 0);
    for (int i = 0; i < n; i++) {
        for (int j = m; j >= w[i]; j--) {
            if (f[j - w[i]] + p[i] > f[j]) {
                f[j] = f[j - w[i]] + p[i];
            }
        }
    }
    cout << f[m] << '\n';
}
