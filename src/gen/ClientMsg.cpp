#include "Stream.h"
#include "ClientMsg.h"

namespace ClientMsg
{

using namespace Struct;

int __BaseMessage__::Serialize(WriteStream *) const
{
	return 0;
}

int __BaseMessage__::Unserialize(ReadStream *)
{
	return 0;
}

Message::Message()
{
	majorCmd = 0;
	minorCmd = 0;
	type = 0;
}

int Message::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (__BaseMessage__::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->majorCmd)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->minorCmd)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->type)) return -1;
	}

	return 0;
}

int Message::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (__BaseMessage__::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->majorCmd)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->minorCmd)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->type)) return -1;
	}

	return 0;
}

LoginCommand::LoginCommand()
{
	this->majorCmd = MAJOR_CMD;
}

int LoginCommand::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (Message::Serialize(writeStream) != 0) return -1;

	return 0;
}

int LoginCommand::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (Message::Unserialize(readStream) != 0) return -1;

	return 0;
}

MapCommand::MapCommand()
{
	this->majorCmd = MAJOR_CMD;
}

int MapCommand::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (Message::Serialize(writeStream) != 0) return -1;

	return 0;
}

int MapCommand::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (Message::Unserialize(readStream) != 0) return -1;

	return 0;
}

FightCommand::FightCommand()
{
	this->majorCmd = MAJOR_CMD;
}

int FightCommand::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (Message::Serialize(writeStream) != 0) return -1;

	return 0;
}

int FightCommand::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (Message::Unserialize(readStream) != 0) return -1;

	return 0;
}

PlayerInfoCommand::PlayerInfoCommand()
{
	this->majorCmd = MAJOR_CMD;
}

int PlayerInfoCommand::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (Message::Serialize(writeStream) != 0) return -1;

	return 0;
}

int PlayerInfoCommand::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (Message::Unserialize(readStream) != 0) return -1;

	return 0;
}

ChatMessageCommand::ChatMessageCommand()
{
	this->majorCmd = MAJOR_CMD;
}

int ChatMessageCommand::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (Message::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ChatMessageCommand::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (Message::Unserialize(readStream) != 0) return -1;

	return 0;
}

WorldMessageCommand::WorldMessageCommand()
{
	this->majorCmd = MAJOR_CMD;
}

int WorldMessageCommand::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (Message::Serialize(writeStream) != 0) return -1;

	return 0;
}

int WorldMessageCommand::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (Message::Unserialize(readStream) != 0) return -1;

	return 0;
}

FriendMessageCommand::FriendMessageCommand()
{
	this->majorCmd = MAJOR_CMD;
}

int FriendMessageCommand::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (Message::Serialize(writeStream) != 0) return -1;

	return 0;
}

int FriendMessageCommand::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (Message::Unserialize(readStream) != 0) return -1;

	return 0;
}

ClientExInfoMessageCommand::ClientExInfoMessageCommand()
{
	this->majorCmd = MAJOR_CMD;
}

int ClientExInfoMessageCommand::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (Message::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ClientExInfoMessageCommand::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (Message::Unserialize(readStream) != 0) return -1;

	return 0;
}

RegistAccountReq::RegistAccountReq()
{
	this->minorCmd = MINOR_CMD;
	sdkType = 0;
}

int RegistAccountReq::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (LoginCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->account.c_str(), this->account.size())) return -1;
	}
	{
		if (!writeStream->Write(this->passwd.c_str(), this->passwd.size())) return -1;
	}
	{
		if (!writeStream->Write(this->model.c_str(), this->model.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->sdkType)) return -1;
	}
	{
		if (!writeStream->Write(this->mac.c_str(), this->mac.size())) return -1;
	}
	{
		if (!writeStream->Write(this->platfrom.c_str(), this->platfrom.size())) return -1;
	}

	return 0;
}

int RegistAccountReq::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (LoginCommand::Unserialize(readStream) != 0) return -1;
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->account.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->passwd.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->model.assign(p, len);
	}
	{
		if (!readStream->Read((int32_t&)this->sdkType)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->mac.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->platfrom.assign(p, len);
	}

	return 0;
}

RegistAccountRes::RegistAccountRes()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int RegistAccountRes::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (LoginCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write(this->account.c_str(), this->account.size())) return -1;
	}

	return 0;
}

int RegistAccountRes::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (LoginCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->account.assign(p, len);
	}

	return 0;
}

LoginSessionReq::LoginSessionReq()
{
	this->minorCmd = MINOR_CMD;
	sdkType = 0;
	vistor = 0;
}

int LoginSessionReq::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (LoginCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->openid.c_str(), this->openid.size())) return -1;
	}
	{
		if (!writeStream->Write(this->openkey.c_str(), this->openkey.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->sdkType)) return -1;
	}
	{
		if (!writeStream->Write(this->mac.c_str(), this->mac.size())) return -1;
	}
	{
		if (!writeStream->Write(this->model.c_str(), this->model.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->vistor)) return -1;
	}
	{
		if (!writeStream->Write(this->platfrom.c_str(), this->platfrom.size())) return -1;
	}

	return 0;
}

