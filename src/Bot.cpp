#include "Bot.h"
#include "logger.h"

using namespace cqhttp;
using namespace google::protobuf::util;

Bot::Bot(const Bot &bot)
{
    this->conn_ptr = bot.conn_ptr;
    this->self_id = bot.self_id;
    this->promise_map = bot.promise_map;
}

Bot::Bot(int64_t self_id, drogon::WebSocketConnectionPtr bot) : conn_ptr(std::move(bot)), self_id(self_id)
{
    this->promise_map = std::make_shared<PromiseMap>(PromiseMap());
    bot_print_options.preserve_proto_field_names = true;
    bot_print_options.always_print_primitive_fields = true;
    bot_parse_options.ignore_unknown_fields = true;
}

std::shared_ptr<cqhttp::SendPrivateMsgResp> Bot::sendPrivateMessage(const std::string &message, int64_t user_id, bool auto_escape)
{
    cqhttp::SendPrivateMsg private_msg;
    private_msg.set_action(cqhttp::Action::send_private_msg);
    auto *params = new cqhttp::SendPrivateMsg_Params;
    params->set_message(message);
    params->set_user_id(user_id);
    params->set_auto_escape(auto_escape);
    private_msg.set_allocated_params(params);

    return sendAndWaitResp<cqhttp::SendPrivateMsgResp, cqhttp::SendPrivateMsg>(private_msg);
}

std::shared_ptr<cqhttp::SendPrivateMsgResp> Bot::sendPrivateMessage(const char *message, int64_t user_id, bool auto_escape)
{
    return sendPrivateMessage(std::string(message), user_id, auto_escape);
}

std::shared_ptr<cqhttp::SendGroupMsgResp> Bot::sendGroupMessage(const std::string &message, int64_t group_id, bool auto_escape)
{
    SendGroupMsg group_msg;
    group_msg.set_action(Action::send_group_msg);
    auto *params = new SendGroupMsg_Params;
    params->set_message(message);
    params->set_group_id(group_id);
    params->set_auto_escape(auto_escape);
    group_msg.set_allocated_params(params);

    return sendAndWaitResp<SendGroupMsgResp, SendGroupMsg>(group_msg);
}

std::shared_ptr<cqhttp::GetLoginInfoResp> Bot::getLoginInfo()
{
    GetLoginInfo login_info;
    login_info.set_action(Action::get_login_info);

    return sendAndWaitResp<GetLoginInfoResp, GetLoginInfo>(login_info);
}

void Bot::setQQProfile(const std::string &nick_name, const std::string &company, const std::string &email, const std::string &college, const std::string &personal_note)
{
    SetQQProfile qq_profile;
    qq_profile.set_action(Action::set_qq_profile);
    SetQQProfile_Params *params = new SetQQProfile_Params;
    params->set_nickname(nick_name);
    params->set_company(company);
    params->set_email(email);
    params->set_college(college);
    params->set_personal_note(personal_note);
    qq_profile.set_allocated_params(params);
    sendOnly<SetQQProfile>(qq_profile);
}

std::shared_ptr<cqhttp::GetModelShowResp> Bot::getModelShow(const std::string &model)
{
    GetModelShow model_show;
    model_show.set_action(Action::_get_model_show);
    GetModelShow_Params *params = new GetModelShow_Params;
    params->set_model(model);
    model_show.set_allocated_params(params);
    return sendAndWaitResp<GetModelShowResp, GetModelShow>(model_show);
}

void Bot::setModelShow(const std::string &model, const std::string &model_show)
{
    SetModelShow set_model;
    set_model.set_action(Action::_set_model_show);
    SetModelShow_Params *params = new SetModelShow_Params;
    params->set_model(model);
    params->set_model_show(model_show);
    set_model.set_allocated_params(params);
    sendOnly(set_model);
}

