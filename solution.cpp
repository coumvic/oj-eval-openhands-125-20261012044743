#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdio>
#include <algorithm>

using namespace std;

class DSU {
private:
    vector<int> parent;
    vector<int> rank;
    
public:
    DSU(int size) {
        parent.resize(size);
        rank.resize(size, 0);
        for (int i = 0; i < size; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void unite(int x, int y) {
        int px = find(x);
        int py = find(y);
        
        if (px == py) return;
        
        if (rank[px] < rank[py]) {
            parent[px] = py;
        } else if (rank[px] > rank[py]) {
            parent[py] = px;
        } else {
            parent[py] = px;
            rank[px]++;
        }
    }
    
    bool same(int x, int y) {
        return find(x) == find(y);
    }
};

int main() {
    int t;
    scanf("%d", &t);
    
    while (t--) {
        int n;
        scanf("%d", &n);
        
        vector<pair<pair<long long, long long>, int>> constraints;
        constraints.reserve(n);
        vector<long long> all_vars;
        all_vars.reserve(n * 2);
        
        // Read all constraints and collect all variables
        for (int i = 0; i < n; i++) {
            long long a, b;
            int e;
            scanf("%lld %lld %d", &a, &b, &e);
            constraints.push_back({{a, b}, e});
            all_vars.push_back(a);
            all_vars.push_back(b);
        }
        
        // Coordinate compression
        sort(all_vars.begin(), all_vars.end());
        all_vars.erase(unique(all_vars.begin(), all_vars.end()), all_vars.end());
        
        unordered_map<long long, int> var_to_idx;
        for (int i = 0; i < (int)all_vars.size(); i++) {
            var_to_idx[all_vars[i]] = i;
        }
        
        DSU dsu(all_vars.size());
        
        // First pass: process all equality constraints
        for (const auto& constraint : constraints) {
            long long a = constraint.first.first;
            long long b = constraint.first.second;
            int e = constraint.second;
            
            if (e == 1) {
                dsu.unite(var_to_idx[a], var_to_idx[b]);
            }
        }
        
        bool possible = true;
        
        // Second pass: check all inequality constraints
        for (const auto& constraint : constraints) {
            long long a = constraint.first.first;
            long long b = constraint.first.second;
            int e = constraint.second;
            
            if (e == 0) {
                if (dsu.same(var_to_idx[a], var_to_idx[b])) {
                    possible = false;
                    break;
                }
            }
        }
        
        printf("%s\n", possible ? "YES" : "NO");
    }
    
    return 0;
}