int LoginSessionReq::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (LoginCommand::Unserialize(readStream) != 0) return -1;
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->openid.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->openkey.assign(p, len);
	}
	{
		if (!readStream->Read((int32_t&)this->sdkType)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->mac.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->model.assign(p, len);
	}
	{
		if (!readStream->Read((int32_t&)this->vistor)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->platfrom.assign(p, len);
	}

	return 0;
}

LoginSessionAccountRes::LoginSessionAccountRes()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	commonServerID = 0;
	accountId = 0;
}

int LoginSessionAccountRes::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (LoginCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write(this->session.c_str(), this->session.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->data.size())) return -1;
		for (std::vector< Struct::ServerInfo >::const_iterator it=this->data.begin(); it!=this->data.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->commonServerID)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->roleServerID.size())) return -1;
		for (std::vector< uint32_t >::const_iterator it=this->roleServerID.begin(); it!=this->roleServerID.end(); ++it) {
			if (!writeStream->Write((int32_t)(*it))) return -1;
		}
	}
	{
		if (!writeStream->Write(this->account.c_str(), this->account.size())) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->accountId)) return -1;
	}

	return 0;
}

int LoginSessionAccountRes::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (LoginCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->session.assign(p, len);
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->data.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			Struct::ServerInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->data.push_back(__inner__);
		}
	}
	{
		if (!readStream->Read((int32_t&)this->commonServerID)) return -1;
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->roleServerID.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			uint32_t __inner__;
			{
				if (!readStream->Read((int32_t&)__inner__)) return -1;
			}
			this->roleServerID.push_back(__inner__);
		}
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->account.assign(p, len);
	}
	{
		if (!readStream->Read((int64_t&)this->accountId)) return -1;
	}

	return 0;
}

SelectServerReq::SelectServerReq()
{
	this->minorCmd = MINOR_CMD;
	gameServerID = 0;
}

int SelectServerReq::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (LoginCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->account.c_str(), this->account.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->gameServerID)) return -1;
	}

	return 0;
}

int SelectServerReq::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (LoginCommand::Unserialize(readStream) != 0) return -1;
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->account.assign(p, len);
	}
	{
		if (!readStream->Read((int32_t&)this->gameServerID)) return -1;
	}

	return 0;
}

SelectServerRes::SelectServerRes()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int SelectServerRes::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (LoginCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (this->gateServerInfo.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write(this->session.c_str(), this->session.size())) return -1;
	}

	return 0;
}

int SelectServerRes::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (LoginCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (this->gateServerInfo.Unserialize(readStream) != 0) return -1;	
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->session.assign(p, len);
	}

	return 0;
}

SelectLogicReq::SelectLogicReq()
{
	this->minorCmd = MINOR_CMD;
}

int SelectLogicReq::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (LoginCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->account.c_str(), this->account.size())) return -1;
	}
	{
		if (!writeStream->Write(this->session.c_str(), this->session.size())) return -1;
	}

	return 0;
}

int SelectLogicReq::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (LoginCommand::Unserialize(readStream) != 0) return -1;
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->account.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->session.assign(p, len);
	}

	return 0;
}

SelectLogicRes::SelectLogicRes()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	updateDelayTime = 0;
}

int SelectLogicRes::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (LoginCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (this->playerInfo.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->roleInfo.size())) return -1;
		for (std::vector< Struct::RoleSimpleInfo >::const_iterator it=this->roleInfo.begin(); it!=this->roleInfo.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (this->chatServerInfo.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write(this->serverName.c_str(), this->serverName.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->updateDelayTime)) return -1;
	}

	return 0;
}

int SelectLogicRes::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (LoginCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (this->playerInfo.Unserialize(readStream) != 0) return -1;	
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->roleInfo.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			Struct::RoleSimpleInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->roleInfo.push_back(__inner__);
		}
	}
	{
		if (this->chatServerInfo.Unserialize(readStream) != 0) return -1;	
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->serverName.assign(p, len);
	}
	{
		if (!readStream->Read((int32_t&)this->updateDelayTime)) return -1;
	}

	return 0;
}

CreateRoleReq::CreateRoleReq()
{
	this->minorCmd = MINOR_CMD;
	jobId = 0;
	sex = 0;
	shape = 0;
}

int CreateRoleReq::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (LoginCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->name.c_str(), this->name.size())) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->jobId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->sex)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->shape)) return -1;
	}

	return 0;
}

int CreateRoleReq::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (LoginCommand::Unserialize(readStream) != 0) return -1;
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->name.assign(p, len);
	}
	{
		if (!readStream->Read((int64_t&)this->jobId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->sex)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->shape)) return -1;
	}

	return 0;
}

