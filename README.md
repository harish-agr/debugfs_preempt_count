Experimental Linux Kernel Module

## USAGE

```
# echo $$ > /sys/kernel/debug/preempt_count
# tail -1 /var/log/messages
Apr 13 08:58:36 vagrant-centos65 kernel: [bash] preempt_count  0
```

```
# echo 1 > /sys/kernel/debug/preempt_count 
# tail -1 /var/log/messages
Apr 13 10:17:14 vagrant-centos65 kernel: [init] preempt_count 0
```
