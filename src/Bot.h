#ifndef PLUGINDEV_BOT_H
#define PLUGINDEV_BOT_H

#include <iostream>
#include <google/protobuf/util/json_util.h>
#include <future>
#include <drogon/WebSocketConnection.h>
#include "protos/cqhttp_api.pb.h"

typedef std::map<std::string, std::shared_ptr<std::promise<std::string>>> PromiseMap;

class Bot
{
public:
    int64_t self_id;
    drogon::WebSocketConnectionPtr conn_ptr;
    std::shared_ptr<PromiseMap> promise_map;

    Bot(const Bot &bot);

    Bot(int64_t self_id, drogon::WebSocketConnectionPtr conn_ptr);

    /**
     * @brief 发送私聊消息
     * @param message 发送的消息，可以是酷Q码
     * @param user_id 对方QQ号，必须是好友
     * @param auto_escape 默认 False
     */
    std::shared_ptr<cqhttp::SendPrivateMsgResp> sendPrivateMessage(const std::string &message, int64_t user_id,
                                                                   bool auto_escape = false);
    /**
     * @brief 发送私聊消息
     * @param message 发送的消息，可以是酷Q码
     * @param user_id 对方QQ号，必须是好友
     * @param auto_escape 默认 False
     */
    std::shared_ptr<cqhttp::SendPrivateMsgResp> sendPrivateMessage(const char *message, int64_t user_id,
                                                                   bool auto_escape = false);

    /**
     * @brief 发送消息，需要指定是群消息还是私聊消息，此方法已弃用
     */
    std::shared_ptr<cqhttp::SendMsgResp> sendMessage(cqhttp::CQHTTP_TYPE message_type, int64_t user_id, int64_t group_id,
                                                     std::string &message, bool auto_escape = false) = delete;

    /**
     * @brief 发送消息到指定群
     * @param message 消息内容，可以包含酷Q码
     * @param group_id 群号，机器人必须在群内
     * @param auto_escape 默认 false
     */
    std::shared_ptr<cqhttp::SendGroupMsgResp> sendGroupMessage(const std::string &message, int64_t group_id,
                                                               bool auto_escape = false);

    /**
     * @brief 获取登录账号信息
     *
     */
    std::shared_ptr<cqhttp::GetLoginInfoResp> getLoginInfo();

    /**
     * @brief 设置登录账号信息
     * @param nick_name 名称
     * @param company 公司
     * @param email 邮箱
     * @param college 学校
     * @param personal_note 个人说明
     */
    void setQQProfile(const std::string &nick_name,
                      const std::string &company,
                      const std::string &email,
                      const std::string &college,
                      const std::string &personal_note);

    /**
     * @brief 获取企点账号信息，该 API 因文档不齐，弃用。
     */
    void getQiDianAccountInfo() = delete;

    /**
     * @brief 获取在线机型。
     * @param model 机型名称
     */
    std::shared_ptr<cqhttp::GetModelShowResp> getModelShow(const std::string &model);

    /**
     * @brief 设置在线机型
     * @param model 机型名称
     * @param model_show
     */
    void setModelShow(const std::string &model, const std::string &model_show);

    /**
     * @brief 获取当前账号在线客户端列表
     * @param no_cache 是否无视缓存
     */
    std::shared_ptr<cqhttp::GetOnlineClientsResp> getOnlineClients(bool no_cache = false);

    /**
     * @brief 获取陌生人信息
     * @param user_id QQ 号码
     * @param no_cache 是否不使用缓存（使用缓存可能更新不及时, 但响应更快）
     */
    std::shared_ptr<cqhttp::GetStrangerInfoResp> getStrangerInfo(int64_t user_id, bool no_cache = false);

    /**
     * @brief 获取好友列表
     */
    std::shared_ptr<cqhttp::GetFriendListResp> getFriendList();

    /**
     * @brief 获取单向好友列表
     */
    std::shared_ptr<cqhttp::UnidirectionalFriendListResp> getUnidirectionalFriendList();

    /**
     * @brief 删除好友
     * @param user_id QQ 号
     */
    void delFriend(int64_t user_id);

    /**
     * @brief 删除单向好友
     * @param user_id QQ 号
     */
    void delUnidirectionalFriend(int64_t user_id);

