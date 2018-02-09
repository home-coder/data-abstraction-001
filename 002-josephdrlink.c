/*************************************************************************
 > Filename   : 002-josephdrlink.c
 > Author     : oneface - one_face@sina.com
 > Company    : Monte Cristo
 > Time       : 2018-02-09 14:15:04
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>

/*
 不要有头节点，仅仅使用首元节点，方便问题的解决
 */

typedef struct _josephdrlink {
	char data;
	struct _josephdrlink *prev;
	struct _josephdrlink *next;
}josephdrlink;

static void josephdrlink_init(josephdrlink **jspdr, int people)
{
	int i = 0;
	josephdrlink *jspdrp = *jspdr, *njspdr;

	if (jspdrp != NULL) {
		printf("josephdrlink is already exsit\n");
		return ;
	}

	while (i < people) {
		njspdr = (josephdrlink *)malloc(sizeof(josephdrlink));
		if (!njspdr) {
			printf("njspdr malloc failed\n");
			return ;
		}
		njspdr->data = 'a' + i++;

		if (!jspdrp) {
			jspdrp = njspdr;
			jspdrp->next = jspdrp;
			jspdrp->prev = jspdrp;
			*jspdr = jspdrp;
		} else {
			njspdr->next = jspdrp->next;
			jspdrp->next->prev = njspdr;
			jspdrp->next = njspdr;
			njspdr->prev = jspdrp;	
		}
		jspdrp = jspdrp->next;
	}
}

static void josephdrlink_show(josephdrlink *jspdr)
{
	josephdrlink *jspdrp = jspdr;
	if (!jspdrp) {
		printf("josephdrlink is not exsit\n");
		return ;
	}

	do {
		printf("%c->", jspdrp->data);
		jspdrp = jspdrp->next;
	} while(jspdrp != jspdr);

	printf("\n");
}

int main(int argc, char **argv)
{
	int people, hit;
	josephdrlink *jspdr = NULL;

	if (argc < 3) {
		fprintf(stderr, "please read usage: ./a.out 24 3\n");
		return ;
	}

	people = atoi(argv[1]);
	hit = atoi(argv[2]);
	printf("p %d  h %d\n", people, hit);

	josephdrlink_init(&jspdr, people);
	josephdrlink_show(jspdr);

	return 0;
}
