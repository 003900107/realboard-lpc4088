/*
   ��demo������ʾ�����ļ�ϵͳ
 */
#include <board.h>
#include <rtthread.h>
#ifdef RT_USING_FINSH
#include <finsh.h>
#include <shell.h>
#endif


#include "components.h"

extern struct netif * netif_list;
extern void lpc_emac_hw_init(void);
extern void list_if(void);
void rt_init_thread_entry(void* parameter)
{
#ifdef RT_USING_LWIP
	/* initialize eth interface */
	lpc_emac_hw_init();
#endif
	
#ifdef RT_USING_COMPONENTS_INIT
	/* initialization RT-Thread Components */
	rt_components_init();
#endif

	rt_kprintf(" link beginning \r\n");
	while( !(netif_list->flags & NETIF_FLAG_UP)) 
	{	/*�ȴ�����׼����*/
		rt_thread_delay( RT_TICK_PER_SECOND);
	}

	rt_kprintf(" link ok \r\n");
    list_if();

	{
		extern rt_err_t mci_hw_init(const char *device_name);
		mci_hw_init("sd0");
	}
    /* do some thing here. */
}

int rt_application_init()
{
    rt_thread_t tid;

    tid = rt_thread_create("init",
        rt_init_thread_entry, RT_NULL,
        2048, RT_THREAD_PRIORITY_MAX/3, 20);//
	
    if (tid != RT_NULL)
        rt_thread_startup(tid);
	
    return 0;
}

#include <finsh.h>
int mountsd(const char * path)
{
	const char * mountpath = "/sd";
	if (path != NULL)
		mountpath = path;
    /* Filesystem Initialization */
#ifdef RT_USING_DFS
#ifdef RT_USING_DFS_ELMFAT
	/* mount sd card fat partition 1 as root directory */
	if (dfs_mount("sd0", mountpath, "elm", 0, 0) == 0)
	{
		rt_kprintf("[ok]\n");
		return 0;
	}
	else
	{
		rt_kprintf("[failed!]\n");
		return -1;
	}
#endif
#endif
}
FINSH_FUNCTION_EXPORT(mountsd, mount sdcard)

int mountnfs(const char * path)
{
	const char * mountpath = "/";
	if (path != NULL)
		mountpath = path;
	rt_kprintf("mount nfs to %s...", mountpath);
	if (dfs_mount(RT_NULL, mountpath, "nfs", 0, RT_NFS_HOST_EXPORT) == 0)
	{
		rt_kprintf("[ok]\n");
		return 0;
	}
	else
	{
		rt_kprintf("[failed!]\n");
		return -1;
	}
}
FINSH_FUNCTION_EXPORT(mountnfs, mount nfs)
