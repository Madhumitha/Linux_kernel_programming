cmd_/home/admin/Linux_kernel_programming/7_BMP280/modules.order := {   echo /home/admin/Linux_kernel_programming/7_BMP280/bme280.ko; :; } | awk '!x[$$0]++' - > /home/admin/Linux_kernel_programming/7_BMP280/modules.order
