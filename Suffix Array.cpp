#include<bits/stdc++.h>
using namespace std;

vector<int> sort_cyclic_shifts(string const& s) {
    int n = s.size();
    const int alphabet = 256;
	vector<int> p(n), c(n), cnt(max(alphabet, n), 0);
    for (int i = 0; i < n; i++)
        cnt[s[i]]++;
    for (int i = 1; i < alphabet; i++)
        cnt[i] += cnt[i-1];
    for (int i = 0; i < n; i++)
        p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i-1]])
            classes++;
        c[p[i]] = classes - 1;
    }
    /** second part */
	vector<int> pn(n), cn(n);
    for (int h = 0; (1 << h) < n; ++h) {
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0)
                pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; i++)
            cnt[c[pn[i]]]++;
        for (int i = 1; i < classes; i++)
            cnt[i] += cnt[i-1];
        for (int i = n-1; i >= 0; i--)
            p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; i++) {
            pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
            pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]};
            if (cur != prev)
                ++classes;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }
    return p;
}
vector<int> suffix_array_construction(string s) {
    s += "$"; /** ascii value of $=36, * =42, | = 124 & = 38*/
    vector<int> sorted_shifts = sort_cyclic_shifts(s);
    sorted_shifts.erase(sorted_shifts.begin());
    return sorted_shifts;
}
/**For this below two, We have to save every version of c-array from SuffixArray construction */
//int compareSubstring(int i, int j, int l, int k) {
//	/*** l is the smallest length's substring between these two.
//		k is the biggest number such... 2^k <= l
//		and i and j are the starting index of two substrings. */
//    pair<int, int> a = {c[k][i], c[k][(i+l-(1 << k))%n]};
//    pair<int, int> b = {c[k][j], c[k][(j+l-(1 << k))%n]};
//    return a == b ? 0 : a < b ? -1 : 1;
//}

//int lcp(int i, int j) {
//	/**  longest common prefix of two arbitrary suffixes with starting position i and j. */
//    int ans = 0, log_n = (int)log2(n);
//    for (int k = log_n; k >= 0; k--) {
//        if (c[k][i] == c[k][j]) {
//            ans += 1 << k;
//            i += 1 << k;
//            j += 1 << k;
//        }
//    }
//    return ans;
//}
vector<int> lcp_construction(string const& s, vector<int> const& p) {
    int n = s.size();
    vector<int> rank(n, 0);
    for (int i = 0; i < n; i++)
        rank[p[i]] = i;

    int k = 0;
    vector<int> lcp(n-1, 0);
    for (int i = 0; i < n; i++) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = p[rank[i] + 1];
        while (i + k < n && j + k < n && s[i+k] == s[j+k])
            k++;
        lcp[rank[i]] = k;
        if (k)
            k--;
    }
    return lcp;
    /** lcp[i] = maximum prefix match of the suffixes starts from s[p[i]] and s[p[i-1]] */
}
long long numberOfDifferentSubstring(string s)
{
	/** Here , we have to construct suffix array in O(nlogn) and lcp array in O(n).
	(n*(n+1))/2 - (sum of lcp from 0 to s.length()-2);  */
}
int main()
{
	string s;
	cin>>s;
	vector<int>v =  suffix_array_construction(s);
	vector<int>lcp = lcp_construction(s,v);
	for(auto z : v) cout<<z<<' ';cout<<endl;
	for(auto z : lcp) cout<<z<<' ';cout<<endl;
	return 0;
}
