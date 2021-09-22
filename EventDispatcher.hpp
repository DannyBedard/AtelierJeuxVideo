#ifndef EVENTDISPATCHER_HPP
#define EVENTDISPATCHER_HPP

#include <map>
#include "Observer.hpp"
#include "GameEvent.hpp"

using namespace std;

namespace TIE{
    class EventDispatcher {
    private:
        map<unsigned int, Observable> events;

    public:
        void Bind(unsigned int eventType, Observer* observer){
            events[eventType].AddObserver(observer);
        }

        void Unbind(unsigned int eventType, Observer* observer){
            events[eventType].RemoveObserver(observer);
        }

        void Dispatch(){
            if (events.find(GameEvent::GetType()) != events.end())
                events[GameEvent::GetType()].Notify();
        }
    };
}

#endif 