CreateRoleRes::CreateRoleRes()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int CreateRoleRes::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (LoginCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (this->playerInfo.Serialize(writeStream) != 0) return -1;
	}
	{
		if (this->roleInfo.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int CreateRoleRes::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (LoginCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (this->playerInfo.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (this->roleInfo.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

SessionOverSync::SessionOverSync()
{
	this->minorCmd = MINOR_CMD;
}

int SessionOverSync::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (LoginCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int SessionOverSync::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (LoginCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

ServerHreatSync::ServerHreatSync()
{
	this->minorCmd = MINOR_CMD;
	time = 0;
	uid = 0;
}

int ServerHreatSync::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (LoginCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int64_t)this->time)) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->uid)) return -1;
	}

	return 0;
}

int ServerHreatSync::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (LoginCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int64_t&)this->time)) return -1;
	}
	{
		if (!readStream->Read((int64_t&)this->uid)) return -1;
	}

	return 0;
}

ServerHreatRes::ServerHreatRes()
{
	this->minorCmd = MINOR_CMD;
	time = 0;
	uid = 0;
}

int ServerHreatRes::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (LoginCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int64_t)this->time)) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->uid)) return -1;
	}

	return 0;
}

int ServerHreatRes::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (LoginCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int64_t&)this->time)) return -1;
	}
	{
		if (!readStream->Read((int64_t&)this->uid)) return -1;
	}

	return 0;
}

PackageCodeReq::PackageCodeReq()
{
	this->minorCmd = MINOR_CMD;
}

int PackageCodeReq::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (LoginCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->code.c_str(), this->code.size())) return -1;
	}

	return 0;
}

int PackageCodeReq::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (LoginCommand::Unserialize(readStream) != 0) return -1;
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->code.assign(p, len);
	}

	return 0;
}

PackageCodeRes::PackageCodeRes()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int PackageCodeRes::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (LoginCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int PackageCodeRes::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (LoginCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

EnterWorldReq::EnterWorldReq()
{
	this->minorCmd = MINOR_CMD;
	roleId = 0;
}

int EnterWorldReq::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (LoginCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int64_t)this->roleId)) return -1;
	}

	return 0;
}

int EnterWorldReq::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (LoginCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int64_t&)this->roleId)) return -1;
	}

	return 0;
}

EnterWorldRes::EnterWorldRes()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int EnterWorldRes::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (LoginCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (this->roleInfo.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int EnterWorldRes::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (LoginCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (this->roleInfo.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

DeleteRoleReq::DeleteRoleReq()
{
	this->minorCmd = MINOR_CMD;
	roleId = 0;
}

int DeleteRoleReq::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (LoginCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->account.c_str(), this->account.size())) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->roleId)) return -1;
	}

	return 0;
}

int DeleteRoleReq::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (LoginCommand::Unserialize(readStream) != 0) return -1;
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->account.assign(p, len);
	}
	{
		if (!readStream->Read((int64_t&)this->roleId)) return -1;
	}

	return 0;
}

DeleteRoleRes::DeleteRoleRes()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	roleId = 0;
}

int DeleteRoleRes::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (LoginCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->roleId)) return -1;
	}

	return 0;
}

int DeleteRoleRes::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (LoginCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int64_t&)this->roleId)) return -1;
	}

	return 0;
}

KickPlayerNotify::KickPlayerNotify()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int KickPlayerNotify::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (LoginCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int KickPlayerNotify::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (LoginCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

EnterMapReq::EnterMapReq()
{
	this->minorCmd = MINOR_CMD;
}

int EnterMapReq::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int EnterMapReq::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

EnterMapRes::EnterMapRes()
{
	this->minorCmd = MINOR_CMD;
	sceneId = 0;
	mapId = 0;
	ret = 0;
}

int EnterMapRes::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->pos.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->sceneId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->mapId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (this->server.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int EnterMapRes::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->pos.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->sceneId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->mapId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (this->server.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

EnterMapNotify::EnterMapNotify()
{
	this->minorCmd = MINOR_CMD;
}

int EnterMapNotify::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->players.size())) return -1;
		for (std::vector< Struct::FighterCompleteInfo >::const_iterator it=this->players.begin(); it!=this->players.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int EnterMapNotify::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->players.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			Struct::FighterCompleteInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->players.push_back(__inner__);
		}
	}

	return 0;
}

MoveReq::MoveReq()
{
	this->minorCmd = MINOR_CMD;
}

int MoveReq::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->pos.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int MoveReq::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->pos.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

MoveRes::MoveRes()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int MoveRes::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->pos.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int MoveRes::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->pos.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

MoveNotify::MoveNotify()
{
	this->minorCmd = MINOR_CMD;
}

int MoveNotify::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->msgs.size())) return -1;
		for (std::vector< Struct::FighterBaseInfo >::const_iterator it=this->msgs.begin(); it!=this->msgs.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int MoveNotify::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->msgs.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			Struct::FighterBaseInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->msgs.push_back(__inner__);
		}
	}

	return 0;
}

