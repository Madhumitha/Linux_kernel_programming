cmd_/home/admin/Linux_kernel_programming/06_pwm_driver/Module.symvers := sed 's/\.ko$$/\.o/' /home/admin/Linux_kernel_programming/06_pwm_driver/modules.order | scripts/mod/modpost -m -a  -o /home/admin/Linux_kernel_programming/06_pwm_driver/Module.symvers -e -i Module.symvers   -T -
