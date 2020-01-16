#include<bits/stdc++.h>
using namespace std;

int n;
string s;
vector<int>d1,d2;

void Manachr()
{
    for (int i = 0, l = 0, r = -1; i < n; i++)
    {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        cout<<k<<endl;
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k])
        {
            k++;
        }
        d1[i] = k--;
        if (i + k > r)
        {
            l = i - k;
            r = i + k;
        }
    }
    for (int i = 0, l = 0, r = -1; i < n; i++)
    {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k])
        {
            k++;
        }
        d2[i] = k--;
        if (i + k > r)
        {
            l = i - k - 1;
            r = i + k ;
        }
    }
}


int main()
{
    cin>>s;
    n = s.length();
    d1.assign(n,0);
    d2.assign(n,0);
    Manachr();
    for(int i=0;i<n;i++) cout<<d1[i]<<' ';cout<<endl;
    for(int i=0;i<n;i++) cout<<d2[i]<<' ';cout<<endl;
    return 0;
}
