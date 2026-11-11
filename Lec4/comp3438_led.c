#include <linux/module.h>
#include <linux/init.h>
#include <linux/kdev_t.h>
#include <linux/printk.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/string.h>
#include <linux/gpio.h>
#include <mach/gpio.h>
#include <asm-generic/uaccess.h>

#define S_N 0
#define N_D 1
#define DEVICE_NAME "LED device"

#define LED1 S5PV210_GPJ2(0)
#define LED2 S5PV210_GPJ2(1)
#define LED3 S5PV210_GPJ2(2)
#define LED4 S5PV210_GPJ2(3)
#define LED_ON 0
#define LED_OFF 1

static dev_t dev_no;
static int major;
static int minor;
static struct cdev my_cdev;
static char msg[] = "LED! from the LED driver.";

static int my_open(struct inode * inodep, struct file * fp) {
    printk("Device " DEVICE_NAME " open.\n");
    return 0;
}

static ssize_t my_write(struct file *fp, const char __user *buf, size_t intended, loff_t * offset) {
    char kbuf[10];
    int ret;
    ret = copy_from_user(kbuf, buf, 1);
    if (ret) {
        printk("Fail to copy data from the user space to the kernel space!\n");
        return -1;
    }
    if (kbuf[0] != '0') {
        gpio_set_value(LED1, LED_ON);
        gpio_set_value(LED2, LED_ON);
        gpio_set_value(LED3, LED_ON);
        gpio_set_value(LED4, LED_ON);
    } 
    else {
        gpio_set_value(LED1, LED_OFF);
        gpio_set_value(LED2, LED_OFF);
        gpio_set_value(LED3, LED_OFF);
        gpio_set_value(LED4, LED_OFF);
    }
    return 1;
}

static ssize_t my_read(struct file *fp, char __user *buf, size_t intended, loff_t * offset) {
    int num, ret;
    if (intended < strlen(msg))
        num = intended;
    else
        num = strlen(msg);
    ret = copy_to_user(buf, msg, num);
    if (ret) {
        printk("Fail to copy data from the kernel space to the user space!\n");
        return -1;
    }
    return num;
}

static int my_release(struct inode * inodep, struct file * fp) {
    printk("Device " DEVICE_NAME " close.\n");
    return 0;
}

static struct file_operations fop = {
    .owner = THIS_MODULE,
    .read = my_read,
    .write = my_write,
    .open = my_open,
    .release = my_release
};

static int __init my_init(void) {
    int ret;
    ret = alloc_chrdev_region(&dev_no, S_N, N_D, DEVICE_NAME);
    if (ret < 0) {
        printk("Device " DEVICE_NAME " cannot get major number.\n");
        return ret;
    }
    major = MAJOR(dev_no);
    minor = MINOR(dev_no);
    printk("Device " DEVICE_NAME " inistialized with major = %d, minor_start = %d.\n", major, minor);

    cdev_init(&my_cdev, &fop);
    my_cdev.owner = THIS_MODULE;
    my_cdev.dev = dev_no;
    my_cdev.count = N_D;

    ret = cdev_add(&my_cdev, dev_no, N_D);
    if (ret) {
        printk("Device " DEVICE_NAME " register fail.\n");
        return -1;
    }
    return 0;
}

static void __exit my_exit(void) {
    cdev_del(&my_cdev);
    unregister_chrdev_region(dev_no, N_D);
    printk("Device " DEVICE_NAME " unloaded.\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("24104918d");
MODULE_DESCRIPTION("LED device driver");