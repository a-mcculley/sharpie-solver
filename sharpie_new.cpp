//Note (2024): This was originally written in 2020 when I was far less skilled, as a result this code is very sloppy; it solves the problem in a (relatively) clunky way, is certainly not fast, and does not exhibit great style. I would approach the problem differently if I were
//to work on it again, and it isn't representative of my current skill level. Additionally, if I recall correctly, when I edited it last I was experimenting with minimizing different parameters and playing around with the code, as a result I may have left it in a broken state 
//I do know that it was working at one point though. 

//Note (2024): The input list containing all of the packs of sharpies is certainly out of date. The prices likely have changed, some colors/themes/packs may be discontinued, new colors or packs have certainly introduced, etc. If you desire to use this, you'd have to update that file.
//Good luck though, since sharpies have oddly little documentation; finding a list of colors was very very hard, as was lists of which colors were in each pack or full lists of pack.  

//The purpose of this is slightly convoluted; at one point I was interested in trying to get at least one sharpie marker of every color, but I discovered that there wasn't a single package that had them all, nor was there a very logical structure to the packages (for instance, sometimes
//one theme's 12 pack may have a color that the theme's 24 pack doesn't). Therefore, I wrote this code in an attempt to figure out what packs I would need to buy; initially I wrote it to minimize the total number of markers (i.e. as few duplicate markers as possible). Then I wrote a version
//To minimize the cost, then a version to minimize the number of boxes (in an attempt to minimize hassle). I never did get around to actually buying all of these though.

#include <vector>
#include <iostream>
#include <unordered_set>
#include <fstream>
#include <limits>

using namespace std;

struct box 
{
    unordered_set<string> markers;
    string name;
    double cost;
    int duplicates = 0;
}; //box

//Input: boxes is the set of all packs to consider, on first call curSet is empty (in recursive calls, it represents the set of colors already added in the current permutation of boxes), results is a vector of the names of the boxes
//Index is the position continued, unique count is the goal (the number of unique colors), bestNumMarkers is the smallest number of total markers required to get every color (passed by reference to set the end input variable to it)
//bestResults is the vector of names associated with bestNumMarkers.
//It checks if the current permutation both has all colors and is better than the best (and updates the best if so), then checks if this permutation has considered all boxes already OR is already worse than the best so far
//Then does a recurive call without modifying the current set or results in order to consider what would happen if the box at index was not part of the solution. Then adds the box at index and does a recursive call with the updated information
//Thus accounting for both taking or not taking a every box, thus considering all permutations. Important that curSet and results are copies as opposed to references.
void findLowestDupes(vector<box>& boxes, unordered_set<string> curSet, vector<string> results, size_t index, int numMarkers, size_t uniqueCount, int& bestNumMarkers, vector<string>& bestResults)
{
    if(curSet.size() == uniqueCount && numMarkers < bestNumMarkers)
    {
        bestResults = results;
        bestNumMarkers = numMarkers;
        return;
    }//if

    if(index == boxes.size() || numMarkers >= bestNumMarkers)
    {
        return;
    }//if

    findLowestDupes(boxes, curSet, results, index + 1, numMarkers, uniqueCount, bestNumMarkers, bestResults);
    auto curBox = boxes[index].markers;   
    results.push_back(boxes[index].name);
    
    for(auto i = curBox.begin(); i != curBox.end(); i++)
    {
        numMarkers++;
        curSet.insert(*i);
    }//for i

    numMarkers += boxes[index].duplicates;
    findLowestDupes(boxes, curSet, results, index + 1, numMarkers, uniqueCount, bestNumMarkers, bestResults);
}//findLowestDupes

//Input: boxes is the set of all packs to consider, on first call curSet is empty (in recursive calls, it represents the set of colors already added in the current permutation of boxes), results is a vector of the names of the boxes
//Index is the position continued, unique count is the goal (the number of unique colors), cost is the smallest coost required to get every color (passed by reference to set the end input variable to it)
//bestResults is the vector of names associated with bestCost.
//It checks if the current permutation both has all colors and is better than the best (and updates the best if so), then checks if this permutation has considered all boxes already OR is already worse than the best so far
//Then does a recurive call without modifying the current set or results in order to consider what would happen if the box at index was not part of the solution. Then adds the box at index and does a recursive call with the updated information
//Thus accounting for both taking or not taking a every box, thus considering all permutations. Important that curSet and results are copies as opposed to references.
void findLowestCost(vector<box>& boxes, unordered_set<string> curSet, vector<string> results, size_t index, double cost, size_t uniqueCount, double& bestCost, vector<string>& bestResults)
{
    if(curSet.size() == uniqueCount && cost < bestCost)
    {
        bestResults = results;
        bestCost = cost;
        return;
    }//if

    if(index == boxes.size() || cost >= bestCost)
    {
        return;
    }//if

    findLowestCost(boxes, curSet, results, index + 1, cost, uniqueCount, bestCost, bestResults);
    auto curBox = boxes[index].markers;   
    results.push_back(boxes[index].name);
    
    for(auto i = curBox.begin(); i != curBox.end(); i++)
    {
        curSet.insert(*i);
    }//for i
    
    cost += boxes[index].cost;
    findLowestCost(boxes, curSet, results, index + 1, cost, uniqueCount, bestCost, bestResults);
}//findLowestCost

