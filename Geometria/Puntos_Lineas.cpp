#include <bits/stdc++.h>
using namespace std;

const double INF = 1e9;
const double EPS = 1e-9;
const double PI=acos(-1.0);

double DEG_to_RAD(double d) { return d*M_PI/180.0; }
double RAD_to_DEG(double r) { return r*180.0/M_PI; }

struct P {
  int x, y;                                      
  P() { x = y = 0; }                        
  P(int _x, int _y) : x(_x), y(_y) {}
  bool operator==(const P &p){return x==p.x && y==p.y;}  
  P operator+(const P &p)const{return P(x+p.x,y+p.y);}
  P operator-(const P &p)const{return P(x-p.x,y-p.y);}
  long long operator*(P p)const{return x*p.y-y*p.x;}
};

struct pt {// for 3D add z coordinate
  double x, y;                                   
  pt() { x = y = 0.0; }                       
  pt(double _x, double _y) : x(_x), y(_y) {}  

  bool operator==(pt p){return abs(x-p.x)<=EPS&&abs(y-p.y)<=EPS;}
  pt operator+(pt p){return pt(x+p.x,y+p.y);}
  pt operator-(pt p){return pt(x-p.x,y-p.y);}
  pt operator*(double t){return pt(x*t,y*t);}
	pt operator/(double t){return pt(x/t,y/t);}
  double operator*(pt p){return x*p.x+y*p.y;}
  // pt operator^(pt p){ //only for 3D
  //		return pt(y*p.z-z*p.y,z*p.x-x*p.z,x*p.y-y*p.x);}
  double operator%(pt p){return x*p.y-y*p.x;}
  
  // bool operator<(pt p)const{ // for convex hull
	// 	return x<p.x-EPS||(abs(x-p.x)<=EPS&&y<p.y-EPS);}
  bool operator < (pt other) const {          
    if (fabs(x-other.x) > EPS)                   // Util para ordenar
      return x < other.x;                        // Por coordenada X
    return y < other.y;                          // Si empatan por coordenada Y
  }

};

double dist(const pt &p1, const pt &p2) {                // Euclidean distance
  // hypot(dx, dy) returns sqrt(dx*dx + dy*dy)
  return hypot(p1.x-p2.x, p1.y-p2.y);            // return double
}

// Rotar p por theta grados en contra de las manecillas alrededor del origen (0, 0)
pt rotate(pt p, double theta) {
  double rad = DEG_to_RAD(theta);                // Convertir a radian
  return pt(p.x*cos(rad) - p.y*sin(rad),
               p.x*sin(rad) + p.y*cos(rad));
}

//Coeficientes ax + by + c = 0
//B=0 Linea vertical B=1 Linea No vertical
struct line { double a, b, c; };                 // most versatile

// Convierte 2 puntos en una linea pasada por referencia
void pointsToLine(pt p1, pt p2, line &l) {
  if (fabs(p1.x-p2.x) < EPS)                     // vertical line is fine
    l = {1.0, 0.0, -p1.x};                       // default values
  else {
    double a = -(double)(p1.y-p2.y) / (p1.x-p2.x);
    l = {a, 1.0, -(double)(a*p1.x) - p1.y};      // NOTE: b always 1.0
  }
}

// not needed since we will use the more robust form: ax + by + c = 0
struct line2 { double m, c; };                   // alternative way

int pointsToLine2(pt p1, pt p2, line2 &l) {
  if (p1.x == p2.x) {                            // vertical line
    l.m = INF;                                   // this is to denote a
    l.c = p1.x;                                  // line x = x_value
    return 0;                                    // differentiate result
  }
  else {
    l.m = (double)(p1.y-p2.y) / (p1.x-p2.x);
    l.c = p1.y - l.m*p1.x;
    return 1;                                    // standard y = mx + c
  }
}

bool areParallel(line l1, line l2) {             // check a & b
  return (fabs(l1.a-l2.a) < EPS) && (fabs(l1.b-l2.b) < EPS);
}

bool areSame(line l1, line l2) {                 // also check  c
  return areParallel(l1 ,l2) && (fabs(l1.c-l2.c) < EPS);
}

