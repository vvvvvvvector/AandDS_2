#include <iostream>
#include <cmath>
#include <string>

#define T 18
#define M (2 * T - 1)

struct Info
{
    std::string key;
    std::string description;
};

struct BTreeNode
{
    int n_keys;

    BTreeNode *parent;
    bool is_leaf;

    Info *keys;
    BTreeNode **pointers;

    BTreeNode()
    {
        keys = new Info[M];
        pointers = new BTreeNode *[M + 1];
    }
};

BTreeNode *search_key_and_update(BTreeNode *, std::string);
std::string search_description(BTreeNode *, std::string);
void push(BTreeNode **, Info);
void split(BTreeNode **);

void delete_btree(BTreeNode **);

void insert_key_by_index(BTreeNode *treeNode, int idx, Info el) // +
{
    for (int i = treeNode->n_keys - 1; i >= idx; i--)
        treeNode->keys[i + 1] = treeNode->keys[i];

    treeNode->keys[idx] = el;

    treeNode->n_keys++;
}

void delete_key_by_index(BTreeNode *treeNode, int idx) // +
{
    for (int i = idx; i < treeNode->n_keys - 1; i++)
        treeNode->keys[i] = treeNode->keys[i + 1];

    treeNode->n_keys--;
}

void insert_ptr_by_index(BTreeNode *treeNode, int idx, BTreeNode *ptr) // +
{
    for (int i = treeNode->n_keys; i >= idx; i--)
        treeNode->pointers[i] = treeNode->pointers[i - 1];

    treeNode->pointers[idx] = ptr;
}

void delete_ptr_by_index(BTreeNode *treeNode, int idx)
{
    for (int i = idx; i < treeNode->n_keys; i++)
        treeNode->pointers[i] = treeNode->pointers[i + 1];
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    BTreeNode *root = nullptr;

    int n;
    std::cin >> n;

    std::cin.ignore();

    for (int i = 0; i < n; i++)
    {
        std::string input;
        std::getline(std::cin, input);

        if (input.find(':') == std::string::npos)
        {
            if (root != nullptr)
            {
                std::string search_result = search_description(root, input);

                if (search_result == "")
                    std::cout << "BRAK\n";
                else
                    std::cout << search_result << '\n';
            }
            else
                std::cout << "BRAK\n";
        }
        else
        {
            std::size_t del_pos = input.find(':');

            std::string key = input.substr(0, del_pos);
            std::string value = input.substr(del_pos + 2);

            BTreeNode *node = search_key_and_update(root, key);

            if (node != nullptr)
            {
                for (int i = 0; i < node->n_keys; i++)
                {
                    if (node->keys[i].key == key)
                        node->keys[i].description = value;
                }
            }
            else
                push(&root, {key, value});
        }
    }

    delete_btree(&root);

    return 0;
}

void push(BTreeNode **root, Info info)
{
    if (*root == nullptr) // +
    {
        BTreeNode *node = new BTreeNode();

        node->parent = nullptr;
        node->is_leaf = true;
        node->n_keys = 0;

        insert_key_by_index(node, 0, info);
        insert_ptr_by_index(node, 0, nullptr);
        insert_ptr_by_index(node, 1, nullptr);

        *root = node;
    }
    else
    {
        if ((*root)->is_leaf)
        {
            int index = 0;

            while (index < (*root)->n_keys && (*root)->keys[index].key < info.key)
                index++;

            insert_key_by_index((*root), index, info);

            if (index == 0)
                insert_ptr_by_index((*root), 0, nullptr);
            else
                insert_ptr_by_index((*root), index + 1, nullptr);

            if ((*root)->n_keys == M)
                split(root);
        }
        else // +
        {
            int index = 0;

            while (index < (*root)->n_keys && (*root)->keys[index].key < info.key)
                index++;

            push(&(*root)->pointers[index], info);
        }
    }
}

