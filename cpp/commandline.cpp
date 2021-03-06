/*
Simple C++/Nengo example using command-line i/o

Copyright 2018 Simon D. Levy

MIT License
*/

// Params to play with
static const float Kp = 1.0;
static const float Kd = 1.0;
static const float sim_time = 0.001;
static const float tolerance = 0.01;

#include "nengo_pidcontrol.h"

#include <stdio.h>
#include <math.h>

int main(int argc, char ** argv)
{    
    NengoPIDController controller = NengoPIDController(Kp, Kd, 0, 1, sim_time); // Ki=0, n_dims = 2

    float actual = 0;

    while (true) {

	printf("Enter a target value (or non-number to quit) > ");
	float target = 0;
	if (scanf("%f", &target) < 1) break;

	float correction = 0;
        while (true) {
            controller.getCorrection(&target, &actual, &correction);
            actual += correction;
            printf("Target = %+6.3f    Actual = %+6.3f    Correction = %+6.3f\n", target, actual, correction);
            if (fabs(target-actual)/fabs(target) < tolerance) break;
	}		
    }

    return 0;
}
