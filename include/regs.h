#ifndef REGS_H
#define REGS_H

#define SYST_CSR   (*(volatile unsigned int *)0xE000E010)
#define SYST_RVR   (*(volatile unsigned int *)0xE000E014)
#define SYST_CVR   (*(volatile unsigned int *)0xE000E018)

#define SYST_CSR_ENABLE     (1 << 0)
#define SYST_CSR_TICKINT    (1 << 1)
#define SYST_CSR_CLKSOURCE  (1 << 2)

#endif
