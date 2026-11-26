#ifndef SJTU_CROSS_ARRAY_HPP
#define SJTU_CROSS_ARRAY_HPP

namespace sjtu {

class CrossArray {
private:
    struct Row {
        int *data;
        int size;
        int capacity;
    };

    Row *rows_;
    int capacity_;
    int count_;
    int total_;

    void Swap(CrossArray &other) {
        Row *rows = rows_;
        rows_ = other.rows_;
        other.rows_ = rows;
        int value = capacity_;
        capacity_ = other.capacity_;
        other.capacity_ = value;
        value = count_;
        count_ = other.count_;
        other.count_ = value;
        value = total_;
        total_ = other.total_;
        other.total_ = value;
    }

public:
    explicit CrossArray(int lines)
        : rows_(new Row[lines]()), capacity_(lines), count_(0), total_(0) {}

    CrossArray(const CrossArray &other) : CrossArray(other.capacity_) {
        for (int i = 0; i < other.count_; ++i) {
            InsertArrays(other.rows_[i].data, other.rows_[i].size);
        }
    }

    CrossArray &operator=(const CrossArray &other) {
        if (this != &other) {
            CrossArray copy(other);
            Swap(copy);
        }
        return *this;
    }

    CrossArray &WhichGreater(CrossArray &other) {
        return total_ >= other.total_ ? *this : other;
    }

    bool IsSame(const CrossArray &other) {
        return this == &other;
    }

    bool InsertArrays(const int *input, int size) {
        if (count_ == capacity_) return false;
        int *data = new int[size];
        for (int i = 0; i < size; ++i) data[i] = input[i];
        rows_[count_].data = data;
        rows_[count_].size = size;
        rows_[count_].capacity = size;
        ++count_;
        total_ += size;
        return true;
    }

    void AppendArrays(const int *input, int line, int size) {
        if (size == 0) return;
        Row &row = rows_[line];
        const int new_size = row.size + size;
        if (new_size > row.capacity) {
            int new_capacity = row.capacity * 2;
            if (new_capacity < new_size) new_capacity = new_size;
            int *data = new int[new_capacity];
            for (int i = 0; i < row.size; ++i) data[i] = row.data[i];
            // Read the input before freeing the row: input may alias this row.
            for (int i = 0; i < size; ++i) data[row.size + i] = input[i];
            delete[] row.data;
            row.data = data;
            row.capacity = new_capacity;
        } else {
            for (int i = 0; i < size; ++i) row.data[row.size + i] = input[i];
        }
        row.size = new_size;
        total_ += size;
    }

    void DoubleCrossLength() {
        const int new_capacity = capacity_ * 2;
        Row *rows = new Row[new_capacity]();
        for (int i = 0; i < count_; ++i) rows[i] = rows_[i];
        delete[] rows_;
        rows_ = rows;
        capacity_ = new_capacity;
    }

    const int *AtArray(int i) { return rows_[i].data; }

    int &At(int i, int j) { return rows_[i].data[j]; }

    ~CrossArray() {
        for (int i = 0; i < count_; ++i) delete[] rows_[i].data;
        delete[] rows_;
    }
};

} // namespace sjtu

#endif
