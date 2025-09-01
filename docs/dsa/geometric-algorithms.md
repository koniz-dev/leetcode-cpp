# Geometric Algorithms

## Overview

Geometric algorithms solve problems involving geometric objects such as points, lines, polygons, and curves. These algorithms are fundamental to computer graphics, computational geometry, robotics, and many other applications.

## Basic Geometric Primitives

### Point and Vector Operations

```cpp
#include <cmath>
#include <iostream>

struct Point {
    double x, y;
    
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    
    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }
    
    Point operator-(const Point& other) const {
        return Point(x - other.x, y - other.y);
    }
    
    Point operator*(double scalar) const {
        return Point(x * scalar, y * scalar);
    }
    
    double dot(const Point& other) const {
        return x * other.x + y * other.y;
    }
    
    double cross(const Point& other) const {
        return x * other.y - y * other.x;
    }
    
    double magnitude() const {
        return std::sqrt(x * x + y * y);
    }
    
    double distance(const Point& other) const {
        return (*this - other).magnitude();
    }
    
    Point normalize() const {
        double mag = magnitude();
        if (mag == 0) return Point();
        return *this * (1.0 / mag);
    }
    
    // Rotate point around origin by given angle (in radians)
    Point rotate(double angle) const {
        double cos_a = std::cos(angle);
        double sin_a = std::sin(angle);
        return Point(x * cos_a - y * sin_a, x * sin_a + y * cos_a);
    }
};

struct Line {
    Point p1, p2;
    
    Line(const Point& a, const Point& b) : p1(a), p2(b) {}
    
    double length() const {
        return p1.distance(p2);
    }
    
    Point direction() const {
        return (p2 - p1).normalize();
    }
    
    // Check if point lies on line
    bool contains(const Point& p) const {
        return std::abs((p2 - p1).cross(p - p1)) < 1e-9;
    }
    
    // Distance from point to line
    double distanceToPoint(const Point& p) const {
        Point v = p2 - p1;
        Point w = p - p1;
        double c1 = w.dot(v);
        if (c1 <= 0) return p.distance(p1);
        
        double c2 = v.dot(v);
        if (c2 <= c1) return p.distance(p2);
        
        double b = c1 / c2;
        Point pb = p1 + v * b;
        return p.distance(pb);
    }
};
```

### Line Intersection

```cpp
#include <vector>
#include <iostream>

class LineIntersection {
public:
    // Check if two line segments intersect
    static bool segmentsIntersect(const Point& a1, const Point& a2,
                                 const Point& b1, const Point& b2) {
        double c1 = (a2 - a1).cross(b1 - a1);
        double c2 = (a2 - a1).cross(b2 - a1);
        double c3 = (b2 - b1).cross(a1 - b1);
        double c4 = (b2 - b1).cross(a2 - b1);
        
        // Check if segments straddle each other
        if (c1 * c2 < 0 && c3 * c4 < 0) return true;
        
        // Check if any endpoint lies on the other segment
        if (c1 == 0 && onSegment(a1, a2, b1)) return true;
        if (c2 == 0 && onSegment(a1, a2, b2)) return true;
        if (c3 == 0 && onSegment(b1, b2, a1)) return true;
        if (c4 == 0 && onSegment(b1, b2, a2)) return true;
        
        return false;
    }
    
    // Find intersection point of two lines
    static Point lineIntersection(const Line& l1, const Line& l2) {
        Point v1 = l1.p2 - l1.p1;
        Point v2 = l2.p2 - l2.p1;
        Point w = l2.p1 - l1.p1;
        
        double denom = v1.cross(v2);
        if (std::abs(denom) < 1e-9) {
            // Lines are parallel
            return Point(); // Return invalid point
        }
        
        double t = w.cross(v2) / denom;
        return l1.p1 + v1 * t;
    }
    
private:
    static bool onSegment(const Point& a, const Point& b, const Point& c) {
        return c.x <= std::max(a.x, b.x) && c.x >= std::min(a.x, b.x) &&
               c.y <= std::max(a.y, b.y) && c.y >= std::min(a.y, b.y);
    }
};
```

## Convex Hull

### Graham Scan Algorithm