DoHurtTestReq::DoHurtTestReq()
{
	this->minorCmd = MINOR_CMD;
	hurt = 0;
}

int DoHurtTestReq::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->target.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->hurt)) return -1;
	}

	return 0;
}

int DoHurtTestReq::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->target.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int64_t&)this->hurt)) return -1;
	}

	return 0;
}

DoHurtTestRes::DoHurtTestRes()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	hurt = 0;
}

int DoHurtTestRes::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (this->target.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->hurt)) return -1;
	}

	return 0;
}

int DoHurtTestRes::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (this->target.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int64_t&)this->hurt)) return -1;
	}

	return 0;
}

DoHurtTestNotify::DoHurtTestNotify()
{
	this->minorCmd = MINOR_CMD;
	hurt = 0;
}

int DoHurtTestNotify::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->figher.Serialize(writeStream) != 0) return -1;
	}
	{
		if (this->target.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->hurt)) return -1;
	}

	return 0;
}

int DoHurtTestNotify::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->figher.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (this->target.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int64_t&)this->hurt)) return -1;
	}

	return 0;
}

DoActionReq::DoActionReq()
{
	this->minorCmd = MINOR_CMD;
	action = 0;
	undo = 0;
}

int DoActionReq::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->target.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->action)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->undo)) return -1;
	}

	return 0;
}

int DoActionReq::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->target.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->action)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->undo)) return -1;
	}

	return 0;
}

DoActionRes::DoActionRes()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	action = 0;
	undo = 0;
}

int DoActionRes::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (this->target.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->action)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->undo)) return -1;
	}

	return 0;
}

int DoActionRes::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (this->target.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->action)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->undo)) return -1;
	}

	return 0;
}

DoActionNotify::DoActionNotify()
{
	this->minorCmd = MINOR_CMD;
	action = 0;
	undo = 0;
}

int DoActionNotify::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->figher.Serialize(writeStream) != 0) return -1;
	}
	{
		if (this->target.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->action)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->undo)) return -1;
	}

	return 0;
}

int DoActionNotify::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->figher.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (this->target.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->action)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->undo)) return -1;
	}

	return 0;
}

LeaveMapNotify::LeaveMapNotify()
{
	this->minorCmd = MINOR_CMD;
}

int LeaveMapNotify::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->charactors.size())) return -1;
		for (std::vector< Struct::FighterBaseInfo >::const_iterator it=this->charactors.begin(); it!=this->charactors.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int LeaveMapNotify::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->charactors.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			Struct::FighterBaseInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->charactors.push_back(__inner__);
		}
	}

	return 0;
}

EnterDungeonReq::EnterDungeonReq()
{
	this->minorCmd = MINOR_CMD;
	playerUid = 0;
	dungeonUid = 0;
}

int EnterDungeonReq::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int64_t)this->playerUid)) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->dungeonUid)) return -1;
	}

	return 0;
}

int EnterDungeonReq::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int64_t&)this->playerUid)) return -1;
	}
	{
		if (!readStream->Read((int64_t&)this->dungeonUid)) return -1;
	}

	return 0;
}

EnterDungeonRes::EnterDungeonRes()
{
	this->minorCmd = MINOR_CMD;
	dungeonId = 0;
	mapId = 0;
	ret = 0;
}

int EnterDungeonRes::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->fighter.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->dungeonId)) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->mapId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int EnterDungeonRes::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->fighter.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int64_t&)this->dungeonId)) return -1;
	}
	{
		if (!readStream->Read((int64_t&)this->mapId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

LeaveMapRes::LeaveMapRes()
{
	this->minorCmd = MINOR_CMD;
}

int LeaveMapRes::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int LeaveMapRes::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

LeaveDungeonReq::LeaveDungeonReq()
{
	this->minorCmd = MINOR_CMD;
}

int LeaveDungeonReq::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int LeaveDungeonReq::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

LeaveDungeonRes::LeaveDungeonRes()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int LeaveDungeonRes::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int LeaveDungeonRes::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

KillNpcReq::KillNpcReq()
{
	this->minorCmd = MINOR_CMD;
	id = 0;
}

int KillNpcReq::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int64_t)this->id)) return -1;
	}

	return 0;
}

int KillNpcReq::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int64_t&)this->id)) return -1;
	}

	return 0;
}

DungeonEndNotify::DungeonEndNotify()
{
	this->minorCmd = MINOR_CMD;
}

int DungeonEndNotify::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int DungeonEndNotify::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

EnterLandNotify::EnterLandNotify()
{
	this->minorCmd = MINOR_CMD;
	mapId = 0;
}

int EnterLandNotify::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->fighter.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->mapId)) return -1;
	}

	return 0;
}

int EnterLandNotify::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->fighter.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int64_t&)this->mapId)) return -1;
	}

	return 0;
}

