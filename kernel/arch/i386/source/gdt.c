#include <gdt.h>

static struct __global_descriptor_table gdt;

void init_segment_desc(uint32_t base_addr,
                       uint32_t seg_limit,
                       uint8_t access,
                       uint8_t flags,
                       struct __segment_descriptor *seg_desc)
{
    if (seg_limit > 0xfffff)
    {
        kpanic("Segment limit larger than 0xFFFFF");
    }

    seg_desc->limit_lo = (seg_limit & 0xffff);
    seg_desc->base_lo = (base_addr & 0xffff);
    seg_desc->base_hi = (base_addr & 0xff0000) >> 16;
    seg_desc->access = access;
    seg_desc->limit_hi = (seg_limit & 0xf0000) >> 16;
    seg_desc->flags = (flags & 0xf);
    seg_desc->base_vhi = (base_addr & 0xff000000) >> 24;
}

void init_segments(void)
{
    // Initialize Null Segment
    init_segment_desc(NULL, NULL, NULL, NULL, &gdt.null);

    // Initialize Kernel Code Segment
    init_segment_desc(SEG_BASE_ADDR, SEG_LIMIT_CS,
                      (ACS_PRESENT | ACS_R0 | ACS_SEG | ACS_X | ACS_RW),
                      (FLG_GB | FLG_SB),
                      &gdt.k_cs);

    // Initialize Kernel Data Segment
    init_segment_desc(SEG_BASE_ADDR, SEG_LIMIT_DS,
                      (ACS_PRESENT | ACS_R0 | ACS_SEG | ACS_RW),
                      (FLG_GB | FLG_SB),
                      &gdt.k_ds);

    // Initialize Kernel Stack Segment
    init_segment_desc(SEG_BASE_ADDR, SEG_LIMIT_SS,
                      (ACS_PRESENT | ACS_R0 | ACS_SEG | ACS_DIRECTION | ACS_RW),
                      (FLG_GB | FLG_SB),
                      &gdt.k_ss);

    // Initialize User Code Segment
    init_segment_desc(SEG_BASE_ADDR, SEG_LIMIT_CS,
                      (ACS_PRESENT | ACS_R3 | ACS_SEG | ACS_X | ACS_RW),
                      (FLG_GB | FLG_SB),
                      &gdt.u_cs);

    // Initialize User Data Segment
    init_segment_desc(SEG_BASE_ADDR, SEG_LIMIT_DS,
                      (ACS_PRESENT | ACS_R3 | ACS_SEG | ACS_RW),
                      (FLG_GB | FLG_SB),
                      &gdt.u_ds);

    // Initialize User Stack Segment
    init_segment_desc(SEG_BASE_ADDR, SEG_LIMIT_SS,
                      (ACS_PRESENT | ACS_R3 | ACS_SEG | ACS_DIRECTION | ACS_RW),
                      (FLG_GB | FLG_SB),
                      &gdt.u_ss);

    // TODO Initialize Multitasking Task State Segment
    init_segment_desc((uint32_t)&gdt.m_tss, sizeof &gdt.m_tss,
                      (ACS_PRESENT),
                      (NULL),
                      &gdt.m_tss);

    // TODO Initialize Double Fault Handling Task State Segment
    init_segment_desc((uint32_t)&gdt.m_tss, sizeof &gdt.m_tss,
                      (ACS_PRESENT),
                      (NULL),
                      &gdt.m_tss);
}

//* Construct the GDT
void __gdt_init(void)
{
    struct __gdt_r *gdtr = &gdt.gdtr;

    init_segments();

    gdtr->base = GDT_BASE;
    gdtr->size = sizeof gdt;

    // Copy GDT to GDT Base Address
    kmemcpy((char *)gdtr->base, (char *)&gdt, sizeof gdt);

    // Load GDT Registry
    asm volatile("lgdt (%0)"
                 :
                 : "p"(gdtr));

    // Switch to long mode
    asm volatile(".intel_syntax noprefix;"
                 "mov eax, cr0;"
                 "or eax, 1;"
                 "mov cr0, eax;"
                 ".att_syntax;");

    // Reload CS register
    asm volatile(".intel_syntax noprefix;"
                 "push 0x08;"
                 "lea eax, [res_eip];"
                 "push eax;"
                 "retf;"
                 "res_eip:;"
                 ".att_syntax;");

    //! Load segment addresses into segment registers
    asm volatile(".intel_syntax noprefix;"
                 "mov ax, 0x10;"
                 "mov ds, ax;"
                 "mov es, ax;"
                 "mov ss, ax;"
                 "mov fs, ax;"
                 "mov gs, ax;"
                 ".att_syntax;");
}

// TODO Deconstruct the GDT
void __gdt_destroy(void)
{
}

//* Get Kernel Segment Offsets from GDT Base
uint16_t __get_k_cs_offset(void)
{
    return (uint8_t *)&gdt.k_cs - (uint8_t *)&gdt;
}

uint16_t __get_k_ds_offset(void)
{
    return (uint8_t *)&gdt.k_ds - (uint8_t *)&gdt;
}

uint16_t __get_k_ss_offset(void)
{
    return (uint8_t *)&gdt.k_ss - (uint8_t *)&gdt;
}

//* Get User Segment Offsets from GDT Base
uint16_t __get_u_cs_offset(void)
{
    return (uint8_t *)&gdt.u_cs - (uint8_t *)&gdt;
}

uint16_t __get_u_ds_offset(void)
{
    return (uint8_t *)&gdt.u_ds - (uint8_t *)&gdt;
}

uint16_t __get_u_ss_offset(void)
{
    return (uint8_t *)&gdt.u_ss - (uint8_t *)&gdt;
}