std::shared_ptr<cqhttp::GetOnlineClientsResp> Bot::getOnlineClients(bool no_cache)
{
    GetOnlineClients clients;
    clients.set_action(Action::get_online_clients);
    GetOnlineClients_Params *params = new GetOnlineClients_Params;
    params->set_no_cache(no_cache);

    return sendAndWaitResp<GetOnlineClientsResp, GetOnlineClients>(clients);
}

std::shared_ptr<cqhttp::GetStrangerInfoResp> Bot::getStrangerInfo(int64_t user_id, bool no_cache)
{
    GetStrangerInfo stranger_info;
    stranger_info.set_action(Action::get_stranger_info);
    GetStrangerInfo_Params *params = new GetStrangerInfo_Params;
    params->set_no_cache(no_cache);
    params->set_user_id(user_id);
    stranger_info.set_allocated_params(params);

    return sendAndWaitResp<GetStrangerInfoResp, GetStrangerInfo>(stranger_info);
}

std::shared_ptr<cqhttp::GetFriendListResp> Bot::getFriendList()
{
    GetFriendList friend_list;
    friend_list.set_action(Action::get_friend_list);

    return sendAndWaitResp<GetFriendListResp, GetFriendList>(friend_list);
}

std::shared_ptr<cqhttp::UnidirectionalFriendListResp> Bot::getUnidirectionalFriendList()
{
    UnidirectionalFriendList unidirectional_friend_list;
    unidirectional_friend_list.set_action(Action::get_unidirectional_friend_list);

    return sendAndWaitResp<UnidirectionalFriendListResp, UnidirectionalFriendList>(unidirectional_friend_list);
}

void Bot::delFriend(int64_t user_id)
{
    DeleteFriend del_friend;
    del_friend.set_action(Action::delete_friend);
    DeleteFriend_Params *params = new DeleteFriend_Params;
    params->set_user_id(user_id);
    del_friend.set_allocated_params(params);
    sendOnly(del_friend);
}

void Bot::delUnidirectionalFriend(int64_t user_id)
{
    DeleteUnidirectionalFriend del_u_friend;
    del_u_friend.set_action(Action::delete_unidirectional_friend);
    DeleteUnidirectionalFriend_Params *params = new DeleteUnidirectionalFriend_Params;
    params->set_user_id(user_id);
    sendOnly(del_u_friend);
}

std::shared_ptr<cqhttp::GetMsgResp> Bot::getMessage(int32_t message_id)
{
    GetMsg msg;
    msg.set_action(Action::get_msg);
    GetMsg_Params *params = new GetMsg_Params;
    params->set_message_id(message_id);
    msg.set_allocated_params(params);

    return sendAndWaitResp<GetMsgResp, GetMsg>(msg);
}

void Bot::delMessage(int32_t message_id)
{
    DeleteMsg delete_msg;
    delete_msg.set_action(Action::delete_msg);
    DeleteMsg_Params *params = new DeleteMsg_Params;
    params->set_message_id(message_id);
    delete_msg.set_allocated_params(params);
    sendOnly(delete_msg);
}

void Bot::markMsgAsRead(int32_t message_id)
{
    MarkMsgAsRead as_read;
    as_read.set_action(Action::mark_msg_as_read);
    MarkMsgAsRead_Params *params = new MarkMsgAsRead_Params;
    params->set_message_id(message_id);
    as_read.set_allocated_params(params);
    sendOnly(as_read);
}

std::shared_ptr<cqhttp::GetForwardMsgResp> Bot::getForwardMsg(std::string &message_id)
{
    GetForwardMsg forward_msg;
    forward_msg.set_action(Action::get_forward_msg);
    GetForwardMsg_Params *params = new GetForwardMsg_Params;
    params->set_message_id(message_id);
    forward_msg.set_allocated_params(params);

    return sendAndWaitResp<GetForwardMsgResp, GetForwardMsg>(forward_msg);
}

