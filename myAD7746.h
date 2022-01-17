#ifndef _AD7746_H_
#define _AD7746_H_

/* AD7746 Slave Address */
#define AD7746_ADDR			      0x48
#define AD7746_ADDR_WRITE   		  0x90	// 0b|1001000|0	7-bit address + Write Bit
#define AD7746_ADDR_READ   				0x91	// 0b|1001000|1	7-bit address + Read Bit
#define AD7746_CHIP_ID            0x00
/* AD7746 Reset command */
#define AD7746_RESET		      0xBF

/* AD7746 Register Definition */
#define AD7746_ADDR_STATUS   				  0x00
#define AD7746_ADDR_CAP_DATA_H   			0x01
#define AD7746_ADDR_CAP_DATA_M    		0x02
#define AD7746_ADDR_CAP_DATA_L    		0x03
#define AD7746_ADDR_VT_DATA_H   			0x04
#define AD7746_ADDR_VT_DATA_M   			0x05
#define AD7746_ADDR_VT_DATA_L   			0x06
#define AD7746_ADDR_CAP_SETUP  				0x07
#define AD7746_ADDR_VT_SETUP   				0x08
#define AD7746_ADDR_EXC_SETUP   			0x09
#define AD7746_ADDR_CONFIGURATION   	0x0A
#define AD7746_ADDR_CAP_DAC_A   			0x0B
#define AD7746_ADDR_CAP_DAC_B   			0x0C
#define AD7746_ADDR_CAP_OFFSET_H   		0x0D
#define AD7746_ADDR_CAP_OFFSET_L   		0x0E
#define AD7746_ADDR_CAP_GAIN_H   			0x0F
#define AD7746_ADDR_CAP_GAIN_L   			0x10
#define AD7746_ADDR_VOLTAGE_GAIN_H   	0x11
#define AD7746_ADDR_VOLTAGE_GAIN_L		0x12

// AD7746 status register bit masks
#define STATUS_EXCERR						0b00001000
#define STATUS_RDY							0b00000100
#define STATUS_RDYVT						0b00000010
#define STATUS_RDYCAP						0b00000001
//********************************************************************************//

//********************************************************************************//
// AD7746 capacitive channel setup bit masks
// CAPEN = 1 enables capacitive channel for single conversion, continuous conversion, or calibration.
#define CAPSETUP_CAPEN_OFF 					0x00
#define CAPSETUP_CAPEN_ON 					0x80
// CIN2 = 1 switches the internal multiplexer to the second capacitive input on the AD7746.
#define CAPSETUP_CIN2_OFF					  0x00
#define CAPSETUP_CIN2_ON					  0x40
// DIFF = 1 sets differential mode on the selected capacitive input.
#define CAPSETUP_CAPDIFF_OFF 				0x00
#define CAPSETUP_CAPDIFF_ON 				0x20
// CAPCHOP = 1 approximately doubles the capacitive channel conversion times and slightly
// improves the capacitive channel noise performance for the longest conversion times.
#define CAPSETUP_CAPCHOPP_OFF 			0x00
#define CAPSETUP_CAPCHOPP_ON 				0x01
//********************************************************************************//

//********************************************************************************//
// AD7746 Voltage/Temperature channel setup bit masks
// VTEN = 1 enables voltage/temperature channel for single conversion, continuous conversion, or calibration.
#define VTSETUP_VTEN_OFF					  0x00
#define VTSETUP_VTEN_ON						  0x80
// Voltage/Temperature channel input  configuration
// Internal temperature sensor
#define VTSETUP_VTMD_INTERNAL_TEMP	0x00
// External temperature sensor diode
#define VTSETUP_VTMD_EXTERNAL_TEMP	0x20
// VDD monitor
#define VTMD_VDD_MONITOR					  0x40
// External voltage input (VIN)
#define VTSETUP_VTMD_EXTERNAL_VOLTAGE 		0x60
// EXTREF = 0 selects the on-chip internal reference. The internal reference must be used with the internal temperature sensor for proper operation.
#define VTSETUP_EXTREF_OFF					0x00
// EXTREF = 1 selects an external reference voltage connected to REFIN(+), REFIN(–) for the voltage input or the VDD monitor.
#define VTSETUP_EXTREF_ON					  0x10
// VTSHORT = 1 internally shorts the voltage/temperature channel input for test purposes.
#define VTSETUP_VTSHORT_OFF					0x00
#define VTSETUP_VTSHORT_ON					0x02
// VTCHOP = 1 sets internal chopping on the voltage/temperature channel.
// The VTCHOP bit must be set to 1 for the specified voltage/temperature channel performance.
#define VTSETUP_VTCHOP_OFF					0x00
#define VTSETUP_VTCHOP_ON					  0x01
//********************************************************************************//

