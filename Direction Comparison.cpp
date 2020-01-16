
ll kx, ky;

bool sameRow(int x, int y) {return (kx == x);}
bool sameColumn(int x, int y) {return (ky == y);}
ll rowDistance(int x, int y) {return abs(ky - y);}
ll columnDistance(int x, int y) {return abs(kx - x);}

bool sameDiagonalUp(int x, int y) {return (x+y == kx+ky);} /**  '/'  */
bool sameDiagonalDown(int x, int y) {return (x-kx == y-ky);} /**  '\'  */
ll diagonalUpDistance(int x, int y) {return abs(x-kx);}
ll diagonalDownDistance(int x, int y) {return abs(y-ky);}

ll upCovered(ll x, ll y) {return min(x-1, m-y) + min(n-x, y-1);}
ll downCovered(ll x, ll y) {return min(x-1, y-1) + min(n-x, m-y);}
ll diagonalBlocked(int x, int y) {return upCovered(x,y) + downCovered(x,y);}

bool upore(int x, int y) {return (kx < x);}
bool niche(int x, int y) {return (kx > x);}
bool baame(int x, int y) {return (ky < y);}
bool daane(int x, int y) {return (ky > y);}
