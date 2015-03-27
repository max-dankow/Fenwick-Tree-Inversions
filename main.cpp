#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

const int TEST_NUMBER = 200;

class My_Fenwick_Tree
{
public:
    explicit My_Fenwick_Tree(const size_t data_size);
    void update(const size_t start, const long long delta);
    size_t sum(const std::ptrdiff_t start) const;
    size_t sum(const std::ptrdiff_t first, const std::ptrdiff_t second) const;
private:
    size_t f_prev(const size_t number) const;
    size_t f_next(const size_t number) const;
    std::vector<long long> tree;
};

size_t My_Fenwick_Tree::f_prev(size_t number) const
{
    return number & (number + 1);
}

size_t My_Fenwick_Tree::f_next(const size_t number) const
{
    return number | (number + 1);
}

void My_Fenwick_Tree::update(const size_t start, const long long delta)
{
    for (size_t x = start; x < tree.size(); x = f_next(x))
        tree[x] += delta;
}

My_Fenwick_Tree::My_Fenwick_Tree(const size_t data_size)
{
    tree.assign(data_size, 0);
}

size_t My_Fenwick_Tree::sum(const std::ptrdiff_t start) const
{
    size_t result = 0;

    for (std::ptrdiff_t x = start; x >= 0; x = std::ptrdiff_t (f_prev(size_t (x))) - 1)
        result += tree[x];

    return result;
}

size_t My_Fenwick_Tree::sum(const std::ptrdiff_t first, const std::ptrdiff_t second) const
{
    return sum (second) - sum (first - 1);
}

int get_inversion_count(const std::vector<int> &data)
{
    int count = 0;

    My_Fenwick_Tree fenwick(data.size());

    for (size_t i = 0; i < data.size(); ++i)
    {
        count += fenwick.sum(data[i] + 1, data.size() - 1);
        fenwick.update(data[i], 1);
    }

    return count;
}

int simple_solition(const std::vector<int> &data)
{
    int inversion_count = 0;

    for (int i = 0; i < data.size(); ++i)
    {
        for (int j = i + 1; j < data.size(); ++j)
        {
            if (data[i] > data[j])
                ++inversion_count;
        }
    }

    return inversion_count;
}

std::default_random_engine generator;

std::vector<int> generate_permutation(size_t size)
{
    std::vector<int> permutation;

    for (size_t i = 0; i < size; ++i)
        permutation.push_back(i);

    for (size_t i = 0; i < size; ++i)
    {
        std::uniform_int_distribution<size_t> random_index(0, size - 1);
        size_t j = random_index(generator);
        std::swap(permutation[i], permutation[j]);
    }

    return permutation;
}

void test_solution()
{
    for (int i = 0; i < TEST_NUMBER; ++i)
    {
        std::uniform_int_distribution<size_t> random_size(0, 1000);
        std::vector<int> test_data = generate_permutation(random_size(generator));

        int simple = simple_solition(test_data);
        int fenwick = get_inversion_count(test_data);

        std::cout << simple << ' ' << fenwick;

        if (simple == fenwick)
        {
            std::cout << " OK\n";
        }
        else
        {
            std::cout << "\nFAILED.\n";
            exit(-1);
        }
    }

    std::cout << "\nTests OK.\n";
}

int main()
{
    test_solution();
    return 0;
}
