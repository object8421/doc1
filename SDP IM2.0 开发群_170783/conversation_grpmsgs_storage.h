/*
 * conversation_grpmsgs_storage.h
 *
 *  Created on: feb 3, 2015
 *      Author: liuyh
 */

#ifndef GROUP_MESSAGING_SERVER_MODULES_CONVERSATION_GRPMSGS_STORAGE_H_
#define GROUP_MESSAGING_SERVER_MODULES_CONVERSATION_GRPMSGS_STORAGE_H_

#include "service_engine/modules.h"
#include <vector>

namespace group_messaging_server
{

class ConversationGrpMsgsStorage
{
public:
    virtual ~ConversationGrpMsgsStorage() = 0;

    DECLARE_INTERFACE(ConversationGrpMsgsStorage);

	struct ConversationPrimaryKey
	{
		const std::string& convid;
		int convtype;
	};

	struct UserConversation
	{
		std::string uid;
		std::string convid;
		int priority;
		long last_msg_id;
		int last_chat_time;
	};

	struct ConversationPolicy
	{
		std::string convid;
		std::string uid;
		int type;
	};

	struct ChatMsg
	{
		struct ConversationPrimaryKey key;
		long msgid;
		std::string sender;
		int status;
		int msg_time;
		int mine_type;
		std::string content;
	};

public:
	
	virtual std::string addConversation(
			const ConversationPrimaryKey& key,
			int tenid, 
			base::ErrorCode* ec = NULL) = 0;

	virtual std::string addConversation(
			const ConversationPrimaryKey& key,
			const sg::rpc::Uri& uri1, 
			int tenid, 
			base::ErrorCode* ec = NULL) = 0;

	virtual bool delConversation(const ConversationPrimaryKey& key,
			base::ErrorCode* ec = NULL) = 0;

	virtual bool addUserConversation(const std::string& uid, 
			const ConversationPrimaryKey& key, 
			int priority, 
			long msgid, 
			int time, 
			base::ErrorCode* ec = NULL) = 0;

	virtual bool delUserConversation(const std::string& uid, 
			const ConversationPrimaryKey& key, 
			base::ErrorCode* ec = NULL) = 0;

	virtual bool queryUserConver(const ConversationPrimaryKey& key,
			std::vector<UserConversation>& ucvec, 
			base::ErrorCode* ec = NULL) = 0;

	virtual bool addConversationPolicy(const ConversationPrimaryKey& key,
			const std::string& uid, 
			ConversationPolicyType type, 
			base::ErrorCode* ec = NULL) = 0;

	virtual bool delConversationPolicy(const ConversationPrimaryKey& key,
			const std::string& uid,
			ConversationPolicyType type, 
			base::ErrorCode* ec = NULL) = 0;

	virtual bool queryConversationPolicy(const ConversationPrimaryKey& key,
			std::vector<ConversationPolicy>& cpvec, 
			base::ErrorCode* ec = NULL) = 0;

	//这个接口会填充msg的msgid
	virtual bool addMsg(ChatMsg& msg, 
			base::ErrorCode* ec = NULL) = 0;

	virtual bool queryMsg(const ConversationPrimaryKey& key,
			std::vector<ChatMsg>& msgvec, 
			long from_msg_id,
			base::ErrorCode* ec = NULL) = 0;
};

inline ConversationGrpMsgsStorage::~ConversationGrpMsgsStorage() {}


} // namespace group_messaging_server


#endif /* GROUP_MESSAGING_SERVER_MODULES_CONVERSATION_GRPMSGS_STORAGE_H_ */
