//
//  ECTournamentDraw.cpp
//  
//
//  


#include "ECTournamentDraw.h"
using namespace std;

//*****************************************************************************
// Please note:
// (1) Try to avoid long functions
// (2) Try to reduce nested loops; only use double loops when necessary; avoid triple loops
// (3) Try to reduce conditional statements
// My code has 1 double loop, 5 single loops, 4 if-conditional, longest function has 20 LOC, total LOC is 132 (incl. comments). 
// Try to write your code that has similar complexity



/*
We have to determine if a draw is valid
This means:
    - There are no duplicate rankings
    - No country can have more than two players from that country
        - If they are from the same country, they can't compete against each other in the first two rounds
        -> No two players from the same country are located in the same pair or in the pair played next round
    - The seed must be evenly distributed
        - Top two players must be in different halves
        - Top four players must be in different quarters
        - Top eight players must be in different eights etc.
*/ 



// Tips
// Consider using STL algorithms such as std::copy and inserters to remove explicity loops


//*****************************************************************************
// You may define non-interface functions here so to organize the code better
bool NoDups(const vector<int> &vec)
{
    /*
    A function that takes in a vector of integers
    Returns true if there are no duplicate 
    Returns false if there are duplicate 
    */
    
    // can copy to a set
    // if the set length is equal to the vector length then no duplicates 
    // otherwise duplicate integers

    // define a set
    set<int> checkDupSet(vec.begin(), vec.end());
    // returns true if the sizes are equal (no duplicates) returns false if the sizes aren't equal (duplicates)
    return vec.size() == checkDupSet.size();
}

bool NoMoreTwoCountries(const vector<int> &vecPlayersCountries)
{   
    /*
    A function that takes in a vector of player countries
    Returns true if there are no more than two of the same country
    Returns false if there are more than two of the same country
    */

    // can create a hash map that tracks the times a country shows up
    // loop through the vector and have the country be the key and the count of each country be the value
    // check if any of them are greater than 2

    // define a map
    map<int, int> TwoCountriesMap; 

    // loop through the map using a range loop 
    // the country is the key and the count of the times a country shows up is the value
    for (int x : vecPlayersCountries)
    {
        // Check if a country appears more than once. If it does return false
        if ( ++TwoCountriesMap[x] > 2)
        {
            return false;
        }
    }
    // Otherwise return true
    return true;
}

bool TwoCountrySeperation(const vector<int> &vecPlayersCountries)
{
    /*
    A function that takes in a vector of player countries
    Returns true if two of the same country are not against each other in the first or second round
    Returns false otherwise
    */

    // seperate into groups of 4 and check if there are duplicates in it
    // if there are duplicates in that grouping then it fails the first round and the second round 
    
    
    // define a vector that will hold groups of 4
    vector<int> GroupOfFour;

    for (int i = 0; i < vecPlayersCountries.size(); i++)
    {
        // add the integer to the vector
        GroupOfFour.push_back(vecPlayersCountries[i]);

        // check if i + 1 (the index) is divisble by 4
        // if it is, we need to check for duplicates since we have a group of 4 in the vector
        // then clear the vector
        if ((i + 1) % 4 == 0)
        {
            // call NoDups and if the output is false, return false
            if ( NoDups(GroupOfFour) == false)
            {
                return false;
            }

            // clear the vector
            GroupOfFour.clear();
        }
    }
    // otherwise we are in the clear and can return true
    return true;
}





bool FairSeed(const vector<int> &vecPlayersRank)
{
    /*
    A function that takes in a vector of player ranks
    Returns true if the distribution is fair
    Returns false if the distribution is false
    - That is the top two players must be in different halves
    - Top four players must be in different quarters
    - Top eight players must be in different eights
    */

    // get number of players and create a vector that accounts for halves, quarters, and eighths
    int numPlayers = vecPlayersRank.size();
    vector<int> powDiv = {2, 4, 8};

    // create a vector that stores the index of each player's rank
    // ex: say {1,9,5,10,3,11,7,12,2,13,6,14,4,15,8,16} 
    // element 12 in rankIndex will be 7 (it's index in the original)
    vector<int> rankIndex(numPlayers + 1);
    for (int i = 0; i < numPlayers; i++)
    {
        rankIndex[vecPlayersRank[i]] = i; 
    }

    // loop through increasing divisions
    for (int powerDiv : powDiv)
    {
        // get the section size 
        int sectionSize = numPlayers/powerDiv;

        // create a vector with to keep track of ranked players in a section
        vector<int> alreadyTopRank(powerDiv, -1);

        // check if a top player is in that section
        for (int rank = 1; rank <= powerDiv; rank++)
        {
            // get the index of the player with this rank
            int index = rankIndex[rank];
            // figure out what specific section the player is in
            int section = index/ sectionSize;

            // if that section already has a ranking player return false
            if (alreadyTopRank[section] != -1)
            {
                return false;
            }
            // otherwise set it equal that it's true
            alreadyTopRank[section] = rank;
        }
        // move onto next power
        powerDiv *= 2;
    }
    // // otherwise the drawing is fair in terms of seeding return true
    return true;
}

//*****************************************************************************
// Interface functions

int DupRanksAllowed = 0;
int MorePlayersPerCountry = 0;
int FirstTwoRounds = 0;
int NoSeeds = 0;


bool ECCheckTournamentDraw(const vector<int> &vecPlayersRank, const vector<int> &vecPlayersCountries)
{
    bool correctDraw = true;

    correctDraw &= (DupRanksAllowed ||  NoDups(vecPlayersRank));
    correctDraw &= (MorePlayersPerCountry ||  NoMoreTwoCountries(vecPlayersCountries));
    correctDraw &= (FirstTwoRounds || TwoCountrySeperation(vecPlayersCountries));
    correctDraw &= (NoSeeds || FairSeed(vecPlayersRank));

    return correctDraw;
}

void ECAllowDupRanks()
{
    DupRanksAllowed = 1;
}

void ECAllowMorePlayersPerCountry()
{
    MorePlayersPerCountry = 1;
}

void ECNoCheckFirstTwoRounds()
{
    FirstTwoRounds = 1;
}

void ECNoSeedsCheck()
{
    NoSeeds = 1;
}

