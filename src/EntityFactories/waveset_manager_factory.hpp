#ifndef WAVESET_MANAGER_FACTORY_H
#define WAVESET_MANAGER_FACTORY_H

#include "entity.hpp"
#include "program.hpp"
#include "Components/waveset_component.hpp"
#include "Utility/waveset_structs.hpp"

class WavesetManagerFactory
{
public:
	static Entity build(std::string fileName);

	static waveset WavesetManagerFactory::readWavesetFile(std::string fileName);
	static wave WavesetManagerFactory::readWaveDataFile(std::string fileName);
	static cluster WavesetManagerFactory::readClusterDataFile(std::string fileName);
private:
};

#endif