cmd_/home/admin/Linux_kernel_programming/05_lcd_driver/Module.symvers := sed 's/\.ko$$/\.o/' /home/admin/Linux_kernel_programming/05_lcd_driver/modules.order | scripts/mod/modpost -m -a  -o /home/admin/Linux_kernel_programming/05_lcd_driver/Module.symvers -e -i Module.symvers   -T -