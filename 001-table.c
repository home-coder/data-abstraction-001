#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct _table_data {
	int *data;
	unsigned int length;
	unsigned int size;
}table_data;

static void table_show(table_data *tdata)
{
	int i;

	for (i = 0; i < tdata->length; i++) {
		printf("%d->", tdata->data[i]);
	}
	printf("\n");
}

static void table_init(table_data **tdata, unsigned int size)
{
	*tdata = (table_data *)malloc(sizeof(table_data));
	if (!*tdata) {
		printf("malloc failed :tdata\n");
		exit(-1);
	}

	(*tdata)->size = size;
	(*tdata)->data = (int *)malloc(sizeof(int) * (*tdata)->size);
	if (!((*tdata)->data)) {
		printf("malloc failed :data\n");
		exit(-1);	
	}

	memset((*tdata)->data, 0xf, size);
	(*tdata)->length = 0;
}

static void table_insert(table_data *tdata, unsigned int loc, int data)
{
	int i;

	if (loc < 0 || loc >= tdata->length + 1) {
		printf("locaction (%d) is invalid\n", loc);
		exit(-1);
	}

	if (tdata->length == tdata->size ) {
		tdata->data = (int *)realloc(tdata->data, (tdata->size + 8) * sizeof(int));
		if (!tdata->data) {
			printf("realloc failed\n");
			exit(-1);
		}
	}

	for (i = tdata->length; i > loc; i--) {
		tdata->data[i] = tdata->data[i-1];
	}
	tdata->data[loc] = data;
	tdata->length++;
	table_show(tdata);
}

static void table_modify(table_data *tdata, unsigned int loc, int data)
{
	if (loc < 0 || loc >= tdata->length + 1) {
		printf("locaction (%d) is invalid\n", loc);
		exit(-1);
	}

	tdata->data[loc] = data;
}

static void table_delet(table_data *tdata, unsigned int loc)
{
	int i;

	if (loc < 0 || loc >= tdata->length + 1 || tdata->length <= 0) {
		printf("locaction (%d) is invalid\n", loc);
		exit(-1);
	}

	for (i = loc; i < tdata->length-1; i++) {
		tdata->data[i] = tdata->data[i+1];
	}
	tdata->length--;
	table_show(tdata);
}

static int table_select(table_data *tdata, int data)
{
	int i;

	for (i = 0; i < tdata->length; i++) {
		if (tdata->data[i] == data) {
			return i;
		}
	}
	return -1;
}

int main()
{
	table_data *tdata;

	table_init(&tdata, 10);
	printf("tdata size is %d\n", tdata->size);

	table_insert(tdata, 0, 9);
	table_insert(tdata, 0, 8);
	table_insert(tdata, 1, 3);
	table_insert(tdata, 0, 1);
	table_insert(tdata, 4, 2);

	table_modify(tdata, 1, 7);

	table_delet(tdata, 5);
	table_delet(tdata, 0);

	unsigned int loc = table_select(tdata, 7);
	printf("loc is %d\n", loc);

	table_show(tdata);

exit:
	free(tdata);
	return 0;
}