// returns true (+ intersection point p) if two lines are intersect
bool areIntersect(line l1, line l2, pt &p) {
  if (areParallel(l1, l2)) return false;         // no intersection
  // solve system of 2 linear algebraic equations with 2 unknowns
  p.x = (l2.b*l1.c - l1.b*l2.c) / (l2.a*l1.b - l1.a*l2.b);
  // special case: test for vertical line to avoid division by zero
  if (fabs(l1.b) > EPS) p.y = -(l1.a*p.x + l1.c);
  else                  p.y = -(l2.a*p.x + l2.c);
  return true;
}

struct vec { double x, y; // name: `vec' is different from STL vector
  vec(double _x, double _y) : x(_x), y(_y) {}
};
vec toVec(const pt &a, const pt &b) {      // convert 2 points
  return vec(b.x-a.x, b.y-a.y);                  // to vector a->b
}
vec scale(const vec &v, double s) {              // s = [<1..1..>1]
  return vec(v.x*s, v.y*s);                      // shorter/eq/longer
}                                                // return a new vec
pt translate(const pt &p, const vec &v) {  // translate p
  return pt(p.x+v.x, p.y+v.y);                // according to v
}                                                // return a new point

// convert point and gradient/slope to line
void pointSlopeToLine(pt p, double m, line &l) {
  l.a = -m;                                      // always -m
  l.b = 1;                                       // always 1
  l.c = -((l.a * p.x) + (l.b * p.y));            // compute this
}

void closestPoint(line l, pt p, pt &ans) {
  // this line is perpendicular to l and pass through p
  line perpendicular;                            
  if (fabs(l.b) < EPS) {                         // vertical line
    ans.x = -(l.c);
    ans.y = p.y;
    return;
  }
  if (fabs(l.a) < EPS) {                         // horizontal line
    ans.x = p.x;
    ans.y = -(l.c);
    return;
  }
  pointSlopeToLine(p, 1/l.a, perpendicular);     // normal line
  // intersect line l with this perpendicular line
  // the intersection point is the closest point
  areIntersect(l, perpendicular, ans);
}

// returns the reflection of point on a line
void reflectionPoint(line l, pt p, pt &ans) {
  pt b;
  closestPoint(l, p, b);                         // similar to distToLine
  vec v = toVec(p, b);                           // create a vector
  ans = translate(translate(p, v), v);           // translate p twice
}

// returns the dot product of two vectors a and b
double dot(vec a, vec b) { return (a.x*b.x + a.y*b.y); }

// returns the squared value of the normalized vector
double norm_sq(vec v) { return v.x*v.x + v.y*v.y; }

double angle(const pt &a, const pt &o, const pt &b) {
  vec oa = toVec(o, a), ob = toVec(o, b);        // a != o != b
  return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob)));
}                                                // angle aob in rad

// returns the distance from p to the line defined by
// two points a and b (a and b must be different)
// the closest point is stored in the 4th parameter (byref)
double distToLine(pt p, pt a, pt b, pt &c) {
  vec ap = toVec(a, p), ab = toVec(a, b);
  double u = dot(ap, ab) / norm_sq(ab);
  // formula: c = a + u*ab
  c = translate(a, scale(ab, u));                // translate a to c
  return dist(p, c);                             // Euclidean distance
}

// returns the distance from p to the line segment ab defined by
// two points a and b (technically, a has to be different than b)
// the closest point is stored in the 4th parameter (byref)
double distToLineSegment(pt p, pt a, pt b, pt &c) {
  vec ap = toVec(a, p), ab = toVec(a, b);
  double u = dot(ap, ab) / norm_sq(ab);
  if (u < 0.0) {                                 // closer to a
    c = pt(a.x, a.y);
    return dist(p, a);                           // dist p to a
  }
  if (u > 1.0) {                                 // closer to b
    c = pt(b.x, b.y);
    return dist(p, b);                           // dist p to b
  }
  return distToLine(p, a, b, c);                 // use distToLine
}

// Producto cruz de 2 vectores a y b of
double cross(vec a, vec b) { return a.x*b.y - a.y*b.x; }

