cmd_/home/admin/Linux_kernel_programming/8_timer/modules.order := {   echo /home/admin/Linux_kernel_programming/8_timer/mytimer.ko; :; } | awk '!x[$$0]++' - > /home/admin/Linux_kernel_programming/8_timer/modules.order
