
void rec(int group, ll jStart, ll jEnd, ll optStart, ll optEnd)
{
    if(jStart > jEnd) return;
    ll jMid = (jStart + jEnd)/2;
    ll optimal = -1, &currentAnswer = dp[group][jMid] = (1LL<<29);

    for(int i=optStart; i<= min(jMid, optEnd); i++ ){
        ll tmp = dp[group-1][i] + c[i+1][jMid];
        if(tmp < currentAnswer){
            currentAnswer = tmp;
            optimal = i;
        }
    }
    rec(group, jStart, jMid-1, optStart, optimal);
    rec(group, jMid+1, jEnd, optimal, optEnd);
}

// In Main

for(int j=1;j<=n; j++){
        dp[1][j] = c[1][j];
    }
    for(int i=2; i<=k; i++){
        rec(i, 1, n, 1, n);
    }
    cout<<dp[k][n]<<nl;
