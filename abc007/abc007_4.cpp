#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <set>
#include <numeric>
#define rep(i, n) for(int i = 0; i < n; i++)
#define ll long long
#define V vector
using namespace std;
const ll INF = 1e18 * 9;


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

// const int mod = 1000000007;
const int mod = 998244353;
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

struct combination {
  vector<mint> fact, ifact;
  // n には aCb の aの最大値を入れて初期化する
  combination(int n):fact(n+1),ifact(n+1) {
    // assert(n < mod);
    fact[0] = 1;
    for (int i = 1; i <= n; ++i) fact[i] = fact[i-1]*i;
    ifact[n] = fact[n].inv();
    for (int i = n; i >= 1; --i) ifact[i-1] = ifact[i]*i;
  }
  mint operator()(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n]*ifact[k]*ifact[n-k];
  }
};

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

// long long dp[ 32 ][ 2 ][ 2 ];
ll solve(string a){
  int n = a.size();
  V<V<V<ll>>> dp(32, V<V<ll>>(2, V<ll>(2, 0)));
  dp[0][0][0] = 1;


  rep(i, n){
    int D = a[i] - '0';
    rep(j, 2){
      rep(k, 2){
        for(int d = 0; d <= ( j ? 9 : D ); d++){
        // for(int d = 0; d <= 9; d++){
          dp[ i + 1 ][ j || ( d < D ) ][ k || d == 4 || d== 9 ] += dp[i][j][k];
        }
      }
    }
  }
  return dp[n][0][1] + dp[n][1][1];
}

int main() {
  ll a, b;
  cin >> a >> b;


  ll ans = solve(to_string(b)) - solve(to_string(a - 1));




  cout << ans << endl;
}