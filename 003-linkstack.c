/***************************************************************************
 > Filename   : 003-linkstack.c
 > Author     : oneface - one_face@sina.com
 > Company    : 一尊还酹江月
 > Time       : 2018-05-05 11:41:22
 > Description: 

 - This program is free software; you can redistribute it and/or modify it
 - under the terms of the GNU General Public License as published by the
 - Free Software Foundation;  either version 2 of the  License, or (at your
 - option) any later version.
 **************************************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct _lstack {
	char data;
	struct _lstack *next;
}lstack;

/*
 * push & pop
 */

static void lstack_push(lstack **lsk, char da)
{
	lstack *ns = (lstack *)malloc(sizeof(lstack));

	ns->data = da;
	ns->next = *lsk;
	*lsk = ns;
}

static void lstack_pop(lstack **lsk)
{
	if (!*lsk) {
		printf("栈已经空\n");
		return ;
	}

	//free 操作
	printf("data: %c\n", (*lsk)->data);
	lstack *f = *lsk;
	*lsk = (*lsk)->next;
	free(f);
}

int main()
{
	lstack *lsk = NULL;

	lstack_push(&lsk, 'a');
	lstack_push(&lsk, 'b');
	lstack_pop(&lsk);
	lstack_pop(&lsk);
	lstack_push(&lsk, 'c');
	lstack_push(&lsk, 'd');
	lstack_push(&lsk, 'c');
	lstack_push(&lsk, 'd');
	lstack_push(&lsk, 'c');
	lstack_push(&lsk, 'd');
	lstack_push(&lsk, 'e');

	lstack_pop(&lsk);
	lstack_pop(&lsk);
	lstack_pop(&lsk);
	lstack_pop(&lsk);
	lstack_pop(&lsk);
	lstack_pop(&lsk);
	lstack_pop(&lsk);
	lstack_pop(&lsk);
	lstack_pop(&lsk);

	return 0;
}
