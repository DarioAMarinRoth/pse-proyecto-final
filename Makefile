##################################################################################
#  VARIABLES
##################################################################################

# Configuración del microcontrolador
MCU = atmega328p
F_CPU = 16000000UL
PROGRAMMER = arduino
PORT = /dev/ttyUSB0
BAUD = 57600

# Herramientas
CC = avr-gcc

# Flags
CFLAGS = -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU)
LDFLAGS = -mmcu=$(MCU)
FIRMWARE = imagen.hex

# Misc
INCLUDE_DIR = ./include
BUILD_DIR = build
APP = program
COMPILE = $(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@
LINK = $(CC) $(LDFLAGS) -o $(BUILD_DIR)/$(APP) $^

##################################################################################
#  REGLAS
##################################################################################

# Apps:
all:
	@echo "Ejecute el comando 'make <app>' donde <app> es una de los siguientes opciones:"
	@echo "  - twi-master-test"
	@echo "  - twi-slave-test"
	@echo ""
	@echo "Recordar hacer make clean antes de compilar otra app."

twi-master-test: $(BUILD_DIR)/gpio.o $(BUILD_DIR)/serial.o $(BUILD_DIR)/twi.o $(BUILD_DIR)/twi_master_test.o
	$(LINK)

twi-slave-test: $(BUILD_DIR)/gpio.o $(BUILD_DIR)/serial.o $(BUILD_DIR)/twi.o $(BUILD_DIR)/twi_slave_test.o
	$(LINK)

# Objetos:
$(BUILD_DIR)/%.o: ./src/drivers/%.c
	mkdir -p $(BUILD_DIR)
	$(COMPILE)

$(BUILD_DIR)/twi_master_test.o: src/tests/unit/twi/twi_master_test.c
	mkdir -p $(BUILD_DIR)
	$(COMPILE)

$(BUILD_DIR)/twi_slave_test.o: src/tests/unit/twi/twi_slave_test.c
	mkdir -p $(BUILD_DIR)
	$(COMPILE)

# Misc:
flash:
	avr-objcopy -O ihex -R .eeprom $(BUILD_DIR)/$(APP) $(BUILD_DIR)/$(FIRMWARE)
	avrdude -p $(MCU) -c arduino -P $(PORT) -b $(BAUD) -D -U flash:w:$(BUILD_DIR)/$(FIRMWARE):i

clean:
	rm -rf $(BUILD_DIR)
	rm -rf cmake-build-debug