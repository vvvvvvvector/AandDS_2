#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <cmath>

struct Vertex
{
    int id;
    double cost;
};

class Compare
{
public:
    bool operator()(Vertex const &v1, Vertex const &v2)
    {
        return v1.cost < v2.cost;
    }
};

void algorithm(int, double, std::list<Vertex> *, double *, int, bool *);

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int X;
    std::cin >> X;

    std::vector<int> bytecoin_idxs;

    bool *is_visited = new bool[X]{0};

    for (int i = 0; i < X; i++)
    {
        bool is_bytecoin;
        std::cin >> is_bytecoin;
        if (is_bytecoin)
            bytecoin_idxs.push_back(i);
    }

    int N;
    std::cin >> N;

    std::list<Vertex> *green_graph = new std::list<Vertex>[X];
    std::list<Vertex> *red_graph = new std::list<Vertex>[X];

    int A, B;
    double A_B_cost, B_A_cost;

    for (int i = 0; i < N; i++)
    {
        std::cin >> A >> B >> A_B_cost >> B_A_cost;

        green_graph[A].push_back({B, 1.0 - A_B_cost});
        green_graph[B].push_back({A, 1.0 - A_B_cost});

        red_graph[A].push_back({B, 1.0 - B_A_cost});
        red_graph[B].push_back({A, 1.0 - B_A_cost});
    }

    int start_vertex;
    std::cin >> start_vertex;

    double *dist_green = new double[X]{0.0};

    algorithm(start_vertex, 1.0, green_graph, dist_green, X, is_visited);

    for (int i = 0; i < X; i++)
        is_visited[i] = 0;

    double *dist_red = new double[X]{0.0};

    double *bytecoin_dist = new double[bytecoin_idxs.size()]{0.0};

    double max = bytecoin_dist[0];

    for (int i = 0; i < bytecoin_idxs.size(); i++)
    {
        algorithm(bytecoin_idxs[i], dist_green[bytecoin_idxs[i]], red_graph, dist_red, X, is_visited);

        if (dist_red[start_vertex] > max)
            max = dist_red[start_vertex];

        for (int i = 0; i < X; i++)
        {
            is_visited[i] = 0;
            dist_red[i] = 0.0;
        }
    }

    max *= 1.2 * 100000.0;

    std::cout << (int)(std::round(max * 10.0) / 10.0) << '\n'; // ???

    delete[] green_graph;
    delete[] red_graph;
    delete[] dist_green;
    delete[] dist_red;
    delete[] is_visited;
    delete[] bytecoin_dist;

    return 0;
}

void algorithm(int start_vertex, double start_cost, std::list<Vertex> *graph, double *dist, int X, bool *is_visited)
{
    std::priority_queue<Vertex, std::vector<Vertex>, Compare> pq;
    pq.push({start_vertex, start_cost});
    dist[start_vertex] = start_cost;

    while (!pq.empty())
    {
        Vertex vertex = pq.top();
        pq.pop();

        if (!is_visited[vertex.id])
        {
            is_visited[vertex.id] = 1;
            for (auto v : graph[vertex.id])
            {
                if (dist[vertex.id] * v.cost > dist[v.id])
                {
                    dist[v.id] = dist[vertex.id] * v.cost;
                    pq.push(v);
                }
            }
        }
    }
}