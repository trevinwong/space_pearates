#include "wave_phase_system.hpp"

WavePhaseSystem::WavePhaseSystem()
{
	mainTimer = 0;
	buildPhaseEndTime = mainTimer + 10000;
}

WavePhaseSystem::~WavePhaseSystem()
{

}

void WavePhaseSystem::mainStateLoop(float dt)
{
	tickMainTimer(dt);
	if (phaseState == 0)
	{
		checkBuildPhaseEnd();
	}
	else
	{

	}
	
	
}

void WavePhaseSystem::tickMainTimer(float dt)
{
	mainTimer += dt;
}

// Check if build phase has ended.
bool WavePhaseSystem::checkBuildPhaseEnd()
{
	// Updating window title with points
	//std::stringstream title_ss;
	//title_ss << "Points: " << 50;
	//glfwSetWindowTitle(m_window, title_ss.str().c_str());

	if (mainTimer >= buildPhaseEndTime)
	{
		return true;
		phaseState = 1;
	}
	else
	{
		return false;
	}
	
}


// Check the amount of enemies remaining in the current wave.
int WavePhaseSystem::checkRemainingEnemies()
{
	return false;
}

// Main enemy phase code
void WavePhaseSystem::enemyPhaseAction()
{
}

/*
Entity WavePhaseSystem::createMapEntityFromFile(char * fileName)
{
	std::string fileNameStr(fileName);
	return createMapEntityFromFile(fileNameStr);
}

Entity WavePhaseSystem::createMapEntityFromFile(std::string fileName)
{
	std::vector<std::vector<char>> tileMap2DArray = MapEntityFactory::readMapDataFile(fileName);
	MapComponent *mapComponent = new MapComponent(tileMap2DArray);

	Entity mapEntity;
	mapEntity.setComponent<MapComponent>(mapComponent);

	return mapEntity;
}
*/

// Read in the file and just turn it into a vector of vec2s.
WavePhaseSystem::wave WavePhaseSystem::readWaveDataFile(std::string fileName)
{
	std::ifstream waveDataFile(fileName);
	int buildTime = 0;
	std::vector<std::string> txtFiles;
	std::vector<int> spawnTimes;
	std::vector<cluster> clusters;
	std::vector<std::pair<std::vector<glm::vec2>, int>> subWaves; 
	if (waveDataFile.good()) {
		int iter = 0;
		
		while (!waveDataFile.eof()) {

			std::string line; // declare a line
			std::getline(waveDataFile, line); // read a line from file
			std::stringstream iss(line); // convert the line string to string stream

			//TODO: Print to console on error
			//TODO: Add more detailed error checking for when invalid data is entered.
			
			
			std::string fileName;
			int time;

			if (iter == 0)
			{
				//TODO: Do something on failure
				if (iss >> buildTime);
			}
			else
			{
				if (iss >> fileName) //Read cluster file name
				{
					//If file previous read
					bool prevRead = false;
					cluster clusterData;
					for (int i = 0; i < txtFiles.size(); i++)
					{
						if (fileName.compare(txtFiles[i]) == 0)
						{
							time = spawnTimes[i];
							clusterData = clusters[i];
							spawnTimes.push_back(spawnTimes[i]);
							clusters.push_back(clusters[i]);
							txtFiles.push_back(fileName);
							prevRead = true;
							break;
						}
					}
					//If new file
					if (!prevRead)
					{
						if (iss.peek() == ',' || iss.peek() == ' ') iss.ignore(); // comma for csv file, space for copying from google sheet
						if (iss >> time) //Read spawn time
						{
							if (iss.peek() == ',' || iss.peek() == ' ') iss.ignore();
							int emptydata = 0;
							if (!(iss >> emptydata)) //Check to ensure no more text is on this line.
							{
								clusterData = WavePhaseSystem::readClusterDataFile(fileName);
								spawnTimes.push_back(time);
								clusters.push_back(clusterData);
								txtFiles.push_back(fileName);

							}
						}
					}
					if (clusterData.enemyData.size() > 0 && time > 0)
					{
						//std::pair<std::vector<glm::vec2>, int> subWave = std::pair<std::vector<glm::vec2>, int>(clusterData, time);
						//subWaves.push_back(subWave);

					}
				}
			}
			iter++;
		}
		// Close the file
		waveDataFile.close();
	}
	struct wave someItem;
	someItem.buildPhaseTime = buildTime;
	someItem.spawnTimes = spawnTimes;
	someItem.clusters = clusters;
	return someItem;
}

// Read in the file and just turn it into a vector of vec2s.
WavePhaseSystem::cluster WavePhaseSystem::readClusterDataFile(std::string fileName)
{
	std::ifstream clusterDataFile(fileName);
	std::vector<glm::vec2> clusterData;
	if (clusterDataFile.good()) {
		while (!clusterDataFile.eof()) {

			std::string line; // declare a line
			std::getline(clusterDataFile, line); // read a line from file
			std::stringstream iss(line); // convert the line string to string stream

			//TODO: Print to console on error
			//TODO: Add more detailed error checking for when invalid data is entered.
			int enemyAmount = 0;
			int enemyID = 0;
			glm::vec2 data = glm::vec2(enemyID, enemyAmount);
			if (iss >> enemyID) //Read enemy ID
			{
				if (iss.peek() == ',' || iss.peek() == ' ') iss.ignore(); // comma for csv file, space for copying from google sheet
				if (iss >> enemyAmount) //Read enemy amount
				{
					if (iss.peek() == ',' || iss.peek() == ' ') iss.ignore();
					int emptydata = 0;
					if (!(iss >> emptydata)) //Check to ensure no more text is on this line.
					{
						data = glm::vec2(enemyID, enemyAmount);
						clusterData.push_back(data);
					}
					
				}
			}
		}
		// Close the file
		clusterDataFile.close();
	}
	struct cluster someItem;
	someItem.enemyData = clusterData;
	return someItem;
}