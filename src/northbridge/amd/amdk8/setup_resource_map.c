#define RES_DEBUG 0

#define RES_PCI_IO 0x10
#define RES_PORT_IO_8 0x22 
#define RES_PORT_IO_32 0x20
#define RES_MEM_IO 0x30

static void setup_resource_map_x(const unsigned int *register_values, int max)
{
	int i;

#if RES_DEBUG
	print_debug("setting up resource map ex....");

#endif

#if RES_DEBUG
	print_debug("\r\n");
#endif
	for(i = 0; i < max; i += 4) {
#if RES_DEBUG
	#if CONFIG_USE_INIT
                printk_debug("%04x: %02x %08x <- & %08x | %08x\r\n", 
			i/4, register_values[i],register_values[i+1], register_values[i+2], register_values[i+3]);
	#else		
                print_debug_hex16(i/4);
                print_debug(": ");
                print_debug_hex8(register_values[i]);
                print_debug(" ");
                print_debug_hex32(register_values[i+1]);
                print_debug(" <- & ");
                print_debug_hex32(register_values[i+2]);
                print_debug(" | ");
                print_debug_hex32(register_values[i+3]);
                print_debug("\r\n");
	#endif
#endif
		switch (register_values[i]) {
		case RES_PCI_IO: //PCI 
			{
			device_t dev;
			unsigned where;
			unsigned long reg;
			dev = register_values[i+1] & ~0xff;
			where = register_values[i+1] & 0xff;
			reg = pci_read_config32(dev, where);
			reg &= register_values[i+2];
			reg |= register_values[i+3];
			pci_write_config32(dev, where, reg);
			}
			break;
		case RES_PORT_IO_8: // io 8
			{
			unsigned where;
			unsigned reg;
			where = register_values[i+1];
			reg = inb(where);
			reg &= register_values[i+2];
			reg |= register_values[i+3];
			outb(reg, where);
			}
			break;
		case RES_PORT_IO_32:  //io32
			{
			unsigned where;
			unsigned long reg;
			where = register_values[i+1];
			reg = inl(where);
			reg &= register_values[i+2];
			reg |= register_values[i+3];
			outl(reg, where);
			}
			break;
#if 0
		case RES_MEM_IO: //mem 
			{
			unsigned where;
			unsigned long reg;
			where = register_values[i+1];
			reg = read32(where);
			reg &= register_values[i+2];
			reg |= register_values[i+3];
			write32( where, reg);
			}
			break;
#endif
		
		} // switch
			
			
	}

#if RES_DEBUG
	print_debug("done.\r\n");
#endif
}


static void setup_iob_resource_map(const unsigned int *register_values, int max)
{
        int i;
        
	for(i = 0; i < max; i += 3) {
                unsigned where;
		unsigned reg;
                
		where = register_values[i];
#if 0
                udelay(2000);
                print_debug_hex16(where);
#endif
                reg = inb(where);
#if 0
                print_debug("=");
                print_debug_hex8(reg);
#endif

                reg &= register_values[i+1];
                reg |= register_values[i+2];
#if 0
                print_debug(" <-  ");
                print_debug_hex8(reg);
#endif
                outb(reg, where);
#if 0

                print_debug(" -> ");
		reg = inb(where);
                print_debug_hex8(reg);
		print_debug("\r\n");
#endif
        }
}

static void setup_io_resource_map(const unsigned int *register_values, int max)
{
        int i;
        
	for(i = 0; i < max; i += 3) {
                unsigned where;
		unsigned long reg;
                
		where = register_values[i];
#if 0
                udelay(2000);
                print_debug_hex16(where);
#endif

                reg = inl(where);
#if 0
		udelay(2000);
                print_debug("=");
                print_debug_hex32(reg);
#endif
                reg &= register_values[i+1];
                reg |= register_values[i+2];

#if 0
		udelay(2000);
                print_debug(" <-  ");
                print_debug_hex32(reg);
#endif
                outl(reg, where);
#if 0
		udelay(2000);
                print_debug(" -> ");
                reg = inl(where);
                print_debug_hex32(reg);
		print_debug("\r\n");
#endif
        }
}

#if 0
static void setup_mem_resource_map(const unsigned int *register_values, int max)
{
        int i;
        
	for(i = 0; i < max; i += 3) {
                unsigned where;
		unsigned long reg;
#if 0
                print_debug_hex32(register_values[i]);
                print_debug(" <-");
                print_debug_hex32(register_values[i+2]);
#endif
                where = register_values[i];
                reg = read32(where);
                reg &= register_values[i+1];
                reg |= register_values[i+2];
                write32( where, reg);
#if 0
                print_debug(" RB ");
                reg = read32(where);
                print_debug_hex32(reg);
                print_debug("\r\n");
#endif
        }
}
#endif