std::shared_ptr<cqhttp::SendGroupForwardMsgResp> Bot::sendGroupForwardMsg(int64_t group_id, std::vector<cqhttp::ForwardMessage> &message)
{
    SendGroupForwardMsg send_forward_msg;
    send_forward_msg.set_action(Action::send_group_forward_msg);
    SendGroupForwardMsg_Params *params = new SendGroupForwardMsg_Params;
    params->set_group_id(group_id);
    for (size_t i = 0; i < message.size(); i++)
    {
        auto *forward_msg = params->add_messages();
        std::string type = message.at(i).type();
        auto *data = new ForwardMessage_Data(message.at(i).data());
        forward_msg->set_type(type);
        forward_msg->set_allocated_data(data);
    }
    send_forward_msg.set_allocated_params(params);

    return sendAndWaitResp<SendGroupForwardMsgResp, SendGroupForwardMsg>(send_forward_msg);
}

std::shared_ptr<cqhttp::SendPrivateForwardMsgResp> Bot::sendPrivateForwardMsg(int64_t user_id, std::vector<cqhttp::ForwardMessage> &message)
{
    SendPrivateForwardMsg send_private_forward_msg;
    send_private_forward_msg.set_action(Action::send_private_forward_msg);
    SendPrivateForwardMsg_Params *params = new SendPrivateForwardMsg_Params;
    params->set_user_id(user_id);
    for (size_t i = 0; i < message.size(); i++)
    {
        ForwardMessage *forward_msg = params->add_messages();
        std::string type = message.at(i).type();
        ForwardMessage_Data *data = new ForwardMessage_Data(message.at(i).data());
        forward_msg->set_type(type);
        forward_msg->set_allocated_data(data);
    }
    send_private_forward_msg.set_allocated_params(params);
    return sendAndWaitResp<SendPrivateForwardMsgResp, SendPrivateForwardMsg>(send_private_forward_msg);
}

std::shared_ptr<cqhttp::GetGroupMsgHistoryResp> Bot::getGroupMsgHistory(int64_t message_seq, int64_t group_id)
{
    GetGroupMsgHistory history;
    history.set_action(Action::get_group_msg_history);
    GetGroupMsgHistory_Params *params = new GetGroupMsgHistory_Params;
    params->set_group_id(group_id);
    params->set_message_seq(message_seq);
    history.set_allocated_params(params);

    return sendAndWaitResp<GetGroupMsgHistoryResp, GetGroupMsgHistory>(history);
}

std::shared_ptr<cqhttp::GetImageResp> Bot::getImage(std::string &file)
{
    GetImage image;
    image.set_action(Action::get_image);
    GetImage_Params *params = new GetImage_Params;
    params->set_file(file);
    image.set_allocated_params(params);

    return sendAndWaitResp<GetImageResp, GetImage>(image);
}

std::shared_ptr<cqhttp::CanSendImageResp> Bot::canSendImage()
{
    CanSendImage xx;
    xx.set_action(Action::can_send_image);

    return sendAndWaitResp<CanSendImageResp, CanSendImage>(xx);
}

std::shared_ptr<cqhttp::OcrImageResp> Bot::ocrImage(std::string image)
{
    OcrImage ocr;
    ocr.set_action(Action::ocr_image);
    OcrImage_Params *params = new OcrImage_Params;
    params->set_image(image);
    ocr.set_allocated_params(params);

    return sendAndWaitResp<OcrImageResp, OcrImage>(ocr);
}

std::shared_ptr<cqhttp::CanSendRecordResp> Bot::canSendRecord()
{
    CanSendRecord record;
    record.set_action(Action::can_send_record);

    return sendAndWaitResp<CanSendRecordResp>(record);
}

