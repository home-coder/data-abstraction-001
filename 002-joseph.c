#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/****************002-joseph.c***********************

使用没有头节点但是要有首元节点的链式存储结构来解决此问题，因为方便删除元素
***************************************************/

typedef struct _joseph {
	char data; //a b c d e f
	struct _joseph *next;
}joseph;

static void josp_init(joseph **josp, int people)
{
	joseph *nnode = NULL, *pjs = *josp;
	int i = 0;

	while (i < people) { //malloc ?
		nnode = (joseph *)malloc(sizeof(joseph));
		if (!nnode) {
			printf("nnode malloc failed\n");
			return ;
		}
		nnode->data = 'a' + i++;

		if (!pjs) {
			pjs = nnode;
			pjs->next = pjs;
			*josp = pjs;
		} else {
			nnode->next = pjs->next;
			pjs->next = nnode;
			pjs = pjs->next;
		}
	}
}

static void josp_show(joseph *josp)
{
	joseph *pjs = josp;
	if (!pjs) {
		printf("josp is not exsit\n");
		return ;
	}

	do {
		printf("%c->", pjs->data);
		pjs = pjs->next;
	}while(pjs != josp);
	printf("\n");
}

int main(int argc, char **argv)
{
	joseph *josp, *last;
	int people, hit;

	if (argc < 3) {
		fprintf(stderr, "Please read usage: ./a.out 24 5  error: %s: \n", strerror(errno));
		exit(-1);
	}

	people = atoi(argv[1]);
	hit = atoi(argv[2]);
	printf("p %d h %d\n", people, hit);

	josp_init(&josp, people);
	josp_show(josp);

#if 0
	last = josp_play(josp, hit);
	printf("last data: %c\n", last->data);
#endif

	return 0;
}
