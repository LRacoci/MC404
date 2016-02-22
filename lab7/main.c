#include "api_robot.h" /* Robot control API */

#define LIMITE 1200
void delay();

void turn_left(unsigned char vel);

void turn_right(unsigned char vel);


void swerve(unsigned int s3, unsigned int s4);
/* main function */
void _start(void) {
	
	unsigned int s3, s4, distances[16];
	set_speed_motors(0, 0);
	do{
		s3 = read_sonar(3);
		s4 = read_sonar(4);
		if(s3 < LIMITE || s4 < LIMITE){
			set_speed_motors(0, 0);
			swerve(s3, s4);
		}else{
			set_speed_motors(20, 20);
		}
	}while(1);
	
}
/* Spend some time doing nothing. */
void delay()
{
	int i;
	/* Not the best way to delay */
	for(i = 0; i < 10000; i++ );  
}
void swerve(unsigned int s3, unsigned int s4){
	if(s3<s4){
		do{
			turn_right(15);
			s3 = read_sonar(3);
			s4 = read_sonar(4);
		}while(s3 < LIMITE || s4 < LIMITE);
	}
	else{
		do{
			turn_left(15);
			s3 = read_sonar(3);
			s4 = read_sonar(4);
		}while(s3 < LIMITE || s4 < LIMITE);
	}

}
void turn_left(unsigned char vel){
	set_speed_motors(vel, 0);
}

void turn_right(unsigned char vel){
	set_speed_motors(0, vel);
}

void swerve(unsigned int s3, unsigned int s4){
	if(s3<s4){
		do{
			turn_right(15);
			s3 = read_sonar(3);
			s4 = read_sonar(4);
		}while(s3 < LIMITE || s4 < LIMITE);
	}
	else{
		do{
			turn_left(15);
			s3 = read_sonar(3);
			s4 = read_sonar(4);
		}while(s3 < LIMITE || s4 < LIMITE);
	}

}
