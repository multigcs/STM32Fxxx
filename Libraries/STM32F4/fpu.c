
#include <stm32f4xx_conf.h>
#include <fpu.h>

void fpuInit(void) {
	FPU->FPCCR &= ~FPU_FPCCR_ASPEN_Msk;			    // turn off FP context save
	FPU->FPCCR &= ~FPU_FPCCR_LSPEN_Msk;			    // turn off lazy save
#ifdef FPU_LAZY_SWITCH
	SCB->SHCSR |= SCB_SHCSR_USGFAULTENA_Msk;		    // turn on usage fault interrupt
	CoreDebug->DEMCR &= ~ CoreDebug_DEMCR_VC_NOCPERR_Msk;   // disable debug halt on UsageFault caused by an access to the FPU Coprocessor
	__fpu_disable();					    // disable FPU access
#endif
}

