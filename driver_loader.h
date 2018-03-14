
/**
 * driver_loader.h
 *
 * Copyright (C) 2018 by Liu YunFeng.
 *
 *        Create : 2018-03-12 23:08:07
 * Last Modified : 2018-03-12 23:08:07
 */

#ifndef __DRIVER_LOADER_H__
#define __DRIVER_LOADER_H__

__BEGIN_DECLS

#define DB_CONNECTION 1
#define DB_DISCONNECTION 2

typedef struct driver_func
{
	int index;
	char *name;
	int (*func)();
}driver_func;

typedef struct driver_manager
{
	char *driver_name;
	void *dl_handle;
	driver_func *func;
	char errstr[128];
} driver_manager;

__END_DECLS

#endif /* __DRIVER_LOADER_H__ */
