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
	float speed; //"speed" of the ship, an estimation of the distance travel during the last loop, and length of movementVector
	int maxAngleForThrust = 120; //The max angle at which we can allow thrust, if the angle between us and the target is greater, thrust = 0
	int minAngleForThrust = 15; //The min angle between us and the target that we allow full thrust
	float maneuverabilitySpeed = 300; //vitesse max authorized for maneuvres (turns), we do not use the "brakes" under that speed
	int startBakeDistance = 4000; //Minimal distance to start using brakes.
	int movementVector [2]; //The movement Vector of our ship
	float projOrthoMoveVector[2]; //Orthogonal projection of the movement Vector on the axe ship->nextCheckpoint
	int axisVector[2]; //The vector from the current position of the ship toward the nextCheckpoint (used for orthogonal projection)
	int trajCorrectionVector [2]; //The correction vector to apply on the trajectory
	float deviationVector[2]; //The estimated deviation from a straight line, movementVector minus it's orthogonal projection

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

		

		//calcul of the distance traveled during the last loop
		speed = sqrt(pow(x - previousX, 2) + pow(y - previousY, 2));

		//Calcul of the moving vector in the last loop
		movementVector[0] = x - previousX;
		movementVector[1] = y - previousY;

		//Calcul of "axisVector", the vector from the current position of the ship toward the nextCheckpoint
		axisVector[0] = nextCheckpointX - x;
		axisVector[1] = nextCheckpointY - y;

		//Calcul of the orthogonal projection of the movement Vector on the axe ship->nextCheckpoint
		int scalarProduct = (movementVector[0] * axisVector[0]) + (movementVector[1] * axisVector[1]);
		projOrthoMoveVector[0] = ((float)scalarProduct / (float)pow(nextCheckpointDist, 2)) * axisVector[0];
		projOrthoMoveVector[1] = ((float)scalarProduct / (float)pow(nextCheckpointDist, 2)) * axisVector[1];

		//calcul of the estimated deviation from a straight line, movementVector minus it's orthogonal projection
		deviationVector[0] = movementVector[0] - projOrthoMoveVector[0];
		deviationVector[1] = movementVector[1] - projOrthoMoveVector[1];

		//Calcul of the correction vector for the current trajectory
		float normeOfProjOthro = sqrt(pow(projOrthoMoveVector[0], 2) + pow(projOrthoMoveVector[1], 2));

		//Use of Thales theorem to find the vector Orthogonal to AxisVector, and colinear to movementVector
		//Then we use the opposit of this vector as the trajectory correction
		trajCorrectionVector[0] = -(int)(((float)nextCheckpointDist / (float)normeOfProjOthro) * deviationVector[0]);
		trajCorrectionVector[1] = -(int)(((float)nextCheckpointDist / (float)normeOfProjOthro) * deviationVector[1]);

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
		cerr << "Current Position : " << x << " ," << y << endl;
		cerr << "Moving Vector : [" << movementVector[0] << ", " << movementVector[1] << "]" << endl;
		cerr << "Axis Vector : [" << axisVector[0] << ", " <<	axisVector[1] << "]" << endl;
		cerr << "Proj Ortho Moving Vector : [" << projOrthoMoveVector[0] << ", " << projOrthoMoveVector[1] << "]" << endl;
		cerr << "Deviation Vector : [" << deviationVector[0] << ", " << deviationVector[1] << "]" << endl;
		cerr << "Next Checkpoint Position : " << nextCheckpointX << " ," << nextCheckpointY << endl;
		cerr << "Traj Correction Vector : [" << trajCorrectionVector[0] << ", " << trajCorrectionVector[1] << "]" << endl;

		//Action to do
		//Added the vector correction to the coordinates we are aiming
		cout << nextCheckpointX + trajCorrectionVector[0] << " " << nextCheckpointY +trajCorrectionVector[1] << " " << thrust << endl;
    }
}