EnterFinish::EnterFinish()
{
	this->minorCmd = MINOR_CMD;
}

int EnterFinish::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int EnterFinish::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

FightTestReq::FightTestReq()
{
	this->minorCmd = MINOR_CMD;
}

int FightTestReq::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FightCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int FightTestReq::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FightCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

FightErrorNotify::FightErrorNotify()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int FightErrorNotify::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FightCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int FightErrorNotify::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FightCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

CastSkillReq::CastSkillReq()
{
	this->minorCmd = MINOR_CMD;
	skillId = 0;
	actionId = 0;
}

int CastSkillReq::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FightCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->skillId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->actionId)) return -1;
	}
	{
		if (this->targetPos.Serialize(writeStream) != 0) return -1;
	}
	{
		if (this->caster.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int CastSkillReq::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FightCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->skillId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->actionId)) return -1;
	}
	{
		if (this->targetPos.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (this->caster.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

CastSkillRes::CastSkillRes()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	skillId = 0;
	actionId = 0;
}

int CastSkillRes::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FightCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->skillId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->actionId)) return -1;
	}
	{
		if (this->targetPos.Serialize(writeStream) != 0) return -1;
	}
	{
		if (this->caster.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int CastSkillRes::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FightCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->skillId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->actionId)) return -1;
	}
	{
		if (this->targetPos.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (this->caster.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

CastSkilNotify::CastSkilNotify()
{
	this->minorCmd = MINOR_CMD;
	skillId = 0;
	actionId = 0;
}

int CastSkilNotify::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FightCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->caster.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->skillId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->actionId)) return -1;
	}
	{
		if (this->targetPos.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int CastSkilNotify::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FightCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->caster.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->skillId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->actionId)) return -1;
	}
	{
		if (this->targetPos.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

DoHurtNotify::DoHurtNotify()
{
	this->minorCmd = MINOR_CMD;
	skillId = 0;
	actionId = 0;
	hurt = 0;
}

int DoHurtNotify::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FightCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->caster.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->skillId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->actionId)) return -1;
	}
	{
		if (this->target.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((double)this->hurt)) return -1;
	}

	return 0;
}

int DoHurtNotify::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FightCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->caster.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->skillId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->actionId)) return -1;
	}
	{
		if (this->target.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((double&)this->hurt)) return -1;
	}

	return 0;
}

DoHitNotify::DoHitNotify()
{
	this->minorCmd = MINOR_CMD;
	skillId = 0;
	actionId = 0;
	index = 0;
	triggerEffectId = 0;
}

int DoHitNotify::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FightCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->caster.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->skillId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->actionId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->target.size())) return -1;
		for (std::vector< Struct::FighterBaseInfo >::const_iterator it=this->target.begin(); it!=this->target.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->index)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->triggerEffectId)) return -1;
	}

	return 0;
}

int DoHitNotify::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FightCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->caster.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->skillId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->actionId)) return -1;
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->target.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			Struct::FighterBaseInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->target.push_back(__inner__);
		}
	}
	{
		if (!readStream->Read((int32_t&)this->index)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->triggerEffectId)) return -1;
	}

	return 0;
}

SkillEndNotify::SkillEndNotify()
{
	this->minorCmd = MINOR_CMD;
	skillId = 0;
	actionId = 0;
}

int SkillEndNotify::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FightCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->caster.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->skillId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->actionId)) return -1;
	}

	return 0;
}

int SkillEndNotify::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FightCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->caster.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->skillId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->actionId)) return -1;
	}

	return 0;
}

AddBuffNotify::AddBuffNotify()
{
	this->minorCmd = MINOR_CMD;
}

int AddBuffNotify::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FightCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->buff.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int AddBuffNotify::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FightCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->buff.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

EndBuffNotify::EndBuffNotify()
{
	this->minorCmd = MINOR_CMD;
}

int EndBuffNotify::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FightCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->buff.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int EndBuffNotify::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FightCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->buff.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

ReviveReq::ReviveReq()
{
	this->minorCmd = MINOR_CMD;
}

int ReviveReq::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FightCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ReviveReq::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FightCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

ReviveRes::ReviveRes()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ReviveRes::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FightCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ReviveRes::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FightCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

FightInfoNotify::FightInfoNotify()
{
	this->minorCmd = MINOR_CMD;
	status = 0;
}

int FightInfoNotify::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FightCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->fighter.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->status)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->curAttr.size())) return -1;
		for (std::vector< uint64_t >::const_iterator it=this->curAttr.begin(); it!=this->curAttr.end(); ++it) {
			if (!writeStream->Write((int64_t)(*it))) return -1;
		}
	}

	return 0;
}

int FightInfoNotify::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FightCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->fighter.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int64_t&)this->status)) return -1;
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->curAttr.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			uint64_t __inner__;
			{
				if (!readStream->Read((int64_t&)__inner__)) return -1;
			}
			this->curAttr.push_back(__inner__);
		}
	}

	return 0;
}

