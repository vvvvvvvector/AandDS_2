#include <iostream>
#include <queue>
#include <ctime>
#include <cstring>
#include <cmath>

struct Artist
{
    int priority;

    double rating;
    char name[26]{'\0'};
};

class Compare
{
public:
    bool operator()(Artist const &a1, Artist const &a2)
    {
        return a1.rating < a2.rating || (a1.rating == a2.rating && a1.priority < a2.priority);
    }
};

struct Node
{
    int cost;
    std::priority_queue<Artist, std::vector<Artist>, Compare> artists;

    Node *parent;
    Node *left_bro;
    Node *right_bro;
};

Node *search(Node *, int);
void push(Node **, int, Artist);
void pop(Node **, Node **);

Node *predecessor(Node *);
Node *succesor(Node *);

void delete_tree(Node **);

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    srand(time(nullptr));

    Node *root = nullptr;

    int n;
    std::cin >> n;

    for (int i = 0, priority = 0; i < n; i++)
    {
        char operation;
        std::cin >> operation;

        if (operation == 'A')
        {
            double x;
            int y, cost;
            char name[26]{'\0'};

            std::cin >> x >> y >> cost >> name;

            Artist artist;
            artist.priority = priority;
            artist.rating = x / 5.0 * std::floor(y / 1000.0);
            strcpy(artist.name, name);

            priority++;

            if (root == nullptr)
            {
                Node *node = new Node;

                node->cost = cost;
                node->artists.push(artist);

                node->parent = nullptr;
                node->left_bro = nullptr;
                node->right_bro = nullptr;

                root = node;
            }
            else
            {
                Node *temp = root;
                push(&temp, cost, artist);
            }
        }
        else
        {
            int cost;
            double rating;

            std::cin >> cost >> rating;

            Node *node = search(root, cost);

            if (node == nullptr)
            {
                std::cout << "-\n";
            }
            else
            {
                if (node->artists.top().rating >= rating)
                {
                    std::cout << node->artists.top().name << '\n';
                    node->artists.pop();
                    if (node->artists.empty())
                    {
                        pop(&root, &node);
                    }
                }
                else
                {
                    std::cout << "-\n";
                }
            }
        }
    }

    delete_tree(&root);

    return 0;
}

Node *search(Node *root, int cost)
{
    if (root != nullptr)
    {
        if (root->cost == cost)
            return root;

        if (root->cost < cost)
            return search(root->right_bro, cost);
        else
            return search(root->left_bro, cost);
    }
    else
    {
        return nullptr;
    }
}

void push(Node **root, int cost, Artist artist)
{
    while (((*root)->cost < cost && (*root)->right_bro != nullptr) || ((*root)->cost > cost && (*root)->left_bro != nullptr))
    {
        if ((*root)->cost < cost)
            *root = (*root)->right_bro;
        else
            *root = (*root)->left_bro;
    }

    if ((*root)->cost == cost)
    {
        (*root)->artists.push(artist);
    }
    else if ((*root)->cost < cost)
    {
        Node *node = new Node;

        node->cost = cost;
        node->artists.push(artist);

        node->parent = *root;
        node->left_bro = nullptr;
        node->right_bro = nullptr;

        (*root)->right_bro = node;
    }
    else
    {
        Node *node = new Node;

        node->cost = cost;
        node->artists.push(artist);

        node->parent = *root;
        node->left_bro = nullptr;
        node->right_bro = nullptr;

        (*root)->left_bro = node;
    }
}

void delete_tree(Node **root)
{
    if (*root == nullptr)
        return;

    delete_tree(&(*root)->left_bro);
    delete_tree(&(*root)->right_bro);

    delete *root;
    *root = nullptr;
}

Node *predecessor(Node *start)
{
    while (start->right_bro != nullptr)
    {
        start = start->right_bro;
    }
    return start;
}

Node *succesor(Node *start)
{
    while (start->left_bro != nullptr)
    {
        start = start->left_bro;
    }
    return start;
}

void pop(Node **root, Node **node)
{
    if ((*node)->left_bro == nullptr && (*node)->right_bro == nullptr) // no bros
    {
        if ((*node)->parent != nullptr)
        {
            if ((*node)->parent->cost > (*node)->cost) // delete left bro
            {
                (*node)->parent->left_bro = nullptr;

                delete *node;
                *node = nullptr;
            }
            else // delete right bro
            {
                (*node)->parent->right_bro = nullptr;

                delete *node;
                *node = nullptr;
            }
        }
        else // delete root
        {
            delete *node;
            *root = *node = nullptr;
        }
    }
    else if ((*node)->right_bro == nullptr && (*node)->left_bro != nullptr) // 1 bro left
    {
        if ((*node)->parent != nullptr)
        {
            (*node)->left_bro->parent = (*node)->parent;

            if ((*node)->parent->cost > (*node)->cost)
                (*node)->parent->left_bro = (*node)->left_bro;
            else
                (*node)->parent->right_bro = (*node)->left_bro;

            delete *node;
            *node = nullptr;
        }
        else // root has 1 left bro
        {
            Node *temp = (*node)->left_bro;
            (*node)->left_bro->parent = nullptr;
            delete *node;
            *node = nullptr;
            *root = temp;
        }
    }
    else if ((*node)->right_bro != nullptr && (*node)->left_bro == nullptr) // 1 bro right
    {
        if ((*node)->parent != nullptr)
        {
            (*node)->right_bro->parent = (*node)->parent;

            if ((*node)->parent->cost > (*node)->cost)
                (*node)->parent->left_bro = (*node)->right_bro;
            else
                (*node)->parent->right_bro = (*node)->right_bro;

            delete *node;
            *node = nullptr;
        }
        else // root has 1 right bro
        {
            Node *temp = (*node)->right_bro;
            (*node)->right_bro->parent = nullptr;
            delete *node;
            *node = nullptr;
            *root = temp;
        }
    }
    else if ((*node)->right_bro != nullptr && (*node)->left_bro != nullptr)
    {
        int num = rand() % 2;
        if (num == 0)
        {
            Node *succ = succesor((*node)->right_bro);

            int cost = succ->cost;
            std::priority_queue<Artist, std::vector<Artist>, Compare> artists = succ->artists;

            pop(root, &succ);

            (*node)->cost = cost;
            (*node)->artists = artists;
        }
        else if (num == 1)
        {
            Node *predec = predecessor((*node)->left_bro);

            int cost = predec->cost;
            std::priority_queue<Artist, std::vector<Artist>, Compare> artists = predec->artists;

            pop(root, &predec);

            (*node)->cost = cost;
            (*node)->artists = artists;
        }
    }
}