#ifndef PLUGINDEV_PLUGIN_H
#define PLUGINDEV_PLUGIN_H



#include <iostream>
#include <memory>
#include "Bot.h"
#include "cqhttp_event.pb.h"
#include "logger.h"

class EXPORT_API Plugin
{
public:
    std::string plugin_name;
    std::string author;
    std::string description;
    std::string email_address;

    Plugin();

    Plugin(const std::string &plugin_name,
           const std::string &author,
           const std::string &description,
           const std::string &email_address);

    /**
     * @brief 私聊消息事件回调，在接收到私聊消息时，框架会调用此函数。
     * @param event 事件
     * @param bot 机器人
     */
    virtual void onPrivateMessage(std::shared_ptr<cqhttp::PrivateMessageEvent> event, std::shared_ptr<Bot> bot);

    /**
     * @brief 群消息事件回调，在接收到群消息时，框架会调用此函数。
     * @param event 事件
     * @param bot 机器人
     */
    virtual void onGroupMessage(std::shared_ptr<cqhttp::GroupMessageEvent> event, std::shared_ptr<Bot> bot);

    /**
     * @brief 私聊消息撤回事件回调，在接收到此事件时，框架会调用此函数。
     * @param event 事件
     * @param bot 机器人
     */
    virtual void onFriendRecall(std::shared_ptr<cqhttp::FriendRecallEvent> event, std::shared_ptr<Bot> bot);

    /**
     * @brief 群聊消息撤回事件回调，在接收到此事件时，框架会调用此函数。
     * @param event 事件
     * @param bot 机器人
     */
    virtual void onGroupRecall(std::shared_ptr<cqhttp::GroupRecallEvent> event, std::shared_ptr<Bot> bot);

    /**
     * @brief 群成员增加，在接收到此事件时，框架会调用此函数。
     * @param event 事件
     * @param bot 机器人
     */
    virtual void onGroupIncrease(std::shared_ptr<cqhttp::GroupIncreaseEvent> event, std::shared_ptr<Bot> bot);

    /**
     * @brief 群成员减少，在接收到此事件时，框架会调用此函数。
     * @param event 事件
     * @param bot 机器人
     */
    virtual void onGroupDecrease(std::shared_ptr<cqhttp::GroupDecreaseEvent> event, std::shared_ptr<Bot> bot);

    /**
     * @brief 群管理员变动，在接收到此事件时，框架会调用此函数。
     * @param event 事件
     * @param bot 机器人
     */
    virtual void onGroupAdmin(std::shared_ptr<cqhttp::GroupAdminChangeEvent> event, std::shared_ptr<Bot> bot);

    /**
     * @brief 群文件上传，在接收到此事件时，框架会调用此函数。
     * @param event 事件
     * @param bot 机器人
     */
    virtual void onGroupUpload(std::shared_ptr<cqhttp::GroupFileUploadEvent> event, std::shared_ptr<Bot> bot);

    /**
     * @brief 群禁言，在接收到此事件时，框架会调用此函数。
     * @param event 事件
     * @param bot 机器人
     */
    virtual void onGroupBan(std::shared_ptr<cqhttp::GroupBanEvent> event, std::shared_ptr<Bot> bot);

    /**
     * @brief 好友添加，在接收到此事件时，框架会调用此函数。
     * @param event 事件
     * @param bot 机器人
     */
    virtual void onFriendAdd(std::shared_ptr<cqhttp::FriendAddEvent> event, std::shared_ptr<Bot> bot);

    /**
     * @brief 通知事件（例如戳一戳等），在接收到此事件时，框架会调用此函数。
     * @param event 事件
     * @param bot 机器人
     */
    virtual void onNotify(std::shared_ptr<cqhttp::NotifyEvent> event, std::shared_ptr<Bot> bot);

    /**
     * @brief 群成员名片更新，在接收到此事件时，框架会调用此函数。
     * @param event 事件
     * @param bot 机器人
     */
    virtual void onGroupCard(std::shared_ptr<cqhttp::GroupCardChangedEvent> event, std::shared_ptr<Bot> bot);

    /**
     * @brief 接收到离线文件，在接收到此事件时，框架会调用此函数。
     * @param event 事件
     * @param bot 机器人
     */
    virtual void onOfflineFile(std::shared_ptr<cqhttp::ReceivedOfflineFileEvent> event, std::shared_ptr<Bot> bot);

    /**
     * @brief 其他客户端在线状态变更，在接收到此事件时，框架会调用此函数。
     * @param event 事件
     */
    virtual void onClientStatus(std::shared_ptr<cqhttp::ClientChangedEvent> event);

    /**
     * @brief 精华消息变更，在接收到此事件时，框架会调用此函数。
     * @param event 事件
     * @param bot 机器人
     */
    virtual void onEssence(std::shared_ptr<cqhttp::EssenceMsgChangedEvent> event, std::shared_ptr<Bot> bot);

    /**
     * @brief 好友申请，在接收到此事件时，框架会调用此函数。
     * @param event 事件
     * @param bot 机器人
     */
    virtual void onFriendRequest(std::shared_ptr<cqhttp::FriendAddRequestEvent> event, std::shared_ptr<Bot> bot);

    /**
     * @brief 群申请，在接收到此事件时，框架会调用此函数。
     * @param event 事件
     * @param bot 机器人
     */
    virtual void onGroupRequest(std::shared_ptr<cqhttp::GroupAddRequestEvent> event, std::shared_ptr<Bot> bot);

    /**
     * @brief 框架生命周期，在接收到此事件时，框架会调用此函数。
     * @param event 事件
     * @param bot 机器人
     */
    virtual void onConnected(std::shared_ptr<cqhttp::LifecycleEvent> event, std::shared_ptr<Bot> bot);

    /**
     * @brief 框架生命周期，在接收到此事件时，框架会调用此函数。
     * @param event 事件
     * @param bot 机器人
     */
    virtual void onDisable(std::shared_ptr<cqhttp::LifecycleEvent> event, std::shared_ptr<Bot> bot);

    /**
     * @brief 框架生命周期，在接收到此事件时，框架会调用此函数。
     * @param event 事件
     * @param bot 机器人
     */
    virtual void onEnable(std::shared_ptr<cqhttp::LifecycleEvent> event, std::shared_ptr<Bot> bot);

    /**
     * @brief 插件生命周期，在接收到此事件时，框架会调用此函数。
     * @param event 事件
     * @param bot 机器人
     */
    virtual void onCreated();

    /**
     * @brief 插件生命周期，在接收到此事件时，框架会调用此函数。
     * @param event 事件
     * @param bot 机器人
     */
    virtual void onDestory();
};

#endif // PLUGINDEV_PLUGIN_H