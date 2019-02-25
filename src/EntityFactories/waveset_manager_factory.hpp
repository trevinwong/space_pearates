#ifndef WAVESET_MANAGER_FACTORY_H
#define WAVESET_MANAGER_FACTORY_H

#include "entity.hpp"
#include "program.hpp"
#include "Components/waveset_component.hpp"
#include "Utility/waveset_structs.hpp"

class WavesetManagerFactory
{
public:
	static Entity build(string fileName);
	static Waveset readWavesetFile(string fileName);
	static Wave readWaveDataFile(string fileName);
	static Cluster readClusterDataFile(string fileName);

	template <typename T>
	static void fillVariable(std::stringstream &iss, T &var, string name) 
	{
		if (!(iss >> var)) {
			cout << "Unable to fill variable: " << name << endl;
			exit(1);
		}
	}

	static int getPreviouslyReadIndex(vector<string> prevReadFileNames, string fileName);	
	static void checkValidFilename(std::ifstream &ifs, string fileName);
	static void checkExtraText(std::stringstream &iss, string type);
	static void checkValidSeparatorAndMove(std::stringstream &iss, string type);
};

#endif