```cpp
#include <vector>
#include <algorithm>
#include <iostream>

class ConvexHull {
private:
    // Find orientation of triplet (p, q, r)
    static int orientation(const Point& p, const Point& q, const Point& r) {
        double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
        if (std::abs(val) < 1e-9) return 0;  // Collinear
        return (val > 0) ? 1 : 2;  // Clockwise or Counterclockwise
    }
    
    // Compare points for sorting
    static bool comparePoints(const Point& p1, const Point& p2) {
        // Find the bottommost point (and leftmost if tied)
        if (p1.y != p2.y) return p1.y < p2.y;
        return p1.x < p2.x;
    }
    
public:
    static std::vector<Point> grahamScan(std::vector<Point> points) {
        int n = points.size();
        if (n < 3) return points;
        
        // Find bottommost point
        int bottommost = 0;
        for (int i = 1; i < n; ++i) {
            if (points[i].y < points[bottommost].y ||
                (points[i].y == points[bottommost].y && points[i].x < points[bottommost].x)) {
                bottommost = i;
            }
        }
        
        // Swap bottommost point to first position
        std::swap(points[0], points[bottommost]);
        
        // Sort remaining points by polar angle with respect to bottommost point
        Point p0 = points[0];
        std::sort(points.begin() + 1, points.end(), [&p0](const Point& a, const Point& b) {
            int o = orientation(p0, a, b);
            if (o == 0) {
                return p0.distance(a) < p0.distance(b);
            }
            return o == 2; // Counterclockwise
        });
        
        // Remove collinear points
        int m = 1;
        for (int i = 1; i < n; ++i) {
            while (i < n - 1 && orientation(p0, points[i], points[i + 1]) == 0) {
                i++;
            }
            points[m] = points[i];
            m++;
        }
        
        if (m < 3) return std::vector<Point>(points.begin(), points.begin() + m);
        
        // Build convex hull
        std::vector<Point> hull;
        hull.push_back(points[0]);
        hull.push_back(points[1]);
        hull.push_back(points[2]);
        
        for (int i = 3; i < m; ++i) {
            while (hull.size() > 1 && 
                   orientation(hull[hull.size() - 2], hull[hull.size() - 1], points[i]) != 2) {
                hull.pop_back();
            }
            hull.push_back(points[i]);
        }
        
        return hull;
    }
    
    // Jarvis March (Gift Wrapping) algorithm
    static std::vector<Point> jarvisMarch(std::vector<Point> points) {
        int n = points.size();
        if (n < 3) return points;
        
        std::vector<Point> hull;
        
        // Find leftmost point
        int leftmost = 0;
        for (int i = 1; i < n; ++i) {
            if (points[i].x < points[leftmost].x) {
                leftmost = i;
            }
        }
        
        int p = leftmost;
        do {
            hull.push_back(points[p]);
            
            int q = (p + 1) % n;
            for (int i = 0; i < n; ++i) {
                if (orientation(points[p], points[i], points[q]) == 2) {
                    q = i;
                }
            }
            
            p = q;
        } while (p != leftmost);
        
        return hull;
    }
};
```

## Polygon Operations

### Point in Polygon

