/*
** EPITECH PROJECT, 2025
** barcade
** File description:
** DynamicLib
*/


#include <dlfcn.h>

extern "C" {
	void *openDynamicLib(const char *path)
	{
		return dlopen(path, RTLD_LAZY);
	}
	void *getFunctionDynamicLib(void *moduleHandle, const char *name)
	{
		return dlsym(moduleHandle, name);
	}
	void closeDynamicLib(void *moduleHandle)
	{
		dlclose(moduleHandle);
	}
	const char *getDlError(void)
	{
		return dlerror();
	}
}