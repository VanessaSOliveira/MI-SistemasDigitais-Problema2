/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'nios2_qsys_0' in SOPC Builder design 'ProjetoSemInstruction'
 * SOPC Builder design path: ../../ProjetoSemInstruction.sopcinfo
 *
 * Generated: Mon Nov 19 14:23:24 BRST 2018
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_qsys"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x00020820
#define ALT_CPU_CPU_FREQ 50000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "tiny"
#define ALT_CPU_DATA_ADDR_WIDTH 0x12
#define ALT_CPU_DCACHE_LINE_SIZE 0
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_DCACHE_SIZE 0
#define ALT_CPU_EXCEPTION_ADDR 0x00010020
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 50000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 0
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 0
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_ICACHE_SIZE 0
#define ALT_CPU_INST_ADDR_WIDTH 0x12
#define ALT_CPU_NAME "nios2_qsys_0"
#define ALT_CPU_RESET_ADDR 0x00010000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x00020820
#define NIOS2_CPU_FREQ 50000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "tiny"
#define NIOS2_DATA_ADDR_WIDTH 0x12
#define NIOS2_DCACHE_LINE_SIZE 0
#define NIOS2_DCACHE_LINE_SIZE_LOG2 0
#define NIOS2_DCACHE_SIZE 0
#define NIOS2_EXCEPTION_ADDR 0x00010020
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 0
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 0
#define NIOS2_ICACHE_LINE_SIZE_LOG2 0
#define NIOS2_ICACHE_SIZE 0
#define NIOS2_INST_ADDR_WIDTH 0x12
#define NIOS2_RESET_ADDR 0x00010000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_LCD_16207
#define __ALTERA_AVALON_ONCHIP_MEMORY2
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_UART
#define __ALTERA_NIOS2_QSYS


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "Cyclone IV E"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/jtag_uart_0"
#define ALT_STDERR_BASE 0x210c8
#define ALT_STDERR_DEV jtag_uart_0
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtag_uart_0"
#define ALT_STDIN_BASE 0x210c8
#define ALT_STDIN_DEV jtag_uart_0
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtag_uart_0"
#define ALT_STDOUT_BASE 0x210c8
#define ALT_STDOUT_DEV jtag_uart_0
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "ProjetoSemInstruction"


/*
 * botaoDescer configuration
 *
 */

#define ALT_MODULE_CLASS_botaoDescer altera_avalon_pio
#define BOTAODESCER_BASE 0x21050
#define BOTAODESCER_BIT_CLEARING_EDGE_REGISTER 0
#define BOTAODESCER_BIT_MODIFYING_OUTPUT_REGISTER 0
#define BOTAODESCER_CAPTURE 0
#define BOTAODESCER_DATA_WIDTH 1
#define BOTAODESCER_DO_TEST_BENCH_WIRING 0
#define BOTAODESCER_DRIVEN_SIM_VALUE 0
#define BOTAODESCER_EDGE_TYPE "NONE"
#define BOTAODESCER_FREQ 50000000
#define BOTAODESCER_HAS_IN 1
#define BOTAODESCER_HAS_OUT 0
#define BOTAODESCER_HAS_TRI 0
#define BOTAODESCER_IRQ -1
#define BOTAODESCER_IRQ_INTERRUPT_CONTROLLER_ID -1
#define BOTAODESCER_IRQ_TYPE "NONE"
#define BOTAODESCER_NAME "/dev/botaoDescer"
#define BOTAODESCER_RESET_VALUE 0
#define BOTAODESCER_SPAN 16
#define BOTAODESCER_TYPE "altera_avalon_pio"


/*
 * botaoEntrar configuration
 *
 */

