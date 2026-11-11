#include <linux/module.h>
#include <linux/init.h>
#include <linux/kdev_t.h>
#include <linux/printk.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/string.h>
#include <asm-generic/uaccess.h>

#define S_N 0
#define N_D 1
#define DEVICE_NAME "Hello World device"

static dev_t dev_no;
static int major;
static int minor;
static struct cdev my_cdev;
static char msg[] = "Hello world! from the hw driver.";

static int my_open(struct inode * inodep, struct file * fp) {
    printk("Device " DEVICE_NAME " open.\n");
    return 0;
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

    cdev_init(&my_cdev, &fop); // Initialize cdev, bind fop to it
    my_cdev.owner = THIS_MODULE;
    my_cdev.dev = dev_no;
    my_cdev.count = N_D;

    ret = cdev_add(&my_cdev, dev_no, N_D); // Register my_cdev with the kernel, the device number (major, minor) can be routed to the functions in fop.  
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
MODULE_DESCRIPTION("Hello World character device driver");