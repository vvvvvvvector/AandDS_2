#include <iostream>
#include <vector>

const int dict_size = 101;
const int prime_num = 100019;

int pow(int, int);
int find_index(int, int, int);

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int text_size;
    std::cin >> text_size;

    int *text = new int[text_size];
    for (int i = 0; i < text_size; i++)
        std::cin >> text[i];

    int pattern_size;
    std::cin >> pattern_size;

    int *pattern = new int[pattern_size];
    for (int i = 0; i < pattern_size; i++)
        std::cin >> pattern[i];

    int H = pow(dict_size, pattern_size - 1); // helps to calculate window_hash(i) +

    int pattern_hash = 0;
    for (int i = 0; i < pattern_size; i++)
        pattern_hash = (dict_size * pattern_hash + pattern[i]) % prime_num; // +

    int window_hash = 0; // init for first window
    for (int i = 0; i < pattern_size; i++)
        window_hash = (dict_size * window_hash + text[i]) % prime_num; // +

    std::vector<int> first_two_indexes;

    for (int i = 0; i <= text_size - pattern_size && first_two_indexes.size() != 2; i++)
    {
        if (window_hash == pattern_hash)
        {
            bool are_equal = true;

            for (int j = 0; j < pattern_size && are_equal; j++)
            {
                if (text[i + j] != pattern[j])
                    are_equal = false;
            }

            if (are_equal)
                first_two_indexes.push_back(i);
        }

        window_hash = (dict_size * (window_hash - text[i] * H) + text[i + pattern_size]) % prime_num;

        if (window_hash < 0)
            window_hash += prime_num;
    }

    std::cout << find_index(first_two_indexes.at(0), first_two_indexes.at(1), text_size) - text_size << '\n';

    delete text;
    delete pattern;

    return 0;
}

int pow(int number, int power) // +
{
    int pow_result = 1;

    for (int i = 0; i < power; i++)
    {
        pow_result *= number;
        pow_result %= prime_num;
    }

    return pow_result;
}

int find_index(int first_idx, int second_idx, int text_size) // +
{
    int next_idx = first_idx + second_idx;

    while (text_size > next_idx)
    {
        int temp = next_idx;

        next_idx += second_idx;

        second_idx = temp;
    }

    return next_idx;
}