cmd_/home/admin/Linux_kernel_programming/10_spi_bme280/Module.symvers := sed 's/\.ko$$/\.o/' /home/admin/Linux_kernel_programming/10_spi_bme280/modules.order | scripts/mod/modpost -m -a  -o /home/admin/Linux_kernel_programming/10_spi_bme280/Module.symvers -e -i Module.symvers   -T -