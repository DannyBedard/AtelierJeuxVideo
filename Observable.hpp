#ifndef OBSERVABLE_HPP
#define OBSERVABLE_HPP

#include <list>

using namespace std;

namespace TIE {
    class Observable {
        public:
        list<Observer*> observers;

        void AddObserver(Observer* observer){
            observers.push_back(observer);
        }

        void RemoveObserver(Observer* observer){
            observers.remove(observer);
        }

        void Notify(){
            for (auto it : observers){
                it->Notification();
            }
        }
    };
}

namespace TIE {
    class Observer {
        public:
        virtual void Notification() = 0;
    };
}

#endif