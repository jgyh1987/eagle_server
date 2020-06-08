#include "GatewayUdpServer.h"
#include "Stream.h"
#include "Defs.h"
#include "PlayerManager.h"

uint32_t g_kcpId = 1;

bool CGatewayUdpServer::CmdMsgParseImp(void *ptNull, const uint32_t nCmdLen, sockaddr *addr, int mask)
{
    //LOGFMTT(" CGatewayUdpServer::cmdMsgParse :%d", nCmdLen);

    //BinaryReadStream stream((const char*)ptNull, nCmdLen);
 //   ClientMsg::Message message;
 //   if(message.Unserialize(&stream) != 0)
 //   {
 //       LOGFMTE("msg Unserialize Error len :%d", nCmdLen);
 //       return false;
 //   }

    //LOGFMTT("  ClientMsg::Message cmd :%d--%d", message.majorCmd, message.minorCmd);

  //  switch(message.majorCmd)    
  //  {
        //default:
        //    {
        //    }
        //    break;
  //  }

    //SendCmd(ptNull, nCmdLen, addr, 0);
    //return true;


    if (mask)
    {
        //kcp
        //find player

        GatewayPlayer *player = PlayerManager::instance()->FindKcpPlayer(mask);
        if (player)
        {
            player->IkcpInput((const char *)ptNull, nCmdLen);

        }
    }
    else
    {
        //test code begin
        protocol::PackageNet stream;
        stream.ParseFromArray(ptNull, nCmdLen);

        switch (stream.id())
        {
        case protocol::cs_udpLogin:
            {
                protocol::UpdLoginReqNet msg;
                msg.ParseFromArray((void *)stream.body().c_str(), (int)stream.body().size());

                GatewayPlayer *player = PlayerManager::instance()->GetPlayerByID(msg.playerid());
                if (!player)
                {
                    return false;
                }

                player->InitKcp(addr, g_kcpId++);
                if (g_kcpId == 0)
                    ++g_kcpId;

                protocol::UpdLoginRspNet send;
                send.set_kcpid(player->GetKcpId());
                send.set_id(msg.id());

                SendClientMsg(&send, protocol::sc_udpLogin, addr, mask);

                LOGI("KCP CREATE " << player->GetKcpId() << "!!!");

            
            }
            break;
        }

        //test code end
    }

    return true;
}

bool CGatewayUdpServer::SendClientMsg(ClientMsg::Message *message, sockaddr *addr)
{
    unsigned char buff[MAX_DATASIZE];
    BinaryWriteStream stream((char*) buff, MAX_DATASIZE - PH_LEN);
    if (message->Serialize(&stream) != 0)
    {
        LOGFMTE("msg Unserialize Error��%d, %d��", message->majorCmd, message->minorCmd);
        return false;
    }
    stream.Flush();
    SendCmd(buff, (uint32_t)stream.GetSize(), addr, 0);

    return true;
}

bool CGatewayUdpServer::SendClientMsg(::google::protobuf::Message *message, int id, sockaddr *addr, uint32_t mask)
{
    unsigned char buff[MAX_DATASIZE];
    int len = (int)message->ByteSizeLong();
    message->SerializeToArray(buff, len);

    protocol::PackageNet stream;
    stream.set_id(id);
    stream.set_body(buff, len);
    len = (int)stream.ByteSizeLong();
    stream.SerializeToArray(buff, len);

    SendCmd(buff, len, addr, mask);

    return true;
}


