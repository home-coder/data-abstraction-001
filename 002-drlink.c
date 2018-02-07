#include <stdio.h>
#include <stdlib.h>

/****************************************

	没有头节点，有头指针->首元节点

****************************************/

typedef struct _drlink_data {
	char data;
	struct _drlink_data *prev;
	struct _drlink_data *next;
}drlink_data;

static void drlink_show(drlink_data *drldata)
{
	drlink_data *drlp = drldata;
	if (!drlp) {
		printf("drlink is not exsit\n");
		return ;
	}

	do {
		printf("%c<->", drlp->data);
		drlp = drlp->next;
	}while(drlp != drldata);
	printf("//"); // 双向循环链表  输出时检测正序和逆序是否都正确
	drlp = drldata;
	do {
		printf("%c<->", drlp->data);
		drlp = drlp->prev;
	}while(drlp != drldata);
	printf("\n");
}

static void drlink_init(drlink_data **drldata)
{
	*drldata = (drlink_data *)malloc(sizeof(drlink_data));
	if (!drldata) {
		printf("drldata malloc failed\n");
		return ;
	}

	(*drldata)->prev = *drldata;
	(*drldata)->next = *drldata;
}

static void drlink_insert(drlink_data **drldata, unsigned int loc, char data)
{
	int i = 0;
	static int first_init = 1;
	drlink_data *drlp = *drldata;
	if (!drlp) {
		printf("drlink is not exsit\n");
		return ;
	}

	if (first_init == 1 && loc == 0) { //第一次insert可以看作是amend了首元节点
		(*drldata)->data = data;
		first_init = 0;
		return ;
	}

	drlink_data *ndrldata = (drlink_data *)malloc(sizeof(drlink_data));
	if (!ndrldata) {
		printf("ndrldata malloc failed\n");
		return ;
	}
	ndrldata->data = data;

	if (loc == 0) {
		drlink_data *pdrldata = drlp->prev;
		pdrldata->next = ndrldata;
		ndrldata->prev = pdrldata;
		ndrldata->next = drlp;
		drlp->prev = ndrldata;
		(*drldata) = ndrldata;
		return ;
	}

	for (; i < loc; i++) {
		drlp = drlp->next;
		if (drlp == *drldata) {
			printf("insert loc %d is invalid\n", loc);
			return ;
		}
	}
	drlink_data *temp = drlp->prev;
	ndrldata->next = drlp;
	drlp->prev = ndrldata;
	temp->next = ndrldata;
	ndrldata->prev = temp;
}

int main()
{
	drlink_data *drldata;	
	drlink_show(drldata);

	drlink_init(&drldata);
	drlink_show(drldata);

	drlink_insert(&drldata, 0, 'a');
	drlink_show(drldata);
	drlink_insert(&drldata, 0, 'a');
	drlink_show(drldata);
	drlink_insert(&drldata, 1, 'e');
	drlink_show(drldata);
	drlink_insert(&drldata, 4, 'i');
	drlink_show(drldata);
#if 0
	drlink_delete();
	drlink_amend();
	drlink_select();
	drlink_destroy();
#endif

	return 0;
}
