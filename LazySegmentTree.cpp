struct LazySegmentTree
{
    vll num;
    int Size;
    struct info
    {
        ll prop,sum;
        info(){}
        info(ll _prop, ll _sum){
            prop = _prop;
            sum = _sum;
        }
    };
    vector<info>Tree;

    void init(int _n){
        num.assign(_n+3, 0);
        Tree.assign(_n*4+3, info(0,0));
        Size = _n;
    }

    void build(int at, int l, int r)
    {
        Tree[at].sum=0;
        if(l == r)
        {
            Tree[at].sum = num[l];
            return ;
        }
        int mid = (l + r)/2;
        build(at*2, l, mid);
        build(at*2 + 1, mid+1, r);
        Tree[at].sum = Tree[at*2].sum + Tree[at*2+1].sum;
    }
    void propagate(int node,int beg,int end)
    {
        if(Tree[node].prop==0)
            return;
        if(beg!=end)
        {
            Tree[node*2].prop += Tree[node].prop;
            Tree[node*2+1].prop += Tree[node].prop;
        }
        Tree[node].sum += Tree[node].prop * (end-beg+1);
        Tree[node].prop=0;
    }
    void update(int node,int beg,int end,int x,int y,int val)
    {
        propagate(node,beg,end);
        if(x>end || y<beg)
            return;
        if(x<=beg && y>=end)
        {
            Tree[node].prop += val;
            propagate(node,beg,end);
            return;
        }
        int left=node*2,right=node*2+1,mid=(beg+end)/2;
        update(left,beg,mid,x,y,val);
        update(right,mid+1,end,x,y,val);

        Tree[node].sum = Tree[left].sum + Tree[right].sum + (end-beg+1)*Tree[node].prop;

    }
    ll query(int node,int beg,int end,int x,int y,int carry=0)
    {
        propagate(node,beg,end);
        if(x>end || y<beg)
            return 0;
        if(beg>=x && end<=y)
            return Tree[node].sum + carry*(end-beg+1);
        int left=node*2,right=node*2+1,mid=(beg+end)/2;

        ll p1 = query(left,beg,mid,x,y,carry+Tree[node].prop);
        ll p2 = query(right,mid+1,end,x,y,carry+Tree[node].prop);

        return p1+p2;
    }
};
