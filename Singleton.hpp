#ifndef SINGLETON_H
#define SINGLETON_H

template<class T>
class Singleton
{
public:
    static T &instance()
    {
        static T self;
        return self;
    }

protected:
    Singleton() = default;
    virtual ~Singleton() = default;
};

#endif // SINGLETON_H