AttrChangeNotify::AttrChangeNotify()
{
	this->minorCmd = MINOR_CMD;
	status = 0;
}

int AttrChangeNotify::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FightCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->fighter.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->status)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->curAttr.size())) return -1;
		for (std::vector< Struct::AttrInfo >::const_iterator it=this->curAttr.begin(); it!=this->curAttr.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int AttrChangeNotify::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FightCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->fighter.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int64_t&)this->status)) return -1;
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->curAttr.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			Struct::AttrInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->curAttr.push_back(__inner__);
		}
	}

	return 0;
}

CreateEffectObjectNotify::CreateEffectObjectNotify()
{
	this->minorCmd = MINOR_CMD;
	skillId = 0;
	actionId = 0;
	longDisId = 0;
}

int CreateEffectObjectNotify::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FightCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->caster.Serialize(writeStream) != 0) return -1;
	}
	{
		if (this->effectObject.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->skillId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->actionId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->longDisId)) return -1;
	}

	return 0;
}

int CreateEffectObjectNotify::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FightCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->caster.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (this->effectObject.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->skillId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->actionId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->longDisId)) return -1;
	}

	return 0;
}

RemoveEffectObjectNotify::RemoveEffectObjectNotify()
{
	this->minorCmd = MINOR_CMD;
}

int RemoveEffectObjectNotify::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FightCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->effectObject.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int RemoveEffectObjectNotify::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FightCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->effectObject.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

NewMailNotify::NewMailNotify()
{
	this->minorCmd = MINOR_CMD;
	count = 0;
}

int NewMailNotify::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->count)) return -1;
	}

	return 0;
}

int NewMailNotify::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->count)) return -1;
	}

	return 0;
}

SendMailReq::SendMailReq()
{
	this->minorCmd = MINOR_CMD;
}

int SendMailReq::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int SendMailReq::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

SendMailRes::SendMailRes()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int SendMailRes::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int SendMailRes::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

RecvMailReq::RecvMailReq()
{
	this->minorCmd = MINOR_CMD;
	mailid = 0;
}

int RecvMailReq::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->mailid)) return -1;
	}

	return 0;
}

int RecvMailReq::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->mailid)) return -1;
	}

	return 0;
}

RecvMailRes::RecvMailRes()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int RecvMailRes::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->mails.size())) return -1;
		for (std::vector< uint32_t >::const_iterator it=this->mails.begin(); it!=this->mails.end(); ++it) {
			if (!writeStream->Write((int32_t)(*it))) return -1;
		}
	}

	return 0;
}

int RecvMailRes::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->mails.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			uint32_t __inner__;
			{
				if (!readStream->Read((int32_t&)__inner__)) return -1;
			}
			this->mails.push_back(__inner__);
		}
	}

	return 0;
}

GetMailListReq::GetMailListReq()
{
	this->minorCmd = MINOR_CMD;
	page = 0;
}

int GetMailListReq::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->page)) return -1;
	}

	return 0;
}

int GetMailListReq::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->page)) return -1;
	}

	return 0;
}

GetMailListRes::GetMailListRes()
{
	this->minorCmd = MINOR_CMD;
	page = 0;
}

int GetMailListRes::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->page)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->mails.size())) return -1;
		for (std::vector< Struct::MailInfo >::const_iterator it=this->mails.begin(); it!=this->mails.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int GetMailListRes::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->page)) return -1;
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->mails.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			Struct::MailInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->mails.push_back(__inner__);
		}
	}

	return 0;
}

NotifyQuestInfo::NotifyQuestInfo()
{
	this->minorCmd = MINOR_CMD;
}

int NotifyQuestInfo::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->normals.size())) return -1;
		for (std::vector< Struct::QuestInfo >::const_iterator it=this->normals.begin(); it!=this->normals.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->days.size())) return -1;
		for (std::vector< Struct::QuestInfo >::const_iterator it=this->days.begin(); it!=this->days.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->canAccepts.size())) return -1;
		for (std::vector< uint64_t >::const_iterator it=this->canAccepts.begin(); it!=this->canAccepts.end(); ++it) {
			if (!writeStream->Write((int64_t)(*it))) return -1;
		}
	}

	return 0;
}

int NotifyQuestInfo::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->normals.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			Struct::QuestInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->normals.push_back(__inner__);
		}
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->days.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			Struct::QuestInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->days.push_back(__inner__);
		}
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->canAccepts.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			uint64_t __inner__;
			{
				if (!readStream->Read((int64_t&)__inner__)) return -1;
			}
			this->canAccepts.push_back(__inner__);
		}
	}

	return 0;
}

NotifyQuestChangeInfo::NotifyQuestChangeInfo()
{
	this->minorCmd = MINOR_CMD;
}

