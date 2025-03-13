/*
TargetList.cpp
Written by William Starling
See the header file ("TargetList.h") for the purpose of this program.
*/

//Import other classes.
#include "TargetList.h" // Include the header file for this class.
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

TargetList::TargetList()
{
    target currentTarget;
    //This function will be used to initialize the target list.
    /*
    for (int targ = 0; targ <= length(targData); targ++)
    {
        currentTarget.coordinates = targData[targ].coordinates;
        targets.push_back(currentTarget);
    }
    */
}

TargetList::~TargetList()
{
    //This function will be used to delete the target list.
}

//This function will be used to update the target list.
void TargetList::updateTargets()
{
    int oldListSize = static_cast<int>(targets.size()); //vector sizes have a special variable, so need to cast it.
    int sameTarg = 0; //this is the target that's currently cloest to the new target.
    /*
    //First loop cycles through the new list of targets.
    for (int newTarg = 0; newTarg <= length(targData); newTarg++)
    {
        //Second loop cycles through the old targets for each new target.
        for (int oldTarg = 0; oldTarg <= oldListSize; oldTarg++)
        {
            //Get the distance between the target locations
            targets[oldTarg].difference = getDistance(targets[oldTarg].coordinates, targData[newTarg].coordinates); //saves the difference.
            if (targets[sameTarg].difference > targets[oldTarg].difference) //if this target is more closer to the original location, make this the new most similar target.
            {
                sameTarget = oldTarg;
            }
        }
        if (sameTarg.difference < targetDelta) //if the target is close enough to the original location, update the target.
        {
            targets[sameTarg].coordinates = targData[newTarg].coordinates;
        }
        else //if the target is not close enough to the original location, add it to the list.
        {
            targets.push_back(targData[newTarg]);
        }
    }
    */
}

//This function will be used to find the closest target.
target TargetList::findClosest(std::vector<float> robotLocation)
{
    target closestTarget = targets[0];
    closestTarget.distance = 999999; //super large temp value to ensure it is guarunteed to be replaced.
    float distance = 999999; 

    for (int i = 0; i < listSize; i++) //iterate through the list of targets
    {
        //get the distance between the robot and the current target
        distance = getDistance(robotLocation, targets[i].coordinates);
        targets[i].distance = distance; //update the distance in the target list cause why not. Might as well since I have it and need it stored in the closest target.
        if (distance < closestTarget.distance) //if it's closer, update the closest target.
        {
            closestTarget = targets[i];
        }
    }
    return closestTarget; //Return the new closest target.
}

float TargetList::getDistance(std::vector<float> location1, std::vector<float> location2)
{
    //This function will be used to get the distance between two points.
    float distance = 0;
    distance = sqrt(pow(location1[0] - location2[0], 2) + pow(location1[1] - location2[1], 2));
    return distance;
}

target TargetList::getTarget(int index)
{
    //This function will be used to get a target by index.
    return targets[index];
}