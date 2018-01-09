extern unsigned long long get_cycles()
{
    long long out;
    asm volatile(
        "CPUID;"   /* serialize instruction execution */
        "RDTSCP;"  /* outputs to EDX:EAX and the (unused) cpuid to ECX*/
        "SHLQ $32,%%rdx;"
        "ORQ %%rdx,%%rax;"
        "MOVQ %%rax,%0;"
        :"=r"(out)
        : /*no input*/
        :"rdx","rax", "rcx"
    );
    return out;
}
