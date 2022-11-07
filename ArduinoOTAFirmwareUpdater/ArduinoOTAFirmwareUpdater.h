/**
 * @file	ArduinoOTAFirmwareUpdater.h
 * @author	ACAMU from JayLooi / RemoteArduino repo
 * @date	06-11-2022
 * @brief	A class for ESP8266 to perform OTA firmware update 
 *			on a connected Arduino Uno
 *
 */
 
#ifndef	ArduinoOTAFirmwareUpdater_H
#define	ArduinoOTAFirmwareUpdater_H

#ifndef	EXTRA_FUNC_CALL_FLAG
	#define	EXTRA_FUNC_CALL_FLAG
#endif

#ifndef DEVICEID
	#define DEVICEID	Unknown
#endif

#define CMD_FLASH_START			0x46		// 'F'
#define OK				        "OK"
#define WARNING_STK_FAILED		"[WARNING] STK FAILED"
#define FLASH_FAILED			"[FAILED] FLASHING FAILED"
#define TIMEOUT					1000UL

#define	DEFAULT_BAUDRATE		115200UL
#define	CMD_UPDATE_BAUDRATE		0x55	// 'U'


class ArduinoOTAFirmwareUpdater {
	public: 
		ArduinoOTAFirmwareUpdater(uint8_t reset_pin, int8_t ind_LED=-1) { 
			_client_id = STR(DEVICEID);
			_reset_pin = reset_pin;
			_ind_LED = ind_LED;

			pinMode(_reset_pin, OUTPUT);
			digitalWrite(_reset_pin, HIGH);

		}
	
	protected:

	    const char *_client_id;
		uint16_t _addr;
		uint32_t _hex_size;
		uint32_t _hex_size_copy;
		bool _is_flashing = false;
		uint32_t _start_time;
		bool _is_timeout = false;

		uint32_t _baudrate;
		uint8_t _reset_pin;
		int8_t _ind_LED;

		
		void _startFlashing(byte *payload, uint32_t length);
		void _setStartFlashTimeout();
        //void _callback(char *topic, byte *payload, uint32_t length);
		void clientFlashArduino(byte *payload, uint32_t length);
		bool _waitOptibootRes_1s();
		void _getSync();
		bool _sendHex(const uint8_t *hex, uint8_t len);

		void _flushRxBuff() { while(Serial.available()) Serial.read(); }
		
		void _setBaudrate(uint32_t baudrate) {
			_baudrate = baudrate;
			Serial.flush();
			Serial.updateBaudRate(_baudrate);
		}
		
		void _setBaudrate(byte *payload, uint32_t length) {
			uint32_t baudrate = 0;
			for(uint8_t i=1;i<length;i++) {
				uint8_t payload_i = (uint8_t)payload[i];
				
				if((payload_i >= '0') && (payload_i <= '9')) {
					baudrate *= 10;
					baudrate += payload_i - '0';
				} else {
					baudrate = _baudrate;
					break;
				}
			}
			
			_setBaudrate(baudrate? baudrate:_baudrate);
		}
};

#endif		/* ArduinoOTAFirmwareUpdater_H */
