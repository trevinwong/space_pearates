#include "waveset_manager_factory.hpp"

Entity WavesetManagerFactory::build(string fileName)
{
	Entity e;
	Waveset waveset = readWavesetFile(fileName);
	//std::shared_ptr<WavesetComponent> wavesetComponent = std::make_shared<WavesetComponent>(WavesetComponent(waveset));
	WavesetComponent* wavesetComponent = new WavesetComponent(waveset);
	e.setComponent<WavesetComponent>(wavesetComponent);
	return e;
}

int WavesetManagerFactory::getPreviouslyReadIndex(vector<string> prevReadFileNames, string fileName)
{
	for (int i = 0; i < prevReadFileNames.size(); i++) {
		if (prevReadFileNames[i].compare(fileName) == 0) return i;
	}
	return -1;
}

void WavesetManagerFactory::checkValidFilename(std::ifstream &ifs, string fileName)
{
	if (!ifs.good()) {
		cout << "Unable to read filename of: " << fileName << endl;
		exit(1);
	}
}

void WavesetManagerFactory::checkExtraText(std::stringstream &iss, string type)
{
	int emptyData = 0;
	if (iss >> emptyData) {
		cout << "Extra text on a line detected while reading: " << type << endl;
		exit(1);
	}
}

void WavesetManagerFactory::checkValidSeparatorAndMove(std::stringstream &iss, string type)
{
	if (iss.peek() != ',' && iss.peek() != ' ') {
		cout << "Invalid separator on a line detected while reading: " << type << endl;
		exit(1);
	} else {
		iss.ignore();
	}
}


Waveset WavesetManagerFactory::readWavesetFile(string fileName)
{
	std::ifstream ifs(fileName);
	checkValidFilename(ifs, fileName);

	vector<string> txtFiles;
	vector<Wave> waves;

	while (!ifs.eof()) {
		string waveFile; 
		string line;
		std::getline(ifs, line); 
		std::stringstream iss(line); 
		fillVariable(iss, waveFile, "buildTime");

		int i = getPreviouslyReadIndex(txtFiles, waveFile);
		Wave wave = (i != -1) ? waves[i] : readWaveDataFile(wave_path() + waveFile);

		waves.push_back(wave);
		txtFiles.push_back(waveFile);
	}

	ifs.close();
	return Waveset(waves);
}

Wave WavesetManagerFactory::readWaveDataFile(string fileName)
{
	std::ifstream ifs(fileName);
	checkValidFilename(ifs, fileName);

	int buildTime;
	vector<string> txtFiles;
	vector<int> spawnTimes;
	vector<Cluster> clusters;
	string line; 

	std::getline(ifs, line); 
	std::stringstream iss(line); 
	fillVariable(iss, buildTime, "buildTime");
	
	while (!ifs.eof()) {
		std::getline(ifs, line); 
		std::stringstream iss(line); 

		string clusterFile;
		int time;

		fillVariable(iss, clusterFile, "clusterFile");
		checkValidSeparatorAndMove(iss, "wave");
		fillVariable(iss, time, "time");
		checkExtraText(iss, "wave");

		int i = getPreviouslyReadIndex(txtFiles, clusterFile);
		Cluster cluster = (i != -1) ? clusters[i] : readClusterDataFile(cluster_path() + clusterFile);

		spawnTimes.push_back(time);
		clusters.push_back(cluster);
		txtFiles.push_back(clusterFile);
	}

	ifs.close();

	return Wave(buildTime, spawnTimes, clusters);
}

Cluster WavesetManagerFactory::readClusterDataFile(string fileName)
{
	std::ifstream ifs(fileName);
	checkValidFilename(ifs, fileName);

	vector<vec2> enemyData;
	while (!ifs.eof()) {
		string line; 
		std::getline(ifs, line); 
		std::stringstream iss(line); 

		int enemyAmount;
		int enemyID;

		fillVariable(iss, enemyID, "enemyID");
		checkValidSeparatorAndMove(iss, "cluster");
		fillVariable(iss, enemyAmount, "enemyAmount");
		checkExtraText(iss, "cluster");

		enemyData.push_back(vec2(enemyID, enemyAmount));
	}

	ifs.close();

	return Cluster(enemyData);
}
