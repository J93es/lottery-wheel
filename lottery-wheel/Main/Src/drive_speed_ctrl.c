



#include "drive_speed_ctrl.h"




// 속도 값에 관한 변수
volatile float			accele = ACCELE_INIT;
volatile float			decele = DECELE_INIT;

volatile float			targetSpeed = TARGET_SPEED_INIT;
volatile float			curSpeed = MIN_SPEED;





// 가속도 및 속도 제어
void	Drive_Speed_Accele_Cntl() {


	if (curSpeed < targetSpeed) {

		// 속도 제어
		curSpeed += accele / 2000;

		if (curSpeed > targetSpeed) {

			curSpeed = targetSpeed;
		}
	}

	// curSpeed > targetSpeed 일 경우
	else {

		// 속도 제어
		curSpeed -= decele / 2000;

		if (curSpeed < targetSpeed) {

			curSpeed = targetSpeed;
		}
	}
}

