#pragma once

namespace DeviousDevices
{
    //for implementing this, I used https://github.com/ArranzCNL/ImprovedCameraSE-NG as reference which also hides arms using nodes
    class NodeHider
    {
    public:
        NodeHider(NodeHider &) = delete;
        void operator=(const NodeHider &) = delete;
        static NodeHider* GetSingleton();


        void HideArms();
        void ShowArms();
        void Setup();
    protected:
        NodeHider(){}
        ~NodeHider(){}

        static NodeHider* _this;
    };

}