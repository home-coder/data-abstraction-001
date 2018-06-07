/***************************************************************************
 > Filename   : x001.c
 > Author     : oneface - one_face@sina.com
 > Company    : 一尊还酹江月
 > Time       : 2018-06-01 16:03:16
 > Description: 
 传入参数范围{0, 360}
 数组0-35
 结果举例：eg1:如果传入330, 则输出32 33 34数组中对应元素的值
		   eg2:如果传入360, 输出35, 0, 1对应的值

 - This program is free software; you can redistribute it and/or modify it
 - under the terms of the GNU General Public License as published by the
 - Free Software Foundation;  either version 2 of the  License, or (at your
 - option) any later version.
 **************************************************************************/
#include <stdio.h>

static void print_voice(int w)
{
	int i;

	if (w < 0 || w > 360) {
		return ;
	}

	w /= 10;
	w = w - 1;
	if (w == -1) {
		printf("%d ", w + 36);
	} else {
		printf("%d ", w);
	}
	for (i = ++w; i < w + 2; i++) {
		if (i == 36) {
			i = 0;
			printf("%d ", i);
			w = -2;
		} else
			printf("%d ", i);
	}
	printf("\n");
}

int main()
{
	int w[37];
	int i;

	for (i = 0; i < 37; i++) {
		w[i] = i * 10;
	}

	for (i = 0; i < 37; i++) {
		print_voice(w[i]);
	}

	return 0;
}
