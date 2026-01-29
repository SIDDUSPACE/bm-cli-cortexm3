.syntax unified
.cpu cortex-m3
.thumb

.global Reset_Handler
.global _isr_vector

.section .isr_vector, "a", %progbits
_isr_vector:
    .word _estack
    .word Reset_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word 0
    .word 0
    .word 0
    .word 0
    .word Default_Handler
    .word Default_Handler
    .word 0
    .word Default_Handler
    .word SysTick_Handler
    .word USART1_IRQHandler  

.section .text
Reset_Handler:
    bl main
    b .

.section .text.Default_Handler, "ax"
.global Default_Handler
Default_Handler:
    b .

.weak SysTick_Handler
SysTick_Handler = Default_Handler
