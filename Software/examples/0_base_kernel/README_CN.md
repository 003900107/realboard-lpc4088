# ��� #

0_basic_kernel��һ��RB4088�Ļ������̣�������һ���������ںˣ������������Ϣ��

һ��������RT-Thread���������´��빹�ɣ�

* RT-Thread���������루application\\startup.c�ļ������������е�`main()`������`rtthread_startup()`������
* �û��Լ���Ӧ�ô��루application\\application.c�ļ������������û��Լ���Ӧ����ں�����`rt_application_init()`����ʵ�֣�
* �û��������ļ���rtconfig.h�ļ���

�����ʾ���У��û��Լ���Ӧ�ô�������Ǵ�����һ���̣߳������ӡһ��

    Hello RT-Thread!

����Ĵ���ʾ����application\\application.c�ļ�����

```
#include <rtthread.h>

void rt_init_thread_entry(void* parameter)
{
    rt_kprintf("Hello RT-Thread!\n");
}
    
int rt_application_init()
{
    rt_thread_t tid;

    tid = rt_thread_create("init",
        rt_init_thread_entry, RT_NULL,
        2048, RT_THREAD_PRIORITY_MAX/3, 20);
    if (tid != RT_NULL)
        rt_thread_startup(tid);

    return 0;
}
```

����`rt_application_init()`����RT-Thread����������`rtthread_startup`���б����á������Ӧ�ó�ʼ����ں����У��û����Դ����Լ������񣨻��һ�����񣩡������ʾ�����Ǵ���һ��������"init"�ĳ�ʼ���̣߳������ʼ���̵߳������`rt_init_thread_entry`������

rt_init_thread_entry����������rt_kprintf�������һ��`Hello RT-Thread!`��Ϣ��

## ���н�� ##

ʹ��GNU GCC��Keil MDK���룬���ص�RB4088����������ǿ��԰ѷ��ڵ�USB�߽ӵ�RB4088�����Ͻӱ����UART0/ISP�Ķ˿��ϣ������ϻ���һ�������豸������ʹ��PuTTY���Կ������еĽ����

     \ | /
    - RT -     Thread Operating System
     / | \     1.2.0 build Dec 18 2013
     2006 - 2013 Copyright by rt-thread team
    Hello RT-Thread!

