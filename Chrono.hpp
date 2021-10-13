#ifndef CHRONO_HPP
#define CHRONO_HPP

#include <chrono>
#include <unistd.h>

namespace TIE {
    class Chrono {
        private:
        std::chrono::system_clock::time_point startTime;
        std::chrono::duration<float> deltaTime;
        std::chrono::duration<float> sec;

        public:
        Chrono(){
            Reset();
            deltaTime = std::chrono::duration<float>(0.0f);
            sec = std::chrono::duration<float>(1.0f);
        }

        void Reset(){
            startTime = std::chrono::system_clock::now();
        }

        float DeltaTime(){
            return deltaTime.count();
        }

        bool Tick(){
            deltaTime += (std::chrono::system_clock::now() - startTime);
            return (std::chrono::system_clock::now() - startTime) >= sec;
        }

        };
}

#endif