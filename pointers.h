//
// Created by egor on 6.05.20.
//

#ifndef SMART_POINTERS_POINTERS_H
#define SMART_POINTERS_POINTERS_H
#include <iostream>
#include <string>

template<typename T>
class UniquePointer
{
protected:
    T* data;
public:
    UniquePointer(T* prt = 0);
    UniquePointer(const UniquePointer&);
    ~UniquePointer();
    T* operator->() const;
    void set(T newData)
    {
        this->data->set(newData);
    }
};

template<typename T>
UniquePointer<T>::UniquePointer(T* ptr)
{
    if (!ptr)
    {
        this->data = NULL;
    }
    else
    {
        this->data = ptr;
    }
}

template<typename T>
UniquePointer<T>::UniquePointer(const UniquePointer& obj) : data(obj.data)
{ }

template<typename T>
UniquePointer<T>::~UniquePointer()
{
    if (this->data)
    {
        delete this->data;
    }
}

template<typename T>
T* UniquePointer<T>::operator->() const
{
    if (this->data)
    {
        return this->data;
    }
    else
    {
        return NULL;
    }
}

template<typename T>
class SharedPointer : public UniquePointer<T>
{
    int count;

public:
    SharedPointer(T* ptr) : UniquePointer<T>(ptr), count(0)
    {
        if (this->data)
        {
            this->count = 1;
        }
    }

    SharedPointer<T>& operator=(const SharedPointer& obj)
    {
        if (this->count <= 0)
        {
            delete this->data;
        }

        this->data = obj.data;
        if (this->data)
        {
            this->count++;
        }

        return *this;
    }

    int getCount() { return this->count; }
};
#endif //SMART_POINTERS_POINTERS_H