//********************************************************************************//
// AD7746 Capacitive channel excitation setup bit masks
// The CLKCTRL bit should be set to 0 for the specified AD7745/AD7746 performance.
// CLKCTRL = 1 decreases the excitation signal frequency and the modulator clock frequency by factor of 2.
// This also increases the conversion time on all channels (capacitive, voltage, and temperature) by a factor of 2.
#define EXCSETUP_CLKCTRL_OFF				0x00
#define EXCSETUP_CLKCTRL_ON					0x80
// When EXCON = 0, the excitation signal is present on the output only during capacitance channel conversion.
// When EXCON = 1, the excitation signal is present on the output during both capacitance and voltage/temperature conversion.
#define EXCSETUP_EXCON_OFF					0x00
#define EXCSETUP_EXCON_ON					  0x40
// EXCB = 1 enables EXCB pin as the excitation output.
#define EXCSETUP_EXCB_OFF					  0x00
#define EXCSETUP_EXCB_ON					  0x20
//nEXCB = 1 enables EXCB pin as the inverted excitation output.
// Only one of the EXCB or the EXCB bits should be set for proper operation.
#define EXCSETUP_nEXCB_OFF					0x00
#define EXCSETUP_nEXCB_ON					  0x10
//EXCA = 1 enables EXCA pin as the excitation output.
#define EXCSETUP_EXCA_OFF					  0x00
#define EXCSETUP_EXCA_ON					  0x08
// EXCA = 1 enables EXCA pin as the inverted excitation output.
// Only one of the EXCA or the EXCA bits should be set for proper operation.
#define EXCSETUP_nEXCA_OFF					0x00
#define EXCSETUP_nEXCA_ON					  0x04
// Excitation Voltage Level
#define EXCSETUP_EXCLVL_VDD_8   		0x00
#define EXCSETUP_EXCLVL_VDD_4    		0x01
#define EXCSETUP_EXCLVL_3VDD_8			0x02
#define EXCSETUP_EXCLVL_VDD_2				0x03
//********************************************************************************//

//********************************************************************************//
// AD7746 Converter update rate and mode of operation setup
// Voltage/temperature channel digital filter setup-conversion time/update rate setup.
// The conversion times in this table are valid for the CLKCTRL = 0 in the EXC SETUP register.
// The conversion times are longer by a factor of two for the CLKCTRL = 1.
#define CONF_VTF_20_MS						  0x00
#define CONF_VTF_32_MS						  0x40
#define CONF_VTF_62_MS						  0x80
#define CONF_VTF_122_MS						  0xC0
// Capacitive channel digital filter setup-conversion time/update rate setup.
// The conversion times in this table are valid for the CLKCTRL = 0 in the EXC SETUP register.
// The conversion times are longer by factor of two for the CLKCTRL = 1.
#define CONF_CAPF_11_MS						  0x00
#define CONF_CAPF_12_MS						  0x08
#define CONF_CAPF_20_MS						  0x10
#define CONF_CAPF_38_MS						  0x18
#define CONF_CAPF_62_MS						  0x20
#define CONF_CAPF_77_MS						  0x28
#define CONF_CAPF_92_MS						  0x30
#define CONF_CAPF_109_MS					  0x38
// Converter mode of operation setup.
#define CONF_MD_IDLE						        0x00
#define CONF_MD_CONTINUOUS_CONVERSION		0x01
#define CONF_MD_SINGLE_CONVERSION			  0x02
#define CONF_MD_POWER_DOWN					    0x03
#define CONF_MD_CAP_OFFSET_CALIBRATION 	0x05
#define	CONF_MD_CAP_GAIN_CALIBRATION		0x06
//********************************************************************************//

//********************************************************************************//
// AD7746 Capacitive DAC setup
// DACAENA = 1 connects capacitive DACA to the positive capacitance input.
#define CAPDACA_DACAENA_OFF					0x00
#define CAPDACA_DACAENA_ON					0x80
//********************************************************************************//

//********************************************************************************//
// AD7746 Capacitive DAC setup
// DACBENB = 1 connects capacitive DACB to the negative capacitance input.
#define CAPDACB_DACBENB_OFF 				0x00
#define CAPDACB_DACBENB_ON					0x80
//********************************************************************************//

/**
 * @brief initialize the AD7746. Please refer to the datasheet to see the default register values.
 *
 * @return None
*/
void AD7746_Init(u8 capsetup, u8 vtsetup, u8 excsetup, u8 conf, u8 capdaca, u8 capdacb);

/**
*/
void AD7746_Reset();


/**
 * @brief Reads one byte data from AD7746 registers, starting from the selected
 *        register address pointer.
*/
u8 AD7746_Read_Byte(u8 reg);

/**
 * @brief Writes onoe byte data into AD7746 registers, starting from the selected
 *        register address pointer.
*/
u8 AD7746_Write_Byte(u8 reg,u8 data);


/**
 * @brief Waits until a conversion on a capacitive channel has been finished and
 *        returns the output data.
 *
 * @return capacitance - The content of the Cap Data register.
*/
u32 AD7746_getCapacitance();

/**
 * @brief Waits until a conversion on a voltage/temperature channel has been
 *        finished and returns the output data.
 *
 * @return temperature - The content of the VT Data register.
*/
u32 AD7746_getTemperature();

/**
 * @brief Writes the Cap Setup Register
 *
 * @return None
*/
void AD7746_WriteCapSetupRegister(u8 data);

/**
 * @brief Writes the Voltage/Temperature configuration Register
 *
 * @param data - The desired register value
 *
 * @return None
*/
void AD7746_WriteVTSetupRegister(u8 data);

/**
 * @brief Writes the Excitation Setup Register
 *
 * @param data - The desired register value
 *
 * @return None
*/
void AD7746_WriteExcSetupRegister(u8 data);

/**
 * @brief Writes the Configuration Register
 *
 * @param data - The desired register value
 *
 * @return None
*/
void AD7746_WriteConfigurationRegister(u8 data);

/**
 * @brief Writes the CAPDAC A configuration register
 *
 * @param data - The desired register value
 *
 * @return None
*/
void AD7746_WriteCapDacARegister(u8 data);

/**
 * @brief Writes the CAPDAC B configuration register
 *
 * @param data - The desired register value
 *
 * @return None
*/
void AD7746_WriteCapDacBRegister(u8 data);

void AD7746_SetCapOffset(u16 offset);

void AD7746_SetCapGain(u16 gain);

void AD7746_SetVoltGain(u16 gain);

float AD7746_CapConvert(u8 capdac);
#endif  // __AD7746_DRIVER_H__
