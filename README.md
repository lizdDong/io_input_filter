# io_input_filter IO输入滤波软件包

## 1 介绍

**io_input_filter** 软件包提供一个有效的输入滤波功能，它会检测引脚电平的稳定状态，直到检测到持续稳定后才会触发状态改变，软件包提供简单易用的接口函数，用户可通过调整`IIF_TIMES`和`IIF_PERIOD`两个宏来改变滤波条件。

## 2 使用方法

### 2.1 配置宏
	IIF_TIMES       // 滤波次数，连续 IIF_TIMES 次读取引脚电平持续为高/低的次数
	IIF_PERIOD      // 滤波周期，每隔 IIF_PERIOD 毫秒读取一次引脚电平
	IIF_DEBUG_MODE  // IIF调试信息输出

### 2.2 接口说明

#### 2.2.1 数据结构:
```
struct io_input_filter
{
    uint8_t pin_id;           // 引脚id，可以由 GET_PIN() 获取
    uint8_t pin_status;       // 滤波后的引脚状态，高/低
    uint8_t filter_counts;    // 当前引脚电平已经持续稳定的次数
    struct io_input_filter *next;    // 单向链表 next
};
```
#### 2.2.2 函数说明：
1. `void iif_init(void);`
初始化函数，使用之前请先进行初始化。

2. `int iif_add_pin(rt_base_t pin);`
将一个引脚加入滤波控制器中，例如：
```
#define IO_IN1  GET_PIN(D, 11)
iif_add_pin(IO_IN1);
```

3. `int iif_read_pin(rt_base_t pin);`
读取引脚状态，例如：
```
if(iif_read_pin(IO_IN1) == PIN_HIGH)
	rt_kprintf("IO_IN1 Changed to HIGH\n");
else
	rt_kprintf("IO_IN1 Changed to LOW\n");
```

## 3 注意事项
软件包需要使能软件定时器`RT_USING_TIMER_SOFT`。

## 4 联系方式
https://github.com/lizdDong/io_input_filter