void Bot::setFriendAddRequest(std::string &flag, bool approve, const std::string &remark)
{
    SetFriendAddRequest friend_add_request;
    friend_add_request.set_action(Action::set_friend_add_request);
    SetFriendAddRequest_Params *params = new SetFriendAddRequest_Params;
    params->set_flag(flag);
    params->set_approve(approve);
    params->set_remark(remark);
    friend_add_request.set_allocated_params(params);

    sendOnly(friend_add_request);
}

void Bot::setGroupAddRequest(std::string &flag, std::string &type, bool approve, const std::string &reason)
{
    SetGroupAddRequest group_add_request;
    group_add_request.set_action(Action::set_group_add_request);
    SetGroupAddRequest_Params *params = new SetGroupAddRequest_Params;
    params->set_flag(flag);
    params->set_sub_type(type);
    params->set_approve(approve);
    params->set_reason(reason);
    group_add_request.set_allocated_params(params);

    sendOnly(group_add_request);
}

std::shared_ptr<cqhttp::GetGroupInfoResp> Bot::getGroupInfo(int64_t group_id, bool no_cache)
{
    GetGroupInfo group_info;
    group_info.set_action(Action::get_group_info);
    GetGroupInfo_Params *params = new GetGroupInfo_Params;
    params->set_group_id(group_id);
    params->set_no_cache(no_cache);
    group_info.set_allocated_params(params);

    return sendAndWaitResp<GetGroupInfoResp>(group_info);
}

std::shared_ptr<cqhttp::GetGroupListResp> Bot::getGroupList(bool no_cache)
{
    GetGroupList group_list;
    group_list.set_action(Action::get_group_list);
    GetGroupList_Params *params = new GetGroupList_Params;
    params->set_no_cache(no_cache);
    group_list.set_allocated_params(params);

    return sendAndWaitResp<GetGroupListResp>(group_list);
}

std::shared_ptr<cqhttp::GetGroupMemberInfoResp> Bot::getGroupMemberInfo(int64_t group_id, int64_t user_id, bool no_cache)
{
    GetGroupMemberInfo member_info;
    member_info.set_action(Action::get_group_member_info);
    GetGroupMemberInfo_Params *params = new GetGroupMemberInfo_Params;
    params->set_group_id(group_id);
    params->set_user_id(user_id);
    params->set_no_cache(no_cache);
    member_info.set_allocated_params(params);

    return sendAndWaitResp<GetGroupMemberInfoResp>(member_info);
}

std::shared_ptr<cqhttp::GetGroupMemberListResp> Bot::getGroupMemberList(int64_t group_id, bool no_cache)
{
    GetGroupMemberList member_list;
    member_list.set_action(Action::get_group_member_list);
    GetGroupMemberList_Params *params = new GetGroupMemberList_Params;
    params->set_group_id(group_id);
    params->set_no_cache(no_cache);
    member_list.set_allocated_params(params);

    return sendAndWaitResp<GetGroupMemberListResp>(member_list);
}

std::shared_ptr<cqhttp::GetGroupHonorInfoResp> Bot::getGroupHonorInfo(int64_t group_id, std::string &type)
{
    GetGroupHonorInfo honor_info;
    honor_info.set_action(Action::get_group_honor_info);
    GetGroupHonorInfo_Params *params = new GetGroupHonorInfo_Params;
    params->set_group_id(group_id);
    params->set_type(type);
    honor_info.set_allocated_params(params);

    return sendAndWaitResp<GetGroupHonorInfoResp>(honor_info);
}

std::shared_ptr<cqhttp::GetGroupSystemMsgResp> Bot::getGroupSystemMsg()
{
    GetGroupSystemMsg sys_msg;
    sys_msg.set_action(Action::get_group_system_msg);

    return sendAndWaitResp<GetGroupSystemMsgResp>(sys_msg);
}

