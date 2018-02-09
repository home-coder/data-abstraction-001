#include <stdio.h>
#include <stdlib.h>

typedef struct _roulette {
	char data;
	struct _roulette *next;
}roulette;

static void roulette_init(roulette **rte, int people)
{
	int i = 0;
	roulette *rtep = *rte;

	if (rtep != NULL) {
		printf("roulette already exsit\n");
		return ;
	}

	while (i < people) {
		roulette *nrte = (roulette *)malloc(sizeof(roulette));
		if (!nrte) {
			printf("nrte malloc failed\n");
			return ;
		}
		nrte->data = 'a' + i++;

		if (!rtep) {
			rtep = nrte;
			rtep->next = rtep;
			*rte = rtep;
		} else {
			nrte->next = rtep->next;
			rtep->next = nrte;	
			rtep = nrte;
		}
	}

}

static void roulette_show(roulette *rte)
{
	roulette *rtep = rte;
	if (!rtep) {
		printf("roulette is not exsit\n");
		return ;
	}

	do {
		printf("%c->", rtep->data);
		rtep = rtep->next;
	} while(rtep != rte);

	printf("\n");
}

static roulette *roulette_play(roulette *rte)
{
	int cham, trig;
	roulette *rtep = rte, *fnode;
	if (!rtep) {
		printf("roulette is not exist\n");
		return ;
	}

	//首先找到首元节点的前趋节点作为计数起始点的前趋
	do {
		rtep = rtep->next;
	} while (rtep->next != rte);

	do {
		printf("please input chamber number & trigger number: ");
		scanf("%d %d", &cham, &trig);
		if (trig < cham) { //活下来了
			rtep = rtep->next;
			roulette_show(rtep);
		} else { //自杀了
			fnode = rtep->next;
			rtep->next = rtep->next->next;
			free(fnode);
			fnode = NULL;
			roulette_show(rtep->next);
		}
	} while(rtep->next != rtep);

	return rtep;
}

int main(int argc, char **argv)
{
	roulette *rte = NULL, *last;
	int people;

	if (argc < 2) {
		fprintf(stderr, "please read usage ./a.out 24\n");
		exit(-1);
	}

	people = atoi(argv[1]);
	printf("people %d\n", people);

	roulette_init(&rte, people);
	roulette_show(rte);

	last = roulette_play(rte);
	if (last) {
		printf("last->data %c\n", last->data);
	}

	return 0;
}
