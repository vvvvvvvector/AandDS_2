#include <cstdio>
#include <cmath>
#include <algorithm>
#include <stack>
#include <list>

struct Point
{
    double x, y; // x = fi, y = r
};

struct
{
    bool operator()(Point const &p1, Point const &p2)
    {
        return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
    }
} compare;

double calculate_angle(Point, Point);
double calculate_distance(Point, Point);
double calculate_determinant(Point, Point, Point);

int remove_if_equal_angles(Point *, int);

std::stack<Point> find_points(Point *, int n);
double calculate_area(std::stack<Point>);

int main()
{
    int n;
    scanf("%d", &n);

    double x, y;
    scanf("%lf %lf", &x, &y);

    Point start_point = {x, y};

    n--;

    Point *points = new Point[n];

    for (int i = 0; i < n; i++)
    {
        scanf("%lf %lf", &x, &y);

        if (y < start_point.y)
        {
            points[i] = start_point;
            start_point = {x, y};
        }
        else if (y == start_point.y)
        {
            if (x < start_point.x)
            {
                points[i] = start_point;
                start_point = {x, y};
            }
            else
                points[i] = {x, y};
        }
        else
            points[i] = {x, y};
    }

    for (int i = 0; i < n; i++)
    {
        Point point = {points[i].x, points[i].y};

        points[i].x = calculate_angle(point, start_point);
        points[i].y = calculate_distance(point, start_point);
    }

    std::sort(points, points + n, compare);

    n = remove_if_equal_angles(points, n);

    double area = calculate_area(find_points(points, n));

    printf("%.3lf", area);

    delete[] points;

    return 0;
}

double calculate_angle(Point point, Point start_point)
{
    return std::atan2(point.y - start_point.y, point.x - start_point.x);
}

double calculate_distance(Point point, Point start_point)
{
    return std::sqrt(std::pow(point.y - start_point.y, 2) + std::pow(point.x - start_point.x, 2));
}

double calculate_determinant(Point p1, Point p2, Point p3)
{
    double p1_x = p1.y * std::cos(p1.x);
    double p1_y = p1.y * std::sin(p1.x);

    double p2_x = p2.y * std::cos(p2.x);
    double p2_y = p2.y * std::sin(p2.x);

    double p3_x = p3.y * std::cos(p3.x);
    double p3_y = p3.y * std::sin(p3.x);

    return p1_x * p2_y - p1_x * p3_y - p2_x * p1_y + p2_x * p3_y + p3_x * p1_y - p3_x * p2_y;
}

int remove_if_equal_angles(Point *points, int size)
{
    int new_size = 0;

    for (int i = 0; i < size - 1; i++)
    {
        if (points[i].x != points[i + 1].x)
            points[new_size++] = points[i];
    }

    points[new_size++] = points[size - 1];

    return new_size;
}

std::stack<Point> find_points(Point *points, int n)
{
    std::stack<Point> stack;

    stack.push({0, 0});
    stack.push({points[0]});
    stack.push({points[1]});

    std::list<Point> list;
    for (int i = 2; i < n; i++)
        list.push_back(points[i]);

    while (!list.empty())
    {
        Point first = stack.top();
        stack.pop();
        Point second = stack.top();
        stack.pop();

        double value = calculate_determinant(second, first, list.front());

        if (value <= 0.0)
        {
            stack.push(second);
        }
        else
        {
            stack.push(second);
            stack.push(first);
            stack.push(list.front());
            list.pop_front();
        }
    }

    return stack;
}

double calculate_area(std::stack<Point> points)
{
    double area = 0.0;

    while (points.size() != 2)
    {
        Point p1 = points.top();
        points.pop();
        Point p2 = points.top();

        double p1_x = p1.y * std::cos(p1.x);
        double p1_y = p1.y * std::sin(p1.x);

        double p2_x = p2.y * std::cos(p2.x);
        double p2_y = p2.y * std::sin(p2.x);

        double c = std::sqrt(std::pow(p2_y - p1_y, 2) + std::pow(p2_x - p1_x, 2));
        double a = p1.y;
        double b = p2.y;

        double s = (a + b + c) / 2.0;

        double triangle_area = std::sqrt(s * (s - a) * (s - b) * (s - c));

        area += triangle_area;
    }

    return area;
}