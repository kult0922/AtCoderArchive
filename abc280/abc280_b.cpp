#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <set>
#include <numeric>
#include <regex>
#define rep(i, n) for(int i = 0; i < n; i++)
#define ll long long
#define V vector
using namespace std;
const ll INF = 1e18;
// 最大公約数
ll gcd(ll a, ll b) { return b?gcd(b,a%b):a;}
// 最小公倍数
ll lcm(ll a, ll b) { return a/gcd(a,b)*b;}


void print() {
  cout << endl;
}

template <class Head, class... Tail>
void print(Head&& head, Tail&&... tail) {
  cout << head;
  if (sizeof...(tail) != 0) cout << " ";
  print(forward<Tail>(tail)...);
}

template <class T>
void print(vector<T> &vec) {
  for (const auto& a : vec) {
    cout << a;
    if (&a != &vec.back()) cout << " ";
  }
  cout << endl;
}

template <class T>
void print(const vector<T> &vec) {
  for (const auto& a : vec) {
    cout << a;
    if (&a != &vec.back()) cout << " ";
  }
  cout << endl;
}

template <class T>
void print(vector<vector<T>> &df) {
  for (const auto& vec : df) {
    print(vec);
  }
}

template <class T>
void print(map<T, T> &mp) {
  for (const auto& a : mp) {
    cout << a.first << "=>" << a.second <<" ";
  }
  cout << endl;
}


// マップのキーの存在を確かめる
template<class MAP, class VALUE>
bool contains_key(MAP& m, VALUE v)
{
  return m.find(v) != m.end();
}


const int mod = 998244353;
// const int mod = 1000000007;
// mint ===
struct mint {
  ll x; // typedef long long ll;
  mint(ll x=0):x((x%mod+mod)%mod){}
  mint operator-() const { return mint(-x);}
  mint& operator+=(const mint a) {
    if ((x += a.x) >= mod) x -= mod;
    return *this;
  }
  mint& operator-=(const mint a) {
    if ((x += mod-a.x) >= mod) x -= mod;
    return *this;
  }
  mint& operator*=(const mint a) { (x *= a.x) %= mod; return *this;}
  mint operator+(const mint a) const { return mint(*this) += a;}
  mint operator-(const mint a) const { return mint(*this) -= a;}
  mint operator*(const mint a) const { return mint(*this) *= a;}
  mint pow(ll t) const {
    if (!t) return 1;
    mint a = pow(t>>1);
    a *= a;
    if (t&1) a *= *this;
    return a;
  }

  // for prime mod
  mint inv() const { return pow(mod-2);}
  mint& operator/=(const mint a) { return *this *= a.inv();}
  mint operator/(const mint a) const { return mint(*this) /= a;}
};
istream& operator>>(istream& is, mint& a) { return is >> a.x;}
ostream& operator<<(ostream& os, const mint& a) { return os << a.x;}
// mint ===



void YN(bool flag){
  if (flag){
    cout << "Yes" << endl;
  }else{
    cout << "No" << endl;
  }
}

V<pair<char, int>> lanlen(string s){
  char prev = 'Z';
  int n = s.size();
  V<pair<char, int>> res;

  rep(i, n){
    if (s[i] == prev){
      res[res.size() - 1].second += 1;
    }else{
      res.push_back(make_pair(s[i], 1));
    }
    prev = s[i];
  }

  return res;
}

struct UnionFind {
  vector<int> par, siz;

  UnionFind(int n) : par(n, -1), siz(n, 1){}

  // 根を求める
  int root(int x) {
    if (par[x] == -1) return x;
    else return par[x] = root(par[x]);
  }

  // xとyが同じグループか判定する
  bool isSame(int x, int y) { return root(x) == root(y); }

  // xを含むグループとyを含むグループを併合する
  bool unite(int x, int y) { 
    x = root(x); y = root(y);
    if (x == y) return false;

    if (siz[x] < siz[y]) swap(x, y);
    par[y] = x;
    siz[x] += siz[y];
    return true;
  }

  // xを含むグループのサイズ
  int size(int x) { return siz[root(x)]; }
};

struct Edge {
  int to;
  long long w;
  Edge(int to, long long w) : to(to), w(w) {}
};

template<class T> bool chmin(T& a, T b) {
    if (a > b) {
        a = b;
        return true;
    }
    else return false;
}

template<class T> bool chmax(T& a, T b) {
    if (a < b) {
        a = b;
        return true;
    }
    else return false;
}

V<ll> dijkstra(const V<V<Edge>>& g, int start){
  // ダイクストラ法
  int n = g.size();
  vector<long long> dist(n, INF);
  dist[start] = 0;

  // (d[v], v) のペアを要素としたヒープを作る
  priority_queue<pair<long long, int>,
                  vector<pair<long long, int>>,
                  greater<pair<long long, int>>> que;
  que.push(make_pair(dist[start], start));

  // ダイクストラ法の反復を開始
  while (!que.empty()) {
      // v: 使用済みでない頂点のうち d[v] が最小の頂点
      // d: v に対するキー値
      int v = que.top().second;
      long long d = que.top().first;
      que.pop();

      // d > dist[v] は，(d, v) がゴミであることを意味する
      if (d > dist[v]) continue; 

      // 頂点 v を始点とした各辺を緩和
      for (auto e : g[v]) {
          if (chmin(dist[e.to], dist[v] + e.w)) {
              // 更新があるならヒープに新たに挿入
              que.push(make_pair(dist[e.to], e.to)); 
          }
      }
  }

  return dist;
  
}

