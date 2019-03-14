#ifndef WAVESET_COMPONENT_H
#define WAVESET_COMPONENT_H

#include "Utility/utility.hpp"
#include "base_component.hpp"
#include "EntityFactories/enemy_factory.hpp"
#include "Utility/waveset_structs.hpp"

// For entities that control the phases and waves of the level.
class WavesetComponent : public BaseComponent
{
public:
	WavesetComponent(Waveset _waveset);
	Waveset waveset;
	static const int typeID = ComponentType::waveset;
	inline virtual int getTypeID() const { return typeID; };
};

#endif