    /**
     * @brief 获取消息
     * @param message_id 消息 ID
     */
    std::shared_ptr<cqhttp::GetMsgResp> getMessage(int32_t message_id);

    /**
     * @brief 撤回消息
     * @param message_id
     */
    void delMessage(int32_t message_id);

    /**
     * @brief 标记消息为已读
     * @param message_id
     */
    void markMsgAsRead(int32_t message_id);

    /**
     * @brief 获取合并转发内容
     * @param message_id 字段 message_id 对应合并转发中的 id 字段
     */
    std::shared_ptr<cqhttp::GetForwardMsgResp> getForwardMsg(std::string &message_id);

    /**
     * @brief 发送合并转发 ( 群聊 )
     * @param group_id 群号
     * @param message 自定义转发消息, 具体看
     * https://docs.go-cqhttp.org/cqcode/#%E5%90%88%E5%B9%B6%E8%BD%AC%E5%8F%91%E6%B6%88%E6%81%AF%E8%8A%82%E7%82%B9
     */
    std::shared_ptr<cqhttp::SendGroupForwardMsgResp> sendGroupForwardMsg(int64_t group_id, std::string &message);

    /**
     * @brief 发送合并转发 ( 好友 )
     * @param user_id 好友QQ号
     * @param message 自定义转发消息, 具体看
     * https://docs.go-cqhttp.org/cqcode/#%E5%90%88%E5%B9%B6%E8%BD%AC%E5%8F%91%E6%B6%88%E6%81%AF%E8%8A%82%E7%82%B9
     */
    std::shared_ptr<cqhttp::SendPrivateForwardMsgResp> sendPrivateForwardMsg(int64_t user_id,
                                                                             std::vector<cqhttp::ForwardMessage> &message);

    /**
     * @brief 获取群消息历史记录
     * @param message_seq 起始消息序号, 可通过 get_msg 获得
     * @param group_id
     */
    std::shared_ptr<cqhttp::GetGroupMsgHistoryResp> getGroupMsgHistory(int64_t message_seq, int64_t group_id);

    /**
     * @brief 获取图片信息
     * @param file 图片缓存文件名
     */
    std::shared_ptr<cqhttp::GetImageResp> getImage(std::string &file);

    /**
     * @brief 检查是否可以发送图片
     */
    std::shared_ptr<cqhttp::CanSendImageResp> canSendImage();

    /**
     * @brief 图片 OCR
     * @param image 图片ID
     */
    std::shared_ptr<cqhttp::OcrImageResp> ocrImage(std::string image);

    /**
     * @brief 获取语音,该 API 暂未被 go-cqhttp 支持
     * @param file 收到的语音文件名（消息段的 file 参数）, 如 0B38145AA44505000B38145AA4450500.silk
     * @param out_format 要转换到的格式, 目前支持 mp3、amr、wma、m4a、spx、ogg、wav、flac
     */
    std::shared_ptr<cqhttp::GetRecordResp> getRecord(std::string &file, std::string &out_format) = delete;

    /**
     * @brief 检查是否可以发送语音
     */
    std::shared_ptr<cqhttp::CanSendRecordResp> canSendRecord();

    /**
     * @brief 处理加好友请求
     * @param flag 加好友请求的 flag（需从上报的数据中获得）
     * @param approve 是否同意请求
     * @param remark 添加后的好友备注（仅在同意时有效）
     */
    void setFriendAddRequest(std::string &flag, bool approve = true, const std::string &remark = std::string(""));

    /**
     * @brief 处理加群请求／邀请
     * @param flag 加群请求的 flag（需从上报的数据中获得）
     * @param type add 或 invite, 请求类型（需要和上报消息中的 sub_type 字段相符）
     * @param approve 是否同意请求／邀请
     * @param reason 拒绝理由（仅在拒绝时有效）
     */
    void setGroupAddRequest(std::string &flag, std::string &type, bool approve = true, const std::string &reason = std::string(""));

    /**
     * @brief 获取群信息
     * @param group_id 群号
     * @param no_cache 是否不使用缓存（使用缓存可能更新不及时, 但响应更快）
     */
    std::shared_ptr<cqhttp::GetGroupInfoResp> getGroupInfo(int64_t group_id, bool no_cache = false);

    /**
     * @brief 获取群列表
     * @param no_cache 是否不使用缓存（使用缓存可能更新不及时, 但响应更快）
     */
    std::shared_ptr<cqhttp::GetGroupListResp> getGroupList(bool no_cache = false);

    /**
     * @brief 获取群成员信息
     * @param group_id 群号
     * @param user_id QQ 号
     * @param no_cache 是否不使用缓存（使用缓存可能更新不及时, 但响应更快）
     */
    std::shared_ptr<cqhttp::GetGroupMemberInfoResp> getGroupMemberInfo(int64_t group_id, int64_t user_id, bool no_cache = false);

    /**
     * @brief 获取群成员列表
     * @param group_id 群号
     * @param no_cache 是否不使用缓存（使用缓存可能更新不及时, 但响应更快）
     */
    std::shared_ptr<cqhttp::GetGroupMemberListResp> getGroupMemberList(int64_t group_id, bool no_cache);

    /**
     * @brief 获取群荣誉信息
     * @param group_id 群号
     * @param type 要获取的群荣誉类型, 可传入 talkative performer legend strong_newbie emotion
     * 以分别获取单个类型的群荣誉数据, 或传入 all 获取所有数据
     */
    std::shared_ptr<cqhttp::GetGroupHonorInfoResp> getGroupHonorInfo(int64_t group_id, std::string &type);

    /**
     * @brief 获取群系统消息
     */
    std::shared_ptr<cqhttp::GetGroupSystemMsgResp> getGroupSystemMsg();

    /**
     * @brief 获取精华消息列表
     * @param group_id 群号
     */
    std::shared_ptr<cqhttp::GetEssenceMsgListResp> getEssenceMsgList(int64_t group_id);

    /**
     * @brief 获取群 @全体成员 剩余次数
     * @param group_id 群号
     */
    std::shared_ptr<cqhttp::GetGroupAtAllRemainResp> getGroupAtAllRemain(int64_t group_id);

    /**
     * @brief 设置群名
     */
    void setGroupName(int64_t group_id, std::string &group_name);

    /**
     * @brief 设置群头像
     * @param group_id 群号
     * @param file 图片文件名
     * @param cache 表示是否使用已缓存的文件
     */
    void setGroupPortrait(int64_t group_id, std::string &file, int cache);

    /**
     * @brief 设置群管理员
     * @param group_id 群号
     * @param user_id 要设置管理员的 QQ 号
     * @param enable true 为设置, false 为取消
     */
    void setGroupAdmin(int64_t group_id, int64_t user_id, bool enable = true);

    /**
     * @brief 设置群名片 ( 群备注 )
     * @param group_id 群号
     * @param user_id 要设置的 QQ 号
     * @param card 群名片内容, 不填或空字符串表示删除群名片
     */
    void setGroupCard(int64_t group_id, int64_t user_id, const std::string &card = std::string(""));

    /**
     * @brief 设置群组专属头衔
     * @param group_id 群号
     * @param user_id 要设置的 QQ 号
     * @param special_title 专属头衔, 不填或空字符串表示删除专属头衔
     * @param duration 专属头衔有效期, 单位秒, -1 表示永久, 不过此项似乎没有效果, 可能是只有某些特殊的时间长度有效, 有待测试
     */
    void setGroupSpecialTitle(int64_t group_id, int64_t user_id,
                              const std::string &special_title = std::string(""), uint32_t duration = -1);

    /**
     * @brief 群单人禁言
     * @param group_id 群号
     * @param user_id 要禁言的 QQ 号
     * @param duration 禁言时长, 单位秒, 0 表示取消禁言
     */
    void setGroupBan(int64_t group_id, int64_t user_id, uint32_t duration = 1800);

    /**
     * @brief 群全员禁言
     * @param group_id 群号
     * @param enable 是否禁言
     */
    void setGroupWholeBan(int64_t group_id, bool enable = true);

    /**
     * @brief 群匿名用户禁言 该 API 从 go-cqhttp-v0.9.36 开始支持
     * @param group_id 	群号
     * @param anonymous 可选, 要禁言的匿名用户对象（群消息上报的 anonymous 字段）
     * @param flag 可选, 要禁言的匿名用户的 flag（需从群消息上报的数据中获得）
     * @param duration 禁言时长, 单位秒, 无法取消匿名用户禁言
     */
    void setGroupAnonymousBan(int64_t group_id, cqhttp::Anonymous &anonymous,
                              std::string &flag, uint32_t duration = 1800);

