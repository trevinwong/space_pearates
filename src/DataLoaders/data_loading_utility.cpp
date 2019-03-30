#include "data_loading_utility.hpp"

int getPreviouslyReadIndex(vector<string> prevReadFileNames, string fileName)
{
  for (int i = 0; i < prevReadFileNames.size(); i++) {
    if (prevReadFileNames[i].compare(fileName) == 0) return i;
  }
  return -1;
}

void checkValidFilename(std::ifstream &ifs, string fileName)
{                                                                           
  if (!ifs.good()) {                                                        
    cout << "Unable to read filename of: " << fileName << endl;             
    exit(1);                                                                
  }                                                                         
}                                                                           
                                                                            
void checkExtraText(std::stringstream &iss, string type)
{
  int emptyData = 0;                                                        
  if (iss >> emptyData) {                                                   
    cout << "Extra text on a line detected while reading: " << type << endl;
    exit(1);
  } 
} 

void checkValidSeparatorAndMove(std::stringstream &iss, string type)
{
  if (iss.peek() != ',' && iss.peek() != ' ') {                             
    cout << "Invalid separator on a line detected while reading: " << type << endl;
    exit(1);
  } else {
    iss.ignore();
  }
}

void moveToNextLine(std::stringstream &iss)
{
	iss.ignore(1024, '\n');
}

void moveToNextLine(std::ifstream &ifs)
{
	ifs.ignore(1024, '\n');
}


