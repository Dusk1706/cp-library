// Codigo para contar el número de maneras de poder llegar desde la esquina
// superior izquierda de un tablero m*n hasta la esquina inferior derecha

#include <bits/stdc++.h>
//Pura gente del coach moy
using namespace std;
#define ENDL '\n'
#define f first
#define s second
#define all(s) begin(s), end(s)
#define rall(n) n.rbegin(), n.rend()
#define FOR(x, b) for(int x = 0; x <b; x++)
#define FORE(x, a, b) for(int x = a; x <= b; x++)
#define FORR(x, a, b) for(int x = a; x >= b; x--)
#define deb(x)      cerr << #x << " = " << x << '\n';
#define deb2(x, y)  cerr << #x << " = " << x << ", " << #y << " = " << y << '\n';
#define _ ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> ii;
typedef vector<int> vi;

const ll MOD = 1e9+7, INF=1e18;
ll gcd(ll a, ll b){return (b?gcd(b,a%b):a);}
ll lcm(ll a, ll b){ if(!a || !b) return 0; return a * b / gcd(a, b); }

map<ii,ull> memo;

ull gridTraveller(int n, int m){
    if(n==0||m==0)  return 0;
    if(n==1&&m==1)  return 1;
    if(memo[{n,m}]) return memo[{n,m}];
    return memo[{n,m}]=gridTraveller(n-1,m)+gridTraveller(n,m-1);
}

void solve(int tc=0){
    cout<<gridTraveller(30,20)<<ENDL;   //Output: 11541847896480
}

int main(){_
    int tc=1;
    // cin>>tc;
    for(int t=0;t<tc;t++){
        solve(t);
    }
    return 0;
}