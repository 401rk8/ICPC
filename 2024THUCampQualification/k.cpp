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

const int mod = 1e9+97;
struct mint {
	int x; mint(int x=0):x(x<0?x+mod:x<mod?x:x-mod){}
	mint(LL y) { y%=mod, x=y<0?y+mod:y; }
	mint& operator += (const mint &y) { x=x+y.x<mod?x+y.x:x+y.x-mod; return *this; }
	mint& operator -= (const mint &y) { x=x<y.x?x-y.x+mod:x-y.x; return *this; }
	mint& operator *= (const mint &y) { x=1ll*x*y.x%mod; return *this; }
	friend mint operator + (mint x,const mint &y) { return x+=y; }
	friend mint operator - (mint x,const mint &y) { return x-=y; }
	friend mint operator * (mint x,const mint &y) { return x*=y; }
	friend bool operator == (const mint &x,const mint &y) { return x.x == y.x; }
};	mint Pow(mint x,LL y=mod-2) { mint z(1);for(;y;y>>=1,x*=x)if(y&1)z*=x;return z; }

const int N = 2e5+5;
int n,q,id[26],siz[N];
mint base[N];
char s[N];

#define ls (u<<1)
#define rs (u<<1|1)
#define mid (l+r>>1)
#define segroot int u=1,int l=1,int r=n
#define lson ls,l,mid
#define rson rs,mid+1,r
struct Info {
	int len,vis; mint val;
	Info(){}
	Info(int len,int vis,mint val):len(len),vis(vis),val(val){}
	Info(int x) { len = 1, vis = 1<<x, val = x; }
	friend bool operator == (const Info &x,const Info &y)
	{ return x.len == y.len && x.vis == y.vis && x.val == y.val; }
	friend Info operator + (const Info &x,const Info &y) {
		return {x.len+y.len, x.vis|y.vis, x.val*base[y.len]+y.val};
	}
} t[N*4];
void up(int u) { t[u] = t[ls] + t[rs]; }
void bld(segroot) {
	if( l == r ) { t[u] = id[s[l]-'a'], ++siz[t[u].val.x]; return; }
	bld(lson), bld(rson), up(u);
}
void mdf(int p,int x,segroot) {
	if( l == r ) { --siz[t[u].val.x], t[u] = x, ++siz[x]; return; }
	p<=mid ? mdf(p,x,lson) : mdf(p,x,rson), up(u);
}
void rep(int x,int y,segroot) {
	if( !(t[u].vis>>x&1) ) return;
	if( l == r ) { --siz[x], t[u] = y, ++siz[y]; return; }
	rep(x,y,lson), rep(x,y,rson), up(u);
}
Info qry(int ql,int qr,segroot) {
	if( qr < l || r < ql ) return {0,0,0};
	if( ql <= l && r <= qr ) return t[u];
	return qry(ql,qr,lson) + qry(ql,qr,rson);
}

void MAIN() {
	iota(id,id+26,0);
	cin>>s+1, n = strlen(s+1);
	bld();
	cin>>q; while( q-- ) {
		int op = read();
		if( op == 1 ) {
			int p; cin>>p;
			mdf(p,id[read<char>()-'a']); 
		} else if( op == 2 ) {
			int x = read<char>()-'a', y = read<char>()-'a';
			if( siz[id[x]] > siz[id[y]] ) swap(id[x],id[y]);
			rep(id[x],id[y]);
		} else {
			int l1,r1,l2,r2; cin>>l1>>r1>>l2>>r2;
			cout<<(qry(l1,r1) == qry(l2,r2) ? "YES\n" : "NO\n");
		}
	}
} signed main() {
#ifdef FT
	freopen("in","r",stdin); freopen("out","w",stdout);
#endif
	ios::sync_with_stdio(0);cin.tie(0);
	base[0] = 1; Rep(i,1,N) base[i] = base[i-1] * 131;
	int lft=1; while( lft-- ) {
		MAIN();
	}
	return 0;
}
