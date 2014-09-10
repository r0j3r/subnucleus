void
multiboot_main(void * boot_info_pa)
{
    boot_info = *(struct multiboot_info *)phystokv(boot_info_pa);

    base_cpu_setup();

    base_fpu_init();

    multiboot_init_mem();

    multiboot_init_cmdline();

    sti();

    console_init();
     
    exit(main);
}
