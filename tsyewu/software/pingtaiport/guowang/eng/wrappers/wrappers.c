/**
 * NOTE:
 *
 * HAL_TCP_xxx API reference implementation: wrappers/os/ubuntu/HAL_TCP_linux.c
 *
 */
 #include<errno.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/signal.h>
#include <linux/types.h>
#include <asm/byteorder.h>
#include <linux/ip.h>
#include <netinet/tcp.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include  <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include<errno.h>


#include <stdarg.h>
#include "infra_types.h"
#include "infra_defs.h"
#include "infra_compat.h"
#include "wrappers_defs.h"
#include "stdarg.h"

#include "systemconfig.h"
#include "datacenter.h"
#include "utily.h"



static pthread_mutex_t gwMutexLock = PTHREAD_MUTEX_INITIALIZER;

static int socketFd = 0;

/**
 *
 * 函数 HAL_Firmware_Persistence_Start() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_Firmware_Persistence_Start() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_Firmware_Persistence_Start(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_Firmware_Persistence_Start, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
void HAL_Firmware_Persistence_Start(void)
{
	return;
}


/**
 *
 * 函数 HAL_Firmware_Persistence_Stop() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_Firmware_Persistence_Stop() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_Firmware_Persistence_Stop(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_Firmware_Persistence_Stop, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
int HAL_Firmware_Persistence_Stop(void)
{
	return (int)1;
}


/**
 *
 * 函数 HAL_Firmware_Persistence_Write() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_Firmware_Persistence_Write() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_Firmware_Persistence_Write(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_Firmware_Persistence_Write, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
int HAL_Firmware_Persistence_Write(char *buffer, uint32_t length)
{
	return (int)1;
}


/**
 *
 * 函数 HAL_Free() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_Free() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_Free(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_Free, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * @brief Deallocate memory block
 *
 * @param[in] ptr @n Pointer to a memory block previously allocated with platform_malloc.
 * @return None.
 * @see None.
 * @note None.
 */
void HAL_Free(void *ptr)
{
	free(ptr);
	return;
}


/**
 *
 * 函数 HAL_GetFirmwareVersion() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_GetFirmwareVersion() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_GetFirmwareVersion(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_GetFirmwareVersion, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * @brief Get firmware version
 *
 * @param [ou] version: array to store firmware version, max length is IOTX_FIRMWARE_VER_LEN
 * @return the actual length of firmware version
 */
int HAL_GetFirmwareVersion(char *version)
{
	char buf[30];
	sprintf(buf,"%d",controlConfigInfo()->softwareVersion);
	memcpy(version,buf,strlen(buf));
	return (int)1;
}


/**
 *
 * 函数 HAL_Kv_Get() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_Kv_Get() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_Kv_Get(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_Kv_Get, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_KV_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
int HAL_Kv_Get(const char *key, void *val, int *buffer_len)
{
	return (int)1;
}


/**
 *
 * 函数 HAL_Kv_Set() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_Kv_Set() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_Kv_Set(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_Kv_Set, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_KV_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
int HAL_Kv_Set(const char *key, const void *val, int len, int sync)
{
	return (int)1;
}


/**
 *
 * 函数 HAL_Malloc() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_Malloc() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_Malloc(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_Malloc, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * @brief Allocates a block of size bytes of memory, returning a pointer to the beginning of the block.
 *
 * @param [in] size @n specify block size in bytes.
 * @return A pointer to the beginning of the block.
 * @see None.
 * @note Block value is indeterminate.
 */
void *HAL_Malloc(uint32_t size)
{
	int *p = NULL;
	p = (int*)malloc(size * sizeof(int));
	return p;
}


/**
 *
 * 函数 HAL_MutexCreate() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_MutexCreate() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_MutexCreate(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_MutexCreate, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * @brief Create a mutex.
 *
 * @retval NULL : Initialize mutex failed.
 * @retval NOT_NULL : The mutex handle.
 * @see None.
 * @note None.
 */
void *HAL_MutexCreate(void)
{
	pthread_mutex_init(&gwMutexLock,NULL);
	
	return (&gwMutexLock);
}


/**
 *
 * 函数 HAL_MutexDestroy() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_MutexDestroy() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_MutexDestroy(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_MutexDestroy, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * @brief Destroy the specified mutex object, it will release related resource.
 *
 * @param [in] mutex @n The specified mutex.
 * @return None.
 * @see None.
 * @note None.
 */
void HAL_MutexDestroy(void *mutex)
{
	pthread_mutex_destroy(mutex);
	return;
}


/**
 *
 * 函数 HAL_MutexLock() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_MutexLock() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_MutexLock(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_MutexLock, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * @brief Waits until the specified mutex is in the signaled state.
 *
 * @param [in] mutex @n the specified mutex.
 * @return None.
 * @see None.
 * @note None.
 */
void HAL_MutexLock(void *mutex)
{
	pthread_mutex_lock(mutex);
	return;
}


