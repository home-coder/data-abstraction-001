#include <stdio.h>

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

	for (; ) {
	
	}

}

int main()
{
	drlink_data *drldata;	
	drlink_show(drldata);
#if 0
	drlink_init(&drldata);
	drlink_insert(drldata, 0, 'a');
	drlink_delete();
	drlink_amend();
	drlink_select();
#endif

	return 0;
}