int NotifyQuestChangeInfo::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->info.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int NotifyQuestChangeInfo::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->info.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

QuestReceiveReq::QuestReceiveReq()
{
	this->minorCmd = MINOR_CMD;
	id = 0;
}

int QuestReceiveReq::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int64_t)this->id)) return -1;
	}

	return 0;
}

int QuestReceiveReq::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int64_t&)this->id)) return -1;
	}

	return 0;
}

CommonErrorNotify::CommonErrorNotify()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int CommonErrorNotify::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int CommonErrorNotify::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

ClientNotifyCmpQuestReq::ClientNotifyCmpQuestReq()
{
	this->minorCmd = MINOR_CMD;
	id = 0;
}

int ClientNotifyCmpQuestReq::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int64_t)this->id)) return -1;
	}

	return 0;
}

int ClientNotifyCmpQuestReq::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int64_t&)this->id)) return -1;
	}

	return 0;
}

NotifyLevelInfo::NotifyLevelInfo()
{
	this->minorCmd = MINOR_CMD;
	level = 0;
}

int NotifyLevelInfo::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->level)) return -1;
	}

	return 0;
}

int NotifyLevelInfo::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->level)) return -1;
	}

	return 0;
}

ChatMessageReq::ChatMessageReq()
{
	this->minorCmd = MINOR_CMD;
	vipLevel = 0;
}

int ChatMessageReq::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (ChatMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->str.c_str(), this->str.size())) return -1;
	}
	{
		if (!writeStream->Write(this->channeltype.c_str(), this->channeltype.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->vipLevel)) return -1;
	}
	{
		if (!writeStream->Write(this->playerName.c_str(), this->playerName.size())) return -1;
	}

	return 0;
}

int ChatMessageReq::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (ChatMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->str.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->channeltype.assign(p, len);
	}
	{
		if (!readStream->Read((int32_t&)this->vipLevel)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->playerName.assign(p, len);
	}

	return 0;
}

ChatMessageRes::ChatMessageRes()
{
	this->minorCmd = MINOR_CMD;
	vipLevel = 0;
}

int ChatMessageRes::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (ChatMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->str.c_str(), this->str.size())) return -1;
	}
	{
		if (!writeStream->Write(this->channeltype.c_str(), this->channeltype.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->vipLevel)) return -1;
	}
	{
		if (!writeStream->Write(this->playerName.c_str(), this->playerName.size())) return -1;
	}

	return 0;
}

int ChatMessageRes::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (ChatMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->str.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->channeltype.assign(p, len);
	}
	{
		if (!readStream->Read((int32_t&)this->vipLevel)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->playerName.assign(p, len);
	}

	return 0;
}

RegisterChannelReq::RegisterChannelReq()
{
	this->minorCmd = MINOR_CMD;
}

int RegisterChannelReq::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (ChatMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->channeltype.size())) return -1;
		for (std::vector< std::string >::const_iterator it=this->channeltype.begin(); it!=this->channeltype.end(); ++it) {
			if (!writeStream->Write((*it).c_str(), (*it).size())) return -1;
		}
	}

	return 0;
}

int RegisterChannelReq::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (ChatMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->channeltype.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			std::string __inner__;
			{
				const char* p;
				size_t len;
				if (!readStream->ReadNoCopy(p, len)) return -1;
				__inner__.assign(p, len);
			}
			this->channeltype.push_back(__inner__);
		}
	}

	return 0;
}

RegisterChannelRes::RegisterChannelRes()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int RegisterChannelRes::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (ChatMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->channeltype.size())) return -1;
		for (std::vector< std::string >::const_iterator it=this->channeltype.begin(); it!=this->channeltype.end(); ++it) {
			if (!writeStream->Write((*it).c_str(), (*it).size())) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int RegisterChannelRes::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (ChatMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->channeltype.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			std::string __inner__;
			{
				const char* p;
				size_t len;
				if (!readStream->ReadNoCopy(p, len)) return -1;
				__inner__.assign(p, len);
			}
			this->channeltype.push_back(__inner__);
		}
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

GMCMDReq::GMCMDReq()
{
	this->minorCmd = MINOR_CMD;
}

int GMCMDReq::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (ChatMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->str.c_str(), this->str.size())) return -1;
	}

	return 0;
}

int GMCMDReq::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (ChatMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->str.assign(p, len);
	}

	return 0;
}

GMCMDRes::GMCMDRes()
{
	this->minorCmd = MINOR_CMD;
}

int GMCMDRes::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (ChatMessageCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int GMCMDRes::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (ChatMessageCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

ChaterInfoReq::ChaterInfoReq()
{
	this->minorCmd = MINOR_CMD;
}

int ChaterInfoReq::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (ChatMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->chaterName.c_str(), this->chaterName.size())) return -1;
	}

	return 0;
}

int ChaterInfoReq::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (ChatMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->chaterName.assign(p, len);
	}

	return 0;
}