//// another variant
// returns 'twice' the area of this triangle A-B-c
// int area2(point p, point q, point r) {
//   return p.x * q.y - p.y * q.x +
//          q.x * r.y - q.y * r.x +
//          r.x * p.y - r.y * p.x;
// }

// note: to accept collinear points, we have to change the `> 0'
// returns true if point r is on the left side of line pq
bool ccw(pt p, pt q, pt r) {
  return cross(toVec(p, q), toVec(p, r)) > -EPS;
}

// returns true if point r is on the same line as the line pq
bool collinear(pt p, pt q, pt r) {
  return fabs(cross(toVec(p, q), toVec(p, r))) < EPS;
}

int main() {
  vector<pt> P;
  P.emplace_back(2e-9, 0);                       // largest
  P.push_back({0, 2});                           // smallest
  P.push_back({1e-9, 1});                        // second smallest
  sort(P.begin(), P.end());
  for (auto &pt : P)                             // the result is
    printf("%.9lf, %.9lf\n", pt.x, pt.y);        // unexpected
  // change
  // const double EPS = 1e-9;
  // to
  // const double EPS = 1e-10;
  // to fix that issue, Rule of Thumb: check the required precision

  pt P1, P2, P3(0, 1); // note that both P1 and P2 are (0.00, 0.00)
  printf("%d\n", P1 == P2);                      // true
  printf("%d\n", P1 == P3);                      // false

  P.clear();
  P.push_back(pt(2, 2));
  P.push_back(pt(4, 3));
  P.push_back(pt(2, 4));
  P.push_back(pt(6, 6));
  P.push_back(pt(2, 6));
  P.push_back(pt(6, 5));

  // sorting points demo
  sort(P.begin(), P.end());
  for (int i = 0; i < (int)P.size(); i++)
    printf("(%.2lf, %.2lf)\n", P[i].x, P[i].y);

  // rearrange the points as shown in the diagram below
  P.clear();
  P.push_back(pt(2, 2));
  P.push_back(pt(4, 3));
  P.push_back(pt(2, 4));
  P.push_back(pt(6, 6));
  P.push_back(pt(2, 6));
  P.push_back(pt(6, 5));
  P.push_back(pt(8, 6));

  /*
  // the positions of these 7 points (0-based indexing)
  6   P4      P3  P6
  5           P5
  4   P2
  3       P1
  2   P0
  1
  0 1 2 3 4 5 6 7 8
  */

  double d = dist(P[0], P[5]);
  printf("Euclidean distance between P[0] and P[5] = %.2lf\n", d); // should be 5.000

  // line equations
  line l1, l2, l3, l4;
  pointsToLine(P[0], P[1], l1);
  printf("%.2lf * x + %.2lf * y + %.2lf = 0.00\n", l1.a, l1.b, l1.c); // should be -0.50 * x + 1.00 * y - 1.00 = 0.00

  pointsToLine(P[0], P[2], l2); // a vertical line, not a problem in "ax + by + c = 0" representation
  printf("%.2lf * x + %.2lf * y + %.2lf = 0.00\n", l2.a, l2.b, l2.c); // should be 1.00 * x + 0.00 * y - 2.00 = 0.00

  // parallel, same, and line intersection tests
  pointsToLine(P[2], P[3], l3);
  printf("l1 & l2 are parallel? %d\n", areParallel(l1, l2)); // no
  printf("l1 & l3 are parallel? %d\n", areParallel(l1, l3)); // yes, l1 (P[0]-P[1]) and l3 (P[2]-P[3]) are parallel

  pointsToLine(P[2], P[4], l4);
  printf("l1 & l2 are the same? %d\n", areSame(l1, l2)); // no
  printf("l2 & l4 are the same? %d\n", areSame(l2, l4)); // yes, l2 (P[0]-P[2]) and l4 (P[2]-P[4]) are the same line (note, they are two different line segments, but same line)
  
  pt p12;
  bool res = areIntersect(l1, l2, p12); // yes, l1 (P[0]-P[1]) and l2 (P[0]-P[2]) are intersect at (2.0, 2.0)
  printf("l1 & l2 are intersect? %d, at (%.2lf, %.2lf)\n", res, p12.x, p12.y);

  // other distances
  pt ans;
  d = distToLine(P[0], P[2], P[3], ans);
  printf("Closest point from P[0] to line         (P[2]-P[3]): (%.2lf, %.2lf), dist = %.2lf\n", ans.x, ans.y, d);
  closestPoint(l3, P[0], ans);
  printf("Closest point from P[0] to line V2      (P[2]-P[3]): (%.2lf, %.2lf), dist = %.2lf\n", ans.x, ans.y, dist(P[0], ans));

  d = distToLineSegment(P[0], P[2], P[3], ans);
  printf("Closest point from P[0] to line SEGMENT (P[2]-P[3]): (%.2lf, %.2lf), dist = %.2lf\n", ans.x, ans.y, d); // closer to A (or P[2]) = (2.00, 4.00)
  d = distToLineSegment(P[1], P[2], P[3], ans);
  printf("Closest point from P[1] to line SEGMENT (P[2]-P[3]): (%.2lf, %.2lf), dist = %.2lf\n", ans.x, ans.y, d); // closer to midway between AB = (3.20, 4.60)
  d = distToLineSegment(P[6], P[2], P[3], ans);
  printf("Closest point from P[6] to line SEGMENT (P[2]-P[3]): (%.2lf, %.2lf), dist = %.2lf\n", ans.x, ans.y, d); // closer to B (or P[3]) = (6.00, 6.00)

  reflectionPoint(l4, P[1], ans);
  printf("Reflection point from P[1] to line      (P[2]-P[4]): (%.2lf, %.2lf)\n", ans.x, ans.y); // should be (0.00, 3.00)

  printf("Angle P[0]-P[4]-P[3] = %.2lf\n", RAD_to_DEG(angle(P[0], P[4], P[3]))); // 90 degrees
  printf("Angle P[0]-P[2]-P[1] = %.2lf\n", RAD_to_DEG(angle(P[0], P[2], P[1]))); // 63.43 degrees
  printf("Angle P[4]-P[3]-P[6] = %.2lf\n", RAD_to_DEG(angle(P[4], P[3], P[6]))); // 180 degrees

  printf("P[0], P[2], P[3] form A left turn? %d\n", ccw(P[0], P[2], P[3])); // no
  printf("P[0], P[3], P[2] form A left turn? %d\n", ccw(P[0], P[3], P[2])); // yes

  printf("P[0], P[2], P[3] are collinear? %d\n", collinear(P[0], P[2], P[3])); // no
  printf("P[0], P[2], P[4] are collinear? %d\n", collinear(P[0], P[2], P[4])); // yes

  pt p(3, 7), q(11, 13), r(35, 30); // collinear if r(35, 31)
  printf("r is on the %s of line p-q (direction p->q)\n", ccw(p, q, r) ? "left" : "right"); // right

  /*
  // the positions of these 6 points
     E<--  4
           3       B D<--
           2   A C
           1
  -4-3-2-1 0 1 2 3 4 5 6
          -1
          -2
   F<--   -3
  */

  // translation
  pt A(2.0, 2.0);
  pt B(4.0, 3.0);
  vec v = toVec(A, B); // imagine there is an arrow from A to B (see the diagram above)
  pt C(3.0, 2.0);
  pt D = translate(C, v); // D will be located in coordinate (3.0 + 2.0, 2.0 + 1.0) = (5.0, 3.0)
  printf("D = (%.2lf, %.2lf)\n", D.x, D.y);
  pt E = translate(C, scale(v, 0.5)); // E will be located in coordinate (3.0 + 1/2 * 2.0, 2.0 + 1/2 * 1.0) = (4.0, 2.5)
  printf("E = (%.2lf, %.2lf)\n", E.x, E.y);

  // rotation
  printf("B = (%.2lf, %.2lf)\n", B.x, B.y); // B = (4.0, 3.0)
  pt F = rotate(B, 90); // rotate B by 90 degrees COUNTER clockwise, F = (-3.0, 4.0)
  printf("F = (%.2lf, %.2lf)\n", F.x, F.y);
  pt G = rotate(B, 180); // rotate B by 180 degrees COUNTER clockwise, G = (-4.0, -3.0)
  printf("G = (%.2lf, %.2lf)\n", G.x, G.y);

  return 0;
}