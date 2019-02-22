#include "EntityFactories/waveset_manager_factory.hpp"

Entity WavesetManagerFactory::build(std::string fileName)
{
	Entity e;
	waveset waveset = readWavesetFile(fileName);
	//std::shared_ptr<WavesetComponent> wavesetComponent = std::make_shared<WavesetComponent>(WavesetComponent(waveset));
	WavesetComponent* wavesetComponent = new WavesetComponent(waveset);
	e.setComponent<WavesetComponent>(wavesetComponent);
	return e;
}


// Read in the waveset file
waveset WavesetManagerFactory::readWavesetFile(std::string fileName)
{
	std::ifstream wavesetFile(fileName);
	std::vector<std::string> txtFiles;
	std::vector<wave> waves;
	if (wavesetFile.good()) {
		while (!wavesetFile.eof()) {

			std::string line; // declare a line
			std::getline(wavesetFile, line); // read a line from file
			std::stringstream iss(line); // convert the line string to string stream

			//TODO: Print to console on error
			//TODO: Add more detailed error checking for when invalid data is entered.
			std::string waveFile;
			if (iss >> waveFile) //Read cluster file name
			{

				wave waveData;
				if (iss.peek() == ',' || iss.peek() == ' ') iss.ignore();
				int emptydata = 0;
				if (!(iss >> emptydata)) //Check to ensure no more text is on this line.
				{
					//If file previous read
					bool prevRead = false;
					for (int i = 0; i < txtFiles.size(); i++)
					{
						if (waveFile.compare(txtFiles[i]) == 0)
						{
							waveData = waves[i];
							prevRead = true;
							break;
						}
					}

					//If new file
					if (!prevRead)
					{
						std::string dir = wave_path();
						waveData = readWaveDataFile(dir + waveFile);
					}
					waves.push_back(waveData);
					txtFiles.push_back(waveFile);

				}
			}

		}
		// Close the file
		wavesetFile.close();
	}
	struct waveset someItem;
	someItem.waves = waves;
	return someItem;
}

// Read in the wave file
wave WavesetManagerFactory::readWaveDataFile(std::string fileName)
{
	std::ifstream waveDataFile(fileName);
	int buildTime = 0;
	std::vector<std::string> txtFiles;
	std::vector<int> spawnTimes;
	std::vector<cluster> clusters;
	if (waveDataFile.good()) {
		int iter = 0;

		while (!waveDataFile.eof()) {

			std::string line; // declare a line
			std::getline(waveDataFile, line); // read a line from file
			std::stringstream iss(line); // convert the line string to string stream

			//TODO: Print to console on error
			//TODO: Add more detailed error checking for when invalid data is entered.
			std::string clusterFile;
			int time;

			if (iter == 0)
			{
				//TODO: Do something on failure
				if (iss >> buildTime);
			}
			else
			{
				if (iss >> clusterFile) //Read cluster file name
				{

					cluster clusterData;

					if (iss.peek() == ',' || iss.peek() == ' ') iss.ignore(); // comma for csv file, space for copying from google sheet
					if (iss >> time) //Read spawn time
					{
						if (iss.peek() == ',' || iss.peek() == ' ') iss.ignore();
						int emptydata = 0;
						if (!(iss >> emptydata)) //Check to ensure no more text is on this line.
						{
							//If file previous read
							bool prevRead = false;
							for (int i = 0; i < txtFiles.size(); i++)
							{
								if (clusterFile.compare(txtFiles[i]) == 0)
								{
									clusterData = clusters[i];
									prevRead = true;
									break;
								}
							}

							//If new file
							if (!prevRead)
							{
								std::string dir = cluster_path();
								clusterData = readClusterDataFile(dir + clusterFile);
							}
							spawnTimes.push_back(time);
							clusters.push_back(clusterData);
							txtFiles.push_back(clusterFile);

						}
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
cluster WavesetManagerFactory::readClusterDataFile(std::string fileName)
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