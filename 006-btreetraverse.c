/***************************************************************************
 > Filename   : 006-btreetraverse.c
 > Author     : oneface - one_face@sina.com
 > Company    : 一尊还酹江月
 > Time       : 2018-05-02 10:46:21
 > Description: 

 - This program is free software; you can redistribute it and/or modify it
 - under the terms of the GNU General Public License as published by the
 - Free Software Foundation;  either version 2 of the  License, or (at your
 - option) any later version.
 **************************************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct _btree{
	int da;
	struct _btree *bl, *br;
}btree;

static void creat_btree(btree **bt)
{
	*bt = (btree *)malloc(sizeof(btree));
	(*bt)->da = 1;

	(*bt)->bl = (btree *)malloc(sizeof(btree));
	(*bt)->br = (btree *)malloc(sizeof(btree));
	(*bt)->bl->da = 2;
	(*bt)->br->da = 3;

	(*bt)->bl->bl = (btree *)malloc(sizeof(btree));
	(*bt)->bl->br = (btree *)malloc(sizeof(btree));
	(*bt)->bl->bl->da = 4;
	(*bt)->bl->bl->bl = NULL;
	(*bt)->bl->bl->br = NULL;
	(*bt)->bl->br->da = 5;
	(*bt)->bl->br->bl = NULL;
	(*bt)->bl->br->br = NULL;

	(*bt)->br->bl = (btree *)malloc(sizeof(btree));
	(*bt)->br->br = (btree *)malloc(sizeof(btree));
	(*bt)->br->bl->da = 6;
	(*bt)->br->bl->bl = NULL;
	(*bt)->br->bl->br = NULL;
	(*bt)->br->br->da = 7;
	(*bt)->br->br->bl = NULL;
	(*bt)->br->br->br = NULL;
}

static void preorder_traverse(btree *bt)
{
	if (bt) {
		printf("%d->", bt->da);
		preorder_traverse(bt->bl);
		preorder_traverse(bt->br);
	}
}

static void inorder_traverse(btree *bt)
{
	if (bt) {
		inorder_traverse(bt->bl);
		printf("%d->", bt->da);
		inorder_traverse(bt->br);
	}
}

static void postorder_traverse(btree *bt)
{
	if (bt) {
		postorder_traverse(bt->bl);
		postorder_traverse(bt->br);
		printf("%d->", bt->da);
	}
}

int main()
{
	btree *bt = NULL;

	//http://data.biancheng.net/view/25.html 中图例作为数据来源
	creat_btree(&bt);
	printf("pre order traverse : ");
	preorder_traverse(bt);
	printf("\nin order traverse  : ");
	inorder_traverse(bt);
	printf("\npost order traverse: ");
	postorder_traverse(bt);
	printf("\n");

	free(bt);

	return 0;
}
