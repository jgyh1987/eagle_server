#include "ECS_AIBehaviac.h"


bool BehaviacSystem::SetTree(BehaviacComponent* cmp, const std::string& treename)
{
	return cmp->m_tree.Init(cmp, treename);
}

void BehaviacSystem::RunBehaviac(BehaviacComponent* cmp)
{
	if (!cmp->m_tree.GetRoot())
		return;

	cmp->m_tree.GetRoot()->Exec(cmp);

	return;
}

