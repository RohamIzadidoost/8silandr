#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mk make_pair


struct P {
    ll x, y;
    void read() { cin >> x >> y; }
    P operator-(const P& b) const { return P{x - b.x, y - b.y}; }
    void operator-=(const P& b) {
        x -= b.x;
        y -= b.y;
    }
    ll operator*(const P& b) const { return x * b.y - y * b.x; }
    bool operator<(const P& b) const { return mk(x, y) < mk(b.x, b.y); }
    bool operator>(const P& b) const { return mk(x, y) > mk(b.x, b.y); }
    bool operator<=(const P& b) const { return mk(x, y) <= mk(b.x, b.y); }
    bool operator>=(const P& b) const { return mk(x, y) >= mk(b.x, b.y); }
    ll triangle(P& b, P& c) { return (b - *this) * (c - *this); }
};
 
bool segintersect(P a, P b, P c, P d) {
    if (!((b - a) * (d - c))) {      // Check if lines are parallel
        if (!((b - a) * (c - a))) {  // Check if lines are collinear
            if (max(a, b) < min(c, d) || max(c, d) < min(a, b)) {
                return 0;
            }
            return 1;
        }
        return 0;
    } else {
        bool fact1 = ((b - a) * (c - a) > 0) && ((b - a) * (d - a) > 0) or
                     ((b - a) * (c - a) < 0) && ((b - a) * (d - a) < 0);
        bool fact2 = ((d - c) * (b - c) > 0) && ((d - c) * (a - c) > 0) or
                     ((d - c) * (b - c) < 0) && ((d - c) * (a - c) < 0);
        if (fact1 || fact2) {
            return 0;
        }
        return 1;
    }
}
 
ll polygonarea2(vector<P> vv) {
    vector<P> v = vv;
    v.push_back(vv[0]);
    ll sum = 0;
    for (int i = 0; i < v.size() - 1; i++) {
        sum += v[i].x * v[i + 1].y - v[i].y * v[i + 1].x;
    }
    return abs(sum);
}
 
// checks if we draw a parallel ray to x vector if it intersects seg P2P3
bool onseg(const P& a, const P& b, const P& c) {
    if ((b - a) * (c - a) != 0) return false;
    return (a.x >= min(b.x, c.x) && a.x <= max(b.x, c.x)) &&
           (a.y >= min(b.y, c.y) && a.y <= max(b.y, c.y));
}
 
string inpolygon(const P& a, const vector<P>& v) {
    ll cnt = 0;
    bool boundary = false;
    int n = v.size();
 
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
 
        if (onseg(a, v[i], v[j])) {
            boundary = true;
            break;
        }
 
        if ((v[i].y > a.y) != (v[j].y > a.y)) {
            double x_intersect =
                (double)(v[j].x - v[i].x) * (a.y - v[i].y) / (v[j].y - v[i].y) +
                v[i].x;
            if (a.x < x_intersect) {
                cnt++;
            }
        }
    }
 
    if (boundary) return "BOUNDARY\n";
    return (cnt % 2 == 1) ? "INSIDE\n" : "OUTSIDE\n";
}
 
