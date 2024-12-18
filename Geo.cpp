#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
 
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef long double ld;

const ll nils = 1000000007;

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
  typedef Point P;
  T x, y;
  explicit Point(T x=0, T y=0) : x(x), y(y) {}
  bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
  bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
  P operator+(P p) const { return P(x+p.x, y+p.y); }
  P operator-(P p) const { return P(x-p.x, y-p.y); }
  P operator*(T d) const { return P(x*d, y*d); }
  P operator/(T d) const { return P(x/d, y/d); }
  T dot(P p) const { return x*p.x + y*p.y; }
  T cross(P p) const { return x*p.y - y*p.x; }
  T cross(P a, P b) const { return (a-*this).cross(b-*this); }
  T dist2() const { return x*x + y*y; }
  double dist() const { return sqrt((double)dist2()); }
  // angle to x-axis in interval [-pi, pi]
  double angle() const { return atan2(y, x); }
  P unit() const { return *this/dist(); } // makes dist()=1
  P perp() const { return P(-y, x); } // rotates +90 degrees
  P normal() const { return perp().unit(); }
  // returns point rotated 'a' radians ccw around the origin
  P rotate(double a) const {
    return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
  friend ostream& operator<<(ostream& os, P p) {
    return os << "(" << p.x << "," << p.y << ")"; }
};

struct Angle {
  int x, y;
  int t;
  Angle(int x, int y, int t=0) : x(x), y(y), t(t) {}
  Angle operator-(Angle b) const { return {x-b.x, y-b.y, t}; }
  int half() const {
    assert(x || y);
    return y < 0 || (y == 0 && x < 0);
  }
  Angle t90() const { return {-y, x, t + (half() && x >= 0)}; }
  Angle t180() const { return {-x, -y, t + half()}; }
  Angle t360() const { return {x, y, t + 1}; }
};
bool operator<(Angle a, Angle b) {
  // add a.dist2() and b.dist2() to also compare distances
  return make_tuple(a.t, a.half(), a.y * (ll)b.x) <
         make_tuple(b.t, b.half(), a.x * (ll)b.y);
}

template<class P> bool onSegment(P s, P e, P p) {
  return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

template<class P> vector<P> segInter(P a, P b, P c, P d) {
  auto oa = c.cross(d, a), ob = c.cross(d, b),
       oc = a.cross(b, c), od = a.cross(b, d);
  // Checks if intersection is single non-endpoint point.
  if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
    return {(a * ob - b * oa) / (ob - oa)};
  set<P> s;
  if (onSegment(c, d, a)) s.insert(a);
  if (onSegment(c, d, b)) s.insert(b);
  if (onSegment(a, b, c)) s.insert(c);
  if (onSegment(a, b, d)) s.insert(d);
  return {all(s)};
}

template<class T>
T polygonArea2(vector<Point<T>>& v) {
  T a = v.back().cross(v[0]);
  rep(i,0,sz(v)-1) a += v[i].cross(v[i+1]);
  return a;
}

vi num, st;
vector<vector<pii>> ed;
int Time;
int comps = 0;
int bridges = 0;
int dfs(int at, int par) {
  int me = num[at] = ++Time, top = me;
  for (auto [y, e] : ed[at]) if (e != par) {
    if (num[y]) {
      top = min(top, num[y]);
      if (num[y] < me)
        st.push_back(e);
    } else {
      int si = sz(st);
      int up = dfs(y, e);
      top = min(top, up);
      if (up == me) {
        st.push_back(e);
                comps++;
        st.resize(si);
      }
      else if (up < me) st.push_back(e);
      else {bridges++;}
    }
  }
  return top;
}

void bicomps() {
  num.assign(sz(ed), 0);
  rep(i,0,sz(ed)) if (!num[i]) dfs(i, -1);
}

int n = 0;
int m = 0;
vector<vl> segments;
map<ll,int> M;
vector<Point<ll> > pts;
vector<vi> C;
vector<vi> taken;

int geti(ll x, ll y){
    ll h = x*nils + y;
    if(M.find(h) != M.end())return M[h];
    M[h] = n;
    pts.push_back(Point<ll>(x, y));
    n++;
    vi temp;
    C.push_back(temp);
    taken.push_back(temp);
    vector<pii> temp2;
    ed.push_back(temp2);
    return n-1;
}
int from;
bool comp(int i, int j){
    Point<ll> pi = pts[i]-pts[from];
    Point<ll> pj = pts[j]-pts[from];
    return Angle(pi.x, pi.y) < Angle(pj.x, pj.y);
}

map<ll,ll> I;

int index(ll i, ll to){
    ll h = i*nils+to;
    assert(I.find(h) != I.end());
    return I[h];
}

vl areas;

ll get_area(int i, int j){
    vector<Point<ll> > polygon;
    int p = i;
    int q = j;
    while(1){
        polygon.push_back(pts[i]);
        taken[i][j] = 1;
        int i2 = C[i][j];
        int j2 = index(i,i2);
        j2 = (j2+1)%sz(C[i2]);
        i = i2;
        j = j2;
        if(i == p && j == q)break;
    }

    return polygonArea2(polygon);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> m;

    rep(c1,0,m){
        ll x1,y1,x2,y2;
        cin >> x1 >> y1 >> x2 >> y2;
        segments.push_back({x1,y1,x2,y2});
        int i = geti(x1,y1);
        int j = geti(x2,y2);
        assert(i != j);
        C[i].push_back(j);
        C[j].push_back(i);
        ed[i].push_back({j, 2*c1});
        ed[j].push_back({i, 2*c1+1});
        taken[i].push_back(0);
        taken[j].push_back(0);
    }

    bool planar = 1;

    rep(c1,0,min(m,1000)){
        rep(c2,c1+1,min(m,1000)){
            Point<ll> p1 = Point<ll>(segments[c1][0], segments[c1][1]);
            Point<ll> q1 = Point<ll>(segments[c1][2], segments[c1][3]);
            Point<ll> p2 = Point<ll>(segments[c2][0], segments[c2][1]);
            Point<ll> q2 = Point<ll>(segments[c2][2], segments[c2][3]);
            vector<Point<ll>> inter = segInter(p1,q1,p2,q2);
            if(sz(inter) == 0)continue;
            if(sz(inter) > 1){
                planar = 0;
                continue;
            }
            if(!(inter[0] == p1 || inter[0] == q1)){
                planar = 0;
            }
        }
    }
    assert(planar);
    bicomps();
    //assert(comps == 1);
    assert(bridges == 0);

    rep(c1,0,n){
        from = c1;
        sort(all(C[c1]), comp);
        
        rep(c2,0,sz(C[c1])){
            ll from2 = C[c1][c2];
            ll h = from2*nils+ll(c1);
            I[h] = c2;
        }
    }

    rep(c1,0,n){
        rep(c2,0,sz(C[c1])){
            if(!taken[c1][c2]){
                areas.push_back(abs(get_area(c1, c2)));
            }
        }
    }
    sort(all(areas));
    double ans = 0.0;

    rep(c1,0,sz(areas)-1){
        ans += areas[c1]*areas[c1];
    }

    cout << setprecision(18) << fixed << ans / 4.0 << "\n";

    return 0;
}