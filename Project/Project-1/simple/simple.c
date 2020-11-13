/**
 * @file simple.c
 * @brief 
 * @author WeixiongLin (wx_lin@outlook.com)
 * @version 1.0
 * @date 2020-11-13
 * 
 * @copyright Copyright (c) 2020  WeixiongLin
 * 
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-11-13 <td>1.0     <td>WeixiongLin     <td>内容
 * </table>
 */

#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/hash.h>
#include<linux/gcd.h>
#include<asm/param.h>
#include<linux/jiffies.h>


/* This function is called when the module is loaded. */

int simple_init(void)
{
    printk(KERN_INFO "Loading Module\n");
    printk(KERN_INFO "GOLDEN_RATIO_PRIME %llu\n", GOLDEN_RATIO_PRIME);
    printk(KERN_INFO "start: %ld\n", jiffies);
    return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
    printk(KERN_INFO "GCD: %lu\n", gcd(3300, 24));
    printk(KERN_INFO "HZ: %d\n", HZ);
    printk(KERN_INFO "end: %ld\n", jiffies);
	printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init(simple_init);
module_exit(simple_exit);


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");
