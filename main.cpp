#include <iostream>
#include <vector>

class My_Fenwick_Tree
{
public:
    explicit My_Fenwick_Tree(const size_t data_size);
    void update(const size_t start, long long delta);
    size_t sum(std::ptrdiff_t start) const;
private:
    size_t f_prev(size_t number) const;
    size_t f_next(size_t number) const;
    std::vector<long long> tree;
};

size_t My_Fenwick_Tree::f_prev(size_t number) const
{
    return number & (number + 1);
}

size_t My_Fenwick_Tree::f_next(size_t number) const
{
    return number | (number + 1);
}

void My_Fenwick_Tree::update(const size_t start, long long delta)
{
    for (size_t x = start; x < tree.size(); x = f_next(x))
        tree[x] += delta;
}

My_Fenwick_Tree::My_Fenwick_Tree(const size_t data_size)
{
    tree.assign(data_size, 0);
}

size_t My_Fenwick_Tree::sum(std::ptrdiff_t start) const
{
    size_t result = 0;

    for (std::ptrdiff_t x = start; x >= 0; x = std::ptrdiff_t (f_prev(size_t (x))) - 1)
        result += tree[x];

    return result;
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    My_Fenwick_Tree fenwick(n);

    return 0;
}
