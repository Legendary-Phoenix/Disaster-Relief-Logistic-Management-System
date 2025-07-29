#pragma once

template <typename T>
class Array {
private:
    T* data;
    int capacity;
    int length;

    void resize() {
        int newCapacity = capacity * 2;
        T* newData = new T[newCapacity];

        for (int i = 0; i < length; ++i)
            newData[i] = data[i];

        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    Array(int initialSize = 10)
        : capacity(initialSize), length(0) {
        data = new T[capacity];
    }

    ~Array() {
        delete[] data;
    }

    void insert(int index, T value) {
        if (length >= capacity) resize();

        for (int i = length; i > index; --i)
            data[i] = data[i - 1];

        data[index] = value;
        length++;
    }

    void append(T value) {
        if (length >= capacity) resize();
        data[length++] = value;
    }

    void removeAt(int index) {
        for (int i = index; i < length - 1; ++i)
            data[i] = data[i + 1];
        length--;
    }

    T& operator[](int index) {
        return data[index];
    }
    
    const T& operator[](int index) const {
    return data[index];
}


    int size() const {
        return length;
    }

    bool isEmpty() const {
        return length == 0;
    }

    
};
