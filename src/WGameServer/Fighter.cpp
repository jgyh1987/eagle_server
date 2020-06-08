#include "Fighter.h"
#include "World.h"
#include "Defs.h"
#include "TimeTick.h"
#include "CommonDrop.h"
#include "ClientMsg.h"
#include "WGamePlayer.h"
#include "MMOSkill.h"
#include "GameBaseTask.h"

Fighter::Fighter(WGamePlayer *player)
    :Character(GetServerObjectUid()), m_player(player)
{
	m_entity = ECSWorldManager::instance()->CreateFighterEntity(player);
}

Fighter::~Fighter()
{
	ECSWorldManager::instance()->DestroyEntity(m_entity);
}

void Fighter::Clear()
{
	Character::Clear();

	return;
}

bool Fighter::Init(uint64_t id)
{

    return true;
}

void Fighter::Update()
{
    Character::Update();


    return;
}

void Fighter::CheckGrid(bool force)
{
	//Grid<WorldObject> *grid = ;
	//if (m_grid != grid)
	//{
	//	if (m_grid)
	//		m_grid->RemoveObject(this);

	//	if (grid)
	//		grid->AddObject(this);

	//	force = true;
	//}

	if (force)
	{

	}

	return;
}

void Fighter::ChangePos(Cmd::t_Scene_Move *recv, const unsigned int nCmdLen)
{
    //if (!CanMove())
    //{
    //    return;
    //}

    Move(recv->pos);

    ClientMsg::MoveRes send1;
    send1.pos.x = x;
    send1.pos.y = y;
    send1.pos.z = z;
    send1.pos.dirx = dirx;
    send1.pos.diry = diry;
    send1.pos.dirz = dirz;
    send1.pos.move = recv->pos.move / POS_DENOMINATOR;
    send1.ret = SUCCESS;
    //m_player->SendClientMsg(&send1);

    ClientMsg::MoveNotify notify;
    notify.msgs.resize(1);
    notify.msgs[0].fightUid = Uid();
    notify.msgs[0].pos.x = x;
    notify.msgs[0].pos.y = y;
    notify.msgs[0].pos.z = z;
    notify.msgs[0].pos.dirx = recv->pos.dirx / POS_DENOMINATOR;
    notify.msgs[0].pos.diry = recv->pos.diry / POS_DENOMINATOR;
    notify.msgs[0].pos.dirz = recv->pos.dirz / POS_DENOMINATOR;
    notify.msgs[0].pos.move = recv->pos.move / POS_DENOMINATOR;
    //BroadcastClientMsg(&notify);

    return;
}

void Fighter::CastSkill(Cmd::t_Scene_Cast_Skill *recv, const unsigned int nCmdLen)
{
    //ClientMsg::CastSkillRes send;
    //Move(recv->src);
    //if (m_skillManager && m_skillManager->CastSkill(recv->skillId, recv->actionId, &recv->target))
    //{
    //    send.caster.fightUid = recv->src.charactorUid;
    //    send.caster.pos.x = recv->src.x / POS_DENOMINATOR;
    //    send.caster.pos.y = recv->src.y / POS_DENOMINATOR;
    //    send.caster.pos.z = recv->src.z / POS_DENOMINATOR;
    //    send.caster.pos.dirx = recv->src.dirx / POS_DENOMINATOR;
    //    send.caster.pos.diry = recv->src.diry / POS_DENOMINATOR;
    //    send.caster.pos.dirz = recv->src.dirz / POS_DENOMINATOR;
    //    send.skillId = (uint32_t)recv->skillId;
    //    send.actionId = recv->actionId;
    //    send.targetPos.pos.x = recv->target.x / POS_DENOMINATOR;
    //    send.targetPos.pos.y = recv->target.y / POS_DENOMINATOR;
    //    send.targetPos.pos.z = recv->target.z / POS_DENOMINATOR;
    //    send.targetPos.pos.dirx = recv->target.dirx / POS_DENOMINATOR;
    //    send.targetPos.pos.diry = recv->target.diry / POS_DENOMINATOR;
    //    send.targetPos.pos.dirz = recv->target.dirz / POS_DENOMINATOR;
    //    send.targetPos.fightUid = recv->target.uid;
    //    send.ret = SUCCESS;

    //}
    //else
    //{
    //    send.ret = DEFAULT_ERROR;
    //}
    //
    //m_player->SendClientMsg(&send);
}

bool Fighter::Revive()
{
    //if (!IsDie())
    //    return false;

    //ClearStatusAllType();
    //m_characterFightInfo.curAttr[EAT_HP] = m_characterFightInfo.curAttr[EAT_MAXHP];

    //ClientMsg::FightInfoNotify notify;
    //notify.fighter.fightUid = Uid();
    //notify.status = Status();
    //notify.curAttr.resize(EAT_MAX);
    //for (uint32_t i = 0; i < EAT_MAX; ++i)
    //    notify.curAttr[i] = m_characterFightInfo.curAttr[i];
    //BroadcastClientMsg(&notify);

    //m_buffManager.AddBuff(5009, 3000, this, this);

    return true;
}