void split(BTreeNode **node)
{
    if ((*node)->parent == nullptr)
    {
        BTreeNode *right = new BTreeNode();
        right->is_leaf = (*node)->is_leaf;
        right->parent = *node;
        right->n_keys = 0;

        for (int i = std::floor(M / 2.0) + 1, j = 0; i < M; i++, j++) // filling empty right node +
            insert_key_by_index(right, j, (*node)->keys[i]);

        for (int i = std::floor(M / 2.0) + 1, j = 0; i < M + 1; i++, j++) // +
            insert_ptr_by_index(right, j, (*node)->pointers[i]);

        BTreeNode *left = new BTreeNode();
        left->is_leaf = (*node)->is_leaf;
        left->parent = *node;
        left->n_keys = 0;

        for (int i = 0; i < std::floor(M / 2.0); i++) // filling empty left node +
            insert_key_by_index(left, i, (*node)->keys[i]);

        for (int i = 0; i < std::floor(M / 2.0) + 1; i++) // +
            insert_ptr_by_index(left, i, (*node)->pointers[i]);

        int n_left_elements = std::floor(M / 2.0);            // +
        int n_right_elements = M - (std::floor(M / 2.0) + 1); // +

        int n_ptr = M + 1;
        while (n_ptr != 0)
        {
            delete_ptr_by_index((*node), 0);
            n_ptr--;
        }

        for (int i = 0; i < M + 1; i++)
            insert_ptr_by_index((*node), i, nullptr);

        for (int i = 0; i < n_left_elements; i++) // delete top node left elements +
            delete_key_by_index((*node), 0);

        for (int i = 0; i < n_right_elements; i++) // delete top node right elements +
            delete_key_by_index((*node), 1);

        (*node)->is_leaf = false;
        insert_ptr_by_index((*node), 0, left);
        insert_ptr_by_index((*node), 1, right);

        for (int i = 0; i < right->n_keys + 1; i++)
        {
            if (right->pointers[i] != nullptr)
                right->pointers[i]->parent = right;
        }

        for (int i = 0; i < left->n_keys + 1; i++)
        {
            if (left->pointers[i] != nullptr)
                left->pointers[i]->parent = left;
        }
    }
    else
    {
        int middle_index = std::floor(M / 2.0);

        BTreeNode *right = new BTreeNode();
        right->is_leaf = (*node)->is_leaf;
        right->parent = (*node)->parent;
        right->n_keys = 0;

        for (int i = middle_index + 1, j = 0; i < M; i++, j++) // filling empty right node
            insert_key_by_index(right, j, (*node)->keys[i]);

        for (int i = middle_index + 1, j = 0; i < M + 1; i++, j++)
            insert_ptr_by_index(right, j, (*node)->pointers[i]);

        int index = 0;

        while (index < (*node)->parent->n_keys && (*node)->parent->keys[index].key < (*node)->keys[middle_index].key)
            index++;

        insert_key_by_index((*node)->parent, index, (*node)->keys[middle_index]);

        insert_ptr_by_index((*node)->parent, index + 1, right);

        int n_right_elements = M - middle_index;

        for (int i = 0, j = (*node)->n_keys; i < n_right_elements; i++, j--)
            delete_ptr_by_index((*node), j);

        for (int i = middle_index + 1; i < M + 1; i++)
            insert_ptr_by_index((*node), i, nullptr);

        for (int i = 0, j = (*node)->n_keys - 1; i < n_right_elements; i++, j--)
            delete_key_by_index((*node), j);

        for (int i = 0; i < right->n_keys + 1; i++)
        {
            if (right->pointers[i] != nullptr)
                right->pointers[i]->parent = right;
        }

        if ((*node)->parent->n_keys == M)
            split(&(*node)->parent);
    }
}

BTreeNode *search_key_and_update(BTreeNode *root, std::string key)
{
    if (root != nullptr)
    {
        int index = 0;

        while (index < root->n_keys && root->keys[index].key < key)
            index++;

        if (root->keys[index].key == key)
            return root;

        if (root->is_leaf)
            return nullptr;

        return search_key_and_update(root->pointers[index], key);
    }

    return nullptr;
}

std::string search_description(BTreeNode *root, std::string key) // +
{
    int index = 0;

    while (index < root->n_keys && root->keys[index].key < key)
        index++;

    if (root->keys[index].key == key)
        return root->keys[index].description;

    if (root->is_leaf)
        return "";

    return search_description(root->pointers[index], key);
}

void delete_btree(BTreeNode **root) // +
{
    if ((*root) == nullptr)
        return;

    for (int i = 0; i < (*root)->n_keys + 1; i++)
    {
        if ((*root)->pointers[i] != nullptr)
            delete_btree(&(*root)->pointers[i]);
    }

    delete *root;
    *root = nullptr;
}