std::shared_ptr<cqhttp::GetEssenceMsgListResp> Bot::getEssenceMsgList(int64_t group_id)
{
    GetEssenceMsgList essence_msg_l;
    essence_msg_l.set_action(Action::get_essence_msg_list);
    GetEssenceMsgList_Params *params = new GetEssenceMsgList_Params;
    params->set_group_id(group_id);
    essence_msg_l.set_allocated_params(params);

    return sendAndWaitResp<GetEssenceMsgListResp>(essence_msg_l);
}

std::shared_ptr<cqhttp::GetGroupAtAllRemainResp> Bot::getGroupAtAllRemain(int64_t group_id)
{
    GetGroupAtAllRemain all_remain;
    all_remain.set_action(Action::get_group_at_all_remain);
    GetGroupAtAllRemain_Params *params = new GetGroupAtAllRemain_Params;
    params->set_group_id(group_id);
    all_remain.set_allocated_params(params);

    return sendAndWaitResp<GetGroupAtAllRemainResp>(all_remain);
}

void Bot::setGroupName(int64_t group_id, std::string &group_name)
{
    SetGroupName set_group_n;
    set_group_n.set_action(Action::set_group_name);
    SetGroupName_Params *params = new SetGroupName_Params;
    params->set_group_id(group_id);
    params->set_group_name(group_name);
    set_group_n.set_allocated_params(params);

    sendOnly(set_group_n);
}

void Bot::setGroupPortrait(int64_t group_id, std::string &file, int cache)
{
    SetGroupPortrait portrait;
    portrait.set_action(Action::set_group_portrait);
    SetGroupPortrait_Params *params = new SetGroupPortrait_Params;
    params->set_group_id(group_id);
    params->set_file(file);
    params->set_cache(cache);
    portrait.set_allocated_params(params);

    sendOnly(portrait);
}

void Bot::setGroupAdmin(int64_t group_id, int64_t user_id, bool enable)
{
    SetGroupAdmin m_set_group_admin;
    m_set_group_admin.set_action(Action::set_group_admin);
    SetGroupAdmin_Params *params = new SetGroupAdmin_Params;
    params->set_group_id(group_id);
    params->set_user_id(user_id);
    params->set_enable(enable);
    m_set_group_admin.set_allocated_params(params);

    sendOnly(m_set_group_admin);
}

void Bot::setGroupCard(int64_t group_id, int64_t user_id, const std::string &card)
{
    SetGroupCard m_set_group_card;
    m_set_group_card.set_action(Action::set_group_card);
    SetGroupCard_Params *params = new SetGroupCard_Params;
    params->set_group_id(group_id);
    params->set_user_id(user_id);
    params->set_card(card);
    m_set_group_card.set_allocated_params(params);

    sendOnly(m_set_group_card);
}

void Bot::setGroupSpecialTitle(int64_t group_id, int64_t user_id, const std::string &special_title, uint32_t duration)
{
    SetGroupSpecialTitle m_special_title;
    m_special_title.set_action(Action::set_group_special_title);
    SetGroupSpecialTitle_Params *params = new SetGroupSpecialTitle_Params;
    params->set_group_id(group_id);
    params->set_user_id(user_id);
    params->set_special_title(special_title);
    params->set_duration(duration);
    m_special_title.set_allocated_params(params);

    sendOnly(m_special_title);
}

void Bot::setGroupBan(int64_t group_id, int64_t user_id, uint32_t duration)
{
    SetGroupBan m_set_group_ban;
    m_set_group_ban.set_action(Action::set_group_ban);
    SetGroupBan_Params *params = new SetGroupBan_Params;
    params->set_group_id(group_id);
    params->set_user_id(user_id);
    params->set_duration(duration);
    m_set_group_ban.set_allocated_params(params);

    sendOnly(m_set_group_ban);
}

void Bot::setGroupWholeBan(int64_t group_id, bool enable)
{
    SetGroupWholeBan m_whole_ban;
    m_whole_ban.set_action(Action::set_group_whole_ban);
    SetGroupWholeBan_Params *params = new SetGroupWholeBan_Params;
    params->set_group_id(group_id);
    params->set_enable(enable);
    m_whole_ban.set_allocated_params(params);

    sendOnly(m_whole_ban);
}

