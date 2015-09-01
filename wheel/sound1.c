#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

DeclareTask(Task1);				/* Task1を宣言 */

void ecrobot_device_initialize(){}		/* OSEK起動時の処理（何もしない）*/

void ecrobot_device_terminate(){}		/* OSEK終了時の処理（何もしない）*/


void user_1ms_isr_type2(void){}

#define TEMPO 25
#define VOLUME 50

void RingTone(int freq, int time, int vol){	/* 音符を再生するユーザー関数を定義 */
	ecrobot_sound_tone(freq, time-5, vol);
	systick_wait_ms(time*10);
}

TASK(SEK_Task_Background)
{
	RingTone(523, TEMPO*2, VOLUME);
	RingTone(587, TEMPO*2, VOLUME);
	RingTone(659, TEMPO*2, VOLUME);
	RingTone(698, TEMPO*2, VOLUME);
	RingTone(659, TEMPO*2, VOLUME);
	RingTone(587, TEMPO*2, VOLUME);
	RingTone(523, TEMPO*3, VOLUME);
	systick_wait_ms(TEMPO*10);

	RingTone(659, TEMPO*2, VOLUME);
	RingTone(698, TEMPO*2, VOLUME);
	RingTone(784, TEMPO*2, VOLUME);
	RingTone(880, TEMPO*2, VOLUME);
	RingTone(784, TEMPO*2, VOLUME);
	RingTone(698, TEMPO*2, VOLUME);
	RingTone(659, TEMPO*3, VOLUME);
	systick_wait_ms(TEMPO*10);

	RingTone(523, TEMPO*2, VOLUME);
	systick_wait_ms(TEMPO*2*10);
	RingTone(523, TEMPO*2, VOLUME);
	systick_wait_ms(TEMPO*2*10);
	RingTone(523, TEMPO*2, VOLUME);
	systick_wait_ms(TEMPO*2*10);
	RingTone(523, TEMPO*2, VOLUME);
	systick_wait_ms(TEMPO*2*10);

	RingTone(523, TEMPO, VOLUME);
	RingTone(523, TEMPO, VOLUME);
	RingTone(587, TEMPO, VOLUME);
	RingTone(587, TEMPO, VOLUME);
	RingTone(659, TEMPO, VOLUME);
	RingTone(659, TEMPO, VOLUME);
	RingTone(698, TEMPO, VOLUME);
	RingTone(698, TEMPO, VOLUME);
	RingTone(659, TEMPO, VOLUME);
	systick_wait_ms(TEMPO*10);
	RingTone(587, TEMPO, VOLUME);
	systick_wait_ms(TEMPO*10);
	RingTone(523, TEMPO*3, VOLUME);
	systick_wait_ms(TEMPO*10);

	
   	display_string("THAT'S ALL !");		/* メッセージを表示する */
	display_update();
	TerminateTask();					/* 処理終了 */
}