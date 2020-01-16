#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+2;

///There can be at most n unique palindromes for a string of size n
struct node             ///a node is a palindromic substring of the string
{
    int nxt[26];        ///link to the palindrome which is formed by adding
                        ///next[i] in both side of this palindrome
    int len;            ///length of the palindrome
    int st,en;          ///starting and ending index of the node
    int suflink;        ///link to the maximum proper suffix palindrome of the node
    int cnt;            ///stores the length of the suffix link chain from it (including this node)
                        ///i.e. the number of palindromic suffix of this node
    int oc;             ///stores the number of occurrence of the node
    void details(int x)
    {
        cout<<"Node no. = "<<x<<", len = "<<len<<", st = "<<st<<", en = "<<en<<", ";
        cout<<"cnt="<<cnt<<", oc="<<oc<<", suflink="<<suflink<<endl;
        for(int i=0;i<26;i++) if(nxt[i]) cout<<i<<' '<<nxt[i]<<", ";
        cout<<endl;
    }
};
struct paltree
{
    string s;
    node t[N];
    int n;                  ///size of string
    int sz;                 ///indicates size of the tree
    int suf;                ///index of maximum suffix palindrome
    void init()
    {
        sz=2,suf=2;
        t[1].len=-1,t[1].suflink=1;  ///node 1- root with length -1
        t[2].len=0,t[2].suflink=1;   ///node 2- root with length 0 i.e null palindrome
    }
    /// return 1 if creates a new palindrome
    int add_letter(int pos)
    {
        int cur=suf,curlen=0;
        int ch=s[pos]-'a';
        ///find the maximum suffix of the prefix+s[pos]
        while(1){
            curlen=t[cur].len;
            if(pos-1-curlen>=0&&s[pos-1-curlen]==s[pos]) break;
            cur=t[cur].suflink;
        }
        if(t[cur].nxt[ch]){
            suf=t[cur].nxt[ch];
            t[suf].oc++;
            return 0;
        }
        ///if the node is not created yet then create the new node
        sz++;
        suf=sz;
        t[sz].oc=1;
        t[sz].len=t[cur].len+2;
        t[cur].nxt[ch]=sz; /// What is the node number of the string that can be got by adding
                            /// ch character , before and after the string that is in cur node.
        t[sz].en=pos;
        t[sz].st=pos-t[sz].len+1;
        if(t[sz].len==1){
            t[sz].suflink=2;
            t[sz].cnt=1;
            return 1;
        }
        /// Now find sz'th node er sufLink
        while(1){
            cur=t[cur].suflink;
            curlen=t[cur].len;
            if(pos-1-curlen>=0&&s[pos-1-curlen]==s[pos]){
                t[sz].suflink=t[cur].nxt[ch];
                break;
            }
        }
        t[sz].cnt=1+t[t[sz].suflink].cnt;
        return 1;
    }
    vector<int> makeTree(string _s)
    {
		s = _s;
		n = s.length();
		vector<int>arr(n,0);
		for(int i=0;i<n; i++){
			add_letter(i);
			arr[i] = t[suf].cnt; /// arr[i] = number of palindromic substring ended in ith position.
		}
		//for(int i=1;i<=sz;i++) t[i].details(i);
		//return arr;
    }
    void Reset()
    {
        for(int i=1;i<=sz;i++){
            t[i].len = t[i].st = t[i].en = t[i].suflink = t[i].cnt = t[i].oc = 0;
            for(int j=0;j<26;j++){
                t[i].nxt[j]=0;
            }
        }
    }
}t;

int main()
{
	t.init();
	t.makeTree("xyxyx");
	//t.makeTree("xyxaababab");
	return 0;
}
