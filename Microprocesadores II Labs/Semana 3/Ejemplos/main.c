#include <stdint.h>

#define RCC_BASE   0x40021000UL
#define FLASH_BASE 0x40022000UL
#define RCC_CR     (*((volatile uint32_t *)(RCC_BASE + 0x00UL)))
#define RCC_CFGR   (*((volatile uint32_t *)(RCC_BASE + 0x04UL)))
#define FLASH_ACR  (*((volatile uint32_t *)(FLASH_BASE + 0x00UL)))

volatile uint32_t con_valor = 5u;
volatile uint32_t desde_cero;
volatile uint32_t cr_observado;
volatile uint32_t cfgr_observado;
volatile uint32_t acr_observado;
volatile uint32_t fuente_sysclk;
volatile uint32_t codigo_ahb;
volatile uint32_t codigo_apb1;
volatile uint32_t codigo_apb2;
volatile uint32_t entrada_pll;
volatile uint32_t division_hse_pll;
volatile uint32_t codigo_pll;
volatile uint32_t latencia_flash;

int main(void)
{
    /* Primera sentencia: detenerse aqui para observar .data y .bss. */
    cr_observado = RCC_CR;
    cfgr_observado = RCC_CFGR;
    acr_observado = FLASH_ACR;

    /* Se extraen codigos. Los divisores se consultan en RM0008. */
    fuente_sysclk = (cfgr_observado >> 2u) & 3u;
    codigo_ahb = (cfgr_observado >> 4u) & 15u;
    codigo_apb1 = (cfgr_observado >> 8u) & 7u;
    codigo_apb2 = (cfgr_observado >> 11u) & 7u;
    entrada_pll = (cfgr_observado >> 16u) & 1u;
    division_hse_pll = (cfgr_observado >> 17u) & 1u;
    codigo_pll = (cfgr_observado >> 18u) & 15u;
    latencia_flash = acr_observado & 7u;

    /* Avanzar paso a paso. Esto no es un temporizador calibrado. */
    while (1) {
        con_valor++;
        desde_cero++;
    }
}
