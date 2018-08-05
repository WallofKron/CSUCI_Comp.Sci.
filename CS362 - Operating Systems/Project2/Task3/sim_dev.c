#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/version.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#include "sim_dev.h"

// arbitrary number
#define SIM_DEV_MAJOR 567
#define SIM_DEV_NAME "sim_dev"

// this space holds the data that device users send to the device
static char *storage = NULL;
#define STORAGE_SIZE 4096

static unsigned long ioctl_control_data;
static unsigned long ioctl_status_data = 0xAABBCCDD;

// open function - called when the "file" /dev/sim_dev is opened in userspace
static int sim_dev_open (struct inode *inode, struct file *file)
{
   // this is a special print functions that allows a user to print from the kernel
	printk("sim_dev_open\n");
	return 0;
}

// close function - called when the "file" /dev/sim_dev is closed in userspace  
static int sim_dev_release (struct inode *inode, struct file *file)
{
	printk("sim_dev_release\n");
	return 0;
}

// read function called when  /dev/sim_dev is read
static ssize_t sim_dev_read( struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
   if (count > STORAGE_SIZE)
       return -EFAULT;

   // a special copy function that allows to copy from kernel space to user space
   if(copy_to_user(buf, storage, count) != 0)
      return -EFAULT;

   return count;
}

// write function called when /dev/sim_dev is written to
static ssize_t sim_dev_write( struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
   if (count > STORAGE_SIZE)
       return -EFAULT;
       
	if (copy_from_user(storage, buf, count) != 0)
		return -EFAULT;

	return count;
}

// ioctl function called when /dev/sim_dev receives an ioctl command
// Ubuntu 10.10: static int sim_dev_ioctl(struct inode *inode, struct file *file, unsigned int command, unsigned long arg)
// Ubuntu 11.04:
static long sim_dev_unlocked_ioctl(struct file *file, unsigned int command, unsigned long arg)
{
	switch ( command )
	{
		case IOCTL_SIM_DEV_WRITE:/* for writing data to arg */
			if (copy_from_user(&ioctl_control_data, (int *)arg, sizeof(int)))
				printk("writing data\n");
			   return -EFAULT;
			break;
			
		case IOCTL_SIM_DEV_READ:/* for reading data from arg */
			if (copy_to_user((int *)arg, &ioctl_status_data, sizeof(int)))
			  	printk("reading data\n");
				 return -EFAULT;
			break;
			
		default:
			return -EINVAL;
	}
	return -EINVAL;
}

//
// mapping of file operations to the driver functions
//
struct file_operations sim_dev_file_operations = {
	.owner	=	THIS_MODULE,
	.llseek	=	NULL,
	.read		=	sim_dev_read,
	.write	=	sim_dev_write,
//	.readdir	=	NULL, // Ubuntu 14.04
	.poll		=	NULL,
//	.ioctl	=	sim_dev_ioctl, // Ubuntu 10.10
	.unlocked_ioctl	=	sim_dev_unlocked_ioctl, // Ubuntu 11.04
	.mmap		=	NULL,
	.open		=	sim_dev_open,
	.flush	=	NULL,
	.release	=	sim_dev_release,
	.fsync	=	NULL,
	.fasync	=	NULL,
	.lock		=	NULL,
};

// Loads a module in the kernel
static int sim_dev_init_module (void)
{
   // here we register sim_dev as a character device
	if (register_chrdev(SIM_DEV_MAJOR, SIM_DEV_NAME, &sim_dev_file_operations) != 0)
	   return -EIO;

	// reserve memory with kmalloc - Allocating Memory in the Kernel
	// GFP_KERNEL --> this does not have to be atomic, so kernel can sleep
	storage = kmalloc(STORAGE_SIZE, GFP_KERNEL);
	if (!storage) {
		printk("kmalloc failed\n");
		return -1;
	}
   printk("Simulated Driver Module Installed\n");
   return 0;
}

//  Removes module from kernel
static void sim_dev_cleanup_module(void)
{
   // specialized function to free memeory in kernel
	kfree(storage);
	unregister_chrdev (SIM_DEV_MAJOR, SIM_DEV_NAME);
   printk("Simulated Driver Module Uninstalled\n");
}

// map the module initialization and cleanup functins
module_init(sim_dev_init_module);
module_exit(sim_dev_cleanup_module);

MODULE_AUTHOR("http://www.cs.csuci.edu/~ajbieszczad");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simulated Device Linux Device Driver");

