#include "Plugin.h"
#include "Bot.h"

Plugin::Plugin() = default;

void Plugin::onFriendRecall(std::shared_ptr<cqhttp::FriendRecallEvent> event, std::shared_ptr<Bot> bot)
{
}

void Plugin::onGroupRecall(std::shared_ptr<cqhttp::GroupRecallEvent> event, std::shared_ptr<Bot> bot)
{
}

void Plugin::onGroupIncrease(std::shared_ptr<cqhttp::GroupIncreaseEvent> event, std::shared_ptr<Bot> bot)
{
}

void Plugin::onGroupDecrease(std::shared_ptr<cqhttp::GroupDecreaseEvent> event, std::shared_ptr<Bot> bot)
{
}

void Plugin::onGroupAdmin(std::shared_ptr<cqhttp::GroupAdminChangeEvent> event, std::shared_ptr<Bot> bot)
{
}

void Plugin::onGroupUpload(std::shared_ptr<cqhttp::GroupFileUploadEvent> event, std::shared_ptr<Bot> bot)
{
}

void Plugin::onGroupBan(std::shared_ptr<cqhttp::GroupBanEvent> event, std::shared_ptr<Bot> bot)
{
}

void Plugin::onFriendAdd(std::shared_ptr<cqhttp::FriendAddEvent> event, std::shared_ptr<Bot> bot)
{
}

void Plugin::onNotify(std::shared_ptr<cqhttp::NotifyEvent> event, std::shared_ptr<Bot> bot)
{
}

void Plugin::onGroupCard(std::shared_ptr<cqhttp::GroupCardChangedEvent> event, std::shared_ptr<Bot> bot)
{
}

void Plugin::onOfflineFile(std::shared_ptr<cqhttp::ReceivedOfflineFileEvent> event, std::shared_ptr<Bot> bot)
{
}

void Plugin::onClientStatus(std::shared_ptr<cqhttp::ClientChangedEvent> event)
{
}

void Plugin::onEssence(std::shared_ptr<cqhttp::EssenceMsgChangedEvent> event, std::shared_ptr<Bot> bot)
{
}

void Plugin::onFriendRequest(std::shared_ptr<cqhttp::FriendAddRequestEvent> event, std::shared_ptr<Bot> bot)
{
}

void Plugin::onGroupRequest(std::shared_ptr<cqhttp::GroupAddRequestEvent> event, std::shared_ptr<Bot> bot)
{
}

void Plugin::onConnected(std::shared_ptr<cqhttp::LifecycleEvent> event, std::shared_ptr<Bot> bot)
{
}

void Plugin::onDisable(std::shared_ptr<cqhttp::LifecycleEvent> event, std::shared_ptr<Bot> bot)
{
}

void Plugin::onEnable(std::shared_ptr<cqhttp::LifecycleEvent> event, std::shared_ptr<Bot> bot)
{
}

void Plugin::onCreated()
{
}

void Plugin::onDestory()
{
}

void Plugin::onPrivateMessage(std::shared_ptr<cqhttp::PrivateMessageEvent>, std::shared_ptr<Bot> bot)
{
}

void Plugin::onGroupMessage(std::shared_ptr<cqhttp::GroupMessageEvent> event, std::shared_ptr<Bot> bot)
{
}

Plugin::Plugin(const std::string &plugin_name, const std::string &author,
               const std::string &description, const std::string &email_address)
{
    this->plugin_name = plugin_name;
    this->author = author;
    this->description = description;
    this->email_address = email_address;
}
