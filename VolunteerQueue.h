#pragma once

#include <iostream>
#include "Volunteer.h"

class VolunteerQueue
{
private:
    Volunteer *queue;
    int front;
    int rear;
    int capacity;
    int count;

    void resize()
    {
        int newCapacity = capacity * 2;
        Volunteer *newQueue = new Volunteer[newCapacity];
        for (int i = 0; i < count; ++i)
        {
            newQueue[i] = queue[front + i];
        }
        delete[] queue;
        queue = newQueue;
        front = 0;
        rear = count - 1;
        capacity = newCapacity;
    }

public:
    VolunteerQueue()
    {
        capacity = 10;
        queue = new Volunteer[capacity];
        front = 0;
        rear = -1;
        count = 0;
    }

    ~VolunteerQueue()
    {
        delete[] queue;
    }

    void enqueue(Volunteer v)
    {
        if (rear + 1 == capacity)
        {
            resize();
        }
        rear++;
        queue[rear] = v;
        count++;
    }

    Volunteer dequeue()
    {
        if (isEmpty())
        {
            throw runtime_error("Queue is empty. Cannot dequeue.");
        }
        Volunteer temp = queue[front];
        front++;
        count--;
        return temp;
    }

    Volunteer peek() const
    {
        if (isEmpty())
        {
            throw runtime_error("Queue is empty. Cannot peek.");
        }
        return queue[front];
    }

    bool isEmpty() const
    {
        return count == 0;
    }

    int size() const
    {
        return count;
    }

    void display() const
    {
        if (isEmpty())
        {
            cout << "Queue is empty." << endl;
            return;
        }
        cout << "Volunteers in Queue:" << endl;
        for (int i = 0; i < count; ++i)
        {
            queue[front + i].display();
            cout << "----------------------" << endl;
        }
    }
};
