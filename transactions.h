//
// Created by egor on 6.05.20.
//

#ifndef SMART_POINTERS_TRANSACTIONS_H
#define SMART_POINTERS_TRANSACTIONS_H
#include <iostream>
#include <iostream>

template<typename T>
class Transaction
{
    T* currState;
    T* prevState;

public:
    Transaction() : prevState(NULL), currState(new T) {}
    Transaction(const Transaction& obj) : currState(new T(*(obj.currState))), prevState(NULL) {}
    ~Transaction()
    {
        delete currState;
        delete prevState;
    }

    Transaction& operator=(const Transaction& obj);
    void show(int);
    bool beginTransaction(T);
    void commit();
    void deleteTransactions();
    T* operator->();
};

template<typename T>
Transaction<T>& Transaction<T>::operator=(const Transaction& obj)
{
    if (this != obj)
    {
        delete this->currState;
        this->currState = new T(*(obj.currState));
    }
    return *this;
}

template<typename T>
T* Transaction<T>::operator->()
{
    return this->currState;
}

template<typename T>
void Transaction<T>::show(int account)
{
    std::cout << "state: " << std::endl;
    if (!account)
    {
        std::cout << "before: " << std::endl;
    }
    else
    {
        std::cout << "after: " << std::endl;
    }

    if (this->prevState)
    {
        std::cout << this->prevState->get() << std::endl;
    }
    else
    {
        std::cout << "prev state = NULL" << std::endl;
    }
    std::cout << "curr state = " << this->currState->get() << std::endl;
}

template<typename T>
bool Transaction<T>::beginTransaction(T newData)
{
    delete this->prevState;
    this->prevState = this->currState;
    this->currState = new T(*this->prevState);

    if (!this->currState)
    {
        return false;
    }

    this->currState->set(newData);

    return true;
}

template<typename T>
void Transaction<T>::commit()
{
    delete this->prevState;
    this->prevState = NULL;
}

template<typename T>
void Transaction<T>::deleteTransactions()
{
    if (this->prevState != NULL)
    {
        delete this->currState;
        this->currState = this->prevState;
        this->prevState = NULL;
    }
}
#endif //SMART_POINTERS_TRANSACTIONS_H
//