/*
   ��demo������������뽫HDC��BMP��ʽͼƬ����TF����Ŀ¼������ʾ��K2�������л�ͼƬ
 */
#include <board.h>
#include <rtthread.h>

#ifdef RT_USING_DFS
#include <dfs_fs.h>
#endif

#include "components.h"

void rt_init_thread_entry(void* parameter)
{
#ifdef RT_USING_COMPONENTS_INIT
	/* initialization RT-Thread Components */
	rt_components_init();
#endif

	rt_hw_spi_init();

	mci_hw_init("sd0");


	/* Filesystem Initialization */
#ifdef RT_USING_DFS
	/* mount sd card fat partition 1 as root directory */
	if (dfs_mount("sd0", "/", "elm", 0, 0) == 0)
	{
		rt_kprintf("File System initialized!\n");

		#if (RT_DFS_ELM_USE_LFN != 0) && (defined RT_DFS_ELM_CODE_PAGE_FILE)
        {
                extern void ff_convert_init(void);
                ff_convert_init();
        }
		#endif

	}
	else
	{
		rt_kprintf("File System initialzation failed!\n");
	}

# ifdef RT_USING_SQLITE
    sqlite_test();
# endif

#endif

    /* do some thing here. */
}

int rt_application_init()
{
    rt_thread_t tid;

    tid = rt_thread_create("init",
        rt_init_thread_entry, RT_NULL,
        2*2048, RT_THREAD_PRIORITY_MAX/3, 20);//

    if (tid != RT_NULL)
        rt_thread_startup(tid);

    return 0;
}