void Bot::setGroupAnonymousBan(int64_t group_id, cqhttp::Anonymous &anonymous, std::string &flag, uint32_t duration)
{
    SetGroupAnonymousBan m_anonymous_ban;
    m_anonymous_ban.set_action(Action::set_group_anonymous_ban);
    SetGroupAnonymousBan_Params *params = new SetGroupAnonymousBan_Params;
    params->set_group_id(group_id);
    Anonymous *anonymous_ptr = new Anonymous(anonymous);
    params->set_allocated_anonymous(anonymous_ptr);
    params->set_anonymous_flag(flag);
    params->set_duration(duration);
    m_anonymous_ban.set_allocated_params(params);

    sendOnly(m_anonymous_ban);
}

void Bot::setEssenceMsg(int32_t message_id)
{
    SetEssenceMsg m_set_essence_msg;
    m_set_essence_msg.set_action(Action::set_essence_msg);
    SetEssenceMsg_Params *params = new SetEssenceMsg_Params;
    params->set_message_id(message_id);
    m_set_essence_msg.set_allocated_params(params);

    sendOnly(m_set_essence_msg);
}

void Bot::delEssenceMsg(int32_t message_id)
{
    DeleteEssenceMsg m_del_essence_msg;
    m_del_essence_msg.set_action(Action::delete_essence_msg);
    DeleteEssenceMsg_Params *params = new DeleteEssenceMsg_Params;
    params->set_message_id(message_id);
    m_del_essence_msg.set_allocated_params(params);

    sendOnly(m_del_essence_msg);
}

void Bot::sendGroupSign(int64_t group_id)
{
    SendGroupSign m_group_sign;
    m_group_sign.set_action(Action::send_group_sign);
    SendGroupSign_Params *params = new SendGroupSign_Params;
    params->set_group_id(group_id);
    m_group_sign.set_allocated_params(params);

    sendOnly(m_group_sign);
}

void Bot::sendGroupNotice(int64_t group_id, std::string &content, std::string &image)
{
    SendGroupNotice m_send_g_notice;
    m_send_g_notice.set_action(Action::_send_group_notice);
    SendGroupNotice_Params *params = new SendGroupNotice_Params;
    params->set_group_id(group_id);
    params->set_content(content);
    params->set_image(image);
    m_send_g_notice.set_allocated_params(params);

    sendOnly(m_send_g_notice);
}

std::shared_ptr<cqhttp::GetGroupNoticeResp> Bot::getGroupNotice(int64_t group_id)
{
    GetGroupNotice m_get_g_notice;
    m_get_g_notice.set_action(Action::_get_group_notice);
    GetGroupNotice_Params *params = new GetGroupNotice_Params;
    params->set_group_id(group_id);
    m_get_g_notice.set_allocated_params(params);

    return sendAndWaitResp<GetGroupNoticeResp>(m_get_g_notice);
}

void Bot::setGroupKick(int64_t group_id, int64_t user_id, bool reject_add_request)
{
    SetGroupKick m_kick;
    m_kick.set_action(Action::set_group_kick);
    SetGroupKick_Params *params = new SetGroupKick_Params;
    params->set_group_id(group_id);
    params->set_user_id(user_id);
    params->set_reject_add_request(reject_add_request);
    m_kick.set_allocated_params(params);

    sendOnly(m_kick);
}

void Bot::setGroupLeave(int64_t group_id, bool is_dismiss)
{
    SetGroupLeave m_leave;
    m_leave.set_action(Action::set_group_leave);
    SetGroupLeave_Params *params = new SetGroupLeave_Params;
    params->set_group_id(group_id);
    params->set_is_dismiss(is_dismiss);
    m_leave.set_allocated_params(params);

    sendOnly(m_leave);
}

