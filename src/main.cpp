#include <iostream>
#include "observable.h"

class A : public Observable<
                            void(void),
                            void(int,std::string),
                            void(int,int)
                            >
{
public:
    enum Event : unsigned
    {
        Event0,
        Event1,
        Event2
    };
    
private:
    int a;
    std::string s;
};

class B
{
public:
    void EventZeroHappened()
    {
        std::cout << "B has observed event zero\n";
    }
    
    
    void EventOneHappened(int a, std::string s)
    {
        std::cout << "B has observed event one with params: " << a << " and " << "\"" << s << "\"" <<'\n';
    }
    
    void EventTwoHappened(int a, int b)
    {
        std::cout << "B has observed event two with params: " << a << " and " << b <<'\n';
    }
};

int main()
{
    A a;
    B b;
    
    auto f = [&b](int i, int j){b.EventTwoHappened(i,j);};
    
    a.AttachObserver<A::Event::Event0>([&b](){b.EventZeroHappened();});
    a.AttachObserver<A::Event::Event1>([&b](int i, std::string s){b.EventOneHappened(i,s);});
    a.AttachObserver<A::Event::Event2>(f);

    a.NotifyObserversOfEvent<A::Event::Event0>();
    a.NotifyObserversOfEvent<A::Event::Event1>(37,"Hello There");
    a.NotifyObserversOfEvent<A::Event::Event2>(182,150);
}