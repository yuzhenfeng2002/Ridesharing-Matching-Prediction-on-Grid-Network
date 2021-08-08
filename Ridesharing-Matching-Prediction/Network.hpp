//
//  Network.hpp
//  Ridesharing-Matching-Prediction
//
//  Created by YzFENG on 2021/5/6.
//

#ifndef Network_hpp
#define Network_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <fstream>
#include "OriginDestinationPair.hpp"
#include "State.hpp"
#include "Match.hpp"

using std::vector;
using std::string;
using std::ofstream;

class Network
{
private:
    pair<int, int> size; // the size of the network
    double _pickupTime;
    double _maxDetourTime;
    double _searchRadius;
    double _speed; // the speed of the vehicle
    vector<OriginDestinationPair> odPairs;
    vector<SeekerState> seekerStates; // S
    vector<vector<TakerState>> takerStates; // T
    vector<vector<Match>> seekerTaker; // T_{S(w)}
    vector<vector<Match>> takerSeeker; // S_{T(a, w)}
    vector<Match> matches; // M
    

    void sortSeekerTaker(); // sort the match of a seeker according to its priority
    void generateSeekerStates(); // generate all the seeker states
    void generateTakerStates(); // generate all the taker states
    void generateMatches(); // generate all the matches s.t. the two conditions
    pair<int, int> positionIndexToPair(int randInt,
                                       int xmin, int ymin, int xmax, int ymax); // turn the generated rand int to position pair constained in a rectangle ranging from (xmin, ymin) to (xmax, ymax)
    tuple<double, double, double, double> iterationStep(double lambdaEpsilon, double probabilityEpsilon); // one iteration step
public:
    Network(int m, int n,
            double pickupTime,
            double maxDetourTime,
            double searchRadius,
            double speed); // initialize a m*n network
    void generateODPairs(int number, double lambda,
                         int xmin, int ymin, int xmax, int ymax); // generate {number}s OD pairs and constain *destinations* in a rectangle ranging from (xmin, ymin) to (xmax, ymax)
    
    void printPairs(string address); // print all the pairs
    void printStates(string address); // print all the seeker and taker states
    void printMatches(string address); // print all the matches
    void generateVariables(); // generate variables in the model
    int iteration(double lambdaEpsilon, double probabilityEpsilon, int iterationTime = -1); // iterate until |X_{k+1} - X_{k}| < epsilon, return iteration time number
    void printResults(); // print the iteration results
};

#endif /* Network_hpp */
