#pragma once
#include "Entity.h"
class PlayerEntity : public Entity
{
private:
	HAPISPACE::DWORD rateOfFire{ 250 };
	HAPISPACE::DWORD lastTimeShot{ 0 };
public:
	PlayerEntity(std::string spriteName);
	~PlayerEntity();

	void Update() override final;
	bool Firing() override final;
	ESide GetSide() const override final { return ESide::ePlayer; }
	EType GetType() const override final { return EType::ePlayer; }
	void SetSide(ESide side) override final {}
	void SetType(EType type) override final {}
	void SetVariation(EVariation) override final {}
	EVariation GetVariation() override final { return EVariation::eBasic; };
};