/**
 *
 * 函数 HAL_MutexUnlock() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_MutexUnlock() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_MutexUnlock(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_MutexUnlock, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * @brief Releases ownership of the specified mutex object..
 *
 * @param [in] mutex @n the specified mutex.
 * @return None.
 * @see None.
 * @note None.
 */
void HAL_MutexUnlock(void *mutex)
{
	pthread_mutex_unlock(mutex);
	return;
}


/**
 *
 * 函数 HAL_Random() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_Random() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_Random(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_Random, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
uint32_t HAL_Random(uint32_t region)
{
	return (region > 0) ? rand() % region : 0;
}


/**
 *
 * 函数 HAL_SSL_Destroy() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_SSL_Destroy() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_SSL_Destroy(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_SSL_Destroy, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/tls/HAL_TLS_mbedtls.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
int32_t HAL_SSL_Destroy(uintptr_t handle)
{
	return (int32_t)1;
}


/**
 *
 * 函数 HAL_SSL_Establish() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_SSL_Establish() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_SSL_Establish(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_SSL_Establish, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/tls/HAL_TLS_mbedtls.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
uintptr_t HAL_SSL_Establish(const char *host,
                            uint16_t port,
                            const char *ca_crt,
                            uint32_t ca_crt_len)
{
	return (uintptr_t)1;
}


/**
 *
 * 函数 HAL_SSL_Read() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_SSL_Read() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_SSL_Read(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_SSL_Read, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/tls/HAL_TLS_mbedtls.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
int HAL_SSL_Read(uintptr_t handle, char *buf, int len, int timeout_ms)
{
	return (int)1;
}


/**
 *
 * 函数 HAL_SSL_Write() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_SSL_Write() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_SSL_Write(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_SSL_Write, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/tls/HAL_TLS_mbedtls.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
int HAL_SSL_Write(uintptr_t handle, const char *buf, int len, int timeout_ms)
{
	return (int)1;
}


/**
 *
 * 函数 HAL_SleepMs() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_SleepMs() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_SleepMs(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_SleepMs, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * @brief Sleep thread itself.
 *
 * @param [in] ms @n the time interval for which execution is to be suspended, in milliseconds.
 * @return None.
 * @see None.
 * @note None.
 */
void HAL_SleepMs(uint32_t ms)
{
	mSleep(ms);
	return;
}


/**
 *
 * 函数 HAL_Snprintf() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_Snprintf() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_Snprintf(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_Snprintf, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * @brief Writes formatted data to string.
 *
 * @param [out] str: @n String that holds written text.
 * @param [in] len: @n Maximum length of character will be written
 * @param [in] fmt: @n Format that contains the text to be written, it can optionally contain embedded format specifiers
     that specifies how subsequent arguments are converted for output.
 * @param [in] ...: @n the variable argument list, for formatted and inserted in the resulting string replacing their respective specifiers.
 * @return bytes of character successfully written into string.
 * @see None.
 * @note None.
 */
int HAL_Snprintf(char *str, const int len, const char *fmt, ...)
{
	va_list args;
//	int rc;

	va_start(args,fmt);
	vsnprintf(str,len,fmt,args);
	va_end(args);
	return (int)1;
}


/**
 *
 * 函数 HAL_Srandom() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_Srandom() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_Srandom(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_Srandom, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
void HAL_Srandom(uint32_t seed)
{
	srand(seed);
	return;
}


/**
 *
 * 函数 HAL_TCP_Destroy() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_TCP_Destroy() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_TCP_Destroy(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_TCP_Destroy, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_TCP_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * @brief Destroy the specific TCP connection.
 *
 * @param [in] fd: @n Specify the TCP connection by handle.
 *
 * @return The result of destroy TCP connection.
 * @retval < 0 : Fail.
 * @retval   0 : Success.
 */
int HAL_TCP_Destroy(uintptr_t fd)
{
	close(fd);
	return (int)1;
}


/**
 *
 * 函数 HAL_TCP_Establish() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_TCP_Establish() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_TCP_Establish(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_TCP_Establish, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_TCP_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * @brief Establish a TCP connection.
 *
 * @param [in] host: @n Specify the hostname(IP) of the TCP server
 * @param [in] port: @n Specify the TCP port of TCP server
 *
 * @return The handle of TCP connection.
   @retval (uintptr_t)(-1): Fail.
   @retval All other values(0 included): Success, the value is handle of this TCP connection.
 */

