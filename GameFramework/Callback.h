//
// Created by Artur Kabirov on 16/5/22.
//

#ifndef STARWARS_CALLBACK_H
#define STARWARS_CALLBACK_H

class Callback
{
public:
    virtual void call() = 0;
};

class StaticCallback : public Callback
{
public:

    StaticCallback(void (*func)()) : m_func(func)
    {

    }

    virtual void call()
    {
        m_func();
    }

private:

    void (*m_func)();
};

#endif
