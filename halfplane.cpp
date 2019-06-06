#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const double inf = 1e100, eps = 1e-9;
const double PI = acos(-1.0L);

struct PT {
  double x, y;
  PT(double x = 0, double y = 0) : x(x), y(y) {}

  PT operator + (const PT &p) const { return PT(x+p.x, y+p.y); }
  PT operator - (const PT &p) const { return PT(x-p.x, y-p.y); }
  PT operator * (double c) const { return PT(x*c, y*c); }
  PT operator / (double c) const { return PT(x/c, y/c); }

  bool operator <(const PT &p) const {
    if(abs(x - p.x) >= eps) return x < p.x;
    return abs(y - p.y) >= eps && y < p.y;
  }
  bool operator ==(const PT &p) const {
    return !(*this < p || p < *this);
  }
};

int cmp (double a, double b = 0) {
  if (abs(a-b) < eps) return 0;
  return (a < b) ? -1 : +1;
}

double cross (PT p, PT q) { return p.x * q.y - p.y*q.x; }
PT normalize (PT p) { return p/hypot(p.x, p.y); }

PT rotateCCW90 (PT p) { return PT(-p.y, p.x); }
PT rotateCW90 (PT p) { return PT(p.y, -p.x); }

struct L {
  PT a, b;
  L(){}
  L(PT a, PT b) : a(a), b(b) {}
  double ang(){
    return atan2(this->b.y - this->a.y, this->b.x - this->a.x);
  }
};
vector<L> line;
vector<PT> poly;

void addL(PT a, PT b) { line.push_back(L(a, b)); }

double angle(const L la) { return atan2(-(la.a.y - la.b.y), la.b.x - la.a.x); }

bool comp(L la, L lb){       
  if (cmp(angle(la), angle(lb)) == 0) return cross((lb.b - lb.a), (la.b - lb.a)) > eps;
    return cmp(angle(la), angle(lb)) < 0;
}

PT computeLineIntersection (PT a, PT b, PT c, PT d) {
  b = b - a; d = c - d; c = c - a;
  //assert(cmp(cross(b, d)) != 0);
  return a + b * (cross(c, d) / cross(b, d));
}

bool check(L l1, L l2, L l3) {
  PT p = computeLineIntersection(l2.a,l2.b, l3.a, l3.b);
  return cross((l1.b - l1.a),  (p - l1.a)) < -eps;
} 

vector<PT> hpi(double m) {
  line.clear();
  for (int i = 0; i < poly.size(); i++){
    int j = (i + 1) % poly.size();
    PT vec = poly[j] - poly[i];
    vec = rotateCW90(vec);
    vec = normalize(vec);
    addL(poly[j] + (vec*m), poly[i] + (vec*m));
  }
  sort(line.begin(), line.end(), comp);
  vector<L> pl(1, line[0]);
  for (int i = 0; i < (int)line.size(); i++) 
    if (cmp(angle(line[i]), angle(pl.back())) != 0) pl.push_back(line[i]);
  deque<int> dq;
  dq.push_back(0);
  dq.push_back(1);
  for (int i = 2; i < (int)pl.size(); i++) {
    while ((int)dq.size() > 1 && check(pl[i], pl[dq.back()], pl[dq[dq.size() - 2]])) dq.pop_back();
    while ((int)dq.size() > 1 && check(pl[i], pl[dq[0]], pl[dq[1]])) dq.pop_front();
    dq.push_back(i);
  }
  while ((int)dq.size() > 1 && check(pl[dq[0]], pl[dq.back()], pl[dq[dq.size() - 2]])) dq.pop_back();
  while ((int)dq.size() > 1 && check(pl[dq.back()], pl[dq[0]], pl[dq[1]])) dq.pop_front();
  vector<PT> res;
  for (int i = 0; i < (int)dq.size(); i++){
    res.emplace_back(computeLineIntersection(pl[dq[i]].a, pl[dq[i]].b, pl[dq[(i + 1) % dq.size()]].a, pl[dq[(i + 1) % dq.size()]].b));
  }
  return res;
}

int main(){
  int n;
  cout << fixed << setprecision(3);
  while (cin >> n && n) {
    poly.clear();
    for(int i = 0; i < n; i++){
      double x, y;
      cin >> x >> y;
      poly.push_back(PT(x, y));
    }
    reverse(poly.begin(), poly.end());
    double l = 0.0, r = 1e10;
    for (int i = 0; i < 200; i++) {
      double mid = (l + r) / 2.0;
      vector<PT> ans = hpi(mid);
      if (hpi(mid).size() > 2) {
        l = mid;
      } else {
        r = mid;
      }
    }
    cout << l << '\n';
  }
  return 0;
}
