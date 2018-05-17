/***************************************************************************
 > Filename   : 006-phuffman.c
 > Author     : oneface - one_face@sina.com
 > Company    : 一尊还酹江月
 > Time       : 2018-05-16 18:57:49
 > Description: 采用指针形式而不是坐标形式，重新实现哈夫曼树的创建和哈夫曼编码

 - This program is free software; you can redistribute it and/or modify it
 - under the terms of the GNU General Public License as published by the
 - Free Software Foundation;  either version 2 of the  License, or (at your
 - option) any later version.
 **************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _hftree {
	int weight;
	struct _hftree *parent, *lchild, *rchild;
} hftree;

typedef char *hfcode;

static void huffman_creat(hftree ** hft, int *w, int s)
{
	int i, j, tmp, s1, s2;

	int m = 2 * s - 1;

	*hft = (hftree *) malloc((m + 1) * sizeof(**hft));
	if (!*hft) {
		printf("*hft malloc failed\n");
		return;
	}

	for (i = 1; i <= s; i++) {
		(*hft)[i].weight = w[i - 1];
		(*hft)[i].parent = (*hft)[i].lchild = (*hft)[i].rchild = NULL;
	}
	for (; i <= m; i++) {
		(*hft)[i].weight = -1;
		(*hft)[i].parent = (*hft)[i].lchild = (*hft)[i].rchild = NULL;
	}

	for (i = s + 1; i <= m; i++) {
		j = 1;
		while ((*hft)[j].parent != NULL && j <= i - 1) {
			j++;
		}
		s1 = j;

		++j;
		while ((*hft)[j].parent != NULL && j <= i - 1) {
			j++;
		}
		s2 = j;

		if ((*hft)[s1].weight > (*hft)[s2].weight) {
			tmp = s1;
			s1 = s2;
			s2 = tmp;
		}

		++j;
		for (; j <= i - 1; j++) {
			if ((*hft)[j].parent == NULL) {
				if ((*hft)[j].weight < (*hft)[s1].weight) {
					s2 = s1;
					s1 = j;
				} else if ((*hft)[j].weight > (*hft)[s1].weight && (*hft)[j].weight < (*hft)[s2].weight) {
					s2 = j;
				}
			}
		}

		printf("s1=%d, s2=%d\n", s1, s2);
		(*hft)[s1].parent = (*hft)[s2].parent = &(*hft)[i];
		(*hft)[i].lchild = &(*hft)[s1];
		(*hft)[i].rchild = &(*hft)[s2];
		(*hft)[i].weight = (*hft)[s1].weight + (*hft)[s2].weight;
	}

}

static void huffman_code(hfcode ** hfc, hftree * hft, int s)
{
	int i;

	*hfc = (hfcode *) malloc(s * sizeof(**hfc));
	if (!*hfc) {
		printf("*hfc malloc failed\n");
		return;
	}

	char *code = (char *)malloc(s * sizeof(char));
	if (!code) {
		printf("code malloc failed\n");
		goto fail1;
	}
	code[s - 1] = '\0';

	for (i = 1; i <= s; i++) {
		int start = s - 1;
		hftree *phft = &hft[i];
		while (phft->parent) {
			if (phft->parent->lchild == phft) {
				code[--start] = '0';
			} else if (phft->parent->rchild == phft) {
				code[--start] = '1';
			} else {
				printf("hehe: no way\n");
			}
			phft = phft->parent;
		}

		(*hfc)[i] = (hfcode) malloc((s - start + 1) * sizeof(***hfc));
		strncpy((*hfc)[i], &code[start], s - start + 1);
	}

	return;
      fail1:
	free(*hfc);
	return;
}

static void print_hfcode(hfcode * hfc, int *w, int s)
{
	int i;
	for (i = 1; i <= s; i++) {
		printf("%d: %s\n", w[i - 1], hfc[i]);
	}
}

int main()
{
	int w[] = { 2, 8, 7, 6, 5, 4 };
	int s = sizeof(w) / sizeof(w[0]);

	hftree *hft = NULL;
	huffman_creat(&hft, w, s);

	hfcode *hfc = NULL;
	huffman_code(&hfc, hft, s);

	print_hfcode(hfc, w, s);

	return 0;
}
