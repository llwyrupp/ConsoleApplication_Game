#pragma once
#include "../Client/Actor/Enemy/Enemy.h"

class Villager : public Enemy
{
	RTTI_DECLARATIONS(Villager, Enemy)
public:
	Villager();
	virtual ~Villager();
private:

	// Inherited via Enemy
	virtual void BeginPlay() override;
	virtual void Tick(float _fDeltaTime) override;
	virtual void Render() override;
};

