#include "DBConnectClient.h"
#include "Stream.h"
#include "Defs.h"
#include "ServerCommand.h"
#include "ClientMsg.h"
#include "LogicDataCommand.h"
#include "LogicGateCommand.h"
#include "GM.h"
#include "OffLinePlayer.h"
#include "LogicService.h"
#include "WorldCommand.h"
#include "LogicTask.h"

CDBConnectClient::CDBConnectClient(const std::string &name, const std::string &ip, const unsigned short port, uint32_t queuesize)
    :CServerConnectClient(name, SERVER_TYPE_LOGIC_DATA, g_serverId, ip, port), m_isRegist(false)
{
}

bool CDBConnectClient::cmdMsgParse(void *ptNull,const uint32_t nCmdLen)
{
    Cmd::t_NullCmd *pNullCmd = (Cmd::t_NullCmd*)ptNull;
    switch (pNullCmd->cmd) 
    {
        case Cmd::CMD_SERVER_INIT:
            return ServerInitMessageParase((Cmd::t_NullCmd*)pNullCmd, nCmdLen);
        case Cmd::CMD_LOGIC_PLAYERINFO:
            return LogicDataMessageParase((Cmd::t_NullCmd*)pNullCmd, nCmdLen);
        case Cmd::CMD_FRIEND_MESSAGE:
            return FriendMessageParase((Cmd::t_NullCmd*)pNullCmd, nCmdLen);
        default:break;
    }

    return false;
}

void CDBConnectClient::CallBackConnectSuccessImp()
{
    Cmd::t_Server_Regist_Req send;
    send.info.serverId = g_serverId;
    send.info.port = g_serverPort;
    strncpy(send.info.serverName, eagle::global["ServerName"].c_str(), sizeof(send.info.serverName));
    strncpy(send.info.serverIP, eagle::global["LogicServerTcpIP"].c_str(), sizeof(send.info.serverIP));
    send.info.serverType = SERVER_TYPE_LOGIC_SERVER;
    SendCmd(&send, sizeof(send));

    return;
}

void CDBConnectClient::CallBackConnectErrorImp()
{

    return;
}

bool CDBConnectClient::ServerInitMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    switch (pNullCmd->para) 
    {
        case Cmd::PARA_SERVER_REGIST_RES:
            {
                LOGI("LogicServer DBConnectClient verify success !!!");

                m_isRegist = true;

                //Test Code Begin
                //for (int i = 0; i < 1000; ++i)
                //{
                //    Cmd::t_Data_Get_PlayerInfo_Req send;
                //    send. = i + 1;
                //    SendToDB(&send, sizeof(send));
                //}
                //Test Code End

                return true;
            }
        default:
            break;
    }

    return false;
}

