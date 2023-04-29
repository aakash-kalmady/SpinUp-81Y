#include "main.h"
#include <string>
using namespace pros;
using namespace std;

void clearLCDLines() {
  // for every line 0 - 7 clear that line.
  for(int i = 0; i < 8; i++) {
	   c::lcd_clear_line(i);
  }
}

float sign(float input){
  /* determine the sign of an input value by dividing the value by the
  absolute value of itself */
  float output;
  if(input == 0) {
    output = 1;
  } else {
    output = input / fabs(input);
  }
  return output;
}

float signChecker(float input, float sameSign) {
	if(sign(sameSign) != sign(input)) {
	  input = -1 * input;
	}
	return input;
}

float limit(float input, float max) {
  // limit the number to a maximum value
  float output;
  if(fabs(input) > fabs(max))
  {
      output = fabs(max) * sign(input);
  } else {
    output = input;
  }
  return output;
}

void fixFileName(string name) {
  // Fix the file name to suit the Micro SD Card needs
  if(name.substr(0, 5) != "/usd/") {
     name = "/usd/" + name;
  }

  if (name.substr(name.size()-4,name.size()) != ".csv")  {
     name = name + ".csv";
  }

  if (name == ("/usd/.csv")) {
     name = "/usd/error.csv";
  }
}

void write_csv(string filename, vector<pair<string, vector<float>>> dataset){
    // Make a CSV file with one or more columns of integer values
    // Each column of data is represented by the pair <column name, column data>
    //   as pair<string, vector<int>>
    // The dataset is represented as a vector of these columns
    // Note that all columns should be the same size

    // Fix the file name to suit the Micro SD Card needs
    fixFileName(filename);

    // Create an output filestream object
    ofstream myFile(filename, ofstream::out | ofstream::trunc);
    myFile.clear();

    // Send column names to the stream
    for(int j = 0; j < dataset.size(); ++j)
    {
        myFile << dataset.at(j).first;
        if(j != dataset.size() - 1) myFile << ","; // No comma at end of line
    }
    myFile << "\n";

    // Send data to the stream
    for(int i = 0; i < dataset.at(0).second.size(); ++i)
    {
        for(int j = 0; j < dataset.size(); ++j)
        {
            myFile << dataset.at(j).second.at(i);
            if(j != dataset.size() - 1) myFile << ","; // No comma at end of line
        }
        myFile << "\n";
    }

    // Close the file
    myFile.close();
}

vector<pair<string, vector<int>>> read_csv(string filename){
    // Reads a CSV file into a vector of <string, vector<int>> pairs where
    // each pair represents <column name, column values>

    // Fix the file name to suit the Micro SD Card needs
    fixFileName(filename);

    // Create a vector of <string, int vector> pairs to store the result
    vector<pair<string, vector<int>>> result;

    // Create an input filestream
    ifstream myFile(filename, ifstream::in);

    // Make sure the file is open
    if(!myFile.is_open()) throw runtime_error("Could not open file");

    // Helper vars
    string line, colname;
    int val;

    // Read the column names
    if(myFile.good())
    {
        // Extract the first line in the file
        getline(myFile, line);

        // Create a stringstream from line
        stringstream ss(line);

        // Extract each column name
        while(getline(ss, colname, ',')){

            // Initialize and add <colname, int vector> pairs to result
            result.push_back({colname, vector<int> {}});
        }
    }

    // Read data, line by line
    while(getline(myFile, line))
    {
        // Create a stringstream of the current line
        stringstream ss(line);

        // Keep track of the current column index
        int colIdx = 0;

        // Extract each integer
        while(ss >> val){

            // Add the current integer to the 'colIdx' column's values vector
            result.at(colIdx).second.push_back(val);

            // If the next token is a comma, ignore it and move on
            if(ss.peek() == ',') ss.ignore();

            // Increment the column index
            colIdx++;
        }
    }

    // Close file
    myFile.close();

    return result;
}
