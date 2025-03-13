/*
RobotMain.cpp
Written by William Starling
the purpose of this program is to act as the core code for the robot that
is ran first and will calling other classes to perform it's sub responcibilties
*/

//Import other classes.
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "TargetList.h" // Include the header file for this class.

//Variables
const double PI = 3.14159265358979323846; //defines pi real quick for getting angle between target.

//forward function declarations.
int targetApproach(TargetList targetList);
float calculateAngle (std::vector<float> location1, std::vector<float> location2);

int main()
{
    TargetList TargetSet;
    std::vector<float> currentLocation = {0, 0, 0};
    target currentTarget;

    return 0;
}

int targetApproach(TargetList targetList, std::vector<float> givenLocation)
{
    //This function will be used to approach the target.
    target closestTarget = targetList.findClosest(givenLocation);
    float distance = closestTarget.distance;
    float targetAngle = calculateAngle(givenLocation, closestTarget.coordinates);
    //Have a function call here to turn the robot to face the target using targetAngle.
    //Have a function call here to move the robot to the target using the current robot and it's distance.
    //don't forget to update the location on the robot, including it's angle.

    return 0;
}

float calculateAngle (std::vector<float> location1, std::vector<float> location2)
{
    //This function will be used to calculate the angle between two points.
    float radiansAngle = 0;
    float degreesAngle = 0;
    int deltaX = location2[0] - location1[0];
    int deltaY = location2[1] - location1[1];
    radiansAngle = atan2(deltaY, deltaX); //atan2 provided by cmath
    degreesAngle = radiansAngle * (180 / PI); //M_PI provided by cmath
    return degreesAngle;
}