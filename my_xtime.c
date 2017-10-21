#include <linux/export.h>
#include <linux/linkage.h>
#include <linux/time.h>
#include <linux/printk.h>
#include <linux/slab.h>
#include <asm/uaccess.h>

asmlinkage int sys_my_xtime(struct timespec* current_time) {
//	printk(KERN_ALERT "SYS_MY_XTIME()\n");
	if (likely(current_time != NULL) ) {
		int size = sizeof(*current_time);
		if (access_ok(VERIFY_WRITE, current_time, size)) {
			
			struct timespec cur_kernel_time = current_kernel_time();
			int cp;
			int sizeCKT = sizeof(cur_kernel_time);
			printk(KERN_ALERT "set:\n");
			cp = copy_to_user(current_time, &cur_kernel_time, sizeCKT);
			
			if (cp > 0) {
				return cp;
			}
			printk(KERN_ALERT "tv_sec:%ld\n", current_time->tv_sec);
			printk(KERN_ALERT "tv_nsec:%ld\n", current_time->tv_nsec);
			printk(KERN_ALERT "return\n");
			return 0;
		} else {
			return EFAULT;
		}
	}

	return 0;

}

EXPORT_SYMBOL(sys_my_xtime);
