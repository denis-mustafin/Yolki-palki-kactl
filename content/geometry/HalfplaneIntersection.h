/**
 * Author: Vsevolod Nagibin
 * Date: 2024-04-09
 * Description: Calculates the intersection of half-planes in a bounding box
 * Works in O(N log N)
 * Status: Works on ICPC 2020 C
 */

struct Point {
    long double x, y;
    Point(long double x, long double y): x(x), y(y) {}
    Point(): x(0), y(0) {}
};

Point operator+(const Point& first, const Point& second) {
    return Point(first.x + second.x, first.y + second.y);
}

Point operator-(const Point& first, const Point& second) {
    return Point(first.x - second.x, first.y - second.y);
}

long double cross(const Point& first, const Point& second) {
    return first.x * second.y - first.y * second.x;
}

long double sqrlen(const Point& P) {
    return P.x * P.x + P.y * P.y;
}

long double len(const Point& P) {
    return sqrtl(sqrlen(P));
}

const long double EPS = 1e-9;

bool is_zero(long double x) {
    return abs(x) < EPS;
}

bool is_less(long double a, long double b) {
    return (a - b) < -EPS;
}

bool is_more(long double a, long double b) {
    return (a - b) > EPS;
}

bool is_leq(long double a, long double b) {
    return (a - b) < EPS;
}

struct Line {
    long double a;
    long double b;
    long double c;
    Line(long double a, long double b, long double c): a(a), b(b), c(c) {}
    Point get_perp() const {
        return Point(a, b);
    }
    long double get_y_by_x(long double x) const {
        return (-c - a * x) / b;
    }
};

// for non collinear !
long double inter_x(const Line& l1, const Line& l2) {
    return (-l1.c * l2.b + l2.c * l1.b) / (l1.a * l2.b - l2.a * l1.b);
}

vector<Point> convex_hull(vector<Point> points) {
    if (points.empty())
        return {};
    for (size_t i = 1; i < points.size(); ++i) {
        if (is_less(points[i].y, points[0].y) || (is_zero(points[i].y - points[0].y) && points[i].x < points[0].x))
            swap(points[0], points[i]);
    }
    sort(points.begin() + 1, points.end(), [&](const Point& a, const Point& b) {
        if (is_zero(cross(a - points[0], b - points[0])))
            return sqrlen(a - points[0]) < sqrlen(b - points[0]);
        return cross(a - points[0], b - points[0]) > 0;
    });
    vector<Point> stack;
    for (Point P : points) {
        while (stack.size() >= 2 && is_leq(cross(stack.back() - stack[stack.size() - 2], P - stack.back()), 0))
            stack.pop_back();
        stack.emplace_back(P);
    }
    return stack;
}

const long double INF = 1e9;

vector<Point> halfplane_inter_points(vector<Line> lines) {
    // ax + by + c >= 0
    long double min_x = -INF;
    long double max_x = INF;
    vector<Line> up; // facing up
    vector<Line> down; // facing down
    for (Line l : lines) {
        if (is_zero(l.b)) {
            if (l.a > 0)
                min_x = max(min_x, -l.c / l.a);
            else
                max_x = min(max_x, -l.c / l.a);
        } else if (l.b > 0) {
            up.emplace_back(l);
        } else {
            down.emplace_back(l);
        }
    }
    if (is_leq(max_x, min_x)) {
        return {};
    }
    auto make_hull = [](vector<Line>& lines, vector<Line>& hull, vector<long double>& xs, bool up) {
        sort(lines.begin(), lines.end(), [up](const Line& l1, const Line& l2) {
            if (is_zero(cross(l1.get_perp(), l2.get_perp()))) {
                // parallel
                // with sqrtl:
                //   return l1.c / len(l1.get_perp()) < l2.c / len(l2.get_perp());
                // without, faster:
                if (is_leq(l1.c, 0)) {
                    if (is_more(l2.c, 0))
                        return true;
                    return is_more(l1.c * l1.c * sqrlen(l2.get_perp()), l2.c * l2.c * sqrlen(l1.get_perp()));
                } else {
                    if (is_leq(l2.c, 0))
                        return false;
                    return is_less(l1.c * l1.c * sqrlen(l2.get_perp()), l2.c * l2.c * sqrlen(l1.get_perp()));
                }
            }
            if (up) {
                return cross(l1.get_perp(), l2.get_perp()) > 0;
            }
            return cross(l1.get_perp(), l2.get_perp()) < 0;
        });
        for (Line l : lines) {
            // skip parallel
            if (!hull.empty() && is_zero(cross(hull.back().get_perp(), l.get_perp())))
                continue;
            if (hull.empty()) {
                hull.emplace_back(l);
                continue;
            }
            while (!xs.empty() && is_leq(inter_x(hull.back(), l), xs.back())) {
                hull.pop_back();
                xs.pop_back();
            }
            xs.emplace_back(inter_x(hull.back(), l));
            hull.emplace_back(l);
        }
    };
    vector<Line> up_hull;
    vector<long double> up_xs;
    make_hull(up, up_hull, up_xs, true);
    vector<Line> down_hull;
    vector<long double> down_xs;
    make_hull(down, down_hull, down_xs, false);
    size_t i1 = 0;
    size_t i2 = 0;
    while (i1 < up_xs.size() && is_less(up_xs[i1], min_x))
        ++i1;
    while (i2 < down_xs.size() && is_less(down_xs[i2], min_x))
        ++i2;
    long double prev = min_x;
    vector<Point> points;
    auto try_pushing_points = [&](long double x, size_t i1, size_t i2) {
        long double y_up = up_hull[i1].get_y_by_x(x);
        long double y_down = down_hull[i2].get_y_by_x(x);
        if (is_less(y_up, y_down)) {
            points.emplace_back(x, y_up);
            points.emplace_back(x, y_down);
        }
        if (!is_zero(cross(up_hull[i1].get_perp(), down_hull[i2].get_perp()))) {
            long double cur_x = inter_x(up_hull[i1], down_hull[i2]);
            if (is_leq(prev, cur_x) && is_leq(cur_x, x)) {
                points.emplace_back(cur_x, up_hull[i1].get_y_by_x(cur_x));
            }
        }
        prev = x;
    };
    try_pushing_points(min_x, i1, i2);
    while (i1 < up_xs.size() || i2 < down_xs.size()) {
        long double cur_x = 0;
        int old_i1 = i1;
        int old_i2 = i2;
        if (i1 < up_xs.size() && (i2 == down_xs.size() || up_xs[i1] < down_xs[i2])) {
            cur_x = up_xs[i1];
            ++i1;
        } else {
            cur_x = down_xs[i2];
            ++i2;
        }
        if (cur_x > max_x)
            cur_x = max_x;
        try_pushing_points(cur_x, old_i1, old_i2);
        if (cur_x == max_x)
            break;
    }
    if (prev < max_x)
        try_pushing_points(max_x, i1, i2);
    return convex_hull(points);
}
