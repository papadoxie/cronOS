#include "../include/gdt.h"
#include <string.h>

void init_segment_desc(uint32_t base_addr,
                       uint32_t seg_limit,
                       uint8_t flags,
                       uint8_t flags_extra,
                       struct __segment_descriptor *seg_desc)
{
    seg_desc->limit_lo = (seg_limit & 0xffff);
    seg_desc->base_lo = (base_addr & 0xffff);
    seg_desc->base_hi = (base_addr & 0xff0000) >> 16;
    seg_desc->flags = flags;
    seg_desc->limit_hi = (seg_limit & 0xf0000) >> 16;
    seg_desc->flags_extra = (flags_extra & 0xf);
    seg_desc->base_vhi = (base_addr & 0xff000000) >> 24;
}

void gdt_init(GlobalDescriptorTable *gdt)
{
    init_segment_desc(0x0, 0x0, 0x0, 0x0, &gdt->null);
}