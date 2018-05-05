/***************************************************************************
 > Filename   : 006-huffman.c
 > Author     : oneface - one_face@sina.com
 > Company    : 一尊还酹江月
 > Time       : 2018-05-02 11:31:02
 > Description: 

 - This program is free software; you can redistribute it and/or modify it
 - under the terms of the GNU General Public License as published by the
 - Free Software Foundation;  either version 2 of the  License, or (at your
 - option) any later version.
 **************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int weight;
	int parent, left, right;
}hftree;

typedef char* hfcode;

static void weight_select(hftree *h, int n, int *d1, int *d2)
{
	int i = 1, tmp;

	while (h[i].parent != -1 && i <= n) {
		i++;
	}
	*d1 = i;

	i++;
	while (h[i].parent != -1 && i <= n) {
		i++;
	}
	*d2 = i;

	if (h[*d1].weight > h[*d2].weight) {
		tmp = *d1;
		*d1 = *d2;
		*d2 = tmp;
	}

	i++;
	while (i <= n) {
		if (h[i].parent != -1) {
			i++;
		} else {
			if (h[i].weight < h[*d1].weight) {
				*d2 = *d1;
				*d1 = i;
			} else if (h[i].weight >= h[*d1].weight && h[i].weight < h[*d2].weight) {
				*d2 = i;
			}
			i++;
		}
	}
}

static void creat_hftree(hftree **hft, int *w, int s)
{
	int m = 2 * s - 1,
		i = 0;

	if (s <= 1) {
		return ;
	}

	*hft = (hftree *)malloc((m+1) * sizeof(hftree));
	if (NULL == *hft) {
		printf("huffman tree malloc failed\n");
		return ;
	}

	//init ...
	hftree *h = *hft;
	for (i = 1; i <= s; i++) {
		(h + i)->weight = w[i - 1];
		(h + i)->parent = -1;
		(h + i)->left = -1;
		(h + i)->right = -1;
	}
	for (; i <= m; i++) {
		(h + i)->weight = -1;
		(h + i)->parent = -1;
		(h + i)->left = -1;
		(h + i)->right = -1;
	}

	//creat ...
	for (i = s + 1; i <= m; i++) {
		int d1, d2;
		weight_select(h, i - 1, &d1, &d2);	
		printf("d1 = %d, d2 = %d\n", d1, d2);
		h[d1].parent = h[d2].parent = i;
		h[i].left = d1;
		h[i].right = d2;
		h[i].weight = h[d1].weight + h[d2].weight;
	}

}

static void	inorder_traverse(hftree *h, int m, int *w)
{
	int l, r;

	if (h[m].left == -1) {
		printf("%d, m=%d w=%d\n", h[m].left, m, w[m-1]);
	} else if (h[m].right == -1) {
		printf("%d, m=%d w=%d\n", h[m].right, m, w[m-1]);
	} else {
		l = h[m].left;
		printf("l = %d\n", l);
		inorder_traverse(h, l, w);
		r = h[m].right;
		printf("r = %d\n", r);
		inorder_traverse(h, r, w);
	}
}

static void huffman_coding_nodeorder(hftree *h, hfcode **hc, int s)
{
	int i, j;
	char *cd = (char *)malloc((s-1) * sizeof(char));
	*hc = (hfcode *)malloc(s * sizeof(hfcode));
	cd[s - 2] = '\0';

	for (i = 1; i <= s; i++) {
		int c = i;
		int start = s - 1;

		while (h[c].parent != -1) {
			j = h[c].parent;
			if (h[j].left == c) {
				cd[--start] = '0';	
			} else {
				cd[--start] = '1';
			}
			c = j;
		}

		(*hc)[i] = (char *)malloc((s - start) * sizeof(char));
		memcpy((*hc)[i], &cd[start], s - start);
	}

}

static void huffman_code_print(hfcode *hc, int s)
{
	int i;
	for (i = 1; i <= s; i++) {
		printf("hc[%d]:%s\n", i, hc[i]);
	}	
}

int main()
{
	int i;
	int w[] = {2, 8, 7, 6, 5, 4};
	int s = sizeof(w)/sizeof(w[0]);
	hftree *hft = NULL;
	
	creat_hftree(&hft, w, s);
	for (i = 0; i < s; i++) {
		printf("%d ", w[i]);
	}
	printf("\n");

	inorder_traverse(hft, 2 * s - 1, w);

	hfcode *hc = NULL;
	//from node
	huffman_coding_nodeorder(hft, &hc, s);

	//from root
	//huffman_coding_rootorder(hft, 2 * s - 1);

	huffman_code_print(hc, s);
	free(hft);
	return 0;
}
