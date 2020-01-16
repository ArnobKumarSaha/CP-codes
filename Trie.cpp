#include<bits/stdc++.h>
using namespace std;

struct node {
    bool endmark;
    node* next[10 + 1];
    int cnt;
    node()
    {
        endmark = false;
        cnt=0;
        for (int i = 0; i < 10; i++)
            next[i] = NULL;
    }
} * root;
void insert(char* str, int len)
{
    node* curr = root;
    for (int i = 0; i < len; i++) {
        int id = str[i] - '0';
        if (curr->next[id] == NULL)
            curr->next[id] = new node();

        curr = curr->next[id];curr->cnt++;
    }
    curr->endmark = 1;
}
bool search(char* str, int len)
{
    node* curr = root;
    for (int i = 0; i < len; i++) {
        int id = str[i] - '0';
        if (curr->next[id] == NULL)
            return false;
        curr = curr->next[id];
    }
    return curr->endmark;
}
void del(node* cur)
{
    for (int i = 0; i < 10; i++)
        if (cur->next[i])
            del(cur->next[i]);
    delete (cur);
}
bool findAnswer(node* cur)
{
	//cout<<cur->cnt<<' '<<cur->endmark<<endl;
	if(cur->cnt > 1 and cur->endmark) return false;
	bool f=true;
	for(int i=0;i<10;i++){
		if(cur->next[i]){
			f = f and findAnswer(cur->next[i]);
		}
	}
	return f;
}
void pri(node* cur, string str)
{
	//cout<<str<<endl;
	bool child = false;
	for(int i=0;i<10;i++){
		if(cur->next[i]){
			child = true;
			pri(cur->next[i], str+( (char)(i+'0') ));
		}
	}
	//if(!child) cout<<str<<endl;
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		root = new node();
		int n;
		scanf("%d",&n);
		char s[12];
		for(int i=0;i<n;i++){
			scanf("%s",s);
			insert(s,strlen(s));
		}
		bool ans = findAnswer(root);
		if(ans) printf("YES\n");
		else printf("NO\n");
		pri(root,"");
		del(root);
	}
    return 0;
}
/*
5
3
911
4562
911426
5
113
12340
123440
12345
98346
*/
