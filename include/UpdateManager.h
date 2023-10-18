#pragma once

#include "NodeHider.h"

namespace DeviousDevices
{
    struct SerialTask
    {
        void*           arg;
        std::function<void(void*)> task;
        bool            freearg;
    };

    class UpdateManager
    {
    SINGLETONHEADER(UpdateManager)
    public:
        void Setup();
        bool AddSerTask(std::function<void(void*)> a_task, void* a_arg, bool a_freearg);
    private:
        bool _installed = false;

        static void Update(RE::Actor* a_actor, float a_delta);
        inline static REL::Relocation<decltype(Update)> Update_old;

        std::mutex _taskmutex;
        void CallSerTasks();
        std::vector<SerialTask> _taskstack;
    };
}