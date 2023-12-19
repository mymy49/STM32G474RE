/*
	Copyright 2023. 홍윤기 all right reserved.

	Permission is hereby granted, free of charge, to any person obtaining
	a copy of this software and associated documentation files (the
	"Software"), to deal in the Software without restriction, including
	without limitation the rights to use, copy, modify, merge, publish,
	distribute, sublicense, and/or sell copies of the Software, and to
	permit persons to whom the Software is furnished to do so, subject to
	the following conditions:

	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
	LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
	OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
	WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <yss.h>
#include <bsp.h>
#include "memory.h"
#include <yss/debug.h>
#include <util/runtime.h>
#include <targets/st/bitfield.h>

void thread_testUartTx(void)
{
	while(1)
	{
		thread::delay(500);
		usart2.send("Hello Word!!\n\r", sizeof("Hello Word!!\n\r"));
	}
}

void thread_testUartRx(void)
{
	while(1)
	{
#if !defined(ST_CUBE_IDE)
		debug_printf("%c\n", usart2.getWaitUntilReceive());
#endif
	}
}

int main(void)
{
	// 운영체체 초기화
	initializeYss();
	
	// 보드 초기화
	initializeBoard();

	// 설정 저장용 메모리 초기화
	Memory::initilize();
	
	thread::add(thread_testUartTx, 512);
	thread::add(thread_testUartRx, 512);

	while(1)
	{
		Led::on(true);
		thread::delay(500);

		Led::on(false);
		thread::delay(500);
	}
}

