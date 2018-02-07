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

static void drlink_delete(drlink_data **drldata, unsigned int loc)
{
	int i = 0;
	drlink_data *drlp = *drldata;
	drlink_data *temp;
	if (!drlp) {
		printf("drlink is not exsit\n");
		return ;
	}

	if (drlp->next == *drldata && loc == 0) { // head 0 0
		printf("0\n");
		free(drlp);
		*drldata = NULL;
		return ;
	}
	if (loc == 0) { //head 0... 1  1
		printf("1\n");
		temp = drlp->prev;
		temp->next = drlp->next;
		drlp->next->prev = temp;
		free(*drldata);
		*drldata = temp->next;
		return ;
	}
	for (; i < loc; i++) { // head... n
		if (drlp->next == *drldata) {
			printf("delete loc %d is invalid\n", loc);
			return ;
		}
		drlp = drlp->next;
	}
	temp = drlp->prev;
	temp->next = drlp->next;
	drlp->next->prev = temp;
	free(drlp);
	drlp = NULL;
}

static void drlink_amend(drlink_data *drldata, unsigned int loc, char data)
{
	int i = 0;
	drlink_data *drlp = drldata;
	if (!drlp) {
		printf("drlink is not exsit\n");
		return ;
	}

	for (; i < loc; i++) {
		drlp = drlp->next;
		if (drlp == drldata) {
			printf("amend loc %d is invalid\n", loc);
			return ;
		}
	}
	drlp->data = data;
}

static int drlink_select(drlink_data *drldata, char data)
{
	int i = 0;
	drlink_data *drlp = drldata;
	if (!drlp) {
		printf("drlink is not exsit\n");
		return ;
	}

	do {
		if (drlp->data == data) {
			return i;
		}
		drlp = drlp->next;
		i++;
	}while(drlp != drldata);

	return -1;
}

static void drlink_destroy(drlink_data **drldata)
{
	drlink_data *drlp = *drldata;
	drlink_data *temp;
	if (!drlp) {
		printf("drlink is not exsit\n");
		return ;
	}

	do {
		drlink_delete(drldata, 0);
		printf("2\n");
	}while(!(*drldata));
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
	drlink_insert(&drldata, 2, 'm');
	drlink_show(drldata);

	drlink_delete(&drldata, 0);
	drlink_show(drldata);
	drlink_delete(&drldata, 1);
	drlink_show(drldata);
	drlink_delete(&drldata, 2);
	drlink_show(drldata);
	drlink_delete(&drldata, 2);
	drlink_show(drldata);

	drlink_amend(drldata, 1, 'p');
	drlink_show(drldata);
	drlink_amend(drldata, 0, 'u');
	drlink_show(drldata);
	drlink_amend(drldata, 2, 'y');
	drlink_show(drldata);

	int loc;
	loc = drlink_select(drldata, 'u');
	printf("select 'u' in loc %d\n", loc);
	loc = drlink_select(drldata, 'p');
	printf("select 'p' in loc %d\n", loc);
	loc = drlink_select(drldata, 'g');
	printf("select 'g' in loc %d\n", loc);

	drlink_destroy(&drldata);
	drlink_show(drldata);

	return 0;
}
