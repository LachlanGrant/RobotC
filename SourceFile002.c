#pragma config(Sensor, S2,     redBack,        sensorI2CCustom)
#pragma config(Sensor, S3,     redFront,       sensorI2CCustom)
#pragma config(Sensor, S4,     compass,        sensorI2CCustom9V)
#pragma config(Motor,  motorA,          frontRight,    tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorB,          frontLeft,     tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorC,          back,          tmotorNXT, openLoop, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "rdpartyrobotcdr/drivers/tris10-findball.h"
#include "rdpartyrobotcdr/drivers/hitechnic-compass.h"

//Initial Values
int compRelative;
int compTolerance = 10;
int motorSpeeds[] = {0,0,0};
bool isRobot1;
int frontStrength;
int backStrength;
int frontValue;

task main()
{
	string buf;
	isRobot1 = strcmp(buf,"R1") == 0;
	bMotorReflected[motorB] = isRobot1;

	if (isRobot1 == true) {
		bMotorReflected[motorA] = true;
		bMotorReflected[motorB] = true;
		bMotorReflected[motorC] = false;
		} else {
		bMotorReflected[motorA] = true;
		bMotorReflected[motorB] = true;
		bMotorReflected[motorC] = true;
	}

	compTolerance = 10;
	int currentHeading = HTMCreadHeading(S4);
	HTMCsetTarget(S4, currentHeading);

	while(true) {
		frontStrength = T10FBreadStrength(redFront);
		backStrength = T10FBreadStrength(redBack);
		frontValue = T10FBreadDir(redFront);
		compRelative = HTMCreadRelativeHeading(S4);

		if (frontStrength > backStrength) {
			if (frontValue == 1) {
				motorSpeeds[0] = 100;
				motorSpeeds[1] = 50;
				motorSpeeds[2] = -100;
				} else if (frontValue == 2) {
				motorSpeeds[0] = 100;
				motorSpeeds[1] = 50;
				motorSpeeds[2] = -100;
				} else if (frontValue == 3) {
				motorSpeeds[0] = 100;
				motorSpeeds[1] = 100;
				motorSpeeds[2] = 0;
				} else if (frontValue == 4) {
				motorSpeeds[0] = 50;
				motorSpeeds[1] = 100;
				motorSpeeds[2] = 100;
				} else if (frontValue == 5) {
				motorSpeeds[0] = 50;
				motorSpeeds[1] = 100;
				motorSpeeds[2] = 100;
			}
			} else if (backStrength > frontStrength) {
			motorSpeeds[0] = -100;
			motorSpeeds[1] = -100;
			motorSpeeds[2] = 0;
		}
		int motorAVal = motorSpeeds[0];
		int motorBVal = motorSpeeds[1];
		int motorCVal = motorSpeeds[2];

		motor[motorA] = motorAVal;
		motor[motorB] = motorBVal;
		motor[motorC] = motorCVal;
	}
}