uintptr_t HAL_TCP_Establish(const char *host, uint16_t port)
{
	struct sockaddr_in  servaddr;
	 if((socketFd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
	 	TRACE_PROJ_SOCKET_INFO("creat socket error : %s(errno: %d)\n",strerror(errno),errno);
		return -1;
	 }

	 memset(&servaddr, 0, sizeof(servaddr));
          servaddr.sin_family = AF_INET;
//	servaddr.sin_addr.s_addr = inet_addr(host);
         servaddr.sin_port = htons(port);

	if(inet_pton(AF_INET, controlConfigInfo()->deviceIp, &servaddr.sin_addr) <= 0){
		TRACE_PROJ_SOCKET_INFO("inet_pton error for \n");
	    	return -1;
           }

	if(connect(socketFd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
		TRACE_PROJ_SOCKET_INFO("connect error: %s(errno: %d)\n",strerror(errno),errno);
		return -1;
	}
	return (uintptr_t)1;
}


/**
 *
 * 函数 HAL_TCP_Read() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_TCP_Read() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_TCP_Read(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_TCP_Read, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_TCP_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * @brief Read data from the specific TCP connection with timeout parameter.
 *        The API will return immediately if 'len' be received from the specific TCP connection.
 *
 * @param [in] fd @n A descriptor identifying a TCP connection.
 * @param [out] buf @n A pointer to a buffer to receive incoming data.
 * @param [out] len @n The length, in bytes, of the data pointed to by the 'buf' parameter.
 * @param [in] timeout_ms @n Specify the timeout value in millisecond. In other words, the API block 'timeout_ms' millisecond maximumly.
 *
 * @retval       -2 : TCP connection error occur.
 * @retval       -1 : TCP connection be closed by remote server.
 * @retval        0 : No any data be received in 'timeout_ms' timeout period.
 * @retval (0, len] : The total number of bytes be received in 'timeout_ms' timeout period.

 * @see None.
 */
int32_t HAL_TCP_Read(uintptr_t fd, char *buf, uint32_t len, uint32_t timeout_ms)
{
	TRACE_PROJ_SOCKET_INFO("#########    HAL_TCP_Read    ########## \n");
	int ret = 0;
	fd_set rset;
	int recvLength = 0;
	while(1){
		FD_ZERO(&rset);
	         FD_SET(fd, &rset);
		ret = select(fd+1, &rset, NULL, NULL, NULL);

		  if ((ret == EBADF) || (ret == EINTR)) {
		   	   printLogToFile("ret == EBADF");
			   TRACE_PROJ_SOCKET_INFO("ret == EBADF \n");
		   
		   }
		  recvLength = recv(fd, buf, len,0);
		  if(recvLength == -1){
			 mSleep(10); 
			 continue;
		  }
		  mSleep(10);
	}
	return (int32_t)1;
}


/**
 *
 * 函数 HAL_TCP_Write() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_TCP_Write() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_TCP_Write(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_TCP_Write, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_TCP_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * @brief Write data into the specific TCP connection.
 *        The API will return immediately if 'len' be written into the specific TCP connection.
 *
 * @param [in] fd @n A descriptor identifying a connection.
 * @param [in] buf @n A pointer to a buffer containing the data to be transmitted.
 * @param [in] len @n The length, in bytes, of the data pointed to by the 'buf' parameter.
 * @param [in] timeout_ms @n Specify the timeout value in millisecond. In other words, the API block 'timeout_ms' millisecond maximumly.
 *
 * @retval      < 0 : TCP connection error occur..
 * @retval        0 : No any data be write into the TCP connection in 'timeout_ms' timeout period.
 * @retval (0, len] : The total number of bytes be written in 'timeout_ms' timeout period.

 * @see None.
 */
int32_t HAL_TCP_Write(uintptr_t fd, const char *buf, uint32_t len, uint32_t timeout_ms)
{
	int ret = 0;
	fd_set rset;
	
	FD_ZERO(&rset);
	FD_SET(fd, &rset);
			 
	ret = select(fd+1,NULL , &rset, NULL, NULL);

	ret = send(fd,buf,len,0);
	if(ret == -1)
		return -1;
	
	return (int32_t)1;
}


/**
 *
 * 函数 HAL_UTC_Get() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_UTC_Get() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_UTC_Get(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_UTC_Get, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
long HAL_UTC_Get(void)
{
	time_t time_now = time(NULL);
	return time_now;
}


/**
 *
 * 函数 HAL_UTC_Set() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_UTC_Set() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_UTC_Set(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_UTC_Set, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
int HAL_UTC_Set(long s)
{
	char buf[100];
	char orgBuf[100];
	char fatBuf[] = "+%Y-%m-%d.%H:%M:%S";
	char headBuf[] = "date -d @";
	sprintf(buf,"%s%ld %s",headBuf,s,fatBuf);
	mySystem(buf,orgBuf,100);
	orgBuf[10] = ' ';
	memset(buf,0,100);
	sprintf(buf,"date -s %s",orgBuf);
	memset(orgBuf,0,100);
	mySystem(buf,orgBuf,100);
	
	return (int)1;
}


/**
 *
 * 函数 HAL_UptimeMs() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_UptimeMs() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_UptimeMs(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_UptimeMs, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * @brief Retrieves the number of milliseconds that have elapsed since the system was boot.
 *
 * @return the number of milliseconds.
 * @see None.
 * @note None.
 */
uint64_t HAL_UptimeMs(void)
{
	return (uint64_t)1;
}


/**
 *
 * 函数 HAL_Vsnprintf() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_Vsnprintf() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_Vsnprintf(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_Vsnprintf, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
int HAL_Vsnprintf(char *str, const int len, const char *format, va_list ap)
{
	return vsnprintf(str,len,format,ap);
}