ChaterInfoRes::ChaterInfoRes()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	level = 0;
	playerId = 0;
	vipLevel = 0;
	photoId = 0;
}

int ChaterInfoRes::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (ChatMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write(this->chaterName.c_str(), this->chaterName.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->level)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->playerId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->vipLevel)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->photoId)) return -1;
	}

	return 0;
}

int ChaterInfoRes::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (ChatMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->chaterName.assign(p, len);
	}
	{
		if (!readStream->Read((int32_t&)this->level)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->playerId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->vipLevel)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->photoId)) return -1;
	}

	return 0;
}

PMReq::PMReq()
{
	this->minorCmd = MINOR_CMD;
	playerId = 0;
}

int PMReq::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (ChatMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->playerId)) return -1;
	}
	{
		if (!writeStream->Write(this->chatMessage.c_str(), this->chatMessage.size())) return -1;
	}

	return 0;
}

int PMReq::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (ChatMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->playerId)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->chatMessage.assign(p, len);
	}

	return 0;
}

PMRes::PMRes()
{
	this->minorCmd = MINOR_CMD;
	playerId = 0;
}

int PMRes::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (ChatMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->playerId)) return -1;
	}
	{
		if (!writeStream->Write(this->chatMessage.c_str(), this->chatMessage.size())) return -1;
	}
	{
		if (!writeStream->Write(this->chaterName.c_str(), this->chaterName.size())) return -1;
	}

	return 0;
}

int PMRes::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (ChatMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->playerId)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->chatMessage.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->chaterName.assign(p, len);
	}

	return 0;
}

WorldOldMessageReq::WorldOldMessageReq()
{
	this->minorCmd = MINOR_CMD;
}

int WorldOldMessageReq::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (ChatMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->channeltype.c_str(), this->channeltype.size())) return -1;
	}

	return 0;
}

int WorldOldMessageReq::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (ChatMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->channeltype.assign(p, len);
	}

	return 0;
}

WorldOldMessageRes::WorldOldMessageRes()
{
	this->minorCmd = MINOR_CMD;
}

int WorldOldMessageRes::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (ChatMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->chatMessage.size())) return -1;
		for (std::vector< std::string >::const_iterator it=this->chatMessage.begin(); it!=this->chatMessage.end(); ++it) {
			if (!writeStream->Write((*it).c_str(), (*it).size())) return -1;
		}
	}
	{
		if (!writeStream->Write(this->channeltype.c_str(), this->channeltype.size())) return -1;
	}

	return 0;
}

int WorldOldMessageRes::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (ChatMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->chatMessage.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			std::string __inner__;
			{
				const char* p;
				size_t len;
				if (!readStream->ReadNoCopy(p, len)) return -1;
				__inner__.assign(p, len);
			}
			this->chatMessage.push_back(__inner__);
		}
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->channeltype.assign(p, len);
	}

	return 0;
}

UnRegisterChannelReq::UnRegisterChannelReq()
{
	this->minorCmd = MINOR_CMD;
}

int UnRegisterChannelReq::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (ChatMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->channeltype.c_str(), this->channeltype.size())) return -1;
	}

	return 0;
}

int UnRegisterChannelReq::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (ChatMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->channeltype.assign(p, len);
	}

	return 0;
}

UnRegisterChannelRes::UnRegisterChannelRes()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int UnRegisterChannelRes::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (ChatMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int UnRegisterChannelRes::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (ChatMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

WorldTestReq::WorldTestReq()
{
	this->minorCmd = MINOR_CMD;
}

int WorldTestReq::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int WorldTestReq::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

WorldTestRes::WorldTestRes()
{
	this->minorCmd = MINOR_CMD;
}

int WorldTestRes::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int WorldTestRes::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

WorldMatchReq::WorldMatchReq()
{
	this->minorCmd = MINOR_CMD;
	type = 0;
}

int WorldMatchReq::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->type)) return -1;
	}

	return 0;
}

int WorldMatchReq::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->type)) return -1;
	}

	return 0;
}

WorldMatchRes::WorldMatchRes()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int WorldMatchRes::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (this->dungeonBaseInfo.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int WorldMatchRes::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (this->dungeonBaseInfo.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

FriendTestReq::FriendTestReq()
{
	this->minorCmd = MINOR_CMD;
}

int FriendTestReq::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int FriendTestReq::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

FriendTestRes::FriendTestRes()
{
	this->minorCmd = MINOR_CMD;
}

int FriendTestRes::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int FriendTestRes::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

ClientErrorMsgNotify::ClientErrorMsgNotify()
{
	this->minorCmd = MINOR_CMD;
}

int ClientErrorMsgNotify::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (ClientExInfoMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->errorInfo.c_str(), this->errorInfo.size())) return -1;
	}

	return 0;
}

int ClientErrorMsgNotify::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (ClientExInfoMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->errorInfo.assign(p, len);
	}

	return 0;
}

};