```cpp
#include <vector>
#include <iostream>

class PolygonOperations {
public:
    // Ray casting algorithm to check if point is inside polygon
    static bool pointInPolygon(const Point& point, const std::vector<Point>& polygon) {
        int n = polygon.size();
        if (n < 3) return false;
        
        bool inside = false;
        for (int i = 0, j = n - 1; i < n; j = i++) {
            if (((polygon[i].y > point.y) != (polygon[j].y > point.y)) &&
                (point.x < (polygon[j].x - polygon[i].x) * (point.y - polygon[i].y) /
                          (polygon[j].y - polygon[i].y) + polygon[i].x)) {
                inside = !inside;
            }
        }
        
        return inside;
    }
    
    // Winding number algorithm (more robust)
    static bool pointInPolygonWinding(const Point& point, const std::vector<Point>& polygon) {
        int n = polygon.size();
        if (n < 3) return false;
        
        double windingNumber = 0;
        for (int i = 0; i < n; ++i) {
            Point p1 = polygon[i];
            Point p2 = polygon[(i + 1) % n];
            
            if (p1.y <= point.y) {
                if (p2.y > point.y && (p2 - p1).cross(point - p1) > 0) {
                    windingNumber++;
                }
            } else {
                if (p2.y <= point.y && (p2 - p1).cross(point - p1) < 0) {
                    windingNumber--;
                }
            }
        }
        
        return windingNumber != 0;
    }
    
    // Calculate polygon area using shoelace formula
    static double polygonArea(const std::vector<Point>& polygon) {
        int n = polygon.size();
        if (n < 3) return 0;
        
        double area = 0;
        for (int i = 0; i < n; ++i) {
            int j = (i + 1) % n;
            area += polygon[i].x * polygon[j].y;
            area -= polygon[j].x * polygon[i].y;
        }
        
        return std::abs(area) / 2.0;
    }
    
    // Check if polygon is convex
    static bool isConvex(const std::vector<Point>& polygon) {
        int n = polygon.size();
        if (n < 3) return false;
        
        int sign = 0;
        for (int i = 0; i < n; ++i) {
            Point p1 = polygon[i];
            Point p2 = polygon[(i + 1) % n];
            Point p3 = polygon[(i + 2) % n];
            
            double cross = (p2 - p1).cross(p3 - p2);
            if (cross != 0) {
                if (sign == 0) {
                    sign = (cross > 0) ? 1 : -1;
                } else if (sign != (cross > 0 ? 1 : -1)) {
                    return false;
                }
            }
        }
        
        return true;
    }
};
```

## Closest Pair

### Divide and Conquer Approach

```cpp
#include <vector>
#include <algorithm>
#include <iostream>
#include <climits>

class ClosestPair {
private:
    static double closestPairRecursive(std::vector<Point>& points, int left, int right) {
        if (right - left <= 3) {
            return closestPairBruteForce(points, left, right);
        }
        
        int mid = (left + right) / 2;
        double midX = points[mid].x;
        
        double leftMin = closestPairRecursive(points, left, mid);
        double rightMin = closestPairRecursive(points, mid, right);
        double minDist = std::min(leftMin, rightMin);
        
        // Find points within minDist of the middle line
        std::vector<Point> strip;
        for (int i = left; i < right; ++i) {
            if (std::abs(points[i].x - midX) < minDist) {
                strip.push_back(points[i]);
            }
        }
        
        // Sort strip by y-coordinate
        std::sort(strip.begin(), strip.end(), [](const Point& a, const Point& b) {
            return a.y < b.y;
        });
        
        // Check distances in strip
        for (size_t i = 0; i < strip.size(); ++i) {
            for (size_t j = i + 1; j < strip.size() && 
                 (strip[j].y - strip[i].y) < minDist; ++j) {
                double dist = strip[i].distance(strip[j]);
                minDist = std::min(minDist, dist);
            }
        }
        
        return minDist;
    }
    
    static double closestPairBruteForce(const std::vector<Point>& points, int left, int right) {
        double minDist = std::numeric_limits<double>::max();
        
        for (int i = left; i < right; ++i) {
            for (int j = i + 1; j < right; ++j) {
                double dist = points[i].distance(points[j]);
                minDist = std::min(minDist, dist);
            }
        }
        
        return minDist;
    }
    
public:
    static double findClosestPair(std::vector<Point> points) {
        int n = points.size();
        if (n < 2) return 0;
        
        // Sort points by x-coordinate
        std::sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
            return a.x < b.x;
        });
        
        return closestPairRecursive(points, 0, n);
    }
    
    // Return the actual closest pair
    static std::pair<Point, Point> getClosestPair(std::vector<Point> points) {
        int n = points.size();
        if (n < 2) return {Point(), Point()};
        
        std::sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
            return a.x < b.x;
        });
        
        double minDist = std::numeric_limits<double>::max();
        std::pair<Point, Point> closestPair;
        
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                double dist = points[i].distance(points[j]);
                if (dist < minDist) {
                    minDist = dist;
                    closestPair = {points[i], points[j]};
                }
            }
        }
        
        return closestPair;
    }
};
```

## Line Segment Intersection

### Sweep Line Algorithm

