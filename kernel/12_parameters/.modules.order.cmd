cmd_/home/admin/Linux_kernel_programming/12_parameters/modules.order := {   echo /home/admin/Linux_kernel_programming/12_parameters/my_parameter.ko; :; } | awk '!x[$$0]++' - > /home/admin/Linux_kernel_programming/12_parameters/modules.order