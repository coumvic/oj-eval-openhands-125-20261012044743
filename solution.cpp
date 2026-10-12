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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    scanf("%d", &t);
    
    while (t--) {
        int n;
        scanf("%d", &n);
        
        // First pass: collect all variables and store constraints
        vector<long long> all_vars;
        vector<pair<long long, long long>> equal_constraints;
        vector<pair<long long, long long>> unequal_constraints;
        
        all_vars.reserve(n * 2);
        equal_constraints.reserve(n);
        unequal_constraints.reserve(n);
        
        for (int i = 0; i < n; i++) {
            long long a, b;
            int e;
            scanf("%lld %lld %d", &a, &b, &e);
            
            all_vars.push_back(a);
            all_vars.push_back(b);
            
            if (e == 1) {
                equal_constraints.push_back({a, b});
            } else {
                unequal_constraints.push_back({a, b});
            }
        }
        
        // Coordinate compression
        sort(all_vars.begin(), all_vars.end());
        all_vars.erase(unique(all_vars.begin(), all_vars.end()), all_vars.end());
        
        unordered_map<long long, int> var_to_idx;
        var_to_idx.reserve(all_vars.size() * 2);
        for (int i = 0; i < (int)all_vars.size(); i++) {
            var_to_idx[all_vars[i]] = i;
        }
        
        DSU dsu(all_vars.size());
        
        // Process equality constraints
        for (const auto& constraint : equal_constraints) {
            dsu.unite(var_to_idx[constraint.first], var_to_idx[constraint.second]);
        }
        
        bool possible = true;
        
        // Check inequality constraints
        for (const auto& constraint : unequal_constraints) {
            if (dsu.same(var_to_idx[constraint.first], var_to_idx[constraint.second])) {
                possible = false;
                break;
            }
        }
        
        printf("%s\n", possible ? "YES" : "NO");
    }
    
    return 0;
}