```cpp
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>

struct Event {
    enum Type { START, END };
    
    Type type;
    Point point;
    int segmentId;
    
    Event(Type t, const Point& p, int id) : type(t), point(p), segmentId(id) {}
    
    bool operator<(const Event& other) const {
        if (point.x != other.point.x) return point.x < other.point.x;
        if (type != other.type) return type < other.type;
        return point.y < other.point.y;
    }
};

class LineSegmentIntersection {
private:
    struct Segment {
        Point start, end;
        int id;
        
        Segment(const Point& s, const Point& e, int i) : start(s), end(e), id(i) {}
        
        double getYAtX(double x) const {
            if (std::abs(end.x - start.x) < 1e-9) return start.y;
            double t = (x - start.x) / (end.x - start.x);
            return start.y + t * (end.y - start.y);
        }
    };
    
    static bool segmentsIntersect(const Segment& s1, const Segment& s2) {
        Point a1 = s1.start, a2 = s1.end;
        Point b1 = s2.start, b2 = s2.end;
        
        double c1 = (a2 - a1).cross(b1 - a1);
        double c2 = (a2 - a1).cross(b2 - a1);
        double c3 = (b2 - b1).cross(a1 - b1);
        double c4 = (b2 - b1).cross(a2 - b1);
        
        if (c1 * c2 < 0 && c3 * c4 < 0) return true;
        
        if (c1 == 0 && onSegment(a1, a2, b1)) return true;
        if (c2 == 0 && onSegment(a1, a2, b2)) return true;
        if (c3 == 0 && onSegment(b1, b2, a1)) return true;
        if (c4 == 0 && onSegment(b1, b2, a2)) return true;
        
        return false;
    }
    
    static bool onSegment(const Point& a, const Point& b, const Point& c) {
        return c.x <= std::max(a.x, b.x) && c.x >= std::min(a.x, b.x) &&
               c.y <= std::max(a.y, b.y) && c.y >= std::min(a.y, b.y);
    }
    
public:
    static std::vector<std::pair<int, int>> findIntersections(
        const std::vector<std::pair<Point, Point>>& segments) {
        
        std::vector<Event> events;
        std::vector<Segment> segs;
        
        // Create events and segments
        for (size_t i = 0; i < segments.size(); ++i) {
            const auto& seg = segments[i];
            Point start = seg.first, end = seg.second;
            
            if (start.x > end.x) std::swap(start, end);
            
            segs.emplace_back(start, end, i);
            events.emplace_back(Event::START, start, i);
            events.emplace_back(Event::END, end, i);
        }
        
        // Sort events
        std::sort(events.begin(), events.end());
        
        // Sweep line algorithm
        std::set<int, std::function<bool(int, int)>> activeSegments(
            [&segs](int a, int b) {
                double x = std::max(segs[a].start.x, segs[b].start.x);
                return segs[a].getYAtX(x) < segs[b].getYAtX(x);
            });
        
        std::vector<std::pair<int, int>> intersections;
        
        for (const Event& event : events) {
            if (event.type == Event::START) {
                // Insert segment
                auto it = activeSegments.insert(event.segmentId).first;
                
                // Check for intersections with neighbors
                if (it != activeSegments.begin()) {
                    auto prev = std::prev(it);
                    if (segmentsIntersect(segs[*prev], segs[*it])) {
                        intersections.push_back({*prev, *it});
                    }
                }
                
                auto next = std::next(it);
                if (next != activeSegments.end()) {
                    if (segmentsIntersect(segs[*it], segs[*next])) {
                        intersections.push_back({*it, *next});
                    }
                }
            } else {
                // Remove segment
                auto it = activeSegments.find(event.segmentId);
                if (it != activeSegments.end()) {
                    auto prev = it, next = it;
                    if (it != activeSegments.begin()) {
                        --prev;
                        ++next;
                        if (next != activeSegments.end()) {
                            if (segmentsIntersect(segs[*prev], segs[*next])) {
                                intersections.push_back({*prev, *next});
                            }
                        }
                    }
                    activeSegments.erase(it);
                }
            }
        }
        
        return intersections;
    }
};
```

## Triangulation

### Delaunay Triangulation (Simplified)

