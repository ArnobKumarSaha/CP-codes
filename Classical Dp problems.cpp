
ll histogram(int a[]) /** a[i] is the height of the i'th bar */
{
    stack<pll>s;
    s.push({-1,0});
    a[n+1]=0;
    for(int i=1;i<=n+1;i++){
        if(s.top().first > a[i]){
            ll indx = s.top().second;
            while(s.top().first > a[i]) {
                k = (i-s.top().second)*s.top().first;
                indx = s.top().second;
                ans = max(ans,k);
                s.pop();
            }
            s.push( {a[i], indx} );
        }
        else s.push({a[i], i});
    }
    return ans;
}
ll rodCutting(int a[]) /** a[i] is the price of the stick of length i */
{
    vi profit(n+3, 0);
    profit[1] = a[1];
    for(int i=2;i<=n;i++){
        int x=0;
        for(int j=1;j<i;j++){
            x = max(x, profit[j] + profit[i-j] );
        }
        profit[i] = max((ll)x, a[i]);
    }
    return profit[n];
}
ll subsetSum(int a[])/** a[i] is the value of i'th coin */
{
    vector<vi >chart(n+2, vi(sum+2));
    for(int i=0;i<=n;i++) chart[i][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=sum;j++){
            int f = (j-a[i] >= 0) ? chart[i-1][j-a[i]] : false;
            chart[i][j] = chart[i-1][j] or f;
            cout<<chart[i][j]<<' ';
        }
        cout<<nl;
    }
    asche;
    int curi=n, curj = sum;
    cout<<"Answer : ";
    while(curi >= 1)
    {
        if(chart[curi-1][curj] == 0){
            cout<<a[curi]<<' ';
            curj-=a[curi];
            curi--;
        }
        else curi--;
    }
    cout<<nl;
    return chart[n][sum]; /** returns 1, if possible to make sum using the available coins*/
}
