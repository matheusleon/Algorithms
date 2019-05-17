#include <bits/stdc++.h>

using namespace std;

struct event {
  int type, x, y1, y2;
  bool operator < (const event a) {
    if (x == a.x) {
      if (type == a.type) {
        if (y1 == a.y1) {
          return y2 < a.y2;
        }
        return y1 < a.y1;
      } 
      return type < a.type;
    } 
    return x < a.x;
  }
};

int main() {
  int n;
  cin >> n;
  vector<event> events;
  for (int i = 0; i < n; i++) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    events.push_back({0, x1, y1, y2});
    events.push_back({1, x2, y1, y2});
  }
  sort(events.begin(), events.end());
  long long area = 0;
  int last_x = -1;
  multiset<int> points;
  for (event curr : events) {
    if (last_x != -1) {
      long long min_y = *(points.begin());
      long long max_y = *(--points.end());
      long long delta_y = max_y - min_y;
      long long delta_x = curr.x - last_x;
      area += delta_x * delta_y;
    }
    if (curr.type == 0) {
      points.insert(curr.y1);
      points.insert(curr.y2);
    } else {
      points.erase(points.find(curr.y1));
      points.erase(points.find(curr.y2));
    }
    last_x = curr.x;
  }
  cout << area << '\n';
  return 0;
}
