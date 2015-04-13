#include <linux/module.h>
#include <linux/debugfs.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <asm-generic/uaccess.h>

MODULE_AUTHOR("ito hiroya");
MODULE_DESCRIPTION("debugfs preempt_count");
MODULE_LICENSE("GPL");

static int file_value;
static struct dentry *dentry_file;

static ssize_t debugfs_show_preempt_count(struct file *file,
		const char __user *buf, size_t count, loff_t *ppos)
{
	char buffer[16];
	pid_t id;
	struct pid *pid;
	struct task_struct *task;

	if (count > sizeof(buffer) -1)
		return -EINVAL;

	if (copy_from_user(buffer, buf, count))
		return -EFAULT;

	buffer[count] = '\0';

	id = simple_strtoul(buffer, NULL, 10);
	if (!id)
		return -EINVAL;

	pid = find_get_pid(id);
	if (!pid)
		return -ESRCH;

	task = get_pid_task(pid, PIDTYPE_PID);
	if (!task) {
		put_pid(pid);
		return -ESRCH;
	}

	printk(KERN_INFO "[%s] pid: %d preempt_count: %d\n",
				task->comm,
				id,
				task_thread_info(task)->preempt_count);

	put_task_struct(task);
	put_pid(pid);

	return count;
}

static struct file_operations fops = {
	.write = debugfs_show_preempt_count,
};

static int __init debugfs_init(void)
{
	dentry_file = debugfs_create_file("preempt_count", 0644, NULL, &file_value, &fops);
	if (!dentry_file) {
		printk(KERN_ERR "Failed to debugfs_create_file: preempt_count");
		return -ENODEV;
	}
		
	return 0;
}

static void __exit debugfs_exit(void)
{
	debugfs_remove(dentry_file);
}

module_init(debugfs_init);
module_exit(debugfs_exit);
