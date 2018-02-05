#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
                      <-         <- <-
   |头节点data不初始化->首元节点0->1->2 |
*/
typedef struct _dlink_data {
	char data;
	struct _dlink_data *next;
	struct _dlink_data *prev;
}dlink_data;

static void dlink_show(dlink_data *dldata)
{
	dlink_data *dlp = dldata;
	if (!dlp) {
		printf("dlink is not exsit\n");
		return ;
	}

	if (dlp->next == NULL) {
		printf("dlink has no data\n");
		return ;
	}

	dlp = dlp->next;
	for (; dlp != NULL; dlp = dlp->next) {
		printf("%c->", dlp->data);
	}

	printf("\n");
}

static void dlink_init(dlink_data **dldata)
{
	*dldata = (dlink_data *)malloc(sizeof(dlink_data));
	if (!*dldata) {
		printf("dldata malloc failed\n");
		return ;
	}

	(*dldata)->next = NULL;
	(*dldata)->prev = NULL;
}

static void dlink_insert(dlink_data *dldata, unsigned int loc, char data)
{
	printf("insert loc %d data %c-->\n", loc, data);
	int i = 0;
	dlink_data *dlp = dldata;
	if (!dlp) {
		printf("dlink is not exsit\n");
		return ;
	}

	dlink_data *ndnode = (dlink_data *)malloc(sizeof(dlink_data));
	if (!ndnode) {
		printf("ndnode malloc failed\n");
		return ;
	}
	ndnode->data = data;

	for (; i < loc; i++) {
		dlp = dlp->next;
		if (!dlp) {
			printf("insert loc %d is invalid\n", loc);
			return ;
		}
	}
	if (!dlp->next) {
		dlp->next = ndnode;
		ndnode->prev = dlp;
		ndnode->next = NULL;
	} else {
		ndnode->next = dlp->next;
		ndnode->next->prev = ndnode;
		dlp->next = ndnode;
		ndnode->prev = dlp;
	}

}

static void dlink_delete(dlink_data *dldata, unsigned int loc)
{
	printf("delete loc %d-->\n", loc);
	int i = 0;
	dlink_data *dlp = dldata;
	if (!dlp) {
		printf("dlink is not exsit\n");
		return ;
	}
	if (!dlp->next) {
		printf("delete loc %d is invalid\n", loc);
		return ;
	}
	//0
	//1
	for (; i < loc; i++) {
		dlp = dlp->next;
		if (!dlp || !dlp->next) {
			printf("delete loc %d is invalid\n", loc);
			return ;
		}
	}
	dlink_data *denode = dlp->next;
	if (!dlp->next->next) {
		dlp->next = NULL;
	} else {
		dlp->next = dlp->next->next;
		dlp->next->prev = dlp;
	}
	free(denode);
	denode = NULL;
}

static void dlink_amend(dlink_data *dldata, unsigned int loc, char data)
{
	printf("amend loc %d data %c-->\n", loc, data);
	int i = 0;
	dlink_data *dlp = dldata;
	if (!dlp) {
		printf("dlink is not exsit\n");
		return ;
	}
	
	for (; i < loc; i++) {
		dlp = dlp->next;
		if (!dlp) {
			printf("amend loc %d is invalid\n", loc);
			return ;
		}
	}
	if (!dlp->next) {
		printf("amend loc %d is invalid\n", loc);
		return ;
	} else {
		dlp->next->data = data;
	}
}

static int dlink_select(dlink_data *dldata, char data)
{
	int loc = 0;
	dlink_data *dlp = dldata;
	if (!dlp) {
		printf("dlink is not exsit\n");
		return -1;
	}

	for (dlp = dlp->next; dlp != NULL; dlp = dlp->next) {
		if (dlp->data == data) {
			return loc;
		}
		loc++;
	}
	return -1;
}

int main()
{
	dlink_data *dldata;

	dlink_init(&dldata);
	dlink_show(dldata);

	dlink_insert(dldata, 0, 'e');
	dlink_insert(dldata, 0, 'm');
	dlink_insert(dldata, 3, 'n');
	dlink_insert(dldata, 3, 'n');
	dlink_insert(dldata, 3, 'n');
	dlink_insert(dldata, 0, 'q');
	dlink_insert(dldata, 2, 't');
	dlink_insert(dldata, 2, 't');
	dlink_insert(dldata, 2, 't');
	dlink_insert(dldata, 3, 'n');
	dlink_insert(dldata, 3, 'n');
	dlink_insert(dldata, 3, 'n');
	dlink_insert(dldata, 3, 'n');
	dlink_insert(dldata, 2, 't');
	dlink_show(dldata);

	dlink_delete(dldata, 2);
	dlink_show(dldata);
	dlink_delete(dldata, 0);
	dlink_show(dldata);
	dlink_delete(dldata, 2);
	dlink_show(dldata);
	dlink_delete(dldata, 5);
	dlink_show(dldata);
	dlink_delete(dldata, 0);
	dlink_show(dldata);
	dlink_delete(dldata, 0);
	dlink_show(dldata);
	dlink_delete(dldata, 0);
	dlink_show(dldata);

	dlink_amend(dldata, 3, 'o');
	dlink_amend(dldata, 0, 'i');
	dlink_amend(dldata, 7, 'p');
	dlink_show(dldata);

	int loc;
	loc = dlink_select(dldata, 'p');
	printf("select 'p' loc in %d\n", loc);
	loc = dlink_select(dldata, 'n');
	printf("select 'n' loc in %d\n", loc);
	loc = dlink_select(dldata, 'i');
	printf("select 'i' loc in %d\n", loc);

	return 0;
}
