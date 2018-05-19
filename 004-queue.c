/***************************************************************************
 > Filename   : 026.c
 > Author     : oneface - one_face@sina.com
 > Company    : 一尊还酹江月
 > Time       : 2018-05-18 13:07:58
 > Description: 

 - This program is free software; you can redistribute it and/or modify it
 - under the terms of the GNU General Public License as published by the
 - Free Software Foundation;  either version 2 of the  License, or (at your
 - option) any later version.
 **************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define MAX  256

typedef struct {
	int front, rear;
	int elem[MAX];
}aqueue; //array;

static void creat_queue(aqueue **aque)
{
	*aque = (aqueue *)malloc(sizeof(**aque));
	(*aque)->front = (*aque)->rear = 0;
}

static void en_queue(aqueue *aque, int elem)
{
	if (aque->rear != 0 && aque->rear % MAX == aque->front) {
		printf("queue is full\n");
		return ;
	}

	aque->elem[aque->rear] = elem;
	aque->rear++;
}

static int de_queue(aqueue *aque, int *elem)
{
	if (aque->front != 0 && aque->front % MAX == aque->rear) {
		printf("queue is null\n");
		return -1;
	}

	*elem = aque->elem[aque->front];
	aque->front++;

	return 0;
}

int main()
{
	aqueue *aque = NULL;

	creat_queue(&aque);
	en_queue(aque, 1);
	en_queue(aque, 2);
	en_queue(aque, 3);
	en_queue(aque, 4);

	int da, ret = 0;
	de_queue(aque, &da);
	printf("da=%d\n", da);
	de_queue(aque, &da);
	printf("da=%d\n", da);
	de_queue(aque, &da);
	printf("da=%d\n", da);
	de_queue(aque, &da);
	printf("da=%d\n", da);
	ret = de_queue(aque, &da);
	printf("ret=%d  da=%d\n", ret, da);
	ret = de_queue(aque, &da);
	printf("ret=%d  da=%d\n", ret, da);

	return 0;
}