ll gcd(ll a, ll b) {
    while (b != 0) {
        ll temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
pair<ll,ll> insideBoundary(vector<P>&v){
    ll bnd=0,in=0;
    ll area2=polygonarea2(v);
    for  (int i=0;i<v.size();i++){
       ll j=(i+1)%v.size();
        if (v[i].x==v[j].x) bnd+=abs(v[j].y-v[i].y);
        else if (v[i].y==v[j].y) bnd+=abs(v[j].x-v[i].x);
        else bnd+=gcd(abs(v[j].x-v[i].x),abs(v[j].y-v[i].y));
    }
    in=(area2+2-bnd)/2;
    return mk(in,bnd);
}
 
bool ccw(const P& a, const P& b, const P& c) {
    return (b - a) * (c - a) > 0;
}
 
vector<P> convexhull(vector<P> v) {
    ll n = v.size(), k = 0;
    if (n == 1) return v;
    sort(v.begin(), v.end());
    vector<P> hull(2 * n);
    for (ll i = 0; i < n; ++i) {
        while (k >= 2 && ccw(hull[k - 2], hull[k - 1], v[i])) --k;
        hull[k++] = v[i];
    }
    for (ll i = n - 2, t = k + 1; i >= 0; --i) {
        while (k >= t && ccw(hull[k - 2], hull[k - 1], v[i])) --k;
        hull[k++] = v[i];
    }
    hull.resize(k-1); 
    return hull;
}


struct Line {
    // ax + by + c = 0
    ll a, b, c;

    Line() {}
    Line(ll a, ll b, ll c) : a(a), b(b), c(c) {}

    Line(const P& p1, const P& p2) {
        a = p2.y - p1.y;
        b = p1.x - p2.x;
        c = -(a * p1.x + b * p1.y);
    }

    bool onLine(const P& p) const {
        return a * p.x + b * p.y + c == 0;
    }

    bool parallel(const Line& other) const {
        return a * other.b == b * other.a;
    }

    bool same(const Line& other) const {
        return parallel(other) && a * other.c == c * other.a &&
               b * other.c == c * other.b;
    }

    pair<double, double> intersect(const Line& other) const {
        double det = (double)a * other.b - (double)b * other.a;
        double x = (double)(b * other.c - c * other.b) / det;
        double y = (double)(c * other.a - a * other.c) / det;
        return {x, y};
    }

    double dist(const P& p) const {
        return abs((double)a * p.x + (double)b * p.y + c) /
               sqrt((double)a * a + (double)b * b);
    }
};


struct Circle {
    P c;
    ll r;

    Circle() {}
    Circle(P c, ll r) : c(c), r(r) {}

    bool contains(const P& p) const {
        ll dx = p.x - c.x;
        ll dy = p.y - c.y;
        return dx * dx + dy * dy <= r * r;
    }


    int intersectLine(const Line& l, vector<pair<double,double>>& pts) const {
        double d = l.dist(c);
        if (d > r) return 0;

        double A = l.a, B = l.b, C = l.c;
        double x0 = c.x, y0 = c.y;

        double t = -(A * x0 + B * y0 + C) / (A * A + B * B);
        double xh = x0 + A * t;
        double yh = y0 + B * t;

        if (abs(d - r) < 1e-9) {
            pts.push_back({xh, yh});
            return 1;
        }

        double len = sqrt(r * r - d * d);
        double vx = -B / sqrt(A * A + B * B);
        double vy = A / sqrt(A * A + B * B);

        pts.push_back({xh + vx * len, yh + vy * len});
        pts.push_back({xh - vx * len, yh - vy * len});
        return 2;
    }


    int intersectCircle(const Circle& other, vector<pair<double,double>>& pts) const {
        double d = hypot(c.x - other.c.x, c.y - other.c.y);

        if (d > r + other.r) return 0;
        if (d < abs(r - other.r)) return 0;
        if (d == 0 && r == other.r) return -1; 

        double a = (r * r - other.r * other.r + d * d) / (2 * d);
        double h = sqrt(max(0.0, (double)r * r - a * a));

        double x2 = c.x + a * (other.c.x - c.x) / d;
        double y2 = c.y + a * (other.c.y - c.y) / d;

        double rx = -(other.c.y - c.y) * (h / d);
        double ry = (other.c.x - c.x) * (h / d);

        pts.push_back({x2 + rx, y2 + ry});
        if (h > 1e-9)
            pts.push_back({x2 - rx, y2 - ry});

        return pts.size();
    }
};

Line perpendicularBisector(const P& a, const P& b) {
    ll mx = a.x + b.x;
    ll my = a.y + b.y;
    ll dx = b.x - a.x;
    ll dy = b.y - a.y;
    ll A = -dy * 2;
    ll B = dx * 2;
    ll C = dy * mx - dx * my;

    return Line(A, B, C);
}
Line angleBisector(const P& a, const P& b, const P& c) {
    double v1x = a.x - b.x;
    double v1y = a.y - b.y;
    double v2x = c.x - b.x;
    double v2y = c.y - b.y;
    double d1 = hypot(v1x, v1y);
    double d2 = hypot(v2x, v2y);
    v1x /= d1; v1y /= d1;
    v2x /= d2; v2y /= d2;
    double dx = v1x + v2x;
    double dy = v1y + v2y;
    double A = -dy;
    double Bc = dx;
    double C = -(A * b.x + Bc * b.y);
    const double SCALE = 1e6;
    return Line(
        (ll)(A * SCALE),
        (ll)(Bc * SCALE),
        (ll)(C * SCALE)
    );
}

void sortAroundOrigin(vector<P>& v) {
    auto half = [&](const P& p) {
        return (p.y > 0) || (p.y == 0 && p.x > 0);
    };

    sort(v.begin(), v.end(), [&](const P& a, const P& b) {
        bool ha = half(a);
        bool hb = half(b);
        if (ha != hb) return ha > hb;  
        ll cross = a * b; 
        if (cross != 0) return cross > 0; 
        return a.x * a.x + a.y * a.y < b.x * b.x + b.y * b.y;
    });
}

vector<pair<double,double>> tangentPoints(const P& p, const Circle& cir) {
    vector<pair<double,double>> res;

    double dx = p.x - cir.c.x;
    double dy = p.y - cir.c.y;
    double r = cir.r;

    double d2 = dx*dx + dy*dy;
    if (d2 < r*r) return res;   

    double d = sqrt(d2);
    double base = atan2(dy, dx);

    if (d2 == r*r) {
        res.push_back({p.x, p.y});
        return res;
    }

    double ang = acos(r / d);

    for (int s : {-1, 1}) {
        double theta = base + s * ang;
        double x = cir.c.x + r * cos(theta);
        double y = cir.c.y + r * sin(theta);
        res.push_back({x, y});
    }
    return res;
}

pair<double,double> rotatePoint(const P& p, const P& O, double ang) {
    double x = p.x - O.x;
    double y = p.y - O.y;

    double c = cos(ang);
    double s = sin(ang);

    double xr = x * c - y * s;
    double yr = x * s + y * c;

    return {xr + O.x, yr + O.y};
}


pair<double,double> invertPoint(const P& p, const Circle& cir) {
    double dx = p.x - cir.c.x;
    double dy = p.y - cir.c.y;

    double d2 = dx*dx + dy*dy;
    double k = (double)cir.r * cir.r / d2;

    double x = cir.c.x + dx * k;
    double y = cir.c.y + dy * k;

    return {x, y};
}

const double PI = acos(-1);
using cd = complex<double>;
 
vector<cd> fft(vector<cd> v, bool invert) {
    int n = v.size();
    if (n == 1) return v;
 
    vector<cd> P[2];
    for (int i = 0; i < n; i++) P[i & 1].push_back(v[i]);
 
    vector<cd> S0 = fft(P[0], invert);
    vector<cd> S1 = fft(P[1], invert);
 
    vector<cd> res(n);
 
    cd wn = invert ? cd(cos(-2 * PI / n), sin(-2 * PI / n)) : cd(cos(2 * PI / n), sin(2 * PI / n));
 
    cd w(1);
    for (int i = 0; i < n / 2; i++) {
        res[i] = S0[i] + w * S1[i];
        res[i + n / 2] = S0[i] - w * S1[i];
        w *= wn;
    }
 
    if (invert)
        for (cd& x : res) x /= 2.0;
 
    return res;
}


