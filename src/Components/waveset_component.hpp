#ifndef WAVESET_COMPONENT_H
#define WAVESET_COMPONENT_H

#include "utility.hpp"
#include "base_component.hpp"
#include "entityFactories/enemy_factory.hpp"
#include "Utility/waveset_structs.hpp"

// For entities that control the phases and waves of the level.
class WavesetComponent : public BaseComponent
{
public:
	WavesetComponent(waveset wavese);
	~WavesetComponent();
	static const int typeID = ComponentType::waveset;
	inline virtual int getTypeID() const { return typeID; };

	waveset m_waveset;

};

#endif
