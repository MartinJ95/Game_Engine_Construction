#pragma once
#include "Entity.h"
#include "vector2.hpp"
class SceneryEntity : public Entity
{
private:

public:
	SceneryEntity(std::string spriteName);
	~SceneryEntity();

	void Update() override final;
	bool Firing() override final { return false; };
	ESide GetSide() const override final { return ESide::eNeutral; }
	EType GetType() const override final { return EType::eScenery; }
	void SetSide(ESide side) override final {}
	void SetType(EType type) override final {}
	void SetVariation(EVariation) override final {}
	EVariation GetVariation() override final { return EVariation::eBasic; };
};

