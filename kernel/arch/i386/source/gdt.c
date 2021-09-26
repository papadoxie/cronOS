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

void gdt_init(GlobalDescriptorTable *gdt)
{
    init_segment_desc(NULL, NULL, NULL, NULL, &gdt->null);

    //* Initialize Kernel Code Segment
    init_segment_desc(BASE_ADDR, SEG_LIMIT_CS,
                      (ACS_PRESENT | ACS_R0 | ACS_SEG | ACS_X | ACS_RW | ACS_ACCESS),
                      (FLG_GB | FLG_SB),
                      &gdt->k_cs);

    //* Initialize Kernel Data Segment
    init_segment_desc(BASE_ADDR, SEG_LIMIT_DS,
                      (ACS_PRESENT | ACS_R0 | ACS_SEG | ACS_RW | ACS_ACCESS),
                      (FLG_GB | FLG_SB),
                      &gdt->k_ds);

    //* Initialize Kernel Stack Segment
    init_segment_desc(BASE_ADDR, SEG_LIMIT_SS,
                      (ACS_PRESENT | ACS_R0 | ACS_SEG | ACS_DIRECTION | ACS_RW | ACS_ACCESS),
                      (FLG_GB | FLG_SB),
                      &gdt->k_ss);

    //* Initialize User Code Segment
    init_segment_desc(BASE_ADDR, SEG_LIMIT_CS,
                      (ACS_PRESENT | ACS_R3 | ACS_SEG | ACS_X | ACS_RW | ACS_ACCESS),
                      (FLG_GB | FLG_SB),
                      &gdt->u_cs);

    //* Initialize User Data Segment
    init_segment_desc(BASE_ADDR, SEG_LIMIT_DS,
                      (ACS_PRESENT | ACS_R3 | ACS_SEG | ACS_RW | ACS_ACCESS),
                      (FLG_GB | FLG_SB),
                      &gdt->u_ds);

    //* Initialize User Stack Segment
    init_segment_desc(BASE_ADDR, SEG_LIMIT_SS,
                      (ACS_PRESENT | ACS_R3 | ACS_SEG | ACS_DIRECTION | ACS_RW | ACS_ACCESS),
                      (FLG_GB | FLG_SB),
                      &gdt->u_ss);
}