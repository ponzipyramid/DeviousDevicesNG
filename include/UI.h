#pragma once

#include <functional>
#include <future>
#include <vector>

namespace DeviousDevices {

    class MessageBox {
        class MessageBoxResultCallback : public RE::IMessageBoxCallback {
            std::function<void(unsigned int)> _callback;

        public:
            ~MessageBoxResultCallback() override {}
            MessageBoxResultCallback(std::function<void(unsigned int)> callback) : _callback(callback) {}
            void Run(RE::IMessageBoxCallback::Message message) override {
                _callback(static_cast<unsigned int>(message));
            }
        };

    public:
        static void Show(const std::string& bodyText, std::vector<std::string> buttonTextValues,
                         std::function<void(unsigned int)> callback) {
            auto* factoryManager = RE::MessageDataFactoryManager::GetSingleton();
            auto* uiStringHolder = RE::InterfaceStrings::GetSingleton();
            auto* factory = factoryManager->GetCreator<RE::MessageBoxData>(
                uiStringHolder->messageBoxData); 
            auto* messagebox = factory->Create();
            RE::BSTSmartPointer<RE::IMessageBoxCallback> messageCallback =
                RE::make_smart<MessageBoxResultCallback>(callback);
            messagebox->callback = messageCallback;
            messagebox->bodyText = bodyText;
            for (auto text : buttonTextValues) messagebox->buttonText.push_back(text.c_str());
            messagebox->QueueMessage();
        }

        static void Show(RE::BGSMessage* msg, std::function<void(unsigned int)> callback) { 
            RE::BSString desc;
            msg->GetDescription(desc, msg->ownerQuest);

            std::vector<std::string> buttonTextValues;
            for (const auto& btn : msg->menuButtons) buttonTextValues.push_back(std::string(btn->text.c_str()));

            Show(std::string(desc.c_str()), buttonTextValues, callback);
        }
    };
}