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

#if 0
	link_amend();
	link_show(ldata);
	link_select();
	link_show(ldata);
#endif
	return 0;
}
