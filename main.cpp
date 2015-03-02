#include <iostream>
#include <vector>

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

int get_inversion_count(const std::vector<int> data)
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

int main()
{
    std::ios_base::sync_with_stdio(false);

    size_t n;
    std::cin >> n;
    std::vector<int> numbers;
    for (size_t i = 0; i < n; ++i)
    {
        int input_value;
        std::cin >> input_value;
        numbers.push_back(input_value);
    }

    std::cout << get_inversion_count(numbers) << '\n';

    return 0;
}
