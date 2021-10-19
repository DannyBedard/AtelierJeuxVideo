#ifndef CHRONO_HPP
#define CHRONO_HPP

#include <chrono>
#include <unistd.h>

using namespace std;
using namespace std::chrono;

namespace TIE {
    class Chrono {
        private:
        steady_clock::time_point start;
        /*std::chrono::system_clock::time_point startTime;
        std::chrono::duration<float> totalTime;
        std::chrono::duration<float> sec;*/

        public:
        Chrono(){
            Reset();
        }

        inline void Reset() { //Méthode d'une seule ligne, les appels font juste copier la ligne au lieu d'appeler la méthode
            start = steady_clock::now();
        }

        double GetElapsedSeconds(){
            return duration_cast<nanoseconds>(steady_clock::now() - start).count() / 1000000000.0;
        }

        //Atelier 5
        /*Chrono(){
            Reset();
            totalTime = std::chrono::duration<float>(0.0f);
            sec = std::chrono::duration<float>(1.0f);
        }

        void Reset(){
            startTime = std::chrono::system_clock::now();
        }

        float TotalTime(){
            return totalTime.count();
        }

        bool Tick(){
            totalTime += (std::chrono::system_clock::now() - startTime);
            if (std::chrono::system_clock::now() - startTime >= sec){
                Reset();
                return true;
            }
            return false;
            
        }*/

        };
}

#endif