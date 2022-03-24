#include <iostream>
#include <list>
#include <queue>

#define INF 2147483647

int d_x[] = {0, 1, -1};
int d_y[] = {3, 2, 2};

bool bfs(std::list<int> *, int, int *, int *, int &, int *);
bool dfs(std::list<int> *, int, int *, int *, int &, int *, int);

int main()
{
    int n, m;

    scanf("%d %d", &n, &m);

    char *map = new char[n * n];
    int *id_map = new int[n * n];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            id_map[i * n + j] = -1;
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (i % 2 == 0)
        {
            for (int j = 0; j < n; j++)
            {
                if (j % 2 == 0)
                    map[i * n + j] = '1';
                else
                    map[i * n + j] = '0';
            }
        }
        else
        {
            for (int j = 0; j < n; j++)
            {
                if (j % 2 == 0)
                    map[i * n + j] = '0';
                else
                    map[i * n + j] = '1';
            }
        }
    }

    for (int i = 0; i < m; i++)
    {
        int col, row;
        scanf("%d %d", &col, &row);
        map[row * n + col] = 'x';
    }

    int n_black = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (map[i * n + j] == '1')
            {
                for (int k = 0; k < 3; k++)
                {
                    if (map[(i + d_y[k]) * n + (j + d_x[k])] == '0' && (i + d_y[k]) <= (n - 1) && (j + d_x[k]) >= 0 && (j + d_x[k]) <= (n - 1))
                    {
                        n_black++;
                        break;
                    }
                }
            }
        }
    }

    std::list<int> *graph = new std::list<int>[n_black];

    int id_black = 0, id_white = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (map[i * n + j] == '1')
            {
                bool shoot_someone = false;
                for (int k = 0; k < 3; k++)
                {
                    if (map[(i + d_y[k]) * n + (j + d_x[k])] == '0' && (i + d_y[k]) <= (n - 1) && (j + d_x[k]) >= 0 && (j + d_x[k]) <= (n - 1))
                    {
                        shoot_someone = true;
                        if (id_map[(i + d_y[k]) * n + (j + d_x[k])] == -1)
                        {
                            graph[id_black].push_back(id_white);
                            id_map[(i + d_y[k]) * n + (j + d_x[k])] = id_white;
                            id_white++;
                        }
                        else
                        {
                            graph[id_black].push_back(id_map[(i + d_y[k]) * n + (j + d_x[k])]);
                        }
                    }
                }
                if (shoot_someone)
                {
                    id_map[i * n + j] = id_black;
                    id_black++;
                }
            }
        }
    }

    int *pair_black = new int[id_black]; // vertex index -> pair in white vertexes set
    int *pair_white = new int[id_white]; // vertex index -> pair in black vertexes set

    int *distances = new int[id_black];

    for (int i = 0; i < id_black; i++)
        pair_black[i] = -1; // no pair at the begining
    for (int i = 0; i < id_white; i++)
        pair_white[i] = -1; // no pair at the begining

    int height = INF;

    int m_size = 0;

    while (bfs(graph, id_black, pair_black, pair_white, height, distances))
    {
        for (int i = 0; i < id_black; i++)
        {
            if (pair_black[i] == -1)
            {
                if (dfs(graph, id_black, pair_black, pair_white, height, distances, i))
                    m_size++;
            }
        }
    }

    std::cout << n * n - m_size << '\n';

    delete[] map;
    delete[] id_map;
    delete[] graph;
    delete[] pair_black;
    delete[] pair_white;
    delete[] distances;

    return 0;
}

bool bfs(std::list<int> *graph, int size_black, int *pair_black, int *pair_white, int &height, int *distances)
{
    std::queue<int> q;

    for (int i = 0; i < size_black; i++)
    {
        if (pair_black[i] == -1) // if free -> add to queue
        {
            distances[i] = 0;
            q.push(i);
        }
        else
        {
            distances[i] = INF;
        }
    }

    height = INF;

    while (!q.empty())
    {
        int vertex = q.front();
        q.pop();

        if (vertex != -1)
        {
            if (distances[vertex] < height)
            {
                for (int v : graph[vertex])
                {
                    if (pair_white[v] == -1 && height == INF)
                    {
                        height = distances[vertex] + 1;
                        q.push(pair_white[v]);
                    }
                    else if (distances[pair_white[v]] == height)
                    {
                        distances[pair_white[v]] = distances[vertex] + 1;
                        q.push(pair_white[v]);
                    }
                }
            }
        }
    }

    return height != INF;
}

bool dfs(std::list<int> *graph, int size_black, int *pair_black, int *pair_white, int &height, int *distances, int start_vertex)
{
    if (start_vertex != -1)
    {
        for (int v : graph[start_vertex])
        {
            if (distances[pair_white[v]] == distances[start_vertex] + 1)
            {
                if (dfs(graph, size_black, pair_black, pair_white, height, distances, pair_white[v]))
                {
                    pair_white[v] = start_vertex;
                    pair_black[start_vertex] = v;
                    return true;
                }
            }
            else if (height == distances[start_vertex] + 1 && pair_white[v] == -1)
            {
                if (dfs(graph, size_black, pair_black, pair_white, height, distances, pair_white[v]))
                {
                    pair_white[v] = start_vertex;
                    pair_black[start_vertex] = v;
                    return true;
                }
            }
        }
        distances[start_vertex] = INF;
        return false;
    }
    return true;
}