bool CDBConnectClient::LogicDataMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    switch (pNullCmd->para) 
    {
        case Cmd::PARA_DATA_GET_PLAYERINFO_RES:
            {
                Cmd::t_Data_Get_PlayerInfo_Res *recv = (Cmd::t_Data_Get_PlayerInfo_Res*)pNullCmd;

                if (recv->funType)
                {
                    LogicPlayer *player = NULL;
                    LOGD("CDBConnectClient::LogicDataMessageParase off player ret = " << recv->ret << " account = " << recv->playerinfo.account);

                    player = World::instance()->GetPlayerByID(recv->playerinfo.playerId);
                    if (!player)
                    {
                        player = COffLinePLayerManager::instance()->GetOffPlayerById(recv->playerinfo.playerId);
                    }

                    if (player)
                    {

                    }
                    else if (SUCCESS == recv->ret)
                    {
                        player = World::instance()->CreatePlayer(recv->playerinfo);
                        if (!player)
                            return false;

                        if (!player->UnSerializeWithDB(recv))
                        {
                            LOGD("CDBConnectClient::LogicDataMessageParase off player Error account = " << recv->playerinfo.account);
                            World::instance()->FreePlayer(player);
                            return false;
                        }
                        else
                        {
                            COffLinePLayerManager::instance()->AddOffPlayer(player);
                        }
                    }

                    LogicPlayer *srcPlayer = World::instance()->GetPlayerByID(recv->srcPlayer);
                    if (!srcPlayer)
                        return false;

                    srcPlayer->OffPlayerDataCallBack(player, recv->funType);
                }
                else
                {
                    Cmd::t_Get_PlayerInfo_Res send;
                    
                    LogicPlayer *player = NULL;
                    LOGD("CDBConnectClient::LogicDataMessageParase ret = " << recv->ret << " account = " << recv->playerinfo.account);
                    send.ret = recv->ret;
                    if (SUCCESS == recv->ret)
                    {
                        player = World::instance()->GetPlayerByID(recv->playerinfo.playerId);
                        if (player)
                        {
							return false;
                        }

						player = World::instance()->CreatePlayer(recv->playerinfo);
						if (!player)
						{
							LOGE("logic CreatePlayer failed !!!");
							return false;
						}

                        if (!player->UnSerializeWithDB(recv) || !World::instance()->AddPlayer(player))
                        {
                            LOGE("CDBConnectClient player->UnSerialize Error account = " << recv->playerinfo.account);
                            World::instance()->RemovePlayer(player);
                            send.ret = DEFAULT_ERROR;
                            player = NULL;
                        }
                        else
                        {
                            send.playerinfo = player->GetPlayrInfoBase();
                        }
                    }

                    SendToGateway(&send, sizeof(send));
                    if (player)
                    {
                        player->NotifyLoginGame();
                        player->SyncLoginMsg();
                        COffLinePLayerManager::instance()->RemoveOffPlayer(player->Id());
                    }
                }

                return true;
            }
            break;
        case Cmd::PARA_DATA_CREATE_ROLEINFO_RES:
            {
                Cmd::t_Data_Create_RoleInfo_Res *recv = (Cmd::t_Data_Create_RoleInfo_Res*)pNullCmd;
                LogicPlayer *player = World::instance()->GetPlayerByID(recv->roleinfo.playerId);
                if (!player)
                {
                    LOGE("CDBConnectClient::LogicDataMessageParase t_Data_Create_RoleInfo_Res player null , playerId = " << recv->roleinfo.playerId);
                    return false;
                }
                
                if (SUCCESS == recv->ret)
                {
                    //todo: load config
                    player->AddRoleInfo(recv->roleinfo);
                }
                
                player->NotifyCreateRole(recv);
                LOGD("CDBConnectClient::t_Data_Create_RoleInfo_Res ret = " << recv->ret << " account = " << player->Account());
                return true;
            }
            break;
        case Cmd::PARA_DATA_GETROLEINFO_RES:  //
            {
                Cmd::t_Data_GetRoleInfo_Res *recv = (Cmd::t_Data_GetRoleInfo_Res*)pNullCmd;

                if (0 == recv->funType)
                {
                    LogicPlayer *player = World::instance()->GetPlayerByID(recv->roleInfo.playerId);
                    if (!player)
                    {
                        LOGE("CDBConnectClient::LogicDataMessageParase t_Data_GetRoleInfo_Res player null ,ret:" << recv->ret << " playerId = " << recv->roleInfo.playerId);
                        return false;
                    }

                    player->SetAsyncMsg(false);

                    if (SUCCESS == recv->ret)
                    {
                        //
                        if (player->InitRoleInfo(recv))
                        {
                            player->EnterToWorld();
                        }
                        else
                            LOGE("CDBConnectClient::LogicDataMessageParase player->InitWorldRoleInfo failed,playerId = " << recv->roleInfo.playerId);
                    }
                    else
                    {
                        player->NotifyClientError(NO_ROLEINFO);
                    }
                }

                return true;
            }
            break;
        case Cmd::PARA_DATA_SAVE_ROLEINFO_RES:
            {
                Cmd::t_Data_Save_RoleInfo_Res *recv = (Cmd::t_Data_Save_RoleInfo_Res*)pNullCmd;
                LogicPlayer *player = World::instance()->GetPlayerByID(recv->playerId);
                if (player)
                    if (!recv->ret)
                        player->NotifyClientError(PLAYER_DATA_ERROR);
            }
            break;
        case Cmd::PARA_DATA_UPDATE_ITEM_RES:
        {
            Cmd::t_Data_Update_Item_Res *recv = (Cmd::t_Data_Update_Item_Res*)pNullCmd;
            LogicPlayer *player = World::instance()->GetPlayerByID(recv->playerId);
            if (player)
            {
                if (SUCCESS == recv->ret)
                {
                    
                }
                else
                {
                    player->NotifyClientError(PLAYER_DATA_ERROR);
                }
            }

        }
        break;
        default:
            break;
    }

    return false;
}

bool CDBConnectClient::FriendMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{

    return false;
}


