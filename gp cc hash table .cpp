#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef pair<int, int> pii;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_map;


struct chash {
    int operator()(pii x) const { return x.first* 31 + x.second; }
};
typedef gp_hash_table<pii , int, chash> pght;


typedef cc_hash_table<int, int, hash<int>> cht;
typedef cc_hash_table<
    int, int, hash<int>, equal_to<int>, direct_mask_range_hashing<int>,
    hash_standard_resize_policy<hash_exponential_size_policy<>, hash_load_check_resize_trigger<true>, true> >
    cc;




struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
typedef gp_hash_table<long long,int,custom_hash> ght;
typedef gp_hash_table<
    int, int, hash<int>,equal_to<int>, direct_mod_range_hashing<int>, linear_probe_fn<>,
    hash_standard_resize_policy<hash_prime_size_policy,hash_load_check_resize_trigger<true>, true>  >
    gp;

typedef unordered_map <ll , int ,custom_hash> umap;


bool eraseVals = false;
void benchmarkUmap(string msg, vector<pii> &vals, int NUM_ITERS) {
    clock_t begin = clock();
    umap test;
    for (int t = 0; t < NUM_ITERS; t++) {
        for (auto i : vals) {
            test[i.first] = test[i.first] + i.second * t;
        }
    }
    cout << msg << ": " << string(60 - msg.size(), ' ') << "\t" << (double)(clock() - begin) / CLOCKS_PER_SEC << endl;
}
void benchmarkCC(string msg, vector<pii> &vals, int NUM_ITERS) {
    clock_t begin = clock();
    cht test;
    for (int t = 0; t < NUM_ITERS; t++) {
        for (auto i : vals) {
            test[i.first] = test[i.first] + i.second * t;
        }
    }
    cout << msg << ": " << string(60 - msg.size(), ' ') << "\t" << (double)(clock() - begin) / CLOCKS_PER_SEC << endl;
}
void benchmarkGP(string msg, vector<pii> &vals, int NUM_ITERS) {
    clock_t begin = clock();
    ght test;
    for (int t = 0; t < NUM_ITERS; t++) {
        for (auto i : vals) {
            test[i.first] = test[i.first] + i.second * t;
        }
    }
    cout << msg << ": " << string(60 - msg.size(), ' ') << "\t" << (double)(clock() - begin) / CLOCKS_PER_SEC << endl;
}
void benchmarkStl(string msg, vector<pii> &vals, int NUM_ITERS) {
    clock_t begin = clock();
    unordered_map<int, int> test;
    for (int t = 0; t < NUM_ITERS; t++) {
        for (auto i : vals) {
            test[i.first] = test[i.first] + i.second * t;
        }
    }
    cout << msg << ": " << string(60 - msg.size(), ' ') << "\t" << (double)(clock() - begin) / CLOCKS_PER_SEC << endl;
}

void benchmark(string msg, vector<pii> vals, int NUM_ITERS) {
    benchmarkStl("unordered map " + msg, vals, NUM_ITERS);
    benchmarkCC("policy cc hash table " + msg, vals, NUM_ITERS);
    benchmarkGP("policy gp hash table " + msg, vals, NUM_ITERS);
    benchmarkGP("safe unordered map " + msg, vals, NUM_ITERS);
    cout << endl;
}

vector<pii> generateVec(int max_val, bool shuffled) {
    vector<int> k(max_val), v(max_val);
    vector<pii> vals;
    iota(k.begin(), k.end(), 0);
    iota(v.begin(), v.end(), 0);
    if (shuffled) {
        random_shuffle(k.begin(), k.end());
        random_shuffle(v.begin(), v.end());
    }
    for (int i = 0; i < max_val; i++) {
        vals.push_back({k[i], v[i]});
    }
    return vals;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    benchmark("linear insertion", generateVec(1e6, false), 1);
    benchmark("linear read/write", generateVec(1e4, false), 1000);
    //benchmark("random insertion", generateVec(1e7, true), 1);
    //benchmark("random read/write", generateVec(1e5, true), 1000);
}



/** Hashing in a BIT */
//const int S = 1e9+1;
//const int maxfen = 1e9;
//void add(long long p, int v) {
//    for (/*p += S*/; p < maxfen; p += p & -p)
//        Tree[p] += v;
//}
//int sum(int p) {
//    int ans = 0;
//    for (/*p += S*/; p; p ^= p & -p)
//        ans += Tree[p];
//    return ans;
//}
//int main()
//{
//    for(ll i=1;i<=1e9;i*=10) add(i,2);
//    cout<<sum(1e7+1)<<endl;
//    return 0;
//}
