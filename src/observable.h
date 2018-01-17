#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <functional>
#include <vector>
#include <tuple>

template<typename ... Funcs>
class Observable
{
public:
    using ObserverList = std::tuple<std::vector<std::function<Funcs>>...>;
    
    template<unsigned int eventidx, typename Callable>
    void AttachObserver(Callable c)
    {
        std::get<eventidx>(observers).push_back(c);
    }
    
    template<unsigned int eventidx,typename ... T>
    void NotifyObserversOfEvent(T ... args)
    {
        for(auto f: std::get<eventidx>(observers))
        {
            f(std::forward<T>(args)...);
        }
    }
    
private:
    ObserverList observers;
};

#endif //OBSERVABLE_H