ll llpow(ll a, ll n){
  ll ans = 1;
  rep(i, n) ans *= a;

  return ans;
}

// 最大更新遅延
struct LazySegmentTree {
private:
  int n;
  vector<ll> node, lazy;
  vector<bool> lazyFlag;

public:
  LazySegmentTree(vector<ll> v) {
    int sz = (int)v.size();
    n = 1; while(n < sz) n *= 2;
    node.resize(2*n-1);
    lazy.resize(2*n-1, 0);
    lazyFlag.resize(2*n-1, false);

    for(int i=0; i<sz; i++) node[i+n-1] = v[i];
    for(int i=n-2; i>=0; i--) node[i] = max(node[i*2+1], node[i*2+2]);
  }

  void lazyEvaluate(int k, int l, int r) {
    if(lazyFlag[k]) {
      node[k] = lazy[k];
      if(r - l > 1) {
        lazy[k*2+1] = lazy[k*2+2] = lazy[k];
        lazyFlag[k*2+1] = lazyFlag[k*2+2] = true;
      }
      lazyFlag[k] = false;
    }
  }

  void update(int a, int b, ll x, int k=0, int l=0, int r=-1) {
    if(r < 0) r = n;
    lazyEvaluate(k, l, r);
    if(b <= l || r <= a) return;
    if(a <= l && r <= b) {
      lazy[k] = x;
      lazyFlag[k] = true;
      lazyEvaluate(k, l, r);
    }
    else {
      update(a, b, x, 2*k+1, l, (l+r)/2);
      update(a, b, x, 2*k+2, (l+r)/2, r);
      node[k] = max(node[2*k+1], node[2*k+2]);
    }
  }

  ll find(int a, int b, int k=0, int l=0, int r=-1) {
    if(r < 0) r = n;
    lazyEvaluate(k, l, r);
    if(b <= l || r <= a) return -INF;
    if(a <= l && r <= b) return node[k];
    ll vl = find(a, b, 2*k+1, l, (l+r)/2);
    ll vr = find(a, b, 2*k+2, (l+r)/2, r);
    return max(vl, vr);
  }
};

/*
int dfs(V<V<int>>& g, V<int>& dp, int v, int pre){
  dp[v] = 1;
  for(int nv : g[v]){
    if(nv == pre) continue;
    dp[v] += dfs(g, dp, nv, v);
  }
  return dp[v];
}
*/


bool isInside(int i, int j, int h, int w) {
  if(i >= h || j >= w){
    return false;
  }
  if(i < 0 || j < 0){
    return false;
  }
  return true; 
}

bool isValid(int i, int j, int h, int w, const V<string>& grid) {
  return isInside(i, j, h, w) && grid[i][j] == '.';
}

int trans(int idx, int n, int shift){
  return (idx + n - (shift % n)) % n;
}

ll tenwa(ll x){
  ll ans = 0;
  while(x > 0){
    ans += x % 10;
    x /= 10;
  }

  return ans;
}

string toBit(ll x){
  string s = "";
  while (x > 0)
  {
    s += to_string(x % 2);
    x /= 2;
  }

  return s;
}

ll toNum(string s){
  ll x = 0;
  rep(i, s.size()){
    if(s[i] == '1'){
      x += llpow((ll)2, (ll)i);
    }
  }
  return x;
}

ll getMin(V<ll>& x, ll n){
  V<ll> xf(n);
  sort(x.begin(), x.end());
  ll x_fuben = INF;

  for(int i = 1; i < n; i++){
    xf[0] += x[i] - x[0];
  }

  for(int i = 1; i < n; i++){
    ll diff = x[i] - x[i-1];
    ll L_num = i;
    ll R_num = n-i;
    xf[i] = xf[i-1] + (diff * L_num) - (diff * R_num);
  }

  rep(i, n){
    x_fuben = min(x_fuben, xf[i]);
  }

  return x_fuben;
}

const int di[] = {-1,0,1,0};
const int dj[] = {0,-1,0,1};

mint tousa_sum(mint start, ll kousu, mint d){
  return (mint)kousu * ((mint)2 * start + (mint)(kousu - 1) * d) / 2;
}

vector<ll> enumdiv(ll n) { 
  vector<ll> S;
  for (ll i = 1; 1LL*i*i <= n; i++) if (n%i == 0) { S.push_back(i); if (i*i != n) S.push_back(n / i); }
  sort(S.begin(), S.end());
  return S;
}

struct Point {
  int x, y;
  Point (int x = 0, int y = 0): x(x), y(y) {};
  Point operator- (const Point& a) const {
    return Point(x - a.x, y - a.y);
  }

};

double f(ll cnt, double a, double b){
  double g = 1.0 + (double)cnt;
  return b * (double)cnt + (a / sqrt(g));
}

int main() {
  int n;
  cin >> n;
  int su = 0;
  int su_ = 0;
  V<int> a(n);
  V<int> ans;
  rep(i, n) cin >> a[i];


  rep(i, n){
    su += a[i] - su_;
    ans.push_back(a[i] - su_);
    su_ = su;
  }

  print(ans);





}