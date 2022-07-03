#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

typedef long double ld;

struct route {
    vector<int> v;
    int demand, p, ranc;
};

vector<route> routes;

void build(int n, vector<int> & need) {
    routes.resize(n);
    for (int i = 1; i < n; i++) {
        routes[i].v = {i};
        routes[i].demand = need[i];
        routes[i].p = i;
        routes[i].ranc = 0;
    }
}

int get_root(int u) {
    if (routes[u].p == u) return u;
    return routes[u].p = get_root(routes[u].p);
}

bool check(int u, int v) {
    return get_root(u) == get_root(v);
}

int routescnt;

void join(int u, int v, int mcap) {
    u = get_root(u);
    v = get_root(v);
    if (u == v) return;
    if (routes[u].demand + routes[v].demand > mcap) return;
    routescnt--;
    if (routes[u].ranc < routes[v].ranc) swap(u, v);
    routes[u].demand += routes[v].demand;
    for (auto r : routes[v].v) {
        routes[u].v.push_back(r);
    }
    routes[v].p = u;
    if (routes[u].ranc == routes[v].ranc) routes[u].ranc++;
}

ld tsp(vector<pair<int, int>> & nodes) {
    int n = nodes.size();
    vector<ld> x(n);
    vector<ld> y(n);
    for (int i = 0; i < n; i++) {
        x[i] = nodes[i].first;
        y[i] = nodes[i].second;
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
    return sum;
}

int main() {
    int n, m, mcap;
    cin >> n >> m >> mcap;
    routescnt = n - 1;
    vector<int> need(n);
    vector<pair<int, int>> nodes;
    for (int i = 0; i < n; i++) {
        ld x, y;
        cin >> need[i] >> x >> y;
        nodes.push_back({x, y});
    }
    vector<tuple<ld, int, int>> savings; // save, u, v
    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ld di0 = hypot(nodes[0].first - nodes[i].first, nodes[0].second - nodes[i].second);
            ld dj0 = hypot(nodes[0].first - nodes[j].first, nodes[0].second - nodes[j].second);
            ld dij = hypot(nodes[i].first - nodes[j].first, nodes[i].second - nodes[j].second);
            ld s = di0 + dj0 - dij;
            savings.push_back({s, i, j});
        }
    }
    sort(savings.rbegin(), savings.rend());
    build(n, need);
    for (auto [s, i, j] : savings) {
        join(i, j, mcap);
        if (routescnt <= m) break;
    }
    vector<bool> checked(n, false);
    ld res = 0;
    for (int i = 1; i < n; i++) {
        int root = get_root(i);
        if (checked[root]) continue;
        vector<pair<int, int>> tnodes;
        tnodes.push_back(nodes[0]);
        for (auto r : routes[root].v) {
            tnodes.push_back(nodes[r]);
        }
        res += tsp(tnodes);
        checked[root] = true;
    }
    cout << res << '\n';
}
