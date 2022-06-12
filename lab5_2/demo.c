#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#define MAJOR_NUM 60
#define MODULE_NAME "demo"

static int iCount = 0;

static ssize_t drv_read(struct file *filp, char *buf, size_t count, loff_t *ppos) {
	printk("Enter Read function\n");
	printk("W_buf_size: %d\n", (int) count);

	char *userChar = "";
	copy_from_user(userChar, buf, count);
	userChar[count - 1] = 0;
	printk("userChar(chr): %s\n", userChar);
	char gpio[10] = {0};
	strncpy(gpio, userChar, 3);
	printk("gpio: %s, length: %d\n", gpio, strlen(gpio));
	struct file *io;
	loff_t pos = 0;
	mm_segment_t old_fs;
	old_fs = get_fs();
	set_fs(get_ds());
	io = filp_open("/sys/class/gpio/export", O_WRONLY, 0);
	vfs_write(io, gpio, strlen(gpio), &pos);
	filp_close(io, NULL);

	pos = 0;
	char val[50];
	strcpy(val, "/sys/class/gpio/gpio");
	strcat(val, gpio);
	strcat(val, "/value");
	io = filp_open(val, O_RDONLY, 0);
	vfs_read(io, userChar, count, &pos);
	copy_to_user(buf, userChar + *ppos, count);
	filp_close(io, NULL);
	return count;
}
static ssize_t drv_write(struct file *flip, const char *buf, size_t count, loff_t *ppos){
	printk("Enter Write function\n");
	printk("%d\n", iCount);
	printk("W_buf_size: %d\n", (int)count);
	char *userChar = "";
 	char dest[50], dir[50], val[50];
	copy_from_user(userChar, buf, count);
	userChar[count - 1] = '\0';
	printk("userChar(chr): %s\n", userChar);
	//printk("userChar(int): %d\n", (int)sizeof(userChar));
	char gpio[10] = {0};
	strncpy(gpio, userChar, 3);
	printk("gpio: %s, length: %d\n", gpio, strlen(gpio));
	struct file *io;
	loff_t pos = 0;
	mm_segment_t old_fs;
	old_fs = get_fs();
	set_fs(get_ds());

	//export
	io = filp_open("/sys/class/gpio/export", O_WRONLY, 0);
	vfs_write(io, gpio, strlen(gpio), &pos);
	filp_close(io, NULL);

	//set-dir
	strcpy(dest, "/sys/class/gpio/gpio");
	strcat(dest, gpio);
	strcpy(dir, dest);
	strcat(dir, "/direction");
	strcpy(val, dest);
	strcat(val, "/value");
	io = filp_open(dir, O_WRONLY, 0);
	vfs_write(io, "out", 3, &pos);
	filp_close(io, NULL);
	pos = 0;



	//set-value
	io = filp_open(val, O_WRONLY, 0);
	vfs_write(io, &userChar[count - 2], 1, &pos);
	filp_close(io, NULL);
	pos = 0;
	
	set_fs(old_fs);
	iCount++;
	return count;
}

long drv_ioctl(struct file *filp, unsigned int cmd, unsigned long arg){
	printk("Enter I/O Control function\n");
	return 0;	
}

static int drv_open(struct inode *inode, struct file *filp){
	printk("Enter Open function\n");
	return 0;
}

static int drv_release(struct inode *inode, struct file *filp){
	printk("Enter Release function\n");
	return 0;
}

struct file_operations drv_fops = {
	read: drv_read,
	write: drv_write,
	unlocked_ioctl: drv_ioctl,
	open: drv_open,
	release: drv_release
};

static int demo_init(void){
	if(register_chrdev(MAJOR_NUM, "demo", &drv_fops) < 0){
		printk("<1>%s: can't get major %d\n", MODULE_NAME, MAJOR_NUM);
		return(-EBUSY);
	}
	printk("<1>%s: started\n", MODULE_NAME);
	return 0;
}

static void demo_exit(void){
	unregister_chrdev(MAJOR_NUM, "demo");
	printk("<1>%s: removed\n", MODULE_NAME);
}


module_init(demo_init);
module_exit(demo_exit);
MODULE_LICENSE("GPL");



