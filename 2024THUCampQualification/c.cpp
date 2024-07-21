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

struct Heap {
	std::priority_queue<int> a,b;
	Heap() { a.push(-1e9); }
	void push(int x) { a.emplace(x); }
	void pop(int x) { b.emplace(x); }
	int top() {
		while( sz(b) && a.top() == b.top() ) a.pop(), b.pop();
		return a.top();
	}
};

const int N = 1e5+5;
int n,q,a[N],lst[N];
Vi e[N];
Heap stop;

int son[N],rk[N];
Vi anc[N],b[N];
#define ls (u<<1)
#define rs (u<<1|1)
#define mid (l+r>>1)
struct {
	int n;
	Vi t;
	vector<Heap> leaf;
	void init(int sz) { n = sz, t.assign((n+1)*4,-1e9), leaf.resize(n+1); }
	void mdf(int p,int x,bool op,int u,int l,int r) {
		if( l == r ) {
			op ? leaf[l].push(x) : leaf[l].pop(x),
			t[u] = leaf[l].top();
			return;
		}
		p<=mid ? mdf(p,x,op,ls,l,mid) : mdf(p,x,op,rs,mid+1,r),
		t[u] = max(t[ls], t[rs]);
	}
	int qry(int ql,int qr,int u,int l,int r) {
		if( qr < l || r < ql ) return -1e9;
		if( ql <= l && r <= qr ) return t[u];
		return max(qry(ql,qr,ls,l,mid), qry(ql,qr,rs,mid+1,r));
	}
} seg[N];
void mdf(int u,bool op) {
	rFor(i,sz(anc[u])-2,0) {
		int x = anc[u][i], p = rk[anc[u][i+1]];
		seg[x].mdf(p,a[u]-b[u][i],op,1,1,seg[x].n);
	}
}
int qry(int u) {
	int res = seg[u].t[1];
	rFor(i,sz(anc[u])-2,0) {
		int x = anc[u][i], p = rk[anc[u][i+1]];
		ckmax(res, max(seg[x].qry(1,p-1,1,1,seg[x].n),
			seg[x].qry(p+1,seg[x].n,1,1,seg[x].n)) - b[u][i]);
	}
	Rep(i,0,sz(anc[u])) ckmax(res, a[anc[u][i]]-b[u][i]);
	return res;
}

int rt,siz[N],mxsz[N],dep[N];
bool del[N];
void fdrt(int u,int fa) {
	siz[u] = mxsz[u] = 1;
	for(int v : e[u]) if( !del[v] && v != fa )
		fdrt(v,u), siz[u] += siz[v], ckmax(mxsz[u],siz[v]);
	ckmax(mxsz[u],siz[0]-siz[u]);
	if( mxsz[u] <= mxsz[rt] ) rt = u;
}
void dfs(int u,int fa) {
	dep[u] = dep[fa] + 1, siz[u] = 1;
	anc[u].pb(rt), b[u].pb(dep[u]-1);
	for(int v : e[u]) if( !del[v] && v != fa ) dfs(v,u), siz[u] += siz[v];
}
int dvd(int u,int size) {
	siz[rt=0] = size, fdrt(u,0), del[u=rt] = 1;
	dfs(u,0);
	for(int v : e[u]) if( !del[v] ) rk[dvd(v,siz[v])] = ++son[u];
	return u;
}

void MAIN() {
	cin>>n>>q; For(i,1,n) cin>>a[i];
	Rep(i,1,n, x,y) cin>>x>>y, e[x].pb(y), e[y].pb(x);
	mxsz[0] = n, dvd(1,n);
	For(u,1,n) seg[u].init(son[u]);
	For(u,1,n) mdf(u,1);
	while( q-- ) {
		char op; int t,x; cin>>op>>t>>x;
		if( op == '-' ) lst[x] = t, stop.push(a[x]-t);
		else if( op == '+' )
			stop.pop(a[x]-lst[x]), mdf(x,0), a[x] += t-lst[x], mdf(x,1);
		else cout<<max({qry(x)-t,stop.top(),0})<<'\n';
	}
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
