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

const int N = 2.5e5+5;
int n,m,fa[N],a[N],b[N];
mint ans;

struct {
	int cnt,fa[N*2],h[N*2];
	stack<pair<int*,int>> stk;
	void init() { cnt = 2*n, iota(fa+1,fa+cnt+1,1); }
	int find(int u) { while( u != fa[u] ) u = fa[u]; return u; }
	void mrg(int u,int v) {
		if( (u=find(u)) == (v=find(v)) ) return;
		if( h[u] > h[v] ) swap(u,v);
		stk.emplace(&fa[u],fa[u]), stk.emplace(&h[v],h[v]);
		--cnt, fa[u] = v, h[v] += h[u]==h[v];
	}
	void undo(int x,int y) {
		cnt = x;
		for(; sz(stk) > y; stk.pop()) *stk.top().fi = stk.top().se;
	}
} dsu;

#define ls (u<<1)
#define rs (u<<1|1)
#define mid (l+r>>1)
#define segroot int u=1,int l=0,int r=m
#define lson ls,l,mid
#define rson rs,mid+1,r
Vi t[N*4][2];
void ins(int ql,int qr,int x,bool op,segroot) {
	if( qr < l || r < ql ) return;
	if( ql <= l && r <= qr ) { t[u][op].pb(x); return; }
	ins(ql,qr,x,op,lson), ins(ql,qr,x,op,rson);
}
void dfs(segroot) {
	int cnt = dsu.cnt, sz = sz(dsu.stk);
	for(int i : t[u][0]) {
		dsu.mrg(a[i],b[i]), dsu.mrg(a[i]+n,b[i]+n);
		if( dsu.find(a[i]) == dsu.find(a[i]+n) ) goto togo;
		if( dsu.find(b[i]) == dsu.find(b[i]+n) ) goto togo;
	}
	for(int i : t[u][1]) {
		dsu.mrg(a[i],b[i]+n), dsu.mrg(a[i]+n,b[i]);
		if( dsu.find(a[i]) == dsu.find(a[i]+n) ) goto togo;
		if( dsu.find(b[i]) == dsu.find(b[i]+n) ) goto togo;
	}
	if( l == r ) {
		// cerr<<l<<": "<<dsu.cnt<<'\n';
		ans += Pow(2,dsu.cnt/2-1);
	} else dfs(lson), dfs(rson);
	togo: dsu.undo(cnt,sz);
}

void MAIN() {
	cin>>n>>m; For(i,2,n) cin>>fa[i]; For(i,1,m) cin>>a[i]>>b[i];
	For(i,1,m) ins(i,m,i,0), ins(0,i-1,i,1);
	dsu.init(), dfs();
	cout<<ans.x;
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
