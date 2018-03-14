
/**
 * a.cpp
 *
 * Copyright (C) 2018 by Liu YunFeng.
 *
 *        Create : 2018-03-10 18:57:59
 * Last Modified : 2018-03-10 18:57:59
 */

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "log.h"
#include "util.h"
#include "dbug.h"
#include "config_loader.h"
#include "driver_loader.h"

int main(int argc, char **argv)
{
	DBUG_PUSH("d:t:O");
	DBUG_ENTER(__func__);
	DBUG_PROCESS("main");

	int retval = 0;
	st_log_meta log;

	if((retval=log_open(".", "a.txt", LOG_DEBUG, &log)) != 0)
	{
		DBUG_PRINT(__func__, ("log_open fail. %s", strerror(retval)));
		DBUG_RETURN(RETURN_FAILURE);
	}

	if((retval=LOG_ERROR(&log, "%s", strerror(11)))!=0)
	{
		DBUG_PRINT(__func__, ("log_write fail. %s", strerror(retval)));
		DBUG_RETURN(RETURN_FAILURE);
	}

	if((retval=LOG_INFO(&log, "%s", strerror(12)))!=0)
	{
		DBUG_PRINT(__func__, ("log_write fail. %s", strerror(retval)));
		DBUG_RETURN(RETURN_FAILURE);
	}

	if((retval=LOG_WARN(&log, "%s", strerror(13)))!=0)
	{
		DBUG_PRINT(__func__, ("log_write fail. %s", strerror(retval)));
		DBUG_RETURN(RETURN_FAILURE);
	}

	fsmc_config_t conf;
	memset(&conf, 0x0, sizeof(fsmc_config_t));
	load_config("test.ini", &conf);

	driver_manager driver;
	char driver_name[100] = "";
	if(get_config_value(&conf, "Oracle", "Driver", driver_name)!=RETURN_SUCCESS)
	{
		DBUG_PRINT(__func__, ("get_config_value fail"));
		DBUG_RETURN(RETURN_FAILURE);
	}
	driver.driver_name = strdup(driver_name);
	if(load_driver(&driver) == RETURN_FAILURE)
	{
		DBUG_PRINT("load_driver", ("%s", driver.errstr));
		DBUG_RETURN(RETURN_FAILURE);
	}

	unload_config(&conf);

	log_close(&log);
	DBUG_RETURN(RETURN_SUCCESS);
}
