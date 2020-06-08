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

::()
{
	majorCmd = 0;
	minorCmd = 0;
	type = 0;
}

int ::Serialize(WriteStream * writeStream) const
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

int ::Unserialize(ReadStream * readStream)
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

::()
{
	this->majorCmd = MAJOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (Message::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (Message::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->majorCmd = MAJOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (Message::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (Message::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->majorCmd = MAJOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (Message::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (Message::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->majorCmd = MAJOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (Message::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (Message::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->majorCmd = MAJOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (Message::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (Message::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->majorCmd = MAJOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (Message::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (Message::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->majorCmd = MAJOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (Message::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (Message::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->majorCmd = MAJOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (Message::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (Message::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->majorCmd = MAJOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (Message::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (Message::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->majorCmd = MAJOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (Message::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (Message::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
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

	return 0;
}

int ::Unserialize(ReadStream * readStream)
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

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (LoginCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (LoginCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	sdkType = 0;
}

int ::Serialize(WriteStream * writeStream) const
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
		if (!writeStream->Write(this->mac.c_str(), this->mac.size())) return -1;
	}
	{
		if (!writeStream->Write(this->model.c_str(), this->model.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->sdkType)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
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
		this->mac.assign(p, len);
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

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	sdkType = 0;
}

int ::Serialize(WriteStream * writeStream) const
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

	return 0;
}

int ::Unserialize(ReadStream * readStream)
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

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	commonServerID = 0;
	accountId = 0;
}

int ::Serialize(WriteStream * writeStream) const
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
		for (std::vector<::Struct::ServerInfo>::const_iterator it=this->data.begin(); it!=this->data.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->commonServerID)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->roleServerID.size())) return -1;
		for (std::vector<uint32_t>::const_iterator it=this->roleServerID.begin(); it!=this->roleServerID.end(); ++it) {
			if (!writeStream->Write((int32_t)(*it))) return -1;
		}
	}
	{
		if (!writeStream->Write(this->account.c_str(), this->account.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->accountId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
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
			::Struct::ServerInfo __inner__;
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
		if (!readStream->Read((int32_t&)this->accountId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (LoginCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (LoginCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	commonServerID = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (LoginCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->data.size())) return -1;
		for (std::vector<::Struct::ServerInfo>::const_iterator it=this->data.begin(); it!=this->data.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->commonServerID)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->roleServerID.size())) return -1;
		for (std::vector<uint32_t>::const_iterator it=this->roleServerID.begin(); it!=this->roleServerID.end(); ++it) {
			if (!writeStream->Write((int32_t)(*it))) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (LoginCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->data.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::ServerInfo __inner__;
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

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	serverID = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (LoginCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->account.c_str(), this->account.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->serverID)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
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
		if (!readStream->Read((int32_t&)this->serverID)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (LoginCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (LoginCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
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

int ::Unserialize(ReadStream * readStream)
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

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	characterNum = 0;
	serverPort = 0;
	updateDelayTime = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (LoginCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->characterNum)) return -1;
	}
	{
		if (this->playerInfo.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write(this->serverIP.c_str(), this->serverIP.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->serverPort)) return -1;
	}
	{
		if (!writeStream->Write(this->serverName.c_str(), this->serverName.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->updateDelayTime)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (LoginCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->characterNum)) return -1;
	}
	{
		if (this->playerInfo.Unserialize(readStream) != 0) return -1;	
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->serverIP.assign(p, len);
	}
	{
		if (!readStream->Read((int32_t&)this->serverPort)) return -1;
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

::()
{
	this->minorCmd = MINOR_CMD;
	job = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (LoginCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->name.c_str(), this->name.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->job)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
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
		if (!readStream->Read((int32_t&)this->job)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	characterNum = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (LoginCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->characterNum)) return -1;
	}
	{
		if (this->playerInfo.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (LoginCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->characterNum)) return -1;
	}
	{
		if (this->playerInfo.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (LoginCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (LoginCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	time = 0;
	id = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (LoginCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int64_t)this->time)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->id)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (LoginCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int64_t&)this->time)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->id)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	time = 0;
	id = 0;
	serverTime = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (LoginCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int64_t)this->time)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->id)) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->serverTime)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (LoginCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int64_t&)this->time)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->id)) return -1;
	}
	{
		if (!readStream->Read((int64_t&)this->serverTime)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (LoginCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->code.c_str(), this->code.size())) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
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

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (LoginCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (LoginCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (LoginCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->name.c_str(), this->name.size())) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (LoginCommand::Unserialize(readStream) != 0) return -1;
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->name.assign(p, len);
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (LoginCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write(this->name.c_str(), this->name.size())) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
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
		this->name.assign(p, len);
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (LoginCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (LoginCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	funBitMap = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (LoginCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->funBitMap)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (LoginCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->funBitMap)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->team1info.size())) return -1;
		for (std::vector<::Struct::DungeonsPlayerInfo>::const_iterator it=this->team1info.begin(); it!=this->team1info.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->team1info.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::DungeonsPlayerInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->team1info.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->playerinfo.size())) return -1;
		for (std::vector<::Struct::DungeonsPlayerInfo>::const_iterator it=this->playerinfo.begin(); it!=this->playerinfo.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->playerinfo.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::DungeonsPlayerInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->playerinfo.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	dungeonId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->dungeonId)) return -1;
	}
	{
		if (this->playerInfo.Serialize(writeStream) != 0) return -1;
	}
	{
		if (this->mapInfo.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->dungeonId)) return -1;
	}
	{
		if (this->playerInfo.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (this->mapInfo.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->playerInfo.size())) return -1;
		for (std::vector<::Struct::DungeonsPlayerInfo>::const_iterator it=this->playerInfo.begin(); it!=this->playerInfo.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->playerInfo.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::DungeonsPlayerInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->playerInfo.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	mapId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->mapId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->mapId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->mapInfo.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->mapInfo.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	endType = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->endType)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->endType)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	endType = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->endType)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->endType)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	fighterUid = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int64_t)this->fighterUid)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int64_t&)this->fighterUid)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	npcUid = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int64_t)this->npcUid)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int64_t&)this->npcUid)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	npcUid = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int64_t)this->npcUid)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int64_t&)this->npcUid)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->fightersInfo.size())) return -1;
		for (std::vector<::Struct::FightAttrInfo>::const_iterator it=this->fightersInfo.begin(); it!=this->fightersInfo.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->fightersInfo.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::FightAttrInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->fightersInfo.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	fighterUid = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int64_t)this->fighterUid)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int64_t&)this->fighterUid)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->npcInfo.size())) return -1;
		for (std::vector<::Struct::DungeonsNpcInfo>::const_iterator it=this->npcInfo.begin(); it!=this->npcInfo.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->npcInfo.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::DungeonsNpcInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->npcInfo.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->npcUid.size())) return -1;
		for (std::vector<::Struct::CreateNpcClientKey>::const_iterator it=this->npcUid.begin(); it!=this->npcUid.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->npcUid.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::CreateNpcClientKey __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->npcUid.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->players.size())) return -1;
		for (std::vector<::Struct::FighterPos>::const_iterator it=this->players.begin(); it!=this->players.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->players.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::FighterPos __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->players.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->player.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->player.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->player.size())) return -1;
		for (std::vector<::Struct::MainCityPlayerAttrInfo>::const_iterator it=this->player.begin(); it!=this->player.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->player.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::MainCityPlayerAttrInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->player.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	playerUid = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int64_t)this->playerUid)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int64_t&)this->playerUid)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->pos.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->pos.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->player.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->player.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	dungeonId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->dungeonId)) return -1;
	}
	{
		if (this->playerInfo.Serialize(writeStream) != 0) return -1;
	}
	{
		if (this->mapInfo.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->dungeonId)) return -1;
	}
	{
		if (this->playerInfo.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (this->mapInfo.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->playerInfo.size())) return -1;
		for (std::vector<::Struct::DungeonsPlayerInfo>::const_iterator it=this->playerInfo.begin(); it!=this->playerInfo.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->playerInfo.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::DungeonsPlayerInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->playerInfo.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	npcUid = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int64_t)this->npcUid)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int64_t&)this->npcUid)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	npcUid = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int64_t)this->npcUid)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int64_t&)this->npcUid)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->fightersInfo.size())) return -1;
		for (std::vector<::Struct::FightAttrInfo>::const_iterator it=this->fightersInfo.begin(); it!=this->fightersInfo.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->fightersInfo.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::FightAttrInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->fightersInfo.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	fighterUid = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int64_t)this->fighterUid)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int64_t&)this->fighterUid)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->npcInfo.size())) return -1;
		for (std::vector<::Struct::DungeonsNpcInfo>::const_iterator it=this->npcInfo.begin(); it!=this->npcInfo.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->npcInfo.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::DungeonsNpcInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->npcInfo.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->npcUid.size())) return -1;
		for (std::vector<::Struct::CreateNpcClientKey>::const_iterator it=this->npcUid.begin(); it!=this->npcUid.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->npcUid.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::CreateNpcClientKey __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->npcUid.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	endType = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->endType)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->endType)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	endType = 0;
	jobTitleId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->endType)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->jobTitleId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->rewards.size())) return -1;
		for (std::vector<::Struct::DropItem>::const_iterator it=this->rewards.begin(); it!=this->rewards.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->endType)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->jobTitleId)) return -1;
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->rewards.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::DropItem __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->rewards.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	mapId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->mapId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->mapId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (MapCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->mapInfo.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (MapCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->mapInfo.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FightCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->pos.size())) return -1;
		for (std::vector<::Struct::FighterPos>::const_iterator it=this->pos.begin(); it!=this->pos.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FightCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->pos.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::FighterPos __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->pos.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FightCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->fightpos.size())) return -1;
		for (std::vector<::Struct::FighterPos>::const_iterator it=this->fightpos.begin(); it!=this->fightpos.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FightCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->fightpos.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::FighterPos __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->fightpos.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	skillId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FightCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->pos.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->skillId)) return -1;
	}
	{
		if (this->targetPos.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->data.size())) return -1;
		for (std::vector<BYTE>::const_iterator it=this->data.begin(); it!=this->data.end(); ++it) {
			if (!writeStream->Write((char)(*it))) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FightCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->pos.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->skillId)) return -1;
	}
	{
		if (this->targetPos.Unserialize(readStream) != 0) return -1;	
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->data.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			BYTE __inner__;
			{
				if (!readStream->Read((char&)__inner__)) return -1;
			}
			this->data.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	skillId = 0;
	skillUid = 0;
	anger = 0;
	manual = 0;
	weapon1anger = 0;
	weapon2anger = 0;
	ret = 0;
	isBuff = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FightCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->skillId)) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->skillUid)) return -1;
	}
	{
		if (this->pos.Serialize(writeStream) != 0) return -1;
	}
	{
		if (this->targetPos.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->data.size())) return -1;
		for (std::vector<BYTE>::const_iterator it=this->data.begin(); it!=this->data.end(); ++it) {
			if (!writeStream->Write((char)(*it))) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->anger)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->manual)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->weapon1anger)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->weapon2anger)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->isBuff)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FightCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->skillId)) return -1;
	}
	{
		if (!readStream->Read((int64_t&)this->skillUid)) return -1;
	}
	{
		if (this->pos.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (this->targetPos.Unserialize(readStream) != 0) return -1;	
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->data.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			BYTE __inner__;
			{
				if (!readStream->Read((char&)__inner__)) return -1;
			}
			this->data.push_back(__inner__);
		}
	}
	{
		if (!readStream->Read((int32_t&)this->anger)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->manual)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->weapon1anger)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->weapon2anger)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->isBuff)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	skillId = 0;
	skillUid = 0;
	hitIndex = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FightCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->pos.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->skillId)) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->skillUid)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->hitIndex)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->hurt.size())) return -1;
		for (std::vector<uint64_t>::const_iterator it=this->hurt.begin(); it!=this->hurt.end(); ++it) {
			if (!writeStream->Write((int64_t)(*it))) return -1;
		}
	}
	{
		if (this->effectPos.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FightCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->pos.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->skillId)) return -1;
	}
	{
		if (!readStream->Read((int64_t&)this->skillUid)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->hitIndex)) return -1;
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->hurt.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			uint64_t __inner__;
			{
				if (!readStream->Read((int64_t&)__inner__)) return -1;
			}
			this->hurt.push_back(__inner__);
		}
	}
	{
		if (this->effectPos.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FightCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->hurtlist.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FightCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->hurtlist.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FightCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->data.c_str(), this->data.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->dataInfo.size())) return -1;
		for (std::vector<::Struct::ClientFightInfo>::const_iterator it=this->dataInfo.begin(); it!=this->dataInfo.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FightCommand::Unserialize(readStream) != 0) return -1;
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->data.assign(p, len);
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->dataInfo.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::ClientFightInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->dataInfo.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FightCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->data.c_str(), this->data.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->dataInfo.size())) return -1;
		for (std::vector<::Struct::ClientFightInfo>::const_iterator it=this->dataInfo.begin(); it!=this->dataInfo.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FightCommand::Unserialize(readStream) != 0) return -1;
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->data.assign(p, len);
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->dataInfo.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::ClientFightInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->dataInfo.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FightCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->data.c_str(), this->data.size())) return -1;
	}
	{
		if (this->dataInfo.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FightCommand::Unserialize(readStream) != 0) return -1;
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->data.assign(p, len);
	}
	{
		if (this->dataInfo.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FightCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->data.c_str(), this->data.size())) return -1;
	}
	{
		if (this->dataInfo.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FightCommand::Unserialize(readStream) != 0) return -1;
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->data.assign(p, len);
	}
	{
		if (this->dataInfo.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	count = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FightCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->count)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FightCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->count)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FightCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FightCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FightCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FightCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	count = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FightCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->count)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FightCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->count)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->info.size())) return -1;
		for (std::vector<::Struct::DungeonsStatus>::const_iterator it=this->info.begin(); it!=this->info.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->chapterRewards.size())) return -1;
		for (std::vector<::Struct::ChapterRewards>::const_iterator it=this->chapterRewards.begin(); it!=this->chapterRewards.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->info.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::DungeonsStatus __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->info.push_back(__inner__);
		}
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->chapterRewards.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::ChapterRewards __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->chapterRewards.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	id = 0;
	intervalId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->id)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->intervalId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->id)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->intervalId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	haveBlackShopNpc = 0;
	intervalId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (this->info.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->haveBlackShopNpc)) return -1;
	}
	{
		if (this->intervalPlayer.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->intervalId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (this->info.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->haveBlackShopNpc)) return -1;
	}
	{
		if (this->intervalPlayer.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->intervalId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	id = 0;
	endType = 0;
	blackShop = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->id)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->endType)) return -1;
	}
	{
		if (this->star.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write(this->data.c_str(), this->data.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->dropItem.size())) return -1;
		for (std::vector<::Struct::DropItem>::const_iterator it=this->dropItem.begin(); it!=this->dropItem.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->killMonster.size())) return -1;
		for (std::vector<::Struct::CopyMapMonsterInfo>::const_iterator it=this->killMonster.begin(); it!=this->killMonster.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((char)this->blackShop)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->id)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->endType)) return -1;
	}
	{
		if (this->star.Unserialize(readStream) != 0) return -1;	
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->data.assign(p, len);
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->dropItem.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::DropItem __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->dropItem.push_back(__inner__);
		}
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->killMonster.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::CopyMapMonsterInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->killMonster.push_back(__inner__);
		}
	}
	{
		if (!readStream->Read((char&)this->blackShop)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	endType = 0;
	exp = 0;
	money = 0;
	intervalId = 0;
	daymapCount = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->data.c_str(), this->data.size())) return -1;
	}
	{
		if (this->star.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->starLoot.size())) return -1;
		for (std::vector<::Struct::DropItem>::const_iterator it=this->starLoot.begin(); it!=this->starLoot.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->endType)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->exp)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->money)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->intervalId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->daymapCount)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->data.assign(p, len);
	}
	{
		if (this->star.Unserialize(readStream) != 0) return -1;	
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->starLoot.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::DropItem __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->starLoot.push_back(__inner__);
		}
	}
	{
		if (!readStream->Read((int32_t&)this->endType)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->exp)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->money)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->intervalId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->daymapCount)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	id = 0;
	count = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->id)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->count)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->id)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->count)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	count = 0;
	ret = 0;
	daymapCount = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->count)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->loots.size())) return -1;
		for (std::vector<::Struct::CopyMapInfo>::const_iterator it=this->loots.begin(); it!=this->loots.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->daymapCount)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->exp.size())) return -1;
		for (std::vector<uint32_t>::const_iterator it=this->exp.begin(); it!=this->exp.end(); ++it) {
			if (!writeStream->Write((int32_t)(*it))) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->count)) return -1;
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->loots.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::CopyMapInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->loots.push_back(__inner__);
		}
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->daymapCount)) return -1;
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->exp.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			uint32_t __inner__;
			{
				if (!readStream->Read((int32_t&)__inner__)) return -1;
			}
			this->exp.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->info.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->info.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->sweepInfo.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->sweepInfo.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	id = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->id)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->id)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	dungeonId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->dungeonId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->dungeonId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	dungeonId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->strategys.size())) return -1;
		for (std::vector<::Struct::DungeonsStrategyInfo>::const_iterator it=this->strategys.begin(); it!=this->strategys.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->dungeonId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->strategys.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::DungeonsStrategyInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->strategys.push_back(__inner__);
		}
	}
	{
		if (!readStream->Read((int32_t&)this->dungeonId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	dungeonId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->dungeonId)) return -1;
	}
	{
		if (!writeStream->Write(this->strategy.c_str(), this->strategy.size())) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->dungeonId)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->strategy.assign(p, len);
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	dungeonId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->strategys.size())) return -1;
		for (std::vector<::Struct::DungeonsStrategyInfo>::const_iterator it=this->strategys.begin(); it!=this->strategys.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->dungeonId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->strategys.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::DungeonsStrategyInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->strategys.push_back(__inner__);
		}
	}
	{
		if (!readStream->Read((int32_t&)this->dungeonId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	daymapCount = 0;
	discountChapterId = 0;
	energy = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->daymapCount)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->discountChapterId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->energy)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->daymapCount)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->discountChapterId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->energy)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	curSubId = 0;
	curLayer = 0;
	maxLayer = 0;
	maxSubId = 0;
	reward = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->curSubId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->curLayer)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->maxLayer)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->maxSubId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->reward)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->curSubId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->curLayer)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->maxLayer)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->maxSubId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->reward)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	layer = 0;
	subId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->layer)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->subId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->layer)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->subId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	layer = 0;
	subId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->layer)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->subId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->layer)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->subId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	layer = 0;
	subId = 0;
	ret = 0;
	endType = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->layer)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->subId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->endType)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->loot.size())) return -1;
		for (std::vector<::Struct::DropItem>::const_iterator it=this->loot.begin(); it!=this->loot.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->layer)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->subId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->endType)) return -1;
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->loot.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::DropItem __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->loot.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	layer = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->layer)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->layer)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	reward = 0;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->reward)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->reward)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	index = 0;
	reward = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->index)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->reward)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->index)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->reward)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (this->info.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (this->info.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->doubleInfo.size())) return -1;
		for (std::vector<::Struct::DungeonDoubleInfo>::const_iterator it=this->doubleInfo.begin(); it!=this->doubleInfo.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->doubleInfo.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::DungeonDoubleInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->doubleInfo.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	dungeonId = 0;
	strategyId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->dungeonId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->strategyId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->dungeonId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->strategyId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	selfClike = 0;
	strategyId = 0;
	dungeonId = 0;
	clike = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->selfClike)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->strategyId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->dungeonId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->clike)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->selfClike)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->strategyId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->dungeonId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->clike)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	mapType = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->mapType)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->mapType)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (this->room.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (this->room.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	playerId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->playerId)) return -1;
	}
	{
		if (this->room.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->playerId)) return -1;
	}
	{
		if (this->room.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->room.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->room.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	roomUid = 0;
	mapType = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->captainName.c_str(), this->captainName.size())) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->roomUid)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->mapType)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->captainName.assign(p, len);
	}
	{
		if (!readStream->Read((int64_t&)this->roomUid)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->mapType)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	roomUid = 0;
	ret = 0;
	mapType = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int64_t)this->roomUid)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->mapType)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int64_t&)this->roomUid)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->mapType)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->roomInfo.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->roomInfo.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ready = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ready)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ready)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	playerMaxCount = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ready.size())) return -1;
		for (std::vector<uint32_t>::const_iterator it=this->ready.begin(); it!=this->ready.end(); ++it) {
			if (!writeStream->Write((int32_t)(*it))) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->playerMaxCount)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->ready.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			uint32_t __inner__;
			{
				if (!readStream->Read((int32_t&)__inner__)) return -1;
			}
			this->ready.push_back(__inner__);
		}
	}
	{
		if (!readStream->Read((int32_t&)this->playerMaxCount)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	playerMaxCount = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->playerMaxCount)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->playerMaxCount)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->info.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->info.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	levelType = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->levelType)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->levelType)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	index = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->index)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->index)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	index = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->index)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->index)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	stars = 0;
	rewards = 0;
	freeRefresh = 0;
	jionCount = 0;
	buyRefreshCount = 0;
	buyJionCount = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->info.size())) return -1;
		for (std::vector<::Struct::BossRushGateInfo>::const_iterator it=this->info.begin(); it!=this->info.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->stars)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->rewards)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->freeRefresh)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->jionCount)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->buyRefreshCount)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->buyJionCount)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->info.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::BossRushGateInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->info.push_back(__inner__);
		}
	}
	{
		if (!readStream->Read((int32_t&)this->stars)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->rewards)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->freeRefresh)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->jionCount)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->buyRefreshCount)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->buyJionCount)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	index = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->index)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->index)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	rewards = 0;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->rewards)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->rewards)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	free = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->free)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->free)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	freeRefresh = 0;
	buyRefreshCount = 0;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->info.size())) return -1;
		for (std::vector<::Struct::BossRushGateInfo>::const_iterator it=this->info.begin(); it!=this->info.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->freeRefresh)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->buyRefreshCount)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->info.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::BossRushGateInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->info.push_back(__inner__);
		}
	}
	{
		if (!readStream->Read((int32_t&)this->freeRefresh)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->buyRefreshCount)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	jionCount = 0;
	buyJionCount = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->jionCount)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->buyJionCount)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->jionCount)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->buyJionCount)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PVEDungeosCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PVEDungeosCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	count = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->count)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->count)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	mailid = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->mailid)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->mailid)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->mails.size())) return -1;
		for (std::vector<uint32_t>::const_iterator it=this->mails.begin(); it!=this->mails.end(); ++it) {
			if (!writeStream->Write((int32_t)(*it))) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
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

::()
{
	this->minorCmd = MINOR_CMD;
	page = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->page)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->page)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	page = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->page)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->mails.size())) return -1;
		for (std::vector<::Struct::MailInfo>::const_iterator it=this->mails.begin(); it!=this->mails.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
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
			::Struct::MailInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->mails.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->str.c_str(), this->str.size())) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->str.assign(p, len);
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->str.c_str(), this->str.size())) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->str.assign(p, len);
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->itemList.size())) return -1;
		for (std::vector<::Struct::ItemInfo>::const_iterator it=this->itemList.begin(); it!=this->itemList.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->itemList.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::ItemInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->itemList.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->equipList.size())) return -1;
		for (std::vector<::Struct::EquipInfo>::const_iterator it=this->equipList.begin(); it!=this->equipList.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->equipList.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::EquipInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->equipList.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	uid = 0;
	exp = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int64_t)this->uid)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->exp)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int64_t&)this->uid)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->exp)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->equip.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->equip.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	uid = 0;
	level = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int64_t)this->uid)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->level)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int64_t&)this->uid)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->level)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->equip.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->equip.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	uid = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int64_t)this->uid)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int64_t&)this->uid)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	uid = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->equip.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->uid)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->equip.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int64_t&)this->uid)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	id = 0;
	index = 0;
	teamIndex = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->id)) return -1;
	}
	{
		if (!writeStream->Write((char)this->index)) return -1;
	}
	{
		if (!writeStream->Write((char)this->teamIndex)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->id)) return -1;
	}
	{
		if (!readStream->Read((char&)this->index)) return -1;
	}
	{
		if (!readStream->Read((char&)this->teamIndex)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	id = 0;
	index = 0;
	teamIndex = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (this->partnerteam.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->id)) return -1;
	}
	{
		if (!writeStream->Write((char)this->index)) return -1;
	}
	{
		if (!writeStream->Write((char)this->teamIndex)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (this->partnerteam.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->id)) return -1;
	}
	{
		if (!readStream->Read((char&)this->index)) return -1;
	}
	{
		if (!readStream->Read((char&)this->teamIndex)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	curIndex = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->partnerteams.size())) return -1;
		for (std::vector<::Struct::PartnerTeamInfo>::const_iterator it=this->partnerteams.begin(); it!=this->partnerteams.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->curIndex)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->haveRoles.size())) return -1;
		for (std::vector<::Struct::MsgRoleInfo>::const_iterator it=this->haveRoles.begin(); it!=this->haveRoles.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->havePhotos.size())) return -1;
		for (std::vector<uint32_t>::const_iterator it=this->havePhotos.begin(); it!=this->havePhotos.end(); ++it) {
			if (!writeStream->Write((int32_t)(*it))) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->partnerteams.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::PartnerTeamInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->partnerteams.push_back(__inner__);
		}
	}
	{
		if (!readStream->Read((int32_t&)this->curIndex)) return -1;
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->haveRoles.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::MsgRoleInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->haveRoles.push_back(__inner__);
		}
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->havePhotos.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			uint32_t __inner__;
			{
				if (!readStream->Read((int32_t&)__inner__)) return -1;
			}
			this->havePhotos.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	uid = 0;
	index = 0;
	teamIndex = 0;
	pos = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int64_t)this->uid)) return -1;
	}
	{
		if (!writeStream->Write((char)this->index)) return -1;
	}
	{
		if (!writeStream->Write((char)this->teamIndex)) return -1;
	}
	{
		if (!writeStream->Write((char)this->pos)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int64_t&)this->uid)) return -1;
	}
	{
		if (!readStream->Read((char&)this->index)) return -1;
	}
	{
		if (!readStream->Read((char&)this->teamIndex)) return -1;
	}
	{
		if (!readStream->Read((char&)this->pos)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	id = 0;
	index = 0;
	teamIndex = 0;
	pos = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (this->partnerteam.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->id)) return -1;
	}
	{
		if (!writeStream->Write((char)this->index)) return -1;
	}
	{
		if (!writeStream->Write((char)this->teamIndex)) return -1;
	}
	{
		if (!writeStream->Write((char)this->pos)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (this->partnerteam.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->id)) return -1;
	}
	{
		if (!readStream->Read((char&)this->index)) return -1;
	}
	{
		if (!readStream->Read((char&)this->teamIndex)) return -1;
	}
	{
		if (!readStream->Read((char&)this->pos)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	teamIndex = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((char)this->teamIndex)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->changePos.size())) return -1;
		for (std::vector<uint32_t>::const_iterator it=this->changePos.begin(); it!=this->changePos.end(); ++it) {
			if (!writeStream->Write((int32_t)(*it))) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((char&)this->teamIndex)) return -1;
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->changePos.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			uint32_t __inner__;
			{
				if (!readStream->Read((int32_t&)__inner__)) return -1;
			}
			this->changePos.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	teamIndex = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((char)this->teamIndex)) return -1;
	}
	{
		if (this->partnerteam.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((char&)this->teamIndex)) return -1;
	}
	{
		if (this->partnerteam.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	index = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->index)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->index)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	index = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->index)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->index)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	shoptype = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->shoptype)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->shoptype)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	shoptype = 0;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->shoptype)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->items.size())) return -1;
		for (std::vector<::Struct::ShopItemInfo>::const_iterator it=this->items.begin(); it!=this->items.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->shoptype)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->items.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::ShopItemInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->items.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	shoptype = 0;
	index = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->shoptype)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->index)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->shoptype)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->index)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	shoptype = 0;
	ret = 0;
	index = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->shoptype)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->index)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->shoptype)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->index)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->levelTime.size())) return -1;
		for (std::vector<uint32_t>::const_iterator it=this->levelTime.begin(); it!=this->levelTime.end(); ++it) {
			if (!writeStream->Write((int32_t)(*it))) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->waitUnload.size())) return -1;
		for (std::vector<uint32_t>::const_iterator it=this->waitUnload.begin(); it!=this->waitUnload.end(); ++it) {
			if (!writeStream->Write((int32_t)(*it))) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->items.size())) return -1;
		for (std::vector<::Struct::DropItem>::const_iterator it=this->items.begin(); it!=this->items.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->levelTime.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			uint32_t __inner__;
			{
				if (!readStream->Read((int32_t&)__inner__)) return -1;
			}
			this->levelTime.push_back(__inner__);
		}
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->waitUnload.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			uint32_t __inner__;
			{
				if (!readStream->Read((int32_t&)__inner__)) return -1;
			}
			this->waitUnload.push_back(__inner__);
		}
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->items.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::DropItem __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->items.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	sweepEnergy = 0;
	energy = 0;
	gold = 0;
	money = 0;
	exp = 0;
	level = 0;
	fight = 0;
	vipLevel = 0;
	recoverEnergyTime = 0;
	jjcTicket = 0;
	worldChatFreeTimes = 0;
	juedouChangCount = 0;
	buyMoneyCount = 0;
	buyJJCTicketCount = 0;
	guildQiandao = 0;
	guildReward = 0;
	guildWeekHuoyueReward = 0;
	guildMulPveCount = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->sweepEnergy)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->energy)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->gold)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->money)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->exp)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->commonCion.size())) return -1;
		for (std::vector<::Struct::DropItem>::const_iterator it=this->commonCion.begin(); it!=this->commonCion.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->level)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->fight)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->vipLevel)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->recoverEnergyTime)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->jjcTicket)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->giftTreeList.size())) return -1;
		for (std::vector<::Struct::PlayerGiftInfo>::const_iterator it=this->giftTreeList.begin(); it!=this->giftTreeList.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->worldChatFreeTimes)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->juedouChangCount)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->buyMoneyCount)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->buyJJCTicketCount)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->guildQiandao)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->guildReward)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->guildWeekHuoyueReward)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->guildMulPveCount)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->sweepEnergy)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->energy)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->gold)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->money)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->exp)) return -1;
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->commonCion.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::DropItem __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->commonCion.push_back(__inner__);
		}
	}
	{
		if (!readStream->Read((int32_t&)this->level)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->fight)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->vipLevel)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->recoverEnergyTime)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->jjcTicket)) return -1;
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->giftTreeList.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::PlayerGiftInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->giftTreeList.push_back(__inner__);
		}
	}
	{
		if (!readStream->Read((int32_t&)this->worldChatFreeTimes)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->juedouChangCount)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->buyMoneyCount)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->buyJJCTicketCount)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->guildQiandao)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->guildReward)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->guildWeekHuoyueReward)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->guildMulPveCount)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	baptizeenergy = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->baptizeenergy)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->baptizeenergy)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	uid = 0;
	index = 0;
	baptizeType = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int64_t)this->uid)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->index)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->baptizeType)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int64_t&)this->uid)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->index)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->baptizeType)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	index = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->equip.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->index)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->equip.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->index)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->passiveList.size())) return -1;
		for (std::vector<::Struct::TeamPassiveInfo>::const_iterator it=this->passiveList.begin(); it!=this->passiveList.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->guildSkills.size())) return -1;
		for (std::vector<::Struct::GuildSkill>::const_iterator it=this->guildSkills.begin(); it!=this->guildSkills.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->passiveList.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::TeamPassiveInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->passiveList.push_back(__inner__);
		}
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->guildSkills.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::GuildSkill __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->guildSkills.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	subid = 0;
	level = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->subid)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->level)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->subid)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->level)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	subid = 0;
	level = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->subid)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->level)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->subid)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->level)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	subid = 0;
	level = 0;
	oprType = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->subid)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->level)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->oprType)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->subid)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->level)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->oprType)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	subid = 0;
	level = 0;
	oprType = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->subid)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->level)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->oprType)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->subid)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->level)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->oprType)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	clientType = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->changeItems.size())) return -1;
		for (std::vector<::Struct::ItemInfo>::const_iterator it=this->changeItems.begin(); it!=this->changeItems.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->removeItems.size())) return -1;
		for (std::vector<uint64_t>::const_iterator it=this->removeItems.begin(); it!=this->removeItems.end(); ++it) {
			if (!writeStream->Write((int64_t)(*it))) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->addEquips.size())) return -1;
		for (std::vector<::Struct::EquipInfo>::const_iterator it=this->addEquips.begin(); it!=this->addEquips.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->changeCoins.size())) return -1;
		for (std::vector<::Struct::DropItem>::const_iterator it=this->changeCoins.begin(); it!=this->changeCoins.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->clientType)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->changeGems.size())) return -1;
		for (std::vector<::Struct::GemInfo>::const_iterator it=this->changeGems.begin(); it!=this->changeGems.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->changeFateGuards.size())) return -1;
		for (std::vector<::Struct::FateGuardInfo>::const_iterator it=this->changeFateGuards.begin(); it!=this->changeFateGuards.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->addPartners.size())) return -1;
		for (std::vector<uint32_t>::const_iterator it=this->addPartners.begin(); it!=this->addPartners.end(); ++it) {
			if (!writeStream->Write((int32_t)(*it))) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->changeItems.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::ItemInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->changeItems.push_back(__inner__);
		}
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->removeItems.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			uint64_t __inner__;
			{
				if (!readStream->Read((int64_t&)__inner__)) return -1;
			}
			this->removeItems.push_back(__inner__);
		}
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->addEquips.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::EquipInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->addEquips.push_back(__inner__);
		}
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->changeCoins.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::DropItem __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->changeCoins.push_back(__inner__);
		}
	}
	{
		if (!readStream->Read((int32_t&)this->clientType)) return -1;
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->changeGems.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::GemInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->changeGems.push_back(__inner__);
		}
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->changeFateGuards.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::FateGuardInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->changeFateGuards.push_back(__inner__);
		}
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->addPartners.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			uint32_t __inner__;
			{
				if (!readStream->Read((int32_t&)__inner__)) return -1;
			}
			this->addPartners.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->value1.Serialize(writeStream) != 0) return -1;
	}
	{
		if (this->value2.Serialize(writeStream) != 0) return -1;
	}
	{
		if (this->value3.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->value1.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (this->value2.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (this->value3.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	composeId = 0;
	clientFuncType = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->composeId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->clientFuncType)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->composeId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->clientFuncType)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	clientFuncType = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->clientFuncType)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->clientFuncType)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	PartnerNextFreeTime = 0;
	PartnerNextProtect = 0;
	PartnerLastCounts = 0;
	FateNextFreeTime = 0;
	FateNextProtect = 0;
	FateLastCounts = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->PartnerNextFreeTime)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->PartnerNextProtect)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->PartnerLastCounts)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->FateNextFreeTime)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->FateNextProtect)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->FateLastCounts)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->PartnerNextFreeTime)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->PartnerNextProtect)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->PartnerLastCounts)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->FateNextFreeTime)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->FateNextProtect)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->FateLastCounts)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	PartnerOnceCost = 0;
	PartnerTenCost = 0;
	FateOnceCost = 0;
	FateTenCost = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->PartnerOnceCost)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->PartnerTenCost)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->FateOnceCost)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->FateTenCost)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->PartnerOnceCost)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->PartnerTenCost)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->FateOnceCost)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->FateTenCost)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	extractType = 0;
	isFree = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->extractType)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->isFree)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->extractType)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->isFree)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	extractType = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->items.size())) return -1;
		for (std::vector<::Struct::DropItem>::const_iterator it=this->items.begin(); it!=this->items.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->extractType)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->items.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::DropItem __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->items.push_back(__inner__);
		}
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->extractType)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->normals.size())) return -1;
		for (std::vector<::Struct::QuestInfo>::const_iterator it=this->normals.begin(); it!=this->normals.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->days.size())) return -1;
		for (std::vector<::Struct::QuestInfo>::const_iterator it=this->days.begin(); it!=this->days.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->completeQuests.size())) return -1;
		for (std::vector<uint32_t>::const_iterator it=this->completeQuests.begin(); it!=this->completeQuests.end(); ++it) {
			if (!writeStream->Write((int32_t)(*it))) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->normals.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::QuestInfo __inner__;
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
			::Struct::QuestInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->days.push_back(__inner__);
		}
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->completeQuests.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			uint32_t __inner__;
			{
				if (!readStream->Read((int32_t&)__inner__)) return -1;
			}
			this->completeQuests.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->info.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->info.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	id = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->id)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->id)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->equipUid.size())) return -1;
		for (std::vector<uint64_t>::const_iterator it=this->equipUid.begin(); it!=this->equipUid.end(); ++it) {
			if (!writeStream->Write((int64_t)(*it))) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->equipUid.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			uint64_t __inner__;
			{
				if (!readStream->Read((int64_t&)__inner__)) return -1;
			}
			this->equipUid.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	id = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->id)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->id)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	id = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->id)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->id)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	coinId = 0;
	BuyCount = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->coinId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->BuyCount)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->coinId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->BuyCount)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	coinId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->coinId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->coinId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	activeValue = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->activeValue)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->reward.size())) return -1;
		for (std::vector<::Struct::AvtiveValueReward>::const_iterator it=this->reward.begin(); it!=this->reward.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->activeEvent.size())) return -1;
		for (std::vector<::Struct::AvtiveValueEvent>::const_iterator it=this->activeEvent.begin(); it!=this->activeEvent.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->activeValue)) return -1;
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->reward.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::AvtiveValueReward __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->reward.push_back(__inner__);
		}
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->activeEvent.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::AvtiveValueEvent __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->activeEvent.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	index = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->index)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->index)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	rewards = 0;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->rewards)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->rewards)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	rewards = 0;
	activeValue = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->rewards)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->activeValue)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->rewards)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->activeValue)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	sign = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->sign)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->sign)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	signId = 0;
	isSign = 0;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->signId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->isSign)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->signId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->isSign)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	guideId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->guideId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->guideId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	guideId = 0;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->guideId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->guideId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->monthCards.size())) return -1;
		for (std::vector<::Struct::MonthCardsInfo>::const_iterator it=this->monthCards.begin(); it!=this->monthCards.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->monthCards.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::MonthCardsInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->monthCards.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	cardType = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->cardType)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->cardType)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	cardType = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->cardType)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->cardType)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->redIcons.size())) return -1;
		for (std::vector<::Struct::RedIconInfo>::const_iterator it=this->redIcons.begin(); it!=this->redIcons.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->redIcons.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::RedIconInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->redIcons.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	activityType = 0;
	id = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->activityType)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->id)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->activityType)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->id)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (this->activityTypes.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (this->activityTypes.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->activityTypes.size())) return -1;
		for (std::vector<::Struct::ActivityTypeInfo>::const_iterator it=this->activityTypes.begin(); it!=this->activityTypes.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->activityTypes.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::ActivityTypeInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->activityTypes.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	questId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->questId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->questId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->roleInfo.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->roleInfo.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	uid = 0;
	count = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int64_t)this->uid)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->count)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int64_t&)this->uid)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->count)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	uid = 0;
	count = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->uid)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->count)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int64_t&)this->uid)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->count)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	subid = 0;
	oprType = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->subid)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->oprType)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->subid)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->oprType)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	subid = 0;
	oprType = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->subid)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->oprType)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->subid)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->oprType)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	id = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->id)) return -1;
	}
	{
		if (this->itemId.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->id)) return -1;
	}
	{
		if (this->itemId.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->partner.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->partner.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	curPartnerId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->partners.size())) return -1;
		for (std::vector<::Struct::PartnerInfo>::const_iterator it=this->partners.begin(); it!=this->partners.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->curPartnerId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->partners.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::PartnerInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->partners.push_back(__inner__);
		}
	}
	{
		if (!readStream->Read((int32_t&)this->curPartnerId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	id = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->id)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->id)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->partner.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->partner.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	id = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->id)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->id)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	id = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->id)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->id)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	id = 0;
	subid = 0;
	level = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->id)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->subid)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->level)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->id)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->subid)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->level)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	subid = 0;
	level = 0;
	id = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->subid)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->level)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->id)) return -1;
	}
	{
		if (this->partner.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->subid)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->level)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->id)) return -1;
	}
	{
		if (this->partner.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	id = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->id)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->id)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	id = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->id)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->id)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (this->partner.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (this->partner.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	id = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->id)) return -1;
	}
	{
		if (!writeStream->Write(this->name.c_str(), this->name.size())) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->id)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->name.assign(p, len);
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (this->partner.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (this->partner.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->partner.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->partner.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	index = 0;
	oprType = 0;
	level = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->index)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->oprType)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->level)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->index)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->oprType)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->level)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	oprType = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->oprType)) return -1;
	}
	{
		if (this->equipGrids.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->oprType)) return -1;
	}
	{
		if (this->equipGrids.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->equipGrids.size())) return -1;
		for (std::vector<::Struct::EquipGridInfo>::const_iterator it=this->equipGrids.begin(); it!=this->equipGrids.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->equipGrids.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::EquipGridInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->equipGrids.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->GemStones.size())) return -1;
		for (std::vector<::Struct::GemInfo>::const_iterator it=this->GemStones.begin(); it!=this->GemStones.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->GemStones.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::GemInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->GemStones.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	inlayType = 0;
	equipPos = 0;
	equipGemSolt = 0;
	gemSolt = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->inlayType)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->equipPos)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->equipGemSolt)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->gemSolt)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->inlayType)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->equipPos)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->equipGemSolt)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->gemSolt)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->equip.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->equip.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->fateGuards.size())) return -1;
		for (std::vector<::Struct::FateGuardInfo>::const_iterator it=this->fateGuards.begin(); it!=this->fateGuards.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->playerFateGuards.size())) return -1;
		for (std::vector<::Struct::FateGuardInfo>::const_iterator it=this->playerFateGuards.begin(); it!=this->playerFateGuards.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->fateGuards.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::FateGuardInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->fateGuards.push_back(__inner__);
		}
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->playerFateGuards.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::FateGuardInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->playerFateGuards.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	inlayType = 0;
	pos = 0;
	fateGuardUid = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->inlayType)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->pos)) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->fateGuardUid)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->inlayType)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->pos)) return -1;
	}
	{
		if (!readStream->Read((int64_t&)this->fateGuardUid)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->fateGuard.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->fateGuard.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	preType = 0;
	id = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->preType)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->id)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->preType)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->id)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	id = 0;
	preType = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->id)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->preType)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->id)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->preType)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	id = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->id)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->id)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	id = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->id)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->id)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	id = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->id)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->id)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	curFashionArmor = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->fashionArmors.size())) return -1;
		for (std::vector<uint32_t>::const_iterator it=this->fashionArmors.begin(); it!=this->fashionArmors.end(); ++it) {
			if (!writeStream->Write((int32_t)(*it))) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->curFashionArmor)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->fashionArmors.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			uint32_t __inner__;
			{
				if (!readStream->Read((int32_t&)__inner__)) return -1;
			}
			this->fashionArmors.push_back(__inner__);
		}
	}
	{
		if (!readStream->Read((int32_t&)this->curFashionArmor)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	desFateGuardSolt = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->devourFateGuardUids.size())) return -1;
		for (std::vector<uint64_t>::const_iterator it=this->devourFateGuardUids.begin(); it!=this->devourFateGuardUids.end(); ++it) {
			if (!writeStream->Write((int64_t)(*it))) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->desFateGuardSolt)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->devourFateGuardUids.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			uint64_t __inner__;
			{
				if (!readStream->Read((int64_t&)__inner__)) return -1;
			}
			this->devourFateGuardUids.push_back(__inner__);
		}
	}
	{
		if (!readStream->Read((int32_t&)this->desFateGuardSolt)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (this->fateGuardInfo.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (this->fateGuardInfo.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	maxJobTitleId = 0;
	curJobTitleId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->maxJobTitleId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->curJobTitleId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->maxJobTitleId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->curJobTitleId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	giftId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->giftId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->giftId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	vipGiftList = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->vipGiftList)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->vipGiftList)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	rechargeAmount = 0;
	vipLevel = 0;
	vipGiftList = 0;
	rewardState = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->rechargeAmount)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->vipLevel)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->vipGiftList)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->rewardState)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->rechargeAmount)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->vipLevel)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->vipGiftList)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->rewardState)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	exp = 0;
	level = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->exp)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->level)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->exp)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->level)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	stage = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->stage)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->itemInfo.size())) return -1;
		for (std::vector<::Struct::GoldFundInfo>::const_iterator it=this->itemInfo.begin(); it!=this->itemInfo.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->stage)) return -1;
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->itemInfo.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::GoldFundInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->itemInfo.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	id = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->id)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->id)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	id = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->id)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->id)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	offlineTime = 0;
	baseExp = 0;
	timesExp = 0;
	refreshTime = 0;
	freeTime = 0;
	chargeTime = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->offlineTime)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->baseExp)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->timesExp)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->refreshTime)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->freeTime)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->chargeTime)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->offlineTime)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->baseExp)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->timesExp)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->refreshTime)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->freeTime)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->chargeTime)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->closeActives.size())) return -1;
		for (std::vector<::Struct::CloseActiveInfo>::const_iterator it=this->closeActives.begin(); it!=this->closeActives.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->closeActives.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::CloseActiveInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->closeActives.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (PlayerInfoCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (PlayerInfoCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	nowTime = 0;
}

int ::Serialize(WriteStream * writeStream) const
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
		if (this->playerInfo.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->nowTime)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
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
		if (this->playerInfo.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->nowTime)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	nowTime = 0;
}

int ::Serialize(WriteStream * writeStream) const
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
		if (this->playerInfo.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->nowTime)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
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
		if (this->playerInfo.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->nowTime)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (ChatMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->channeltype.size())) return -1;
		for (std::vector<std::string>::const_iterator it=this->channeltype.begin(); it!=this->channeltype.end(); ++it) {
			if (!writeStream->Write((*it).c_str(), (*it).size())) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
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

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (ChatMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->channeltype.size())) return -1;
		for (std::vector<std::string>::const_iterator it=this->channeltype.begin(); it!=this->channeltype.end(); ++it) {
			if (!writeStream->Write((*it).c_str(), (*it).size())) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
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

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (ChatMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->str.c_str(), this->str.size())) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
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

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (ChatMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->cmdStr.c_str(), this->cmdStr.size())) return -1;
	}
	{
		if (!writeStream->Write(this->resStr.c_str(), this->resStr.size())) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (ChatMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->cmdStr.assign(p, len);
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->resStr.assign(p, len);
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	playerID = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (ChatMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->chaterName.c_str(), this->chaterName.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->playerID)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (ChatMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->chaterName.assign(p, len);
	}
	{
		if (!readStream->Read((int32_t&)this->playerID)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (ChatMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (this->playerInfo.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (ChatMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (this->playerInfo.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	playerId = 0;
	nowTime = 0;
}

int ::Serialize(WriteStream * writeStream) const
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
		if (!writeStream->Write((int32_t)this->nowTime)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
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
		if (!readStream->Read((int32_t&)this->nowTime)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	nowTime = 0;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (ChatMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->chatMessage.c_str(), this->chatMessage.size())) return -1;
	}
	{
		if (this->playerInfo.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->nowTime)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (ChatMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->chatMessage.assign(p, len);
	}
	{
		if (this->playerInfo.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->nowTime)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (ChatMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->channeltype.c_str(), this->channeltype.size())) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
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

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (ChatMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->chatMessage.size())) return -1;
		for (std::vector<std::string>::const_iterator it=this->chatMessage.begin(); it!=this->chatMessage.end(); ++it) {
			if (!writeStream->Write((*it).c_str(), (*it).size())) return -1;
		}
	}
	{
		if (!writeStream->Write(this->channeltype.c_str(), this->channeltype.size())) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
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

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (ChatMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->channeltype.c_str(), this->channeltype.size())) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
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

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (ChatMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (ChatMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (ChatMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->content.c_str(), this->content.size())) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (ChatMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->content.assign(p, len);
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	nowTime = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (ChatMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->str.c_str(), this->str.size())) return -1;
	}
	{
		if (this->playerInfo.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->nowTime)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
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
		if (this->playerInfo.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->nowTime)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	nowTime = 0;
	freeTimes = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (ChatMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->str.c_str(), this->str.size())) return -1;
	}
	{
		if (this->playerInfo.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->nowTime)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->freeTimes)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
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
		if (this->playerInfo.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->nowTime)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->freeTimes)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	port = 0;
	serverId = 0;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->ip.c_str(), this->ip.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->port)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->serverId)) return -1;
	}
	{
		if (!writeStream->Write(this->session.c_str(), this->session.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->ip.assign(p, len);
	}
	{
		if (!readStream->Read((int32_t&)this->port)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->serverId)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->session.assign(p, len);
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	serverId = 0;
	playerId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->account.c_str(), this->account.size())) return -1;
	}
	{
		if (!writeStream->Write(this->session.c_str(), this->session.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->serverId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->playerId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;
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
	{
		if (!readStream->Read((int32_t&)this->serverId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->playerId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	worldChatPort = 0;
	isReconnectFight = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write(this->worldChatIp.c_str(), this->worldChatIp.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->worldChatPort)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->otherPlayer.size())) return -1;
		for (std::vector<::Struct::MulDungeonPlayerInfo>::const_iterator it=this->otherPlayer.begin(); it!=this->otherPlayer.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->isReconnectFight)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->worldChatIp.assign(p, len);
	}
	{
		if (!readStream->Read((int32_t&)this->worldChatPort)) return -1;
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->otherPlayer.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::MulDungeonPlayerInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->otherPlayer.push_back(__inner__);
		}
	}
	{
		if (!readStream->Read((int32_t&)this->isReconnectFight)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	port = 0;
	serverId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->ip.c_str(), this->ip.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->port)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->serverId)) return -1;
	}
	{
		if (!writeStream->Write(this->session.c_str(), this->session.size())) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->ip.assign(p, len);
	}
	{
		if (!readStream->Read((int32_t&)this->port)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->serverId)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->session.assign(p, len);
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	mapId = 0;
	mapType = 0;
	passwd = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->mapId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->mapType)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->passwd)) return -1;
	}
	{
		if (!writeStream->Write(this->title.c_str(), this->title.size())) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->mapId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->mapType)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->passwd)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->title.assign(p, len);
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	passwd = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->passwd)) return -1;
	}
	{
		if (this->room.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->passwd)) return -1;
	}
	{
		if (this->room.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	page = 0;
	mapId = 0;
	mapType = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->page)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->mapId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->mapType)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->page)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->mapId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->mapType)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->rooms.size())) return -1;
		for (std::vector<::Struct::MulDungeonSimpleInfo>::const_iterator it=this->rooms.begin(); it!=this->rooms.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->rooms.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::MulDungeonSimpleInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->rooms.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	roomId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->roomId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->roomId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->room.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->room.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	roomId = 0;
	passwd = 0;
	mapId = 0;
	isInvitation = 0;
	roomUid = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->roomId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->passwd)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->mapId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->isInvitation)) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->roomUid)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->roomId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->passwd)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->mapId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->isInvitation)) return -1;
	}
	{
		if (!readStream->Read((int64_t&)this->roomUid)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	roomId = 0;
	ret = 0;
	roomUid = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->roomId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->roomUid)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->roomId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int64_t&)this->roomUid)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	leaveType = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->leaveType)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->leaveType)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->chatMsg.c_str(), this->chatMsg.size())) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->chatMsg.assign(p, len);
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	serverId = 0;
	playerId = 0;
	vipLevel = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->chatMsg.c_str(), this->chatMsg.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->serverId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->playerId)) return -1;
	}
	{
		if (!writeStream->Write(this->playerName.c_str(), this->playerName.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->vipLevel)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->chatMsg.assign(p, len);
	}
	{
		if (!readStream->Read((int32_t&)this->serverId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->playerId)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->playerName.assign(p, len);
	}
	{
		if (!readStream->Read((int32_t&)this->vipLevel)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->roomInfo.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->roomInfo.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	index = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->index)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->index)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	passwd = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->passwd)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->passwd)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	passwd = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->passwd)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->passwd)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	mapType = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->mapType)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->mapType)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	roomId = 0;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->roomId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->roomId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	playerId = 0;
	playerServerId = 0;
	photoId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->playerId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->playerServerId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->photoId)) return -1;
	}
	{
		if (this->room.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->playerId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->playerServerId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->photoId)) return -1;
	}
	{
		if (this->room.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	mapId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->mapId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->mapId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	mapId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->mapId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->mapId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ready = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ready)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ready)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ready.size())) return -1;
		for (std::vector<uint32_t>::const_iterator it=this->ready.begin(); it!=this->ready.end(); ++it) {
			if (!writeStream->Write((int32_t)(*it))) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->ready.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			uint32_t __inner__;
			{
				if (!readStream->Read((int32_t&)__inner__)) return -1;
			}
			this->ready.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->playerList.size())) return -1;
		for (std::vector<::Struct::MulDungeonPlayerInfo>::const_iterator it=this->playerList.begin(); it!=this->playerList.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->playerList.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::MulDungeonPlayerInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->playerList.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	playerId = 0;
	serverId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->playerId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->serverId)) return -1;
	}
	{
		if (this->invitation.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->playerId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->serverId)) return -1;
	}
	{
		if (this->invitation.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->invitation.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->invitation.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	sync = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->sync)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->sync)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->info.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->info.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (WorldMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (WorldMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	page = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->page)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->page)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	haveReq = 0;
	friendGiftDayCount = 0;
	friendGetDayCount = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->friends.size())) return -1;
		for (std::vector<::Struct::FriendInfo>::const_iterator it=this->friends.begin(); it!=this->friends.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->haveReq)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->friendGiftDayCount)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->friendGetDayCount)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->intimacyRewards.size())) return -1;
		for (std::vector<uint32_t>::const_iterator it=this->intimacyRewards.begin(); it!=this->intimacyRewards.end(); ++it) {
			if (!writeStream->Write((int32_t)(*it))) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->friends.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::FriendInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->friends.push_back(__inner__);
		}
	}
	{
		if (!readStream->Read((int32_t&)this->haveReq)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->friendGiftDayCount)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->friendGetDayCount)) return -1;
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->intimacyRewards.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			uint32_t __inner__;
			{
				if (!readStream->Read((int32_t&)__inner__)) return -1;
			}
			this->intimacyRewards.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	page = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->page)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->page)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->friendReqs.size())) return -1;
		for (std::vector<::Struct::FriendReqInfo>::const_iterator it=this->friendReqs.begin(); it!=this->friendReqs.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->friendReqs.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::FriendReqInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->friendReqs.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	playerId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->playerId)) return -1;
	}
	{
		if (!writeStream->Write(this->playerName.c_str(), this->playerName.size())) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->playerId)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->playerName.assign(p, len);
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->playerInfo.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->playerInfo.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	playerId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->playerId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->playerId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	playerId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->playerId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->playerId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	playerId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->playerId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->playerId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	playerId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->playerId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->playerId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	playerId = 0;
	oper = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->playerId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->oper)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->playerId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->oper)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	playerId = 0;
	oper = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->playerId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->oper)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->playerId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->oper)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->recommends.size())) return -1;
		for (std::vector<::Struct::FriendReqInfo>::const_iterator it=this->recommends.begin(); it!=this->recommends.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->recommends.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::FriendReqInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->recommends.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	playerId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->playerId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->playerId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	playerId = 0;
	friendGiftDayCount = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (this->items.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->playerId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->friendGiftDayCount)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (this->items.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->playerId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->friendGiftDayCount)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	playerId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->playerId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->playerId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	playerId = 0;
	friendGetDayCount = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (this->items.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->playerId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->friendGetDayCount)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (this->items.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->playerId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->friendGetDayCount)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	needFriends = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->needFriends)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->needFriends)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	needFriends = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->needFriends)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->friends.size())) return -1;
		for (std::vector<::Struct::FriendInfo>::const_iterator it=this->friends.begin(); it!=this->friends.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->strangers.size())) return -1;
		for (std::vector<::Struct::FriendReqInfo>::const_iterator it=this->strangers.begin(); it!=this->strangers.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->needFriends)) return -1;
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->friends.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::FriendInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->friends.push_back(__inner__);
		}
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->strangers.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::FriendReqInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->strangers.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	page = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->page)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->page)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	page = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->rankList.size())) return -1;
		for (std::vector<::Struct::JJCPlayerInfo>::const_iterator it=this->rankList.begin(); it!=this->rankList.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->page)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->rankList.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::JJCPlayerInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->rankList.push_back(__inner__);
		}
	}
	{
		if (!readStream->Read((int32_t&)this->page)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	ticket = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->dualList.size())) return -1;
		for (std::vector<::Struct::JJCPlayerInfo>::const_iterator it=this->dualList.begin(); it!=this->dualList.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->ticket)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->dualList.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::JJCPlayerInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->dualList.push_back(__inner__);
		}
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->ticket)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	playerId = 0;
	dualType = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->playerId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->dualType)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->playerId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->dualType)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	winType = 0;
	point = 0;
	winComboCount = 0;
	changePoint = 0;
	JJCClass = 0;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->winType)) return -1;
	}
	{
		if (this->target.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->point)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->winComboCount)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->changePoint)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->JJCClass)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->winType)) return -1;
	}
	{
		if (this->target.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->point)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->winComboCount)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->changePoint)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->JJCClass)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	rank = 0;
	point = 0;
	jjcCoin = 0;
	jjcTicket = 0;
	continuity = 0;
	canRefDualList = 0;
	winCount = 0;
	jjcClass = 0;
	jjcClassPercent = 0;
	updateTicketTime = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->rank)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->point)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->jjcCoin)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->jjcTicket)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->continuity)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->dualList.size())) return -1;
		for (std::vector<::Struct::JJCPlayerInfo>::const_iterator it=this->dualList.begin(); it!=this->dualList.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->canRefDualList)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->winCount)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->jjcClass)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->jjcClassPercent)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->updateTicketTime)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->rank)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->point)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->jjcCoin)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->jjcTicket)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->continuity)) return -1;
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->dualList.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::JJCPlayerInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->dualList.push_back(__inner__);
		}
	}
	{
		if (!readStream->Read((int32_t&)this->canRefDualList)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->winCount)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->jjcClass)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->jjcClassPercent)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->updateTicketTime)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->buffIds.size())) return -1;
		for (std::vector<uint32_t>::const_iterator it=this->buffIds.begin(); it!=this->buffIds.end(); ++it) {
			if (!writeStream->Write((int32_t)(*it))) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->buffIds.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			uint32_t __inner__;
			{
				if (!readStream->Read((int32_t&)__inner__)) return -1;
			}
			this->buffIds.push_back(__inner__);
		}
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->partnerteams.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->partnerteams.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->partnerteams.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->partnerteams.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	page = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->page)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->page)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	page = 0;
	rank = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->playerInfo.size())) return -1;
		for (std::vector<::Struct::FriendReqInfo>::const_iterator it=this->playerInfo.begin(); it!=this->playerInfo.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->page)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->rank)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->playerInfo.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::FriendReqInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->playerInfo.push_back(__inner__);
		}
	}
	{
		if (!readStream->Read((int32_t&)this->page)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->rank)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	page = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->page)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->page)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	page = 0;
	rank = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->playerInfo.size())) return -1;
		for (std::vector<::Struct::FriendReqInfo>::const_iterator it=this->playerInfo.begin(); it!=this->playerInfo.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->page)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->rank)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->playerInfo.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::FriendReqInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->playerInfo.push_back(__inner__);
		}
	}
	{
		if (!readStream->Read((int32_t&)this->page)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->rank)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->friendInfo.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->friendInfo.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	rewardId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->rewardId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->rewardId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	rewardId = 0;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->rewardId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->rewardId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	rewardCount = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->rewardCount)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->dumpPlayerId.size())) return -1;
		for (std::vector<uint32_t>::const_iterator it=this->dumpPlayerId.begin(); it!=this->dumpPlayerId.end(); ++it) {
			if (!writeStream->Write((int32_t)(*it))) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->rewardCount)) return -1;
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->dumpPlayerId.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			uint32_t __inner__;
			{
				if (!readStream->Read((int32_t&)__inner__)) return -1;
			}
			this->dumpPlayerId.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->recommends.size())) return -1;
		for (std::vector<::Struct::FriendReqInfo>::const_iterator it=this->recommends.begin(); it!=this->recommends.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->recommends.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::FriendReqInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->recommends.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	playerId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->playerId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->playerId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->invitationPlayer.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->invitationPlayer.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	targetId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->targetId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->targetId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	dumpUid = 0;
	ret = 0;
	isReconnect = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int64_t)this->dumpUid)) return -1;
	}
	{
		if (this->targetPlayer.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->isReconnect)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int64_t&)this->dumpUid)) return -1;
	}
	{
		if (this->targetPlayer.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->isReconnect)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	targetId = 0;
	criCount = 0;
	endTime = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->targetId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->criCount)) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->endTime)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->targetId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->criCount)) return -1;
	}
	{
		if (!readStream->Read((int64_t&)this->endTime)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	comob = 0;
	badEnd = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->comob)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->badEnd)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->comob)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->badEnd)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	rewardCount = 0;
	comob = 0;
	intimacyReward = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->rewardCount)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->dumpPlayerId.size())) return -1;
		for (std::vector<uint32_t>::const_iterator it=this->dumpPlayerId.begin(); it!=this->dumpPlayerId.end(); ++it) {
			if (!writeStream->Write((int32_t)(*it))) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->dropItem.size())) return -1;
		for (std::vector<::Struct::DropItem>::const_iterator it=this->dropItem.begin(); it!=this->dropItem.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->comob)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->intimacyReward)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->rewardCount)) return -1;
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->dumpPlayerId.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			uint32_t __inner__;
			{
				if (!readStream->Read((int32_t&)__inner__)) return -1;
			}
			this->dumpPlayerId.push_back(__inner__);
		}
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->dropItem.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::DropItem __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->dropItem.push_back(__inner__);
		}
	}
	{
		if (!readStream->Read((int32_t&)this->comob)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->intimacyReward)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->playerIds.size())) return -1;
		for (std::vector<uint32_t>::const_iterator it=this->playerIds.begin(); it!=this->playerIds.end(); ++it) {
			if (!writeStream->Write((int32_t)(*it))) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->playerIds.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			uint32_t __inner__;
			{
				if (!readStream->Read((int32_t&)__inner__)) return -1;
			}
			this->playerIds.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->playerName.c_str(), this->playerName.size())) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->playerName.assign(p, len);
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->player.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->player.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	page = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->page)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->page)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	page = 0;
	rank = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->playerInfo.size())) return -1;
		for (std::vector<::Struct::PartnerSimpleInfo>::const_iterator it=this->playerInfo.begin(); it!=this->playerInfo.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->page)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->rank)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->playerInfo.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::PartnerSimpleInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->playerInfo.push_back(__inner__);
		}
	}
	{
		if (!readStream->Read((int32_t&)this->page)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->rank)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	playerId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->playerId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->playerId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->invitationPlayer.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->invitationPlayer.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	targetId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->targetId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->targetId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	pkUid = 0;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int64_t)this->pkUid)) return -1;
	}
	{
		if (this->targetPlayer.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int64_t&)this->pkUid)) return -1;
	}
	{
		if (this->targetPlayer.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	endType = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->endType)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->endType)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	endType = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->endType)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->endType)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	page = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->page)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->page)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	page = 0;
	rank = 0;
	maxLayer = 0;
	maxSubId = 0;
	time = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->playerInfo.size())) return -1;
		for (std::vector<::Struct::TowerSimpleInfo>::const_iterator it=this->playerInfo.begin(); it!=this->playerInfo.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->page)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->rank)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->maxLayer)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->maxSubId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->time)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->playerInfo.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::TowerSimpleInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->playerInfo.push_back(__inner__);
		}
	}
	{
		if (!readStream->Read((int32_t&)this->page)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->rank)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->maxLayer)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->maxSubId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->time)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	playerId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->playerId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->playerId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	playerId = 0;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (FriendMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->playerId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write(this->playerName.c_str(), this->playerName.size())) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (FriendMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->playerId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->playerName.assign(p, len);
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	guildPhotoId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->guildName.c_str(), this->guildName.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->guildPhotoId)) return -1;
	}
	{
		if (!writeStream->Write(this->guildDeclaration.c_str(), this->guildDeclaration.size())) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->guildName.assign(p, len);
	}
	{
		if (!readStream->Read((int32_t&)this->guildPhotoId)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->guildDeclaration.assign(p, len);
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->info.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->info.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	guildId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->guildId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->guildId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	page = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->page)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->page)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	page = 0;
	guildCount = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->guildList.size())) return -1;
		for (std::vector<::Struct::GuildSimpleInfo>::const_iterator it=this->guildList.begin(); it!=this->guildList.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->page)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->guildCount)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->applys.size())) return -1;
		for (std::vector<uint32_t>::const_iterator it=this->applys.begin(); it!=this->applys.end(); ++it) {
			if (!writeStream->Write((int32_t)(*it))) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->guildList.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::GuildSimpleInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->guildList.push_back(__inner__);
		}
	}
	{
		if (!readStream->Read((int32_t&)this->page)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->guildCount)) return -1;
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->applys.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			uint32_t __inner__;
			{
				if (!readStream->Read((int32_t&)__inner__)) return -1;
			}
			this->applys.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	playerId = 0;
	oper = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->playerId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->oper)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->playerId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->oper)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	oper = 0;
	playerId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->oper)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->playerId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->oper)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->playerId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->players.size())) return -1;
		for (std::vector<::Struct::GuildPlayerInfo>::const_iterator it=this->players.begin(); it!=this->players.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->players.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::GuildPlayerInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->players.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	guildId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->guildId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->guildId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->guildInfo.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->players.size())) return -1;
		for (std::vector<::Struct::GuildPlayerInfo>::const_iterator it=this->players.begin(); it!=this->players.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->guildInfo.Unserialize(readStream) != 0) return -1;	
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->players.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::GuildPlayerInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->players.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	playerId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->playerId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->playerId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	playerId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->playerId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->playerId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	page = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->page)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->page)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	page = 0;
	guildRank = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->guildList.size())) return -1;
		for (std::vector<::Struct::GuildSimpleInfo>::const_iterator it=this->guildList.begin(); it!=this->guildList.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->page)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->guildRank)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->guildList.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::GuildSimpleInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->guildList.push_back(__inner__);
		}
	}
	{
		if (!readStream->Read((int32_t&)this->page)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->guildRank)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	passwd = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->passwd)) return -1;
	}
	{
		if (!writeStream->Write(this->title.c_str(), this->title.size())) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->passwd)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->title.assign(p, len);
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	passwd = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->passwd)) return -1;
	}
	{
		if (this->room.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->passwd)) return -1;
	}
	{
		if (this->room.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	page = 0;
	oprType = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->page)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->oprType)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->page)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->oprType)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	page = 0;
	oprType = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->rooms.size())) return -1;
		for (std::vector<::Struct::GuildRoomSimpleInfo>::const_iterator it=this->rooms.begin(); it!=this->rooms.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}
	{
		if (!writeStream->Write((int32_t)this->page)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->oprType)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->rooms.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::GuildRoomSimpleInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->rooms.push_back(__inner__);
		}
	}
	{
		if (!readStream->Read((int32_t&)this->page)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->oprType)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	roomId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->roomId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->roomId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->room.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->room.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	roomId = 0;
	passwd = 0;
	isInvitation = 0;
	roomUid = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->roomId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->passwd)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->isInvitation)) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->roomUid)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->roomId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->passwd)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->isInvitation)) return -1;
	}
	{
		if (!readStream->Read((int64_t&)this->roomUid)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	roomId = 0;
	ret = 0;
	roomUid = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->roomId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int64_t)this->roomUid)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->roomId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int64_t&)this->roomUid)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->roomInfo.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->roomInfo.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ready = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ready)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ready)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ready.size())) return -1;
		for (std::vector<uint32_t>::const_iterator it=this->ready.begin(); it!=this->ready.end(); ++it) {
			if (!writeStream->Write((int32_t)(*it))) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->ready.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			uint32_t __inner__;
			{
				if (!readStream->Read((int32_t&)__inner__)) return -1;
			}
			this->ready.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	playerId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->playerId)) return -1;
	}
	{
		if (this->invitation.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->playerId)) return -1;
	}
	{
		if (this->invitation.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->invitation.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->invitation.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	roomId = 0;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->roomId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->roomId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	leaveType = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->leaveType)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->leaveType)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	index = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->index)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->index)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->info.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->info.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	passwd = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->passwd)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->passwd)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	passwd = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->passwd)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->passwd)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	playerId = 0;
	photoId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->playerId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->photoId)) return -1;
	}
	{
		if (this->room.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->playerId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->photoId)) return -1;
	}
	{
		if (this->room.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	roomId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->roomId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->roomId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->items.size())) return -1;
		for (std::vector<::Struct::DropItem>::const_iterator it=this->items.begin(); it!=this->items.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->items.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::DropItem __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->items.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	guildId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->declaration.c_str(), this->declaration.size())) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->guildId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->declaration.assign(p, len);
	}
	{
		if (!readStream->Read((int32_t&)this->guildId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write(this->declaration.c_str(), this->declaration.size())) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->declaration.assign(p, len);
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->guildName.c_str(), this->guildName.size())) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->guildName.assign(p, len);
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (this->info.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (this->info.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	guildClass = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->guildClass)) return -1;
	}
	{
		if (!writeStream->Write(this->guildName.c_str(), this->guildName.size())) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->guildClass)) return -1;
	}
	{
		const char* p;
		size_t len;
		if (!readStream->ReadNoCopy(p, len)) return -1;
		this->guildName.assign(p, len);
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	playerId = 0;
	auth = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->playerId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->auth)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->playerId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->auth)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	playerId = 0;
	auth = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->playerId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->auth)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->playerId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->auth)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	playerId = 0;
	oper = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->playerId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->oper)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->playerId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->oper)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	desPlayerId = 0;
	desAuth = 0;
	auth = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->desPlayerId)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->desAuth)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->auth)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->desPlayerId)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->desAuth)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->auth)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	qiandaoType = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->qiandaoType)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->qiandaoType)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	guildMoney = 0;
	gongxian = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->guildMoney)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->gongxian)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->guildMoney)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->gongxian)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	index = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->index)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->index)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	rewardMask = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->rewardMask)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (!readStream->Read((int32_t&)this->rewardMask)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->skillInfo.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->skillInfo.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
	guildMoney = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (this->skillInfo.Serialize(writeStream) != 0) return -1;
	}
	{
		if (!writeStream->Write((int32_t)this->guildMoney)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (this->skillInfo.Unserialize(readStream) != 0) return -1;	
	}
	{
		if (!readStream->Read((int32_t&)this->guildMoney)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (this->skillInfo.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (this->skillInfo.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}
	{
		if (this->skillInfo.Serialize(writeStream) != 0) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}
	{
		if (this->skillInfo.Unserialize(readStream) != 0) return -1;	
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	rewardId = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->rewardId)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->rewardId)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
	ret = 0;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->ret)) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		if (!readStream->Read((int32_t&)this->ret)) return -1;
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (GuildMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write((int32_t)this->info.size())) return -1;
		for (std::vector<::Struct::GuildFirstKillInfo>::const_iterator it=this->info.begin(); it!=this->info.end(); ++it) {
			if ((*it).Serialize(writeStream) != 0) return -1;
		}
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
{
	(void)readStream;
	if (GuildMessageCommand::Unserialize(readStream) != 0) return -1;
	{
		int32_t __len__;
		if (!readStream->Read(__len__)) return -1;
		this->info.reserve(__len__);
		for (int32_t i=0; i<__len__; ++i) {
			::Struct::GuildFirstKillInfo __inner__;
			{
		if (__inner__.Unserialize(readStream) != 0) return -1;	
			}
			this->info.push_back(__inner__);
		}
	}

	return 0;
}

::()
{
	this->minorCmd = MINOR_CMD;
}

int ::Serialize(WriteStream * writeStream) const
{
	(void)writeStream;
	if (ClientExInfoMessageCommand::Serialize(writeStream) != 0) return -1;
	{
		if (!writeStream->Write(this->errorInfo.c_str(), this->errorInfo.size())) return -1;
	}

	return 0;
}

int ::Unserialize(ReadStream * readStream)
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