void Bot::uploadGroupFile(int64_t group_id, std::string &file, std::string &name, std::string &folder)
{
    UploadGroupFile m_upload_file;
    m_upload_file.set_action(Action::upload_group_file);
    UploadGroupFile_Params *params = new UploadGroupFile_Params;
    params->set_group_id(group_id);
    params->set_file(file);
    params->set_name(name);
    params->set_folder(folder);
    m_upload_file.set_allocated_params(params);

    sendOnly(m_upload_file);
}

void Bot::delGroupFile(int64_t group_id, std::string &file_id, int32_t busid)
{
    DeleteGroupFile m_del_group_file;
    m_del_group_file.set_action(Action::delete_group_file);
    DeleteGroupFile_Params *params = new DeleteGroupFile_Params;
    params->set_group_id(group_id);
    params->set_file_id(file_id);
    params->set_busid(busid);
    m_del_group_file.set_allocated_params(params);

    sendOnly(m_del_group_file);
}

void Bot::createGroupFileFolder(int64_t group_id, std::string &name, const std::string &parent_id)
{
    CreateGroupFileFolder m_create_folder;
    m_create_folder.set_action(Action::create_group_file_folder);
    CreateGroupFileFolder_Params *params = new CreateGroupFileFolder_Params;
    params->set_group_id(group_id);
    params->set_name(name);
    params->set_parent_id(parent_id);
    m_create_folder.set_allocated_params(params);

    sendOnly(m_create_folder);
}

void Bot::delGroupFolder(int64_t group_id, std::string &folder_id)
{
    DeleteGroupFolder m_del_folder;
    m_del_folder.set_action(Action::delete_group_folder);
    DeleteGroupFolder_Params *params = new DeleteGroupFolder_Params;
    params->set_group_id(group_id);
    params->set_folder_id(folder_id);
    m_del_folder.set_allocated_params(params);

    sendOnly(m_del_folder);
}

std::shared_ptr<cqhttp::GetGroupFileSystemInfoResp> Bot::getGroupFileSystemInfo(int64_t group_id)
{
    GetGroupFileSystemInfo m_file_sys_info;
    m_file_sys_info.set_action(Action::get_group_file_system_info);
    GetGroupFileSystemInfo_Params *params = new GetGroupFileSystemInfo_Params;
    params->set_group_id(group_id);
    m_file_sys_info.set_allocated_params(params);

    return sendAndWaitResp<GetGroupFileSystemInfoResp>(m_file_sys_info);
}

std::shared_ptr<cqhttp::GetGroupRootFilesResp> Bot::getGroupRootFiles(int64_t group_id)
{
    GetGroupRootFiles m_get_root;
    m_get_root.set_action(Action::get_group_root_files);
    GetGroupRootFiles_Params *params = new GetGroupRootFiles_Params;
    params->set_group_id(group_id);
    m_get_root.set_allocated_params(params);

    return sendAndWaitResp<GetGroupRootFilesResp>(m_get_root);
}

std::shared_ptr<cqhttp::GetGroupFileByFolderResp> Bot::getGroupFileByFolder(int64_t group_id, std::string &folder_id)
{
    GetGroupFileByFolder m_get_files;
    m_get_files.set_action(Action::get_group_files_by_folder);
    GetGroupFileByFolder_Params *params = new GetGroupFileByFolder_Params;
    params->set_group_id(group_id);
    params->set_folder_id(folder_id);
    m_get_files.set_allocated_params(params);

    return sendAndWaitResp<GetGroupFileByFolderResp>(m_get_files);
}

std::shared_ptr<cqhttp::GetGroupFileUrlResp> Bot::getGroupFileUrl(int64_t group_id, std::string &file_id, int32_t busid)
{
    GetGroupFileUrl m_get_url;
    m_get_url.set_action(Action::get_group_file_url);
    GetGroupFileUrl_Params *params = new GetGroupFileUrl_Params;
    params->set_group_id(group_id);
    params->set_file_id(file_id);
    params->set_busid(busid);
    m_get_url.set_allocated_params(params);

    return sendAndWaitResp<GetGroupFileUrlResp>(m_get_url);
}