#define ALT_MODULE_CLASS_botaoEntrar altera_avalon_pio
#define BOTAOENTRAR_BASE 0x21060
#define BOTAOENTRAR_BIT_CLEARING_EDGE_REGISTER 0
#define BOTAOENTRAR_BIT_MODIFYING_OUTPUT_REGISTER 0
#define BOTAOENTRAR_CAPTURE 0
#define BOTAOENTRAR_DATA_WIDTH 1
#define BOTAOENTRAR_DO_TEST_BENCH_WIRING 0
#define BOTAOENTRAR_DRIVEN_SIM_VALUE 0
#define BOTAOENTRAR_EDGE_TYPE "NONE"
#define BOTAOENTRAR_FREQ 50000000
#define BOTAOENTRAR_HAS_IN 1
#define BOTAOENTRAR_HAS_OUT 0
#define BOTAOENTRAR_HAS_TRI 0
#define BOTAOENTRAR_IRQ -1
#define BOTAOENTRAR_IRQ_INTERRUPT_CONTROLLER_ID -1
#define BOTAOENTRAR_IRQ_TYPE "NONE"
#define BOTAOENTRAR_NAME "/dev/botaoEntrar"
#define BOTAOENTRAR_RESET_VALUE 0
#define BOTAOENTRAR_SPAN 16
#define BOTAOENTRAR_TYPE "altera_avalon_pio"


/*
 * botaoSubir configuration
 *
 */

#define ALT_MODULE_CLASS_botaoSubir altera_avalon_pio
#define BOTAOSUBIR_BASE 0x21040
#define BOTAOSUBIR_BIT_CLEARING_EDGE_REGISTER 0
#define BOTAOSUBIR_BIT_MODIFYING_OUTPUT_REGISTER 0
#define BOTAOSUBIR_CAPTURE 0
#define BOTAOSUBIR_DATA_WIDTH 1
#define BOTAOSUBIR_DO_TEST_BENCH_WIRING 0
#define BOTAOSUBIR_DRIVEN_SIM_VALUE 0
#define BOTAOSUBIR_EDGE_TYPE "NONE"
#define BOTAOSUBIR_FREQ 50000000
#define BOTAOSUBIR_HAS_IN 1
#define BOTAOSUBIR_HAS_OUT 0
#define BOTAOSUBIR_HAS_TRI 0
#define BOTAOSUBIR_IRQ -1
#define BOTAOSUBIR_IRQ_INTERRUPT_CONTROLLER_ID -1
#define BOTAOSUBIR_IRQ_TYPE "NONE"
#define BOTAOSUBIR_NAME "/dev/botaoSubir"
#define BOTAOSUBIR_RESET_VALUE 0
#define BOTAOSUBIR_SPAN 16
#define BOTAOSUBIR_TYPE "altera_avalon_pio"


/*
 * botaoVoltar configuration
 *
 */

#define ALT_MODULE_CLASS_botaoVoltar altera_avalon_pio
#define BOTAOVOLTAR_BASE 0x21070
#define BOTAOVOLTAR_BIT_CLEARING_EDGE_REGISTER 0
#define BOTAOVOLTAR_BIT_MODIFYING_OUTPUT_REGISTER 0
#define BOTAOVOLTAR_CAPTURE 0
#define BOTAOVOLTAR_DATA_WIDTH 1
#define BOTAOVOLTAR_DO_TEST_BENCH_WIRING 0
#define BOTAOVOLTAR_DRIVEN_SIM_VALUE 0
#define BOTAOVOLTAR_EDGE_TYPE "NONE"
#define BOTAOVOLTAR_FREQ 50000000
#define BOTAOVOLTAR_HAS_IN 1
#define BOTAOVOLTAR_HAS_OUT 0
#define BOTAOVOLTAR_HAS_TRI 0
#define BOTAOVOLTAR_IRQ -1
#define BOTAOVOLTAR_IRQ_INTERRUPT_CONTROLLER_ID -1
#define BOTAOVOLTAR_IRQ_TYPE "NONE"
#define BOTAOVOLTAR_NAME "/dev/botaoVoltar"
#define BOTAOVOLTAR_RESET_VALUE 0
#define BOTAOVOLTAR_SPAN 16
#define BOTAOVOLTAR_TYPE "altera_avalon_pio"