```cpp
#include <vector>
#include <iostream>

struct Triangle {
    Point a, b, c;
    
    Triangle(const Point& p1, const Point& p2, const Point& p3) : a(p1), b(p2), c(p3) {}
    
    bool contains(const Point& p) const {
        double area = std::abs((b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y)) / 2.0;
        double area1 = std::abs((a.x - p.x) * (b.y - p.y) - (b.x - p.x) * (a.y - p.y)) / 2.0;
        double area2 = std::abs((b.x - p.x) * (c.y - p.y) - (c.x - p.x) * (b.y - p.y)) / 2.0;
        double area3 = std::abs((c.x - p.x) * (a.y - p.y) - (a.x - p.x) * (c.y - p.y)) / 2.0;
        
        return std::abs(area - (area1 + area2 + area3)) < 1e-9;
    }
    
    bool isDelaunay(const Point& p) const {
        // Check if point p is outside the circumcircle of this triangle
        double ax = a.x - p.x, ay = a.y - p.y;
        double bx = b.x - p.x, by = b.y - p.y;
        double cx = c.x - p.x, cy = c.y - p.y;
        
        double det = ax * (by * (cx * cx + cy * cy) - cy * (bx * bx + by * by)) -
                    ay * (bx * (cx * cx + cy * cy) - cx * (bx * bx + by * by)) +
                    (ax * ax + ay * ay) * (bx * cy - cx * by);
        
        return det > 0;
    }
};

class Triangulation {
public:
    static std::vector<Triangle> delaunayTriangulation(std::vector<Point> points) {
        int n = points.size();
        if (n < 3) return {};
        
        // Create super triangle containing all points
        double minX = points[0].x, maxX = points[0].x;
        double minY = points[0].y, maxY = points[0].y;
        
        for (const Point& p : points) {
            minX = std::min(minX, p.x);
            maxX = std::max(maxX, p.x);
            minY = std::min(minY, p.y);
            maxY = std::max(maxY, p.y);
        }
        
        double dx = maxX - minX;
        double dy = maxY - minY;
        double dmax = std::max(dx, dy);
        double midx = (minX + maxX) / 2;
        double midy = (minY + maxY) / 2;
        
        Point p1(midx - 20 * dmax, midy - dmax);
        Point p2(midx, midy + 20 * dmax);
        Point p3(midx + 20 * dmax, midy - dmax);
        
        std::vector<Triangle> triangles = {Triangle(p1, p2, p3)};
        
        // Add points one by one
        for (const Point& point : points) {
            std::vector<Triangle> newTriangles;
            
            for (const Triangle& tri : triangles) {
                if (tri.isDelaunay(point)) {
                    newTriangles.push_back(tri);
                } else {
                    // Split triangle into three new triangles
                    newTriangles.emplace_back(tri.a, tri.b, point);
                    newTriangles.emplace_back(tri.b, tri.c, point);
                    newTriangles.emplace_back(tri.c, tri.a, point);
                }
            }
            
            triangles = newTriangles;
        }
        
        // Remove triangles containing super triangle vertices
        std::vector<Triangle> result;
        for (const Triangle& tri : triangles) {
            if (!containsSuperTriangleVertex(tri, p1, p2, p3)) {
                result.push_back(tri);
            }
        }
        
        return result;
    }
    
private:
    static bool containsSuperTriangleVertex(const Triangle& tri, 
                                          const Point& p1, const Point& p2, const Point& p3) {
        return tri.contains(p1) || tri.contains(p2) || tri.contains(p3);
    }
};
```

## Summary

Geometric algorithms provide solutions for:
- **Basic operations**: Point/vector math, line intersections
- **Convex hull**: Graham scan, Jarvis march
- **Polygon operations**: Point containment, area calculation
- **Closest pair**: Divide and conquer approach
- **Line segment intersection**: Sweep line algorithm
- **Triangulation**: Delaunay triangulation

Key applications:
- **Computer graphics**: Rendering, collision detection
- **Computational geometry**: Algorithm design
- **Robotics**: Path planning, obstacle avoidance
- **Geographic information systems**: Spatial analysis
- **Computer vision**: Feature detection, object recognition

These algorithms form the foundation for solving complex geometric problems in various computational domains.
