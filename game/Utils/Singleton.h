#pragma once

template <typename T>
class Singleton {
public:
    static T& instance()
    {
        static T instance{ token{} };
        return instance;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator= (Singleton) = delete;

protected:
    struct token {};
    Singleton() = default;
};