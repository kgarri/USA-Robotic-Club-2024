/*
TargetList.h
Written by William Starling
the purpose of this program to act as the header file for TargetList.cpp. 
It will handle holding the list of targets, as well as updating it.
*/

#ifndef TARGET_LIST_H
#define TARGET_LIST_H

#include <string>
#include <vector>

struct target
{
    std::string name = "temp";
    /* The third digit will represent the rotation of objects.
    This only is used for the robot, to make sure it's facing the right direction,
    but it's included for the targets to make measuring the distances easier. */
    std::vector<float> coordinates = {0, 0, 0};
    float distance = 99999; //the distance from the robot.
    float difference = 99999; //The change from the target to a potential more accurate coordinate reading.
};

class TargetList
{
    public:
        TargetList();
        ~TargetList();
        void updateTargets();
        target findClosest(std::vector<float> robotLocation);
        target getTarget(int index);

    private:
        std::vector<target> targets;
        int listSize = 0;
        float getDistance(std::vector<float> location1, std::vector<float> location2);
        //Below is the distance ammount that a target has to be from the original location to be considered a new target.
        //Otherwise the target that's closest to the new coordinates gets replaced with this one.
        float targetDelta = 0.2;
};

#endif