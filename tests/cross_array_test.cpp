#include "../CrossArray.hpp"
#include <cassert>
#include <vector>
#include <random>

int main() {
    sjtu::CrossArray zero(0);
    zero.DoubleCrossLength();
    assert(!zero.InsertArrays(nullptr, 0));
    sjtu::CrossArray a(2);
    assert(a.AtArray(0) == nullptr && a.AtArray(1) == nullptr);
    int input[] = {1, -2, 3};
    assert(a.InsertArrays(input, 3));
    input[0] = 99;
    assert(a.At(0, 0) == 1);
    assert(a.InsertArrays(nullptr, 0));
    assert(!a.InsertArrays(input, 3));
    a.AppendArrays(a.AtArray(0), 0, 3);
    assert(a.At(0, 3) == 1 && a.At(0, 5) == 3);
    a.AppendArrays(input, 1, 3);
    sjtu::CrossArray b(a);
    assert(!a.IsSame(b) && a.IsSame(a));
    assert(&a.WhichGreater(b) == &a);
    b.At(0, 0) = 42;
    assert(a.At(0, 0) == 1);
    b.AppendArrays(input, 0, 1);
    assert(&a.WhichGreater(b) == &b);
    const int *old_row = a.AtArray(0);
    a.DoubleCrossLength();
    assert(a.AtArray(0) == old_row);
    assert(a.AtArray(2) == nullptr && a.AtArray(3) == nullptr);
    assert(a.InsertArrays(input, 3));
    b = a;
    b = b;
    b.At(2, 0) = 0;
    assert(a.At(2, 0) == 99);

    std::mt19937 random(1410);
    sjtu::CrossArray actual(1000);
    std::vector<std::vector<int> > expected(1000);
    for (int i = 0; i < 1000; ++i) {
        assert(actual.InsertArrays(nullptr, 0));
    }
    for (int step = 0; step < 100000; ++step) {
        int row = random() % 1000;
        int size = random() % 20;
        int values[20];
        for (int j = 0; j < size; ++j) values[j] = int(random() % 2001) - 1000;
        actual.AppendArrays(values, row, size);
        expected[row].insert(expected[row].end(), values, values + size);
        if (step % 1000 == 0) {
            sjtu::CrossArray copy(actual);
            for (int i = 0; i < 1000; ++i) {
                for (unsigned j = 0; j < expected[i].size(); ++j) {
                    assert(actual.At(i, j) == expected[i][j]);
                    assert(copy.At(i, j) == expected[i][j]);
                }
            }
        }
    }
}
