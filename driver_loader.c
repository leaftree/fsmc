
/**
 * driver_loader.c
 *
 * Copyright (C) 2018 by Liu YunFeng.
 *
 *        Create : 2018-03-14 09:07:50
 * Last Modified : 2018-03-14 09:07:50
 */

#include <dlfcn.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "dbug.h"
#include "util.h"
#include "driver_loader.h"

static int Connection(int a, int b)
{
	printf("a=%d b=%d\n", a, b);
	return 0;
}

static int DisConnection(int a, int b)
{
	printf("a=%d b=%d\n", a, b);
	return 0;
}

static driver_func driver_func_template[] = {
	{DB_CONNECTION, "Connection", (void*)Connection},
	{DB_DISCONNECTION, "DisConnection", (void*)DisConnection},
};

static int open_driver(driver_manager *driver)
{
	DBUG_ENTER(__func__);

	int i;

	driver->dl_handle = dlopen(driver->driver_name, RTLD_LAZY);
	if(driver->dl_handle == NULL)
	{
		sprintf(driver->errstr, "%s", dlerror());
		DBUG_RETURN(RETURN_FAILURE);
	}

	dlerror();
	driver->func = malloc(sizeof(driver_func_template));
	if(driver->func == NULL)
	{
		sprintf(driver->errstr, "%s", strerror(errno));
		DBUG_RETURN(RETURN_FAILURE);
	}
	memcpy(driver->func, &driver_func_template, sizeof(driver_func_template));

	for(i=0; i<sizeof(driver_func_template)/sizeof(driver_func_template[0]); i++)
	{
		driver->func[i].func = dlsym(driver->dl_handle, driver->func[i].name);
		if (driver->func[i].func == NULL)
		{
			sprintf(driver->errstr, "%s", dlerror());
			DBUG_RETURN(RETURN_FAILURE);
		}
	}

	DBUG_RETURN(RETURN_SUCCESS);
}

static int close_driver(driver_manager *driver)
{
	DBUG_ENTER(__func__);

	if(driver == NULL)
		DBUG_RETURN(RETURN_FAILURE);

	mFree(driver->driver_name);
	mFree(driver->func);
	dlclose(driver->dl_handle);
	driver->errstr[0] = 0;

	DBUG_RETURN(RETURN_SUCCESS);
}

int load_driver(driver_manager *driver)
{
	DBUG_ENTER(__func__);

	if(driver == NULL || driver->driver_name == NULL)
		DBUG_RETURN(RETURN_FAILURE);

	DBUG_RETURN(open_driver(driver));

	DBUG_RETURN(RETURN_SUCCESS);
}
