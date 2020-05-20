#pragma once
#include "Entity.h"
class BulletEntity : public Entity
{
private:
	ESide m_side = ESide::eNeutral;
public:
	BulletEntity(std::string spriteName);

	void Update() override final;
	bool Firing() override final { return false; };
	ESide GetSide() const override final { return m_side; }
	EType GetType() const override final { return EType::eBullet; }
	void SetSide(ESide side) override final { m_side = side; }
	void SetType(EType type) override final {}
	void SetVariation(EVariation) override final {}
	EVariation GetVariation() override final { return EVariation::eBasic; };

	~BulletEntity();
};

