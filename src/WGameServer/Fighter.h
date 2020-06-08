#ifndef _FIGHTER_H_ 
#define    _FIGHTER_H_

#include "Sys.h"
#include "CommonType.h"
#include "Skill.h"
#include "Buff.h"
#include "PlayerInfo.h"
#include "WorldCommand.h"
#include "Character.h"
#include "LandmassManager.h"

class WGamePlayer;

class Fighter : public Character
{
public:
    Fighter(WGamePlayer *player);
    ~Fighter();

    uint32_t Type(){return OBJECT_FIGHTER;}
    bool IsType(uint32_t type){return type == OBJECT_FIGHTER;}
	void Clear();

    bool Init(uint64_t id);
    void Update();
	void CheckGrid(bool force = false);

public:
    inline WGamePlayer *GetOwnerPlayer() { return m_player; }

    void ChangePos(Cmd::t_Scene_Move *recv, const unsigned int nCmdLen);
    void CastSkill(Cmd::t_Scene_Cast_Skill *recv, const unsigned int nCmdLen);
    bool Revive();
    
private:
    WGamePlayer *m_player;

};




#endif    


