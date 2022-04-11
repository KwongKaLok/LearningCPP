#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>
#include <sstream>

using namespace std;

template <typename T>
class BiLNode
{
public:
    T data{};
    BiLNode<T> *next{nullptr};
    BiLNode<T> *prev{nullptr};
    BiLNode(T input)
    {
        data = input;
        next = nullptr;
        prev = nullptr;
    }
};

template <typename T>
class Deque
{
private:
    BiLNode<T> *head{nullptr};
    BiLNode<T> *tail{nullptr};
    int size{0};

public:
    Deque() = default;
    ~Deque()
    {
        BiLNode<T> *tmp = head;
        while (tmp != nullptr)
        {
            tmp = tmp->next;
            delete head;
            head = tmp;
        }
    }

    void push_back(const T &value)
    {
        if (head == nullptr)
        {
            head = new BiLNode<T>(value);
            tail = head;
        }
        else
        {
            BiLNode<T> *tmp = new BiLNode<T>(value);
            tmp->prev = tail;
            tail->next = tmp;
            tail = tmp;
        }
        size++;
    }

    void push_front(const T &value)
    {
        if (head == nullptr)
        {
            head = new BiLNode<T>(value);
            tail = head;
        }
        else
        {
            BiLNode<T> *tmp = new BiLNode<T>(value);
            tmp->next = head;
            head->prev = tmp;
            head = tmp;
        }
        size++;
    }

    T pop_back()
    {
        if (head == nullptr)
        {
            cout << "Nothing in deque!";
        }
        if (head->next == nullptr)
        {
            T tmp = head->data;
            delete head;
            head = nullptr;
            size--;
            return tmp;
        }
        T tmp = tail->data;
        BiLNode<T> *bftail = tail->prev;
        delete tail;
        tail = bftail;
        tail->next = nullptr;
        size--;
        return tmp;
    }

    T pop_front()
    {
        if (head == nullptr)
        {
            cout << "Nothing in deque!";
        }
        if (head->next == nullptr)
        {
            T tmp = head->data;
            delete head;
            head = nullptr;
            size--;
            return tmp;
        }
        T tmp = head->data;
        BiLNode<T> *afhead = head->next;
        delete head;
        head = afhead;
        head->prev = nullptr;
        size--;
        return tmp;
    }

    void clear()
    {
        while (size > 0)
            this->pop_back();
    }

    // TODO 1: overload operator==
    bool operator==(const Deque &A)
    {
        if (A.size == this->size)
        {
            BiLNode<T> *tmp1 = this->head;
            BiLNode<T> *tmp2 = A.head;
            for (int i = 0; i < this->size; i++)
            {
                if (tmp1->data == tmp2->data)
                {
                    tmp1 = tmp1->next;
                    tmp2 = tmp2->next;
                }
                else
                {
                    return false;
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    // TODO 2: overload operator=
    void operator=(const Deque &A)
    {
        BiLNode<T> *Aptr = A.head;
        for (int i = 0; i < A.size; i++)
        {
            push_back(Aptr->data);
            Aptr = Aptr->next;
        }
    }

    // TODO 3: overload operator+
    Deque<T> &operator+(const Deque &A)
    {
        Deque<T> *temp = new Deque<T>;
        BiLNode<T> *Aptr = A.head;
        for (int i = 0; i < A.size; i++)
        {
            temp->push_back(Aptr->data);
            Aptr = Aptr->next;
        }
        return (*temp);
    }

    // TODO 4: overload operator<<
    friend ostream &operator<<(ostream &out, const Deque &A)
    {
        BiLNode<T> *Aptr = A.head;
        out << "[";
        for (int i = 0; i < A.size; i++)
        {
            out << Aptr->data;
            Aptr = Aptr->next;
            if (Aptr != nullptr)
            {
                out << "<-->";
            }
        }
        out << "]";
        return out;
    }
};

#endif