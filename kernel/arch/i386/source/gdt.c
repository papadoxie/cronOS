#include "../include/gdt.h"

void init_segment_desc(uint32_t base_addr,
                       uint32_t seg_limit,
                       uint8_t access,
                       uint8_t flags,
                       struct __segment_descriptor *seg_desc)
{
    seg_desc->limit_lo = (seg_limit & 0xffff);
    seg_desc->base_lo = (base_addr & 0xffff);
    seg_desc->base_hi = (base_addr & 0xff0000) >> 16;
    seg_desc->access = access;
    seg_desc->limit_hi = (seg_limit & 0xf0000) >> 16;
    seg_desc->flags = (flags & 0xf);
    seg_desc->base_vhi = (base_addr & 0xff000000) >> 24;
}

void init_segments(struct __global_descriptor_table *gdt)
{
    // Initialize Null Segment
    init_segment_desc(NULL, NULL, NULL, NULL, &gdt->null);

    // Initialize Kernel Code Segment
    init_segment_desc(SEG_BASE_ADDR, SEG_LIMIT_CS,
                      (ACS_PRESENT | ACS_R0 | ACS_SEG | ACS_X | ACS_RW | ACS_ACCESS),
                      (FLG_GB | FLG_SB),
                      &gdt->k_cs);

    // Initialize Kernel Data Segment
    init_segment_desc(SEG_BASE_ADDR, SEG_LIMIT_DS,
                      (ACS_PRESENT | ACS_R0 | ACS_SEG | ACS_RW | ACS_ACCESS),
                      (FLG_GB | FLG_SB),
                      &gdt->k_ds);

    // Initialize Kernel Stack Segment
    init_segment_desc(SEG_BASE_ADDR, SEG_LIMIT_SS,
                      (ACS_PRESENT | ACS_R0 | ACS_SEG | ACS_DIRECTION | ACS_RW | ACS_ACCESS),
                      (FLG_GB | FLG_SB),
                      &gdt->k_ss);

    // Initialize User Code Segment
    init_segment_desc(SEG_BASE_ADDR, SEG_LIMIT_CS,
                      (ACS_PRESENT | ACS_R3 | ACS_SEG | ACS_X | ACS_RW | ACS_ACCESS),
                      (FLG_GB | FLG_SB),
                      &gdt->u_cs);

    // Initialize User Data Segment
    init_segment_desc(SEG_BASE_ADDR, SEG_LIMIT_DS,
                      (ACS_PRESENT | ACS_R3 | ACS_SEG | ACS_RW | ACS_ACCESS),
                      (FLG_GB | FLG_SB),
                      &gdt->u_ds);

    // Initialize User Stack Segment
    init_segment_desc(SEG_BASE_ADDR, SEG_LIMIT_SS,
                      (ACS_PRESENT | ACS_R3 | ACS_SEG | ACS_DIRECTION | ACS_RW | ACS_ACCESS),
                      (FLG_GB | FLG_SB),
                      &gdt->u_ss);

    //TODO Initialize Multitasking Task State Segment

    //TODO Initialize Double Fault Handling Task State Segment
}

void __gdt_init(struct __global_descriptor_table *gdt)
{
    init_segments(gdt);
    gdt->gdtr.base = GDT_BASE;
    gdt->gdtr.size = sizeof *gdt;

    // Copy GDT to GDT Base Address
    kmemcpy((char *)gdt->gdtr.base, (char *)gdt, gdt->gdtr.size);

    // Load GDT Registry
    asm volatile("lgdt (%0)"
                 :
                 : "p"((uint8_t *)&gdt->gdtr));

    // Load segment addresses into segment registers
    asm volatile("  movw $0x10, %ax         \n \
                    movw %ax, %cs           \n \
                    movw %ax, %ds           \n \
                    movw %ax, %ss           \n \
                    movw %ax, %fs           \n \
                    movw %ax, %gs           \n \
                    ljmp $0x08, $res_eip    \n \
                    res_eip:");

}

// uint16_t __get_cs_offset(struct __global_descriptor_table *gdt)
// {

// }