/*
 * hal configuration
 *
 */

#define ALT_MAX_FD 4
#define ALT_SYS_CLK none
#define ALT_TIMESTAMP_CLK none


/*
 * jtag_uart_0 configuration
 *
 */

#define ALT_MODULE_CLASS_jtag_uart_0 altera_avalon_jtag_uart
#define JTAG_UART_0_BASE 0x210c8
#define JTAG_UART_0_IRQ 0
#define JTAG_UART_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_0_NAME "/dev/jtag_uart_0"
#define JTAG_UART_0_READ_DEPTH 64
#define JTAG_UART_0_READ_THRESHOLD 8
#define JTAG_UART_0_SPAN 8
#define JTAG_UART_0_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_0_WRITE_DEPTH 64
#define JTAG_UART_0_WRITE_THRESHOLD 8


/*
 * lcd_16207_0 configuration
 *
 */

#define ALT_MODULE_CLASS_lcd_16207_0 altera_avalon_lcd_16207
#define LCD_16207_0_BASE 0x210b0
#define LCD_16207_0_IRQ -1
#define LCD_16207_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LCD_16207_0_NAME "/dev/lcd_16207_0"
#define LCD_16207_0_SPAN 16
#define LCD_16207_0_TYPE "altera_avalon_lcd_16207"


/*
 * ledAzul configuration
 *
 */

#define ALT_MODULE_CLASS_ledAzul altera_avalon_pio
#define LEDAZUL_BASE 0x210a0
#define LEDAZUL_BIT_CLEARING_EDGE_REGISTER 0
#define LEDAZUL_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LEDAZUL_CAPTURE 0
#define LEDAZUL_DATA_WIDTH 1
#define LEDAZUL_DO_TEST_BENCH_WIRING 0
#define LEDAZUL_DRIVEN_SIM_VALUE 0
#define LEDAZUL_EDGE_TYPE "NONE"
#define LEDAZUL_FREQ 50000000
#define LEDAZUL_HAS_IN 0
#define LEDAZUL_HAS_OUT 1
#define LEDAZUL_HAS_TRI 0
#define LEDAZUL_IRQ -1
#define LEDAZUL_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LEDAZUL_IRQ_TYPE "NONE"
#define LEDAZUL_NAME "/dev/ledAzul"
#define LEDAZUL_RESET_VALUE 0
#define LEDAZUL_SPAN 16
#define LEDAZUL_TYPE "altera_avalon_pio"


/*
 * ledVerde configuration
 *
 */

#define ALT_MODULE_CLASS_ledVerde altera_avalon_pio
#define LEDVERDE_BASE 0x21090
#define LEDVERDE_BIT_CLEARING_EDGE_REGISTER 0
#define LEDVERDE_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LEDVERDE_CAPTURE 0
#define LEDVERDE_DATA_WIDTH 1
#define LEDVERDE_DO_TEST_BENCH_WIRING 0
#define LEDVERDE_DRIVEN_SIM_VALUE 0
#define LEDVERDE_EDGE_TYPE "NONE"
#define LEDVERDE_FREQ 50000000
#define LEDVERDE_HAS_IN 0
#define LEDVERDE_HAS_OUT 1
#define LEDVERDE_HAS_TRI 0
#define LEDVERDE_IRQ -1
#define LEDVERDE_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LEDVERDE_IRQ_TYPE "NONE"
#define LEDVERDE_NAME "/dev/ledVerde"
#define LEDVERDE_RESET_VALUE 0
#define LEDVERDE_SPAN 16
#define LEDVERDE_TYPE "altera_avalon_pio"


/*
 * ledVermelho configuration
 *
 */

