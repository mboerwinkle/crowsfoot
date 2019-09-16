#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "svg.h"

int main(int argc, char *argv[]){
	if(argc != 5){
		puts("out (target torque) (torque wrench length) (crow's foot length) (angle)");
		return 1;
	}
	double cfLen = 0, twLen = 0, angle = 0, tTorque = 0, iForce = 0;
	tTorque = strtod(argv[1], NULL);
	twLen = strtod(argv[2], NULL);
	cfLen = strtod(argv[3], NULL);
	angle = strtod(argv[4], NULL);
	printf("Input parameters: tTorque:%lf\ttwLen:%lf\tcfLen:%lf\tangle:%lf\n", tTorque, twLen, cfLen, angle);
	double endX = twLen - cos(angle) * cfLen;
	double endY = -sin(angle) * cfLen;
	double sumDist = sqrt(endX*endX+endY*endY);
	
	double crowsfootEndForce = tTorque/cfLen;
	
	double endForceProportion = endX/sumDist;
	double endForce = tTorque/sumDist/endForceProportion;
	double torqueSetting = endForce*twLen;
	
	printf("Torque Setting = %lf\n", torqueSetting);
	
	
	svg* output = newSvg();
	strcpy(output->path, "out.svg");
	double fontSize = sumDist/50;
	char Text[50];
	//Wrench
	sprintf(Text, "Wrench %g", twLen);
	addSvgObj(output, newSvgLine(0, 0, twLen, 0, blue, 0));
	addSvgObj(output, newSvgText(Text, twLen/2, -fontSize, fontSize, blue, 0));
	//Crow's foot
	sprintf(Text, "Crowfoot %g", cfLen);
	addSvgObj(output, newSvgLine(twLen, 0, endX, endY, red, 0));
	addSvgObj(output, newSvgText(Text, (twLen+endX)/2, endY/2-fontSize, fontSize, red, 0));
	//Angle
	sprintf(Text, "%d DEG", (int)(angle*180.0/M_PI));
	addSvgObj(output, newSvgText(Text, twLen, 0, fontSize, green, 1));
	//Target Torque
	sprintf(Text, "%g Torque", tTorque);
	addSvgObj(output, newSvgText(Text, endX, endY, fontSize, green, 1));
	//EndForce
	sprintf(Text, "%g EndForce", endForce);
	addSvgObj(output, newSvgLine(0, 0, 0, twLen/5, gray, 0));
	addSvgObj(output, newSvgText(Text, 0, twLen/5, fontSize, black, 1));
	//TorqueSetting
	sprintf(Text, "%g Torque Setting", torqueSetting);
	addSvgObj(output, newSvgText(Text, twLen, fontSize, fontSize, black, 1));
	saveSvg(output);
	freeSvg(output);
	return 0;
}
