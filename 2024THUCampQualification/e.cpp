#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std; using namespace __gnu_pbds; using namespace __gnu_cxx;
#define For(i,x,y,...) for(int i=x,##__VA_ARGS__;i<=(y);++i)
#define rFor(i,x,y,...) for(int i=x,##__VA_ARGS__;i>=(y);--i)
#define Rep(i,x,y,...) for(int i=x,##__VA_ARGS__;i<(y);++i)
#define pb emplace_back
#define sz(a) int((a).size())
#define all(a) (a).begin(),(a).end()
#define fi first
#define se second
#define mkp make_pair
typedef long long LL; typedef vector<int> Vi; typedef pair<int,int> Pii;
auto ckmax=[](auto &x,auto y) { return x<y ? x=y,true : false; };
auto ckmin=[](auto &x,auto y) { return y<x ? x=y,true : false; };
sfmt19937 mt(chrono::steady_clock::now().time_since_epoch().count());
int rnd(int l,int r) { return uniform_int_distribution<>(l,r)(mt); }
template<typename T=int>T read() { T x; cin>>x; return x; }

const int mod = 998244353;
struct mint {
	int x; mint(int x=0):x(x<0?x+mod:x<mod?x:x-mod){}
	mint(LL y) { y%=mod, x=y<0?y+mod:y; }
	mint& operator += (const mint &y) { x=x+y.x<mod?x+y.x:x+y.x-mod; return *this; }
	mint& operator -= (const mint &y) { x=x<y.x?x-y.x+mod:x-y.x; return *this; }
	mint& operator *= (const mint &y) { x=1ll*x*y.x%mod; return *this; }
	friend mint operator + (mint x,const mint &y) { return x+=y; }
	friend mint operator - (mint x,const mint &y) { return x-=y; }
	friend mint operator * (mint x,const mint &y) { return x*=y; }
};	mint Pow(mint x,LL y=mod-2) { mint z(1);for(;y;y>>=1,x*=x)if(y&1)z*=x;return z; }

const int N = 2e5+5;
int n,ans[N];
struct Node { int id,x,y; } a[N];

#define ls(u) t[u].ls
#define rs(u) t[u].rs
#define mid (l+r>>1)
int ind,rt;
struct { int ls,rs,mx; } t[N*32];
void ins(int p,int x,int &u=rt,int l=1,int r=1e9) {
	if( !u ) u = ++ind;
	if( l == r ) { t[u].mx = x; return; }
	p<=mid ? ins(p,x,ls(u),l,mid) : ins(p,x,rs(u),mid+1,r),
	t[u].mx = max(t[ls(u)].mx, t[rs(u)].mx);
}
int qry(int ql,int qr,int &u=rt,int l=1,int r=1e9) {
	if( !u || qr < l || r < ql ) return 0;
	if( ql <= l && r <= qr ) return t[u].mx;
	return max(qry(ql,qr,ls(u),l,mid), qry(ql,qr,rs(u),mid+1,r));
}

void MAIN() {
	cin>>n; For(i,1,n) a[i].id = i, cin>>a[i].x>>a[i].y, ans[i] = INT_MAX;
	auto slv=[]() {
		sort(a+1,a+n+1,[](const Node &x,const Node &y)
			{ return x.x!=y.x ? x.x<y.x : x.y<y.y; });
		rFor(i,n-1,1, mx = a[n].y) {
			ckmin(ans[a[i].id], max(a[i].y-mx,0)), ckmax(mx,a[i].y);
			if( a[i+1].x == a[i].x ) ckmin(ans[a[i+1].id], a[i+1].y-a[i].y);
		}
	};
	slv(); For(i,1,n) swap(a[i].x,a[i].y); slv();
	For(i,1,n)
	ckmin(ans[a[i].id], a[i].x+a[i].y-qry(1,a[i].y)),
	ins(a[i].y,a[i].x+a[i].y);
	For(i,1,n) cout<<ans[i]<<" ";
} signed main() {
#ifdef FT
	freopen("in","r",stdin); freopen("out","w",stdout);
#endif
	ios::sync_with_stdio(0);cin.tie(0);
	int lft=1; while( lft-- ) {
		MAIN();
	}
	return 0;
}
