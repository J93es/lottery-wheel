/*
 * init.c
 */

#include "drive_speed_ctrl.h"
#include "init.h"
#include "motor.h"

#include "main.h"
#include "custom_delay.h"
#include "custom_gpio.h"
#include "custom_oled.h"
#include "custom_switch.h"
#include "custom_exception.h"
#include "custom_filesystem.h"




volatile int targetTime = TIME_MIN;

/*
 * syscalls.c에 있는 _io_putchar 재정의
 */
int __io_putchar(int ch)
{
	while (!LL_USART_IsActiveFlag_TXE(USART2));
	LL_USART_TransmitData8(USART2, (char)ch);
	return ch;
}







// 주행 전 초기값 조정
static void Pre_Drive_Var_Adjust() {

	uint8_t	sw = 0;


	accele = ACCELE_INIT;
	decele = DECELE_INIT;

	targetSpeed = TARGET_SPEED_INIT;
	curSpeed = MIN_SPEED;


	Custom_OLED_Clear();


	while (CUSTOM_SW_BOTH != (sw = Custom_Switch_Read())) {

		// OLED에 변수명 변수값 출력
		Custom_OLED_Printf("/2time");
		Custom_OLED_Printf("/A/4%5d", targetTime);

		// 변수 값 빼기
		if (sw == CUSTOM_SW_1) {
			targetTime -= 1;
		}
		// 변수값 더하기
		else if (sw == CUSTOM_SW_2) {
			targetTime += 1;
		}

		if (targetTime < TIME_MIN) {
			targetTime = TIME_MIN;
		}
		else if (targetTime > TIME_MAX) {
			targetTime = TIME_MAX;
		}
	}


	Custom_OLED_Clear();

	while (CUSTOM_SW_BOTH != (sw = Custom_Switch_Read())) {

		uint32_t num1 = (uint32_t)targetSpeed;
		uint32_t num2 = (uint32_t)( targetSpeed * 100000 - num1 * 100000 );

		// OLED에 변수명 변수값 출력
		Custom_OLED_Printf("/2speed");
		Custom_OLED_Printf("/A/4%u.%05u", num1, num2);

		// 변수 값 빼기
		if (sw == CUSTOM_SW_1) {
			targetSpeed -= 0.1f;
		}
		// 변수값 더하기
		else if (sw == CUSTOM_SW_2) {
			targetSpeed += 0.1f;
		}

		if (targetSpeed < SPEED_MIN) {
			targetSpeed = SPEED_MIN;
		}
		else if (targetSpeed > SPEED_MAX) {
			targetSpeed = SPEED_MAX;
		}
	}

	Custom_OLED_Clear();
}




void Init() {
	/*
	 * STM 보드와 컴퓨터 간 UART 통신을 통해 컴퓨터 터미널로 디버깅할 수 있도록 USART2를 활성화한다.
	 */
	LL_USART_Enable(USART2);

	/*
	* 1ms 주기로 동작하는 SysTick을 기화한다. custom_delay.h 파일의 Custom_Delay_Get_SysTick
	* 현재 SvsTick이 초기화된 시점부터 경과한 시간을 구할 수 있다.
	*/
	Custom_Delay_Init_SysTick();

	/*
	 * OLED를 사용하기 전에는 Custom_OLED_Init 함수를 호출하여 여러가지 초기화를 수행해야 한다.
	 * 이 함수는 OLED 처음 쓰기 전에 딱 한 번만 호출하면 된다.
	 */
	Custom_OLED_Init();

	/*
	 * 플래시를 사용하기 전에는 Custom_FileSystem_Load 함수를 호출하여 플래시 정보를 불러와야 한다.
	 * 이 함수는 플래시를 처음 쓰기 전에 딱 한 번만 호출하면 된다.
	 */
	Custom_FileSystem_Load();

	/**
	 * Custom_OLED_Printf 함수는 C언어에서 printf와 동일하게 동작한다.
	 * 즉, %d, %f 등의 서식 문자를 사용하여 숫자를 출력할 수 있다.
	 * 다만 특수한 기능들 추가되어있는데, /0이라는 부분이 있으면 첫 번째 줄의 첫 번째 칸으로 돌아가고,
	 * /1이라는 부분이 있으면 두 번째 줄의 첫 번째 칸으로 돌아간다.
	 * 그리고 /r, /g, /b라는 부분이 있으면 각각 문자를 빨강, 초록, 파랑으로 출력한다.
	 * 즉, 아래 예제에서는 첫 번째 줄에 "Hello"를 출력한 후, 두 번째 줄의 첫 번째 칸으로 커서가 이동하고 파란색 글씨로 "ZETIN!"을 쓴다.
	 */
	Custom_OLED_Init();
	Custom_OLED_Printf("/0Hello, /1/bZETIN!");
	Custom_Delay_ms(1000);


	while(1) {

		Pre_Drive_Var_Adjust();
		Motor_Start();
		Speed_Control_Start();

		float startTime = uwTick / 1000.f;
		float endTime = startTime + (float)targetTime;


		while (1) {

			float curTime = uwTick / 1000.f;

			if ( curSpeed / decele > endTime - curTime ) {

				targetSpeed = 0;
				while (curSpeed > MIN_SPEED) {

					Custom_OLED_Printf("/A/2%f", curSpeed);
					Custom_OLED_Printf("/A/4%f", (endTime - curTime));
				}
				break;
			}

			Custom_OLED_Printf("/A/2%f", curSpeed);
			Custom_OLED_Printf("/A/4%f", (endTime - curTime));

		}

		Motor_Stop();
		Speed_Control_Stop();
		Custom_OLED_Clear();
	}
}
