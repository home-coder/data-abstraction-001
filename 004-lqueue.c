/***************************************************************************
 > Filename   : 004-lqueue.c
 > Author     : oneface - one_face@sina.com
 > Company    : 一尊还酹江月
 > Time       : 2018-05-05 16:35:27
 > Description: 

 - This program is free software; you can redistribute it and/or modify it
 - under the terms of the GNU General Public License as published by the
 - Free Software Foundation;  either version 2 of the  License, or (at your
 - option) any later version.
 **************************************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct _lqueue{
	char data;
	struct _lqueue *next;
}lqueue;

static void init_lqueue(lqueue **front, lqueue **rear)
{
	lqueue *head = (lqueue *)malloc(sizeof(lqueue));
	*front = *rear = head;
}

static void en_lqueue(lqueue **rear, char da)
{
	if (!*rear) {
		printf("lqueue is not init\n");
		return ;
	}
	lqueue *nq = (lqueue *)malloc(sizeof(lqueue));
	(*rear)->data = da;
	(*rear)->next = nq;
	*rear = nq;
}

static void de_lqueue(lqueue **front, lqueue **rear)
{
	if (!*front) {
		printf("lqueue is not init\n");
		return ;
	}

	if (*front == *rear) {
		printf("队列已空\n");
		return ;
	}
	printf("de queue: %c\n", (*front)->data);
	lqueue *f = *front;
	(*front) = (*front)->next;
	free(f);
}

int main()
{
	lqueue *front, *rear;
	front = rear = NULL;

	en_lqueue(&rear, 'a');
	de_lqueue(&front, &rear);

	init_lqueue(&front, &rear);

	de_lqueue(&front, &rear);
	en_lqueue(&rear, 'a');
	en_lqueue(&rear, 'b');
	en_lqueue(&rear, 'c');
	en_lqueue(&rear, 'd');
	en_lqueue(&rear, 'd');
	en_lqueue(&rear, 'b');
	en_lqueue(&rear, 'c');
	en_lqueue(&rear, 'd');
	en_lqueue(&rear, 'b');
	en_lqueue(&rear, 'c');
	en_lqueue(&rear, 'd');
	en_lqueue(&rear, 'b');
	en_lqueue(&rear, 'c');
	de_lqueue(&front, &rear);
	de_lqueue(&front, &rear);
	de_lqueue(&front, &rear);
	de_lqueue(&front, &rear);
	de_lqueue(&front, &rear);
	de_lqueue(&front, &rear);
	de_lqueue(&front, &rear);
	de_lqueue(&front, &rear);
	de_lqueue(&front, &rear);
	de_lqueue(&front, &rear);
	de_lqueue(&front, &rear);
	de_lqueue(&front, &rear);
	de_lqueue(&front, &rear);
	de_lqueue(&front, &rear);
	de_lqueue(&front, &rear);
	de_lqueue(&front, &rear);
	de_lqueue(&front, &rear);
	de_lqueue(&front, &rear);

	return 0;
}
