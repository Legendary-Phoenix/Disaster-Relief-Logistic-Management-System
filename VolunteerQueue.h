#pragma once

#include "Volunteer.h"

class VolunteerQueue
{
private:
    Volunteer *arr;
    int capacity;
    int front;
    int rear;

    void resize()
    {
        int newCapacity = capacity * 2;
        Volunteer *newArr = new Volunteer[newCapacity];
        int size = rear - front + 1;
        for (int i = 0; i < size; i++)
        {
            newArr[i] = arr[front + i];
        }
        delete[] arr;
        arr = newArr;
        front = 0;
        rear = size - 1;
        capacity = newCapacity;
    }

public:
    VolunteerQueue()
    {
        capacity = 10;
        arr = new Volunteer[capacity];
        front = 0;
        rear = -1;
    }

    ~VolunteerQueue()
    {
        delete[] arr;
    }

    void enqueue(Volunteer v)
    {
        if (rear + 1 == capacity)
        {
            resize();
        }
        arr[++rear] = v;
    }

    Volunteer dequeue()
    {
        if (isEmpty())
        {
            throw out_of_range("Queue is empty");
        }
        return arr[front++];
    }

    bool isEmpty() const
    {
        return front > rear;
    }

    int size() const
    {
        return rear - front + 1;
    }

    Volunteer *getAll() const
    {
        return arr + front;
    }
};