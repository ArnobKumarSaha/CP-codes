#include<bits/stdc++.h>
using namespace std;

struct PREFIX_FUNCTION
{
    int N;
    string s;
    vector<int> pi;
    PREFIX_FUNCTION(string s): N(s.length()), s(s),pi(N) {}
    PREFIX_FUNCTION(): N(0) {}

    void setUp(string _s)
    {
        s = _s;
        N = s.length();
        pi.assign(N,0);
    }

    /** pi[i]=length of the longest proper prefix of the substring s[0…i] which is also a suffix */
    vector<int> prefix_function(string st)
    {
		setUp(st);
        for (int i = 1; i < N; i++)
        {
            int j = pi[i-1];
            while (j > 0 && st[i] != st[j])
                j = pi[j-1];
            if (st[i] == st[j])
                j++;
            pi[i] = j;
        }
        return pi;
    }

    /*** Return -1, if s isn't found in t. else return all of the starting index (of t) of matching. */
    vector<int> KMP(string s, string t)
    {
        pi = prefix_function(s+"#");
        vector<int> ret;
        int prev = pi[N-1],cur=0;
        for(int i=0; i<t.length(); i++)
        {
            int j = prev;
            while( j>0 and t[i]!=s[j])
            {
                j = pi[j-1];
            }
            if(t[i]==s[j]) j++;
            prev = j;
            if(prev == N-1)
            {
                ret.push_back(i-N+2);
            }
        }
        if(ret.empty()) return {-1};
        return ret;
    }

    /** ans[i]= the number of occurance of the prefix of Length i. */
    vector<int> prefix_koybar_ache(string s)
    {
		pi = prefix_function(s);

        vector<int> ans(N + 1);
        for (int i = 0; i < N; i++)
            ans[pi[i]]++;
        for (int i = N-1; i > 0; i--)
            ans[pi[i-1]] += ans[i];
        for (int i = 0; i <= N; i++)
            ans[i]++;
		return ans;
    }
	long long number_of_different_subString(string _s)
    {
		string str="", tmp="";
		long long ret=0;
		for(int i=0;i<_s.length();i++){
			str += _s[i];
			tmp = str;
			reverse(tmp.begin(), tmp.end());
            vector<int> ans = prefix_function(tmp);
            int x = *max_element(ans.begin(),ans.end());
            ret += str.length() - x;
		}
		return ret;
    }
    /** Returns the smallest length k, such that s can represented as a concatenation of one or more copies
            of string s[0, k-1] */
    int compressionLength(string s)
    {
        pi = prefix_function(s);
        int k = N-pi[N-1];
        if(N%k==0) return k;
        else return N;
    }
};

int main()
{
	//freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    PREFIX_FUNCTION p;
    string s,t;
    cin>>s;
    //p.setUp(s);
    vector<int>v;
    cout<<p.compressionLength(s);
    //for(auto z : v) cout<<z<<' ';
    return 0;
}

