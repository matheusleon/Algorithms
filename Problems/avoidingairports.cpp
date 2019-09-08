#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll MAXN = 3e6 + 7;
const ll MAXT = 3e6 + 7;
const ll INF = 1e18 + 7;

class HullDynamic {
public:
    const double_t inf = 1e9;

    struct Line {
        ll m, b;
        double_t start;
        bool is_query;
        
        Line() {}
        
        Line(ll _m, ll _b, double_t _start, bool _is_query) : m(_m), b(_b), start(_start), is_query(_is_query) {}
        
        ll eval(ll x) { 
            return m * x + b; 
        }

        double_t intersect(const Line& l) const {
            return (double_t) (l.b - b) / (m - l.m);
        }

        bool operator< (const Line& l) const {
            if (is_query == 0) return m > l.m;
            return (start < l.start);
        }
    };

    typedef set<Line>::iterator iterator_t;

    bool has_prev(iterator_t it) {
        return (it != hull.begin());
    }

    bool has_next(iterator_t it) {
        return (++it != hull.end());
    }

    bool irrelevant(iterator_t it) {
        if (!has_prev(it) || !has_next(it)) return 0;
        iterator_t prev = it, next = it;
        prev--;
        next++;
        return next->intersect(*prev) <= it->intersect(*prev);
    }

    void update_left(iterator_t it) {
        if (it == hull.begin()) return;
        iterator_t pos = it;
        --it;
        vector<Line> rem;
        while(has_prev(it)) {
            iterator_t prev = it;
            --prev;
            if (prev->intersect(*pos) <= prev->intersect(*it)) {
                rem.push_back(*it);
            } else {
                break;
            }
            --it;
        }
        double_t start = pos->intersect(*it);
        Line f = *pos;
        for (Line r : rem) hull.erase(r);
        hull.erase(f);
        f.start = start;
        hull.insert(f);
    }

    void update_right(iterator_t it) {
        if (!has_next(it)) return;
        iterator_t pos = it;
        ++it;
        vector<Line> rem;
        while(has_next(it)) {
            iterator_t next = it;
            ++next;
            if (next->intersect(*pos) <= pos->intersect(*it)) {
                rem.push_back(*it);
            } else {
                break;
            }
            ++it;
        }
        double_t start = pos->intersect(*it);
        Line f = *it;
        for (Line r : rem) hull.erase(r);
        hull.erase(f);
        f.start = start;
        hull.insert(f);
    }

    void insert_line(ll m, ll b) {
        Line f(m, b, -inf, 0);
        iterator_t it = hull.lower_bound(f);
        if (it != hull.end() && it->m == f.m) {
            if (it->b <= f.b) {
                return;
            } else if (it->b > f.b) {
                hull.erase(it);
            }
        }
        hull.insert(f);
        it = hull.lower_bound(f);
        if (irrelevant(it)) {
            hull.erase(it);
            return;
        }
        update_left(it);
        it = hull.lower_bound(f);
        update_right(it);
    }

    ll get(ll x) {
        Line f(0, 0, x, 1);
        iterator_t it = hull.upper_bound(f);
        assert(it != hull.begin());
        --it;
        return it->m * x + it->b;
    }

private:
    set<Line> hull;
};

HullDynamic cht[MAXN];
long long dp[MAXN];
bool mark[MAXN];

struct event {
  ll type, a, b, tempo, idx;
};

bool cmp(event a, event b) {
  return a.tempo < b.tempo;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  ll n, m;
  cin >> n >> m;
  vector<event> events;
  for (ll i = 1; i <= m; i++) {
    int a, b, s, e;
    cin >> a >> b >> s >> e;
    events.push_back({+1, a, b, s, i});
    events.push_back({-1, a, b, e, i});
  }
  sort(events.begin(), events.end(), cmp);
  cht[1].insert_line(0, 0);
  mark[1] = true;
  long long ans = INF;
  memset(dp, -1, sizeof(dp));
  for (auto x : events) {
    ll type = x.type, a = x.a, b = x.b, tempo = x.tempo, idx = x.idx;
    if (type == 1) {
      if (mark[a]) {
        dp[idx] = 1LL * tempo * tempo + cht[a].get(tempo);
      }
    } else {
      if (dp[idx] != -1) {
        if (b == n) ans = min(ans, dp[idx]);
        cht[b].insert_line(-2 * tempo, dp[idx] + tempo*tempo);
        mark[b] = true;
      }
    }
  }
  cout << ans << '\n';
  return 0;
}
