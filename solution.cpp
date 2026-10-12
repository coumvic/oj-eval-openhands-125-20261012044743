#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdio>
#include <algorithm>

using namespace std;

class DSU {
private:
    unordered_map<long long, long long> parent;
    unordered_map<long long, int> rank;
    
public:
    long long find(long long x) {
        if (parent.find(x) == parent.end()) {
            parent[x] = x;
            rank[x] = 0;
            return x;
        }
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void unite(long long x, long long y) {
        long long px = find(x);
        long long py = find(y);
        
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
    
    bool same(long long x, long long y) {
        return find(x) == find(y);
    }
    
    void clear() {
        parent.clear();
        rank.clear();
    }
};

int main() {
    int t;
    scanf("%d", &t);
    
    DSU dsu;
    
    while (t--) {
        int n;
        scanf("%d", &n);
        
        dsu.clear();
        
        vector<pair<pair<long long, long long>, int>> constraints;
        constraints.reserve(n);
        
        // Read all constraints
        for (int i = 0; i < n; i++) {
            long long a, b;
            int e;
            scanf("%lld %lld %d", &a, &b, &e);
            constraints.push_back({{a, b}, e});
        }
        
        // First pass: process all equality constraints
        for (const auto& constraint : constraints) {
            long long a = constraint.first.first;
            long long b = constraint.first.second;
            int e = constraint.second;
            
            if (e == 1) {
                dsu.unite(a, b);
            }
        }
        
        bool possible = true;
        
        // Second pass: check all inequality constraints
        for (const auto& constraint : constraints) {
            long long a = constraint.first.first;
            long long b = constraint.first.second;
            int e = constraint.second;
            
            if (e == 0) {
                if (dsu.same(a, b)) {
                    possible = false;
                    break;
                }
            }
        }
        
        printf("%s\n", possible ? "YES" : "NO");
    }
    
    return 0;
}