void Bot::uploadPrivateFile(int64_t user_id, std::string &file, std::string &name)
{
    UploadPrivateFile m_upload_p_file;
    m_upload_p_file.set_action(Action::upload_private_file);
    UploadPrivateFile_Params *params = new UploadPrivateFile_Params;
    params->set_user_id(user_id);
    params->set_file(file);
    params->set_name(name);
    m_upload_p_file.set_allocated_params(params);

    sendOnly(m_upload_p_file);
}

std::shared_ptr<cqhttp::GetVersionInfoResp> Bot::getVersionInfo()
{
    GetVersionInfo m_get_version;
    m_get_version.set_action(Action::get_version_info);

    return sendAndWaitResp<GetVersionInfoResp>(m_get_version);
}

std::shared_ptr<cqhttp::GetStatusResp> Bot::getStatus()
{
    GetStatus m_get_status;
    m_get_status.set_action(Action::get_status);

    return sendAndWaitResp<GetStatusResp>(m_get_status);
}

std::shared_ptr<cqhttp::DownloadFileResp> Bot::downloadFile(std::string &url, int32_t thread_count, std::string &headers, int64_t time_out)
{
    DownloadFile m_download_file;
    m_download_file.set_action(Action::download_file);
    DownloadFile_Params *params = new DownloadFile_Params;
    params->set_url(url);
    params->set_thread_count(thread_count);
    params->set_headers(headers);
    m_download_file.set_allocated_params(params);

    return sendAndWaitResp<DownloadFileResp>(m_download_file, time_out);
}

std::shared_ptr<cqhttp::CheckUrlSafelyResp> Bot::checkUrlSafely(std::string &url)
{
    CheckUrlSafely m_check;
    m_check.set_action(Action::check_url_safely);
    CheckUrlSafely_Params *params = new CheckUrlSafely_Params;
    params->set_url(url);
    m_check.set_allocated_params(params);

    return sendAndWaitResp<CheckUrlSafelyResp>(m_check);
}

template <typename T1, typename T2>
inline std::shared_ptr<T1> Bot::sendAndWaitResp(T2 &data, int64_t time_out)
{
    time_t echo;
    std::string echo_str = Action_Name(data.action()) + "_" + std::to_string(time(&echo));
    data.set_echo(echo_str);

    std::string message_str;

    if (!MessageToJsonString(data, &message_str, bot_print_options).ok())
        return nullptr;

    bot_mutex.lock();
    this->conn_ptr->send(message_str, drogon::WebSocketMessageType::Text);
    bot_mutex.unlock();
    // LOG(INFO) << message_str;
    auto promise_ptr = std::make_shared<std::promise<std::string>>();
    promise_map->insert({echo_str, promise_ptr});

    auto m_future = promise_ptr->get_future();
    m_future.wait_for(std::chrono::seconds(time_out));
    promise_map->erase(echo_str);

    auto resp_str = m_future.get();
    auto resp_ptr = std::make_shared<T1>();

    if (!JsonStringToMessage(resp_str, resp_ptr.get(), bot_parse_options).ok()){
        LOG(WARN) << "Failed to parse echo to google message.";
        LOG(INFO) << resp_str;
    }

    return resp_ptr;
}

template <typename T>
void Bot::sendOnly(T &data)
{
    std::string message_str;
    if (!MessageToJsonString(data, &message_str, bot_print_options).ok())
    {
        LOG(ERR) << "Failed to handle " << Action_Name(data.action());
        return;
    }
    bot_mutex.lock();
    this->conn_ptr->send(message_str, drogon::WebSocketMessageType::Text);
    bot_mutex.unlock();
}
