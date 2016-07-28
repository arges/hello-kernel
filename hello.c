/*
 *
 * (C) 2016 Canonical Ltd., Chris J Arges <christopherarges@gmail.com>
 *
 */

#include <linux/kernel.h>
#include <linux/module.h>

#define AUTHOR      "Chris J Arges <christopherarges@gmail.com>"
#define LICENSE     "GPLv2"

static int __init hello_init(void)
{
	printk("Hello, Kernel!\n");
	return 0;
}

static void __exit hello_cleanup(void)
{
	printk("Goodbye, Kernel!\n");
}

module_init(hello_init);
module_exit(hello_cleanup);

MODULE_AUTHOR(AUTHOR);
MODULE_LICENSE(LICENSE);