    /**
     * @brief 设置精华消息
     * @param message_id 消息 ID
     */
    void setEssenceMsg(int32_t message_id);

    /**
     * @brief 移出精华消息
     * @param message_id 消息 ID
     */
    void delEssenceMsg(int32_t message_id);

    /**
     * @brief 群打卡
     * @param group_id
     */
    void sendGroupSign(int64_t group_id);

    /**
     * @brief 群设置匿名
     * 该 API 暂未被 go-cqhttp 支持, 您可以提交 pr 以使该 API 被支持 提交 pr
     * https://github.com/Mrs4s/go-cqhttp/compare
     * @param group_id 群号
     * @param enable 是否允许匿名聊天
     */
    void setGroupAnonymous(int64_t group_id, bool enable = true) = delete;

    /**
     * @brief 发送群公告
     * @param group_id 群号
     * @param content 公告内容
     * @param image 图片路径（可选）
     */
    void sendGroupNotice(int64_t group_id, std::string &content, std::string &image);

    /**
     * @brief 获取群公告
     * @param group_id 群号
     */
    std::shared_ptr<cqhttp::GetGroupNoticeResp> getGroupNotice(int64_t group_id);

    /**
     * @brief 群组踢人
     * @param group_id 群号
     * @param user_id 要踢的 QQ 号
     * @param reject_add_request 拒绝此人的加群请求
     */
    void setGroupKick(int64_t group_id, int64_t user_id, bool reject_add_request = false);

    /**
     * @brief 推出群组
     * @param group_id 群号
     * @param is_dismiss 是否解散, 如果登录号是群主, 则仅在此项为 true 时能够解散
     */
    void setGroupLeave(int64_t group_id, bool is_dismiss = false);

    /**
     * @brief 上传群文件
     * 注意
     * 在不提供 folder 参数的情况下默认上传到根目录
     * 只能上传本地文件, 需要上传 http 文件的话请先调用 download_file API下载
     *
     * @param group_id 群号
     * @param file 本地文件路径
     * @param name 储存名称
     * @param folder 父目录ID
     */
    void uploadGroupFile(int64_t group_id, std::string &file, std::string &name,
                         std::string &folder);

    /**
     * @brief 删除群文件
     * @param group_id 群号
     * @param file_id 文件ID 参考 File 对象
     * @param busid 文件类型 参考 File 对象
     */
    void delGroupFile(int64_t group_id, std::string &file_id, int32_t busid);

    /**
     * @brief 创建群文件文件夹
     * @param group_id 群号
     * @param name 文件夹名称
     * @param parent_id 仅能为 /
     */
    void createGroupFileFolder(int64_t group_id, std::string &name, const std::string &parent_id = std::string("/"));

    /**
     * @brief 删除群文件文件夹
     * @param group_id 群号
     * @param folder_id 文件夹ID 参考 Folder 对象
     */
    void delGroupFolder(int64_t group_id, std::string &folder_id);

    /**
     * @brief 获取群文件系统信息
     * @param group_id 群号
     */
    std::shared_ptr<cqhttp::GetGroupFileSystemInfoResp> getGroupFileSystemInfo(int64_t group_id);

    /**
     * @brief 获取群根目录文件列表
     * @param group_id 群号
     */
    std::shared_ptr<cqhttp::GetGroupRootFilesResp> getGroupRootFiles(int64_t group_id);

    /**
     * @brief 获取群子目录文件列表
     * @param group_id 群号
     * @param folder_id 文件夹ID 参考 Folder 对象
     */
    std::shared_ptr<cqhttp::GetGroupFileByFolderResp> getGroupFileByFolder(int64_t group_id, std::string &folder_id);

    /**
     * @brief 获取群文件资源链接
     * @param group_id 群号
     * @param file_id 文件ID 参考 File 对象
     * @param busid 文件类型 参考 File 对象
     */
    std::shared_ptr<cqhttp::GetGroupFileUrlResp> getGroupFileUrl(int64_t group_id, std::string &file_id, int32_t busid);