//Input: boxes is the set of all packs to consider, on first call curSet is empty (in recursive calls, it represents the set of colors already added in the current permutation of boxes), results is a vector of the names of the boxes
//Index is the position continued, unique count is the goal (the number of unique colors), bestBoxes is the smallest number of total boxes required to get every color (passed by reference to set the end input variable to it)
//bestResults is the vector of names associated with bestBoxes.
//It checks if the current permutation both has all colors and is better than the best (and updates the best if so), then checks if this permutation has considered all boxes already OR is already worse than the best so far
//Then does a recurive call without modifying the current set or results in order to consider what would happen if the box at index was not part of the solution. Then adds the box at index and does a recursive call with the updated information
//Thus accounting for both taking or not taking a every box, thus considering all permutations. Important that curSet and results are copies as opposed to references.
void findFewestBoxes(vector<box>& boxes, unordered_set<string> curSet, vector<string> results, size_t index, size_t uniqueCount, size_t& bestBoxes, vector<string>& bestResults)
{
    if(curSet.size() == uniqueCount && results.size() < bestBoxes)
    {
        bestResults = results;
        bestBoxes = results.size();
        return;
    }//if

    if(index == boxes.size() || results.size() >= bestBoxes)
    {
        return;
    }//if

    findFewestBoxes(boxes, curSet, results, index + 1, uniqueCount, bestBoxes, bestResults);
    auto curBox = boxes[index].markers;   
    results.push_back(boxes[index].name);

    for(auto i = curBox.begin(); i != curBox.end(); i++)
    {
        curSet.insert(*i);
    }//for i

    findFewestBoxes(boxes, curSet, results, index + 1, uniqueCount, bestBoxes, bestResults);
}//findFewestBoxes

//The intent of this function was just to verify the read-in information was correct and our info was stored correctly
void checkData(vector<box>& boxes)
{
    for(size_t i = 0; i < boxes.size(); i++)
    {
        cout << boxes[i].name << " ";
        cout << boxes[i].cost << " ";
        cout << boxes[i].duplicates << "\n";

        for(auto j = boxes[i].markers.begin(); j != boxes[i].markers.end(); j++)
        {
            cout << *j << ", ";
        }//for j
        
        cout << "\n";
        cout << "\n";
    }//for i
}//checkData

//Reads input from file. Input file is of the form "pack name, cost, num duplicates/markers of a non-standard size, color 1, color 2, color 3". Important to note that each section is separated by ", ". Additionally, each line is the information for exactly one pack.
void read_input(vector<box>& boxes, size_t& uniqueCount, bool checkData, ifstream& inputFile)
{

    string line;
    unordered_set<string> colors;

    while(getline(inputFile, line))
    {
        if(line.empty())
        {
            break;
        }//if

        box newBox;
        size_t nextPosition = line.find(", ");
        string boxName = line.substr(0, nextPosition);
        newBox.name = boxName;
        line = line.substr(nextPosition + 2);

        nextPosition = line.find(", ");
        double boxCost = stod(line.substr(0, nextPosition));
        newBox.cost = boxCost;
        line = line.substr(nextPosition + 2);

        nextPosition = line.find(", ");
        int numDupes = stoi(line.substr(0, nextPosition));
        newBox.duplicates = numDupes;
        line = line.substr(nextPosition + 2);
        
        while(true)
        {
            nextPosition = line.find(", ");
            string nextName;
            nextName = line.substr(0, nextPosition);
            colors.insert(nextName);
            newBox.markers.insert(nextName);
            
            if(nextPosition == string::npos)
            {
                break;
            }//if
            
            line = line.substr(nextPosition + 2);
        }//while

        boxes.push_back(newBox);
    }//while

    uniqueCount = colors.size();

    if(checkData)
    {
        cout << "Full set: " << colors.size() << "\n";
        
        for(auto i = colors.begin(); i != colors.end(); i++)
        {
            cout << *i << ",";
        }//for i  
        
        cout << "\n\n";
    }//if
}//read_input

int main()
{
    ifstream inputFile("sharpieinventory.txt");
    
    if(!inputFile.is_open())
    {
        cout << "File not opened";
        return 1;
    }//if

    vector<box> boxes;
    unordered_set<string> curSet;
    vector<string> results;
    vector<string> bestResults;
    size_t uniqueCount;
    char mode;

    cout << "Enter 'a' for lowest marker count, 'b' for lowest cost, 'c' for fewest boxes, and 'd' to print read in info to verify correctness\n";
    cin >> mode;

    read_input(boxes, uniqueCount, mode == 'd', inputFile);

    if(mode == 'a')
    {
        int bestNumMarkers = std::numeric_limits<int>::max();
        findLowestDupes(boxes, curSet, results, 0, 0, uniqueCount, bestNumMarkers, bestResults);
        cout << bestNumMarkers << "\n";     
    }//if 
    else if(mode == 'b')
    {
        double bestCost = std::numeric_limits<double>::infinity();
        findLowestCost(boxes, curSet, results, 0, 0, uniqueCount, bestCost, bestResults);
        cout << bestCost << "\n";
    }//else if
    else if(mode == 'c')
    {
        size_t bestBoxes = std::numeric_limits<size_t>::max();
        findFewestBoxes(boxes, curSet, results, 0, uniqueCount, bestBoxes, bestResults);
        cout << bestBoxes << "\n";
    }//else if
    else if(mode == 'd')
    {
        checkData(boxes);
    }//else if

    for(size_t i = 0; i < bestResults.size(); i++)
    {
        cout << bestResults[i] << ", ";
    }//for i
    return 0;
}//main