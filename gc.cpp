#include <iostream>
#include <vector>
using namespace std;

vector<int> cnt;

bool cmp(int u, int v) {
    return cnt[u] > cnt[v];
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<bool>> g(n, vector<bool> (n, false));
    vector<int> k;
    for (int i = 0; i < n; i++) {
        k.push_back(i);
    }
    cnt.resize(n, 0);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u][v] = true;
        g[v][u] = true;
        cnt[u]++;
        cnt[v]++;
    }
    sort(k.begin(), k.end(), cmp);

    vector<int> col(n, 0);
    for (int c = 1; true; c++) {
        bool flag = true;
        for (int i = 0; i < n; i++) {
            if (!col[i]) flag = false;
        }
        if (flag) {
            cout << c - 1 << '\n';
            break;
        }

        vector<int> cn;
        for (int i : k) {
            if (!col[i]) {
                bool tcol = true;
                for (int v : cn) {
                    if (g[i][v]) {
                        tcol = false;
                        break;
                    }
                }
                if (tcol) {
                    col[i] = c;
                    cn.push_back(i);
                }
            }
        }
    }
}