    /**
     * @brief 上传私聊文件
     * @param user_id 对方 QQ 号
     * @param file 本地文件路径
     * @param name 文件名称
     */
    void uploadPrivateFile(int64_t user_id, std::string &file, std::string &name);

    /**
     * @brief 获取 Cookies
     * 该 API 暂未被 go-cqhttp 支持, 您可以提交 pr 以使该 API 被支持 提交 pr
     * https://github.com/Mrs4s/go-cqhttp/compare
     * @param domain 需要获取 cookies 的域名
     */
    std::shared_ptr<cqhttp::GetCookiesResp> getCookies(const std::string &domain = std::string("")) = delete;

    /**
     * @brief 获取 CSRF Token
     * 该 API 暂未被 go-cqhttp 支持, 您可以提交 pr 以使该 API 被支持 提交 pr
     * https://github.com/Mrs4s/go-cqhttp/compare
     */
    std::shared_ptr<cqhttp::GetCsrfTokenResp> getCsrfToken() = delete;

    /**
     * @brief 获取 QQ 相关接口凭证
     * 该 API 暂未被 go-cqhttp 支持, 您可以提交 pr 以使该 API 被支持 提交 pr
     * https://github.com/Mrs4s/go-cqhttp/compare
     * @param domain 需要获取 cookies 的域名
     */
    std::shared_ptr<cqhttp::GetCredentialsResp> getCredentials(const std::string &domain = std::string("")) = delete;

    /**
     * @brief 获取版本信息
     */
    std::shared_ptr<cqhttp::GetVersionInfoResp> getVersionInfo();

    /**
     * @brief 获取状态
     */
    std::shared_ptr<cqhttp::GetStatusResp> getStatus();

    /**
     * @brief 重启 Go-CqHttp
     * 该 API 由于技术原因，自 1.0.0 版本已被移除，目前暂时没有再加入的计划 #1230
     * @param delay 要延迟的毫秒数, 如果默认情况下无法重启, 可以尝试设置延迟为 2000 左右
     */
    void setRestart(int delay) = delete;

    /**
     * @brief 清理缓存
     * 该 API 暂未被 go-cqhttp 支持, 您可以提交 pr 以使该 API 被支持 提交 pr
     * https://github.com/Mrs4s/go-cqhttp/compare
     */
    void cleanCache() = delete;

    /**
     * @brief 重载事件过滤器
     * @param file 事件过滤器文件
     */
    void reloadEventFilter(std::string &file);

    /**
     * @brief 下载文件到缓存目录
     * 通过这个API下载的文件能直接放入CQ码作为图片或语音发送
     * 调用后会阻塞直到下载完成后才会返回数据，请注意下载大文件时的超时
     * @param url 链接地址
     * @param thread_count 下载线程数
     * @param headers 自定义请求头
     * @param time_out 超时时间，单位秒
     */
    std::shared_ptr<cqhttp::DownloadFileResp> downloadFile(std::string &url, int32_t thread_count,
                                                           std::string &headers, int64_t time_out = 15);

    /**
     * @brief 检查链接安全性
     * @param url 需要检查的链接
     */
    std::shared_ptr<cqhttp::CheckUrlSafelyResp> checkUrlSafely(std::string &url);

    /**
     * @brief 获取中文分词 ( 隐藏 API )
     * 隐藏 API 是不建议一般用户使用的, 它们只应该在 OneBot 实现内部或由 SDK 和框架使用,
     * 因为不正确的使用可能造成程序运行不正常。
     */
    std::shared_ptr<cqhttp::GetWordSlicesResp> getWordSlices(std::string &content) = delete;

    /**
     * @brief 对事件执行快速操作 ( 隐藏 API )
     * @param content 事件数据对象, 可做精简, 如去掉 message 等无用字段
     * @param operation 快速操作对象, 例如 {"ban": true, "reply": "请不要说脏话"}
     */
    void handleQuickOperation(std::string &content, std::string &operation) = delete;

private:
    template <typename T1, typename T2>
    std::shared_ptr<T1> sendAndWaitResp(T2 &data, int64_t time_out = 15);
    template <typename T>
    void sendOnly(T &data);
    std::mutex bot_mutex;
    google::protobuf::util::JsonParseOptions bot_parse_options;
    google::protobuf::util::JsonPrintOptions bot_print_options;
};

#endif // PLUGINDEV_BOT_H
