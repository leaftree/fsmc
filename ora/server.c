
/**
 * dbservice.c
 *
 * Copyright (C) 2018 by Liu YunFeng.
 *
 *        Create : 2018-03-02 11:03:12
 * Last Modified : 2018-03-02 11:03:12
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/prctl.h>
#include <limits.h>
#include <signal.h>

#include <hiredis.h>
#include "cJSON.h"
#include "db.h"

const static int rport = 6379;

int main()
{
	DBUG_ENTER(__func__);

	DBUG_PUSH ("d:t:O");
	DBUG_PROCESS ("测试程序");
	prctl(PR_SET_NAME, "测试程序");

	DBDriver *dbo = DBHEnvNew(NULL, "fzlc50db@afc", "fzlc50db");
	if(dbo == NULL)
	{
		DBUG_PRINT("DBHEnvNew", ("Create database operate handle env fail"));
		DBUG_RETURN(-1);
	}
	if(DBO_SUCC != DBConnection(dbo))
	{
		DBUG_PRINT("Connect to database fail", ("%s", dbo->errstr));
		DBUG_RETURN(-1);
	}

	DBCloseConnection(dbo);
	DBReleaseHEnv(&dbo);

	DBUG_RETURN(0);
}
