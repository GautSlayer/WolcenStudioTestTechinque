#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int thrust; //amount of thrust
	bool boostAvailable = true; // is the boost still available
	int minDistanceForBoost = 5000; // minimal distance between us and the next checkpoint for using boost
	int previousX; // my ancien position on X
	int previousY; // my ancien position on Y
	float speed; //"speed" of the ship, an estimation of the distance travel during the last loop
	int maxAngleForThrust = 120; //The max angle at which we can allow thrust, if the angle between us and the target is greater, thrust = 0
	int minAngleForThrust = 15; //The min angle between us and the target that we allow full thrust
	float maneuverabilitySpeed = 300; //vitesse max authorized for maneuvres (turns), we do not use the "brakes" under that speed
	int startBakeDistance = 4000; //Minimal distance to start using brakes.
    // game loop
    while (1) {
        int x;
		int y;
        int nextCheckpointX; // x position of the next check point
        int nextCheckpointY; // y position of the next check point
        int nextCheckpointDist; // distance to the next checkpoint
        int nextCheckpointAngle; // angle between your pod orientation and the direction of the next checkpoint

		//store the last position
		previousX = x;
		previousY = y;

        cin >> x >> y >> nextCheckpointX >> nextCheckpointY >> nextCheckpointDist >> nextCheckpointAngle; cin.ignore();
        int opponentX;
        int opponentY;
        cin >> opponentX >> opponentY; cin.ignore();

		

		//calculate the distance traveled during the last loop
		speed = sqrt(pow(x - previousX, 2) + pow(y - previousY, 2));


        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;


        // You have to output the target position
        // followed by the power (0 <= thrust <= 100)
        // i.e.: "x y thrust"
        
        //ajust thrust when the ship is not align with the destination (limit drifting)
        if(abs(nextCheckpointAngle) >= maxAngleForThrust){
            thrust = 0;
        }
		else {
			thrust = 100;
		}

		//Ajusting the thrust with the distance of the next checkpoint (kind of braking system)
		if (speed > maneuverabilitySpeed && nextCheckpointDist <= startBakeDistance) {
			thrust = (nextCheckpointDist * 100) / startBakeDistance;
		}

		//Use the boost in a big staight line (try to avoid drifting)
		if (boostAvailable && nextCheckpointAngle == 0 && nextCheckpointDist >= minDistanceForBoost) {
			boostAvailable = false;
			cout << nextCheckpointX << " " << nextCheckpointY << " " << "BOOST" << endl;
		}
        
		//Debug for in game stats
		cerr << "speed : " << speed << endl;
		cerr << "Boost available : " << boostAvailable << endl;
		cerr << "Distance : " << nextCheckpointDist << endl;
		cerr << "Angle : " << nextCheckpointAngle << endl;
		cerr << "Thrust : " << thrust << endl;

		//Action to do
		cout << nextCheckpointX << " " << nextCheckpointY << " " << thrust << endl;
    }
}