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
	while (people--) { //malloc ?
	}
}

int main(int argc, char **argv)
{
	joseph *josp;
	int people, hit;

	if (argc < 3) {
		fprintf(stderr, "Please read usage: ./a.out 24 5  error: %s: \n", strerror(errno));
		exit(-1);
	}

	people = atoi(argv[1]);
	hit = atoi(argv[2]);
	printf("p %d h %d\n", people, hit);

	josp_init(&josp, people);

	return 0;
}
