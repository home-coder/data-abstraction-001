#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _link_data {
	char data;
	struct _link_data *next;
}link_data;

static void link_show(link_data *ldata)
{
	link_data *lp = ldata;
	if (!lp) {
		printf("link is not exsit\n");
		exit(-1);
	}
	if (!lp->next) {
		printf("link data is not exsit\n");
		exit(-1);
	}

	for (lp = lp->next; lp != NULL; lp = lp->next) {
		printf("%c->", lp->data);
	}
	printf("\n");
}

static void link_init(link_data **ldata)
{
	*ldata = (link_data *)malloc(sizeof(link_data));
	if (!*ldata) {
		printf("malloc failed\n");
		exit(-1);
	}
	(*ldata)->next = NULL;
}

static void link_insert(link_data *ldata, unsigned int loc, char data)
{
	int i = 0;
	link_data *lp = ldata;
	if (!lp) {
		printf("link is not exsit\n");
		exit(-1);
	}

	for (; i < loc; i++) {
		lp = lp->next;
		if (!lp) {
			printf("inset loc %d is invalid\n", loc);
			return ;
		}
	}
	link_data *node = (link_data *)malloc(sizeof(link_data));
	if (!node) {
		printf("malloc node failed\n");
		return ;
	}
	node->data = data;

	if (lp->next == NULL) {
		node->next = NULL;
	} else {
		node->next = lp->next;
	};
	lp->next = node;
}

static void link_delet(link_data *ldata, unsigned int loc)
{
	int i = 0;
	link_data *lp = ldata;
	if (!lp) {
		printf("link is not exsit \n");
		exit(-1);
	}

	for (; i < loc; i++) {
		lp = lp->next;
		if (!lp) {
			printf("delet loc %d is invalid\n", loc);
			return ;
		}
	}
	if (!lp->next) {
		printf("delet loc %d is invalid\n", loc);
		return ;
	}
	link_data *dnode = lp->next;
	lp->next = dnode->next;
	free(dnode);
	dnode = NULL;
}

static void link_amend(link_data *ldata, unsigned int loc, char data)
{
	int i = 0;
	link_data *lp = ldata;
	if (!lp) {
		printf("link is not exsit \n");
		exit(-1);
	}

	for (; i < loc; i++) {
		lp = lp->next;
		if (!lp) {
			printf("amend loc %d is invalid\n", loc);
			return ;
		}
	}

	if (!lp->next) {
		printf("amend loc %d is invalid\n", loc);
		return ;
	}

	lp->next->data = data;
}

static int link_select(link_data *ldata, char data)
{
	int i = 0;
	link_data *lp = ldata;
	if (!lp) {
		printf("link is not exsit\n");
		return -1;
	}

	lp = lp->next;
	if (!lp) {
		printf("select link has no data\n");
		return -1;
	}
	for (; lp != NULL; lp = lp->next) {
		if (lp->data == data) {
			return i;
		}
		i++;
	}

	return -1;
}

int main()
{
	link_data *ldata;

	link_init(&ldata);
	link_insert(ldata, 0, 'a');
	link_insert(ldata, 0, '9');
	link_insert(ldata, 1, 'b');
	link_insert(ldata, 0, 'e');
	link_insert(ldata, 4, 'm');
	link_insert(ldata, 7, 'n');
	link_show(ldata);

	link_delet(ldata, 4);
	link_show(ldata);

	link_amend(ldata, 3, 'u');
	link_amend(ldata, 4, 'u');
	link_amend(ldata, 0, 'y');
	link_show(ldata);

	int loc;
	loc = link_select(ldata, 'u');
	printf("select data 'u' is in loc %d\n", loc);
	loc = link_select(ldata, 'y');
	printf("select data 'y' is in loc %d\n", loc);
	loc = link_select(ldata, 't');
	printf("select data 't' is in loc %d\n", loc);

	return 0;
}
