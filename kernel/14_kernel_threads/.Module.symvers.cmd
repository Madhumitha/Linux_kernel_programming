cmd_/home/admin/Linux_kernel_programming/14_kernel_threads/Module.symvers := sed 's/\.ko$$/\.o/' /home/admin/Linux_kernel_programming/14_kernel_threads/modules.order | scripts/mod/modpost -m -a  -o /home/admin/Linux_kernel_programming/14_kernel_threads/Module.symvers -e -i Module.symvers   -T -