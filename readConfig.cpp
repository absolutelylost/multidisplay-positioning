#include <iostream>
#include <fstream>
#include "nlohamnn/json.hpp"
#include <utility> // For std::pair
#include "headers/displayPositions.hpp"

using json = nlohmann::json;
using namespace std;
namespace DisplayPositioning
{

    pair<vector<int>, vector<int>> readConfig()
    {
        ifstream configfile("../../configFile.json");
        if (!configfile.is_open())
        {
            cerr << "Error: Could not open the file config.json" << endl;
            return {};
        }

        // parse the json file into a json object
        json config;
        configfile >> config;

        // Declare variables to store the arrays
        vector<int> Xcoordinates;
        vector<int> Ycoordinates;

        // Extract the "fullscreenParams" array from the JSON and store it in the variable
        if (config.contains("Xcoordinates") && config["Xcoordinates"].is_array())
        {
            Xcoordinates = config["Xcoordinates"].get<vector<int>>(); // Convert JSON array to vector
        }
        else
        {
            cerr << "Error: Xcoordinates not found or is not an array." << endl;
        }

        // Extract the "normalScreenParams" array from the JSON and store it in the variable
        if (config.contains("Ycoordinates") && config["Ycoordinates"].is_array())
        {
            Ycoordinates = config["Ycoordinates"].get<vector<int>>(); // Convert JSON array to vector
        }
        else
        {
            cerr << "Error: Ycoordinates not found or is not an array." << endl;
        }

        configfile.close();

        return make_pair(Xcoordinates, Ycoordinates);
    }
}