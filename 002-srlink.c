#include <stdio.h>
#include <stdlib.h>


/******  不要头节点了(头节点不是必须要有的，但是但凡链表一定要有头指针[指向头节点或者首元节点]) !
<------------------
->0->1-> ... ->99->
Tig: 如果没有了头结点，诸如insert delete可能会引起头指针的改变，所以要使用二级指针 **p
******/

typedef struct _srlink_data {
	char data;
	struct _srlink_data *next;
}srlink_data;

static void srlink_show(srlink_data *srldata)
{
	srlink_data *srlp = srldata;
	if (!srlp) {
		printf("srlink is not exsit\n");
		return ;
	}

	while (1) {
		printf("%c->", srlp->data);
		srlp = srlp->next;
		if (srlp == srldata) {
			break;
		}
	}
	printf("\n");
}

static void srlink_init(srlink_data **srldata)
{
	*srldata = (srlink_data *)malloc(sizeof(srlink_data));
	if (!*srldata) {
		printf("srlink malloc failed\n");
		return ;
	}
	(*srldata)->next = *srldata;
}

static void srlink_insert(srlink_data **srldata, unsigned int loc, char data)
{
	int i = 0;
	static int first_init = 0;
	srlink_data *srlp = *srldata;
	if (!srlp) {
		printf("srlink is not exsit\n");
		return ;
	}

	if (first_init == 0 && loc == 0) {
		srlp->data = data;	
		first_init = -1;
		return ;
	} else {
	}

	srlink_data *nsrldata = (srlink_data *)malloc(sizeof(srlink_data));
	if (!nsrldata) {
		printf("nsrldata malloc failed\n");
		return ;
	}
	nsrldata->data = data;

	if (loc == 0) { // 首元位置
		while (1) {
			if (srlp->next == *srldata) {
				srlp->next = nsrldata;
				nsrldata->next = *srldata;
				*srldata = nsrldata;
				return ;
			}
			srlp = srlp->next;
		}
	}

	for (i = 1; i < loc; i++) {
		srlp = srlp->next;
		if (srlp->next == *srldata) {
			printf("insert loc %d is invalid\n", loc);
			return ;
		}
	}
	nsrldata->next = srlp->next;
	srlp->next = nsrldata;
}

static void srlink_delete(srlink_data **srldata, unsigned int loc)
{
	int i;
	srlink_data *srlp = *srldata;
	srlink_data *prev = NULL;
	if (!srlp) {
		printf("srlink is not exsit\n");
		return ;
	}

	//head(0)->head(0); 0
	if (loc == 0 && srlp->next == *srldata) {
		free(*srldata);
		*srldata = NULL;
		printf("完全删除了整个srlink链表\n");
		return ;
	}

	//head(0)->(1)...->head(0); 0
	if (loc == 0) {
		prev = *srldata;
		while (prev->next != *srldata) {
			prev = prev->next;
		}
		prev->next = (*srldata)->next;
		free(*srldata);
		*srldata = prev->next;
		return ;
	}

	//head(0)->(1)...->head(0); n
	for (i = 1; i < loc; i++) {
		srlp = srlp->next;
		if (srlp->next == *srldata) {
			printf("delete loc %d is invalid\n", loc);
			return ;
		}
	}
	srlink_data *desrlp = srlp->next;
	srlp->next = srlp->next->next;
	free(desrlp);
	desrlp = NULL;
}

static void srlink_amend(srlink_data *srldata, unsigned int loc, char data)
{
	int i = 0;
	srlink_data *srlp = srldata;
	if (!srlp) {
		printf("srlink is not exsit\n");
		return ;
	}

	for (; i < loc; i++) {
		srlp = srlp->next;
		if (srlp == srldata) {
			printf("amend loc %d is invalid\n", loc);
			return ;
		}
	}

	srlp->data = data;
}

static int srlink_select(srlink_data *srldata, char data)
{
	int loc = -1;
	srlink_data *srlp = srldata;
	if (!srlp) {
		printf("srlink is not exsit\n");
		return -1;
	}

	if (srlp->data == data) {
		loc = 0;
		return loc;
	}
	for (srlp = srlp->next, loc = 1; srlp != srldata; srlp = srlp->next) {
		if (srlp->data == data) {
			return loc;
		}
		loc++;
	}

	return -1;
}

int main()
{
	srlink_data *srldata;
	srlink_show(srldata);

	srlink_init(&srldata);
	srlink_show(srldata);

	srlink_insert(&srldata, 0, 'm');
	srlink_insert(&srldata, 0, 't');
	srlink_insert(&srldata, 0, 't');
	srlink_insert(&srldata, 0, 't');
	srlink_insert(&srldata, 3, 'e');
	srlink_insert(&srldata, 3, 'e');
	srlink_insert(&srldata, 3, 'e');
	srlink_insert(&srldata, 2, 'e');
	srlink_insert(&srldata, 1, 'w');
	srlink_show(srldata);

	srlink_delete(&srldata, 0);
	srlink_show(srldata);
	srlink_delete(&srldata, 3);
	srlink_delete(&srldata, 1);
	srlink_delete(&srldata, 3);
	srlink_show(srldata);

	srlink_amend(srldata, 3, 'l');
	srlink_amend(srldata, 0, 'l');
	srlink_amend(srldata, 8, 'l');
	srlink_show(srldata);

	int loc;
	loc = srlink_select(srldata, 'l');
	printf("select 'l' in loc %d\n", loc);
	loc = srlink_select(srldata, 'm');
	printf("select 'm' in loc %d\n", loc);
	loc = srlink_select(srldata, 'q');
	printf("select 'q' in loc %d\n", loc);

	return 0;
}
