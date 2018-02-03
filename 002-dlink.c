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

	if (dlp->next == dlp) {
		printf("dlink has no data\n");
		return ;
	}

	dlp = dlp->next;
	for (; dlp != dldata; dlp = dlp->next) {
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

	(*dldata)->next = *dldata;
	(*dldata)->prev = *dldata;
}

static void dlink_insert(dlink_data *dldata, unsigned int loc, int data)
{
	int i = 0;
	dlink_data *dlp = dldata;
	if (!dlp) {
		printf("dlink is not exsit\n");
		return ;
	}

	for (; i < loc; i++) {
		dlp = dlp->next;
		if (dlp == dldata) {
			printf("insert loc %d is invalid\n", loc);
			return ;
		}
	}
	dlink_data *ndlnode = (dlink_data *)malloc(sizeof(dlink_data));
	if (!ndlnode) {
		printf("ndlnode malloc failed\n");
		return ;
	}
	ndlnode->data = data;

	ndlnode->next = dlp->next;
	dlp->next = ndlnode;
	ndlnode->prev = dlp;
	ndlnode->next->prev = ndlnode;
}

int main()
{
	dlink_data *dldata;

	dlink_init(&dldata);
	dlink_show(dldata);

	dlink_insert(dldata, 0, 'e');
	dlink_insert(dldata, 0, 'm');
	dlink_insert(dldata, 3, 'n');
	dlink_insert(dldata, 0, 'q');
	dlink_show(dldata);

#if 0
	dlink_delete();
	dlink_show(dldata);

	dlink_amend();
	dlink_show(dldata);

	dlink_select();	
	dlink_show(dldata);
#endif
	return 0;
}