#define ALT_MODULE_CLASS_ledVermelho altera_avalon_pio
#define LEDVERMELHO_BASE 0x21080
#define LEDVERMELHO_BIT_CLEARING_EDGE_REGISTER 0
#define LEDVERMELHO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LEDVERMELHO_CAPTURE 0
#define LEDVERMELHO_DATA_WIDTH 1
#define LEDVERMELHO_DO_TEST_BENCH_WIRING 0
#define LEDVERMELHO_DRIVEN_SIM_VALUE 0
#define LEDVERMELHO_EDGE_TYPE "NONE"
#define LEDVERMELHO_FREQ 50000000
#define LEDVERMELHO_HAS_IN 0
#define LEDVERMELHO_HAS_OUT 1
#define LEDVERMELHO_HAS_TRI 0
#define LEDVERMELHO_IRQ -1
#define LEDVERMELHO_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LEDVERMELHO_IRQ_TYPE "NONE"
#define LEDVERMELHO_NAME "/dev/ledVermelho"
#define LEDVERMELHO_RESET_VALUE 0
#define LEDVERMELHO_SPAN 16
#define LEDVERMELHO_TYPE "altera_avalon_pio"


/*
 * onchip_memory2_0 configuration
 *
 */

#define ALT_MODULE_CLASS_onchip_memory2_0 altera_avalon_onchip_memory2
#define ONCHIP_MEMORY2_0_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define ONCHIP_MEMORY2_0_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define ONCHIP_MEMORY2_0_BASE 0x10000
#define ONCHIP_MEMORY2_0_CONTENTS_INFO ""
#define ONCHIP_MEMORY2_0_DUAL_PORT 0
#define ONCHIP_MEMORY2_0_GUI_RAM_BLOCK_TYPE "AUTO"
#define ONCHIP_MEMORY2_0_INIT_CONTENTS_FILE "ProjetoSemInstruction_onchip_memory2_0"
#define ONCHIP_MEMORY2_0_INIT_MEM_CONTENT 1
#define ONCHIP_MEMORY2_0_INSTANCE_ID "NONE"
#define ONCHIP_MEMORY2_0_IRQ -1
#define ONCHIP_MEMORY2_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ONCHIP_MEMORY2_0_NAME "/dev/onchip_memory2_0"
#define ONCHIP_MEMORY2_0_NON_DEFAULT_INIT_FILE_ENABLED 0
#define ONCHIP_MEMORY2_0_RAM_BLOCK_TYPE "AUTO"
#define ONCHIP_MEMORY2_0_READ_DURING_WRITE_MODE "DONT_CARE"
#define ONCHIP_MEMORY2_0_SINGLE_CLOCK_OP 0
#define ONCHIP_MEMORY2_0_SIZE_MULTIPLE 1
#define ONCHIP_MEMORY2_0_SIZE_VALUE 40096
#define ONCHIP_MEMORY2_0_SPAN 40096
#define ONCHIP_MEMORY2_0_TYPE "altera_avalon_onchip_memory2"
#define ONCHIP_MEMORY2_0_WRITABLE 1


/*
 * uart_0 configuration
 *
 */

#define ALT_MODULE_CLASS_uart_0 altera_avalon_uart
#define UART_0_BASE 0x21020
#define UART_0_BAUD 115200
#define UART_0_DATA_BITS 8
#define UART_0_FIXED_BAUD 1
#define UART_0_FREQ 50000000
#define UART_0_IRQ 1
#define UART_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define UART_0_NAME "/dev/uart_0"
#define UART_0_PARITY 'N'
#define UART_0_SIM_CHAR_STREAM ""
#define UART_0_SIM_TRUE_BAUD 0
#define UART_0_SPAN 32
#define UART_0_STOP_BITS 1
#define UART_0_SYNC_REG_DEPTH 2
#define UART_0_TYPE "altera_avalon_uart"
#define UART_0_USE_CTS_RTS 0
#define UART_0_USE_EOP_REGISTER 0

#endif /* __SYSTEM_H_ */
