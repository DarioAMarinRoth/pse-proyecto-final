/**********************************************************************
 *
 * twi.h: Interfaz del módulo TWI (I²C).
 *
 **********************************************************************/

#ifndef _TWI_H
#define _TWI_H

#include <stdint.h>

// CONSTANTS
#define F_MASTER 16000000  // FRECUENCIA DEL PROCESADOR: 16 MHz
#define F_I2C 100000       // FRECUENCIA DE COMUNICACIÓN: 100 kHz
#define DEFAULT_SLA 0x10   // DIRECCIÓN DEL ESCLAVO POR DEFECTO

// PRESCALER VALUES
#define PRESCALER_1 ((0 << TWPS1) | (0 << TWPS0))
#define PRESCALER_4 ((0 << TWPS1) | (1 << TWPS0))
#define PRESCALER_16 ((1 << TWPS1) | (0 << TWPS0))
#define PRESCALER_64 ((1 << TWPS1) | (1 << TWPS0))

// SETTINGS
#define SLA_W(address) (address << 1)
#define SLA_R(address) ((address << 1) | (1 << 0))
#define ENABLE_TWI (1 << TWEN)
#define ENABLE_ACK (1 << TWEA)
#define GEN_START (1 << TWSTA)
#define GEN_STOP (1 << TWSTO)
#define CLEAR_INT (1 << TWINT)

// MISC
#define STATUS_REG_MASK 0xF8


/**
 * \brief Inicializa el TWI en modo maestro.
 *
 * Configura el registro de estado TWI con un prescaler de 16,
 * establece el registro de bit rate TWI para la frecuencia de CPU y TWI,
 * y habilita el TWI.
 */
void master_init();

/**
 * \brief Inicializa el TWI en modo esclavo.
 *
 * Configura el registro de dirección TWI con la dirección del esclavo
 * y habilita el TWI y la generación de ACK.
 */
void slave_init();

/**
 * \brief Inicializa el TWI en modo esclavo con una dirección específica.
 *
 * Configura el registro de dirección TWI con la dirección del esclavo
 * proporcionada y habilita el TWI y la generación de ACK.
 *
 * \param[in] sla Dirección del esclavo a configurar.
 */
void sla_slave_init(const uint8_t sla);

/**
 * \brief Genera una condición de inicio en el bus TWI.
 *
 * Configura el registro de control TWI para generar una condición de inicio
 * y espera hasta que la transmisión se complete.
 *
 * \return Código de estado de la operación de inicio.
 */
uint8_t twi_start(void);

/**
 * \brief Genera una condición de parada en el bus TWI.
 *
 * Configura el registro de control TWI para generar una condición de parada.
 */
void twi_stop(void);

/**
 * \brief Transmite un byte de datos en el bus TWI.
 *
 * Configura el registro de datos TWI con el byte a transmitir y espera
 * hasta que la transmisión se complete.
 *
 * \param[in] data Byte de datos a transmitir.
 * \return Código de estado de la operación de transmisión.
 */
uint8_t transmit(const uint8_t data);

/**
 * \brief Envía una señal de reconocimiento (ACK) en el bus TWI.
 *
 * Configura el registro de control TWI para enviar una señal de reconocimiento
 * y espera hasta que la transmisión se complete.
 */
void send_ACK(void);

/**
 * \brief Envía una señal de no reconocimiento (NACK) en el bus TWI.
 *
 * Configura el registro de control TWI para enviar una señal de no
 * reconocimiento y espera hasta que la transmisión se complete.
 */
void send_NACK(void);

uint8_t twi_master_receive_byte(const uint8_t tx_sla);

uint8_t twi_slave_transmit(const uint8_t data);

/**
 * \brief Recibe datos en modo maestro desde un esclavo TWI.
 *
 * Inicia una condición de inicio, transmite la dirección del esclavo con el bit
 * de lectura, y recibe los datos del esclavo.
 *
 * \param[in] tx_sla Dirección del esclavo desde el cual recibir los datos.
 * \param[in] n Número de bytes a recibir.
 * \return Código de estado de la operación de recepción.
 */
// uint8_t twi_master_receive(const uint8_t tx_sla, const int n);

/**
 * \brief Libera la memoria asignada para el almacenamiento de datos recibidos.
 */
// void free_storage(void);

/**
 * \brief Inicializa el almacenamiento de datos recibidos.
 *
 * Asigna memoria para almacenar los datos recibidos.
 *
 * \param[in] n Número de bytes a almacenar.
 * \return Código de estado de la operación de inicialización.
 */
// int init_data(const size_t n);

/**
 * \brief Obtiene los datos recibidos.
 *
 * Devuelve un puntero a los datos recibidos almacenados.
 *
 * \return Puntero a los datos recibidos.
 */
uint8_t get_received_data(void);

#endif /* _TWI_H */