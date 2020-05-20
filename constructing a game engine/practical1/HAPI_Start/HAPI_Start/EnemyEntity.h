#pragma once
#include "Entity.h"
class EnemyEntity : public Entity
{
private:
	HAPISPACE::DWORD rateOfFire{ 500 };
	HAPISPACE::DWORD lastTimeShot{ 0 };
	EVariation enemyType;
private:
	bool withinRange(float x, float r) { if (x > -r && x < r) { return true; } return false; }
public:
	EnemyEntity(std::string spriteName);
	~EnemyEntity();

	void Update() override final;
	bool Firing() override final;
	ESide GetSide() const override final { return ESide::eEnemy; }
	EType GetType() const override final { return EType::eEnemy; }
	void SetSide(ESide side) override final {}
	void SetType(EType type) override final {}
	void SetVariation(EVariation type) override final { enemyType = type; }
	EVariation GetVariation() override final { return enemyType; };
};

