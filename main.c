/*
#include <util/delay.h>
#include "MCAL/DIO_intervace.h"
#include "MCAL/ADC_interface.h"
#include "MCAL/TWI_interface.h"
#include "MCAL/EEPROM_interface.h"
#include "HAL/CLCD_intreface.h"
#include "HAL/BUZ_interface.h"
#include "HAL/DCMOTOR_interface.h"
#include "HAL/soil moisture_interface.h"
#include "HAL/soil moisture_privit.h"
#include "HAL/DHT11_interface.h"

#define MAX_OWNERS 3
#define EEPROM_ADDR_OWNERS 0x10
#define EEPROM_ADDR_GUESTS 0x50

typedef enum {
    GUEST,
    OWNER
} UserType;

typedef struct {
    u8 name[16];
    u8 pin[4];
} User;
User currentUser;
u8 guestRequest[16];

DCMOTOR_CONFIG pump = {DIO_PORTC, DIO_PIN0, DIO_PIN1};
DCMOTOR_CONFIG fan = {DIO_PORTC, DIO_PIN2, DIO_PIN3};


DHT11_Data env_data;
u8 moisture_percentage = 0;


int main(void) {

	 u8 selection = 0;
   // System_Init
	    KPD_vInit();
	    ADC_vInit();
	    CLCD_voidInit();
	    DHT11_voidInit();
	    SoilMoisture_voidInit();


	    DCMOTOR_uint8Control(&pump, DCMOTOR_STOP);
	    DCMOTOR_uint8Control(&fan, DCMOTOR_STOP);



	    CLCD_voidSetPosition(CLCD_Row_1, CLCD_col_1);
	    CLCD_voidsendString("welcome to Ecohome");
	    _delay_ms(300000);
	    CLCD_voidClearScreen();

    while(1) {

    	     CLCD_voidClearScreen();
    	        CLCD_voidSetPosition(1, 1);
    	        CLCD_voidsendString("Guest(1) Owner(2)");

    	        // Read selection from keypad
    	        do {
    	            selection = KPD_u8GetPressed();
    	        } while(selection != '1' && selection != '2');

    	        if(selection == '1') {
    	            GuestModeHandler();
    	        } else {
    	            OwnerModeHandler();
    	        }
       // Read_Sensors
    	u16 raw_moisture = 0;

    	    if(SoilMoisture_u8GetPercentage(&moisture_percentage) != OK) {
    	        Error_Handler(1);
    	    }


    	    if(DHT11_u8GetData(&env_data) == 0) {
    	        Error_Handler(2);
    	    }
        //Control_Actuators

    	       if(moisture_percentage < MOISTURE_THRESHOLD) {
    	           DCMOTOR_uint8Control(&pump, DCMOTOR_CW);

    	       } else {
    	           DCMOTOR_uint8Control(&pump, DCMOTOR_STOP);

    	       }


    	       if(env_data.Temperature > TEMP_THRESHOLD) {
    	           DCMOTOR_uint8Control(&fan, DCMOTOR_CW);
    	       } else {
    	           DCMOTOR_uint8Control(&fan, DCMOTOR_STOP);
    	       }
        //Update_Display
        CLCD_voidClearScreen();

            // عرض الرطوبة
            CLCD_voidSetPosition(CLCD_Row_1, CLCD_col_1);
            CLCD_voidsendString("Moisture:");
            CLCD_vSendIntNumber(moisture_percentage);
            CLCD_voidsendData('%');

            // عرض درجة الحرارة
            CLCD_voidSetPosition(CLCD_Row_2, CLCD_col_1);
            CLCD_voidsendString("Temp:");
            CLCD_vSendIntNumber(env_data.Temperature);
            CLCD_voidsendData('C');
        _delay_ms(2000); // تأخير 2 ثانية بين كل قراءة
    }
    return 0;
}







void Error_Handler(u8 error_code) {
    CLCD_voidClearScreen();
    CLCD_voidSetPosition(CLCD_Row_1, CLCD_col_1);

    switch(error_code) {
        case 1:
            CLCD_voidsendString("Moisture Error!");
            break;
        case 2:
            CLCD_voidsendString("Temp Sensor Error!");
            break;
        default:
            CLCD_voidsendString("Unknown Error!");
    }
}

u8 CheckOwnerExists(u8* pin) {
    User storedOwner;
    for(u8 i=0; i<MAX_OWNERS; i++) {
        // استخدام الدالة المعدلة ↓
        EEPROM_read(EEPROM_ADDR_OWNERS + i*sizeof(User), (u8*)&storedOwner, sizeof(User));
        if(memcmp(storedOwner.pin, pin, 4) == 0) return 1; // استخدام memcmp بدل strcmp
    }
    return 0;
}

void SaveOwnerToEEPROM(User* owner) {
    for(u8 i=0; i<MAX_OWNERS; i++) {
        User temp;
        EEPROM_read(EEPROM_ADDR_OWNERS + i*sizeof(User), (u8*)&temp, sizeof(User));
        if(temp.pin[0] == 0xFF) {
            // استخدام الدالة المعدلة ↓
            EEPROM_write(EEPROM_ADDR_OWNERS + i*sizeof(User), (u8*)owner, sizeof(User));
            return;
        }
    }
}

void GuestModeHandler(void) {
    CLCD_voidClearScreen();
    CLCD_voidSetPosition(1, 1);
    CLCD_voidsendString("Enter Name:");

    // Get guest name using keypad
    u8 i=0;
    while(i<15) {
        u8 key = KPD_u8GetPressed();
        if(key != 0xff) {
            guestRequest[i++] = key;
            CLCD_voidsendData(key);
        }
    }
    guestRequest[i] = '\0';

    SendGuestRequest();

    CLCD_voidClearScreen();
    CLCD_voidSetPosition(1, 1);
    CLCD_voidsendString("Request Sent!");
    _delay_ms(2000);
}

void OwnerModeHandler(void) {
    CLCD_voidClearScreen();
    CLCD_voidSetPosition(1, 1);
    CLCD_voidsendString("Enter PIN:");

    // Get PIN from keypad
    u8 pin[4];
    for(u8 i=0; i<4; i++) {
        while((pin[i] = KPD_u8GetPressed()) == 0xff);
        CLCD_voidsendData('*');
    }

    if(CheckOwnerExists(pin)) {
        CLCD_voidClearScreen();
        CLCD_voidSetPosition(1, 1);
        CLCD_voidsendString("Welcome Owner!");
        _delay_ms(2000);

        // Control logic for sensors/actuators
        while(1) {
            CheckGuestRequests();
            // Add control logic here
        }
    } else {
        CLCD_voidClearScreen();
        CLCD_voidSetPosition(1, 1);
        CLCD_voidsendString("Invalid PIN!");
        _delay_ms(2000);
    }
}

void SendGuestRequest(void) {
    // استخدام الدالة المعدلة ↓
    EEPROM_write(EEPROM_ADDR_GUESTS, guestRequest, sizeof(guestRequest));
}

void CheckGuestRequests(void) {
    u8 request[16];
    u8 address, data,size;
    EEPROM_read(EEPROM_ADDR_GUESTS, request, sizeof(request));

    if(request[0] != 0xFF) {
        CLCD_voidClearScreen();
        CLCD_voidSetPosition(1, 1);
        CLCD_voidsendString("Guest Request:");
        CLCD_voidSetPosition(2, 1);
        CLCD_voidsendString(request);

        CLCD_voidSetPosition(2, 1);
        CLCD_voidsendString("Accept(1) Deny(2)");

        u8 response;
        do {
            response = KPD_u8GetPressed();
        } while(response != '1' && response != '2');

        if(response == '1') {
            CLCD_voidClearScreen();
            CLCD_voidSetPosition(1, 1);
            CLCD_voidsendString("Welcome ");
            CLCD_voidsendString(request);
        }

        // Clear request
        memset(request, 0xFF, sizeof(request));
        EEPROM_write(address, data,  size);
    }
}
*/

/*


#include "lib/std_typs.h"
#include "MCAL/DIO_intervace.h"
#include "hal/LED_intreface.h"


LED_config LED_Config = {
    .PortName = DIO_PORTC,      // استخدام PORT C
    .PinNumber = DIO_PIN0,      // استخدام PIN 0
    .ActiveState = ACTIVE_HIGH  // LED يعمل عند HIGH
};

int main(void) {

    LED_vInit(LED_Config);

    while (1) {

        LED_vTurnOn(LED_Config);

        // for (volatile u32 i = 0; i < 100000; i++);
    }

    return 0;
}

*/

/*
#include <util/delay.h>
#include "MCAL/DIO_intervace.h"
#include "MCAL/ADC_interface.h"
#include "HAL/CLCD_intreface.h"
#include "HAL/soil moisture_interface.h"

int main(void) {
    u8 moisture_percentage = 0;

    // تهيئة شاشة LCD ومستشعر الرطوبة
    CLCD_voidInit();
    SoilMoisture_voidInit();

    // عرض رسالة ترحيبية
    CLCD_voidClearScreen();
    CLCD_voidSetPosition(CLCD_Row_1, CLCD_col_1);
    CLCD_voidsendString("Soil Moisture:");

    while(1) {
        // قراءة نسبة الرطوبة
        if(SoilMoisture_u8GetPercentage(&moisture_percentage) == OK) {
            // تحديث العرض
            CLCD_voidSetPosition(CLCD_Row_2, CLCD_col_1);
            CLCD_voidsendString("Value: ");
            CLCD_vSendIntNumber(moisture_percentage);
            CLCD_voidsendData('%');
        } else {
            // معالجة الخطأ
            CLCD_voidClearScreen();
            CLCD_voidSetPosition(CLCD_Row_1, CLCD_col_1);
            CLCD_voidsendString("Sensor Error!");
        }

        _delay_ms(2000); // تأخير 2 ثانية
    }
    return 0;
}


*/
/*
#include <util/delay.h>
#include "MCAL/DIO_intervace.h"
#include "MCAL/ADC_interface.h"
#include "hal/CLCD_intreface.h"
#include "hal/CLCD_p2config.h"
#include "hal/LDR_interface.h"
#include "hal/LDR_config.h"

int main(void) {
    u16 light_value = 0;
    LDR_Config_t ldr_config = {
    	 .Copy_u8Channel =LDR_CHANNEL,
        .Copy_u8VoltageRefrence = LDR_VOLTAGE_REFERENCE,
        .Copy_u8ADCRes = LDR_ADC_RESOLUTION,
        . Copy_u16RL = LDR_LOAD_RESISTANCE
    };

    // Initialize peripherals
    CLCD_voidInit();
    ADC_vInit(); // تهيئة ADC من ملفاتك الجديدة
    LDR_enumInit(&ldr_config); // تهيئة LDR مع الإعدادات

    // Display static message
    CLCD_voidClearScreen();
    CLCD_voidSetPosition(CLCD_Row_1, CLCD_col_1);
    CLCD_voidsendString("LDR Value:");

    while(1) {
        // Read LDR value using ADC driver
        if(LDR_enumGetLightIntensity(&ldr_config, &light_value) == LDR_OK) {
            // Display value on LCD
            CLCD_voidSetPosition(CLCD_Row_2, CLCD_col_1);
            CLCD_voidsendString("        "); // Clear previous value
            CLCD_voidSetPosition(CLCD_Row_2, CLCD_col_1);
            CLCD_vSendIntNumber(light_value);
        } else {
            // Handle ADC read error
            CLCD_voidSetPosition(CLCD_Row_2, CLCD_col_1);
            CLCD_voidsendString("ADC Error!");
        }
        _delay_ms(1000); // Update every 1 second
    }

}*/
/*
#include <util/delay.h>
#include "MCAL/DIO_intervace.h"
#include "MCAL/ADC_interface.h"
#include "hal/CLCD_intreface.h"
#include "hal/CLCD_config.h"
#include "hal/LDR_interface.h"
#include "hal/LDR_config.h"


#define LIGHT_THRESHOLD 5000

int main(void)
{
    LDR_Config_t LDR_Config = {
        .Copy_u8Channel = LDR_CHANNEL,
        .Copy_u8VoltageRefrence = LDR_VOLTAGE_REFERENCE,
        .Copy_u8ADCRes = LDR_ADC_RESOLUTION,
        .Copy_u16RL = LDR_LOAD_RESISTANCE
    };

    u16 u16LightValue;
    LDR_ErrorStatus LDR_Status;


    LDR_Status = LDR_enumInit(&LDR_Config);
    CLCD_voidInit();

    if(LDR_Status != LDR_OK)
    {

        CLCD_voidsendString("LDR Init Error");
        while(1);
    }

    while(1)
    {

        LDR_Status = LDR_enumGetLightIntensity(&LDR_Config, &u16LightValue);

        if(LDR_Status == LDR_OK)
        {
            CLCD_voidClearScreen();
            CLCD_voidSetPosition(CLCD_Row_1, CLCD_col_1);

            if(u16LightValue > LIGHT_THRESHOLD)
            {
                CLCD_voidsendString("Night Mode");
            }
            else
            {
                CLCD_voidsendString("Light Mode");
            }
        }
        else
        {
            CLCD_voidClearScreen();
            CLCD_voidsendString("LDR Read Error");
        }

        _delay_ms(1000);
    }

    return 0;
}*/
/*
 * main.c
 *
 * Created: 4/4/2025 10:00:00 PM
 * Author : User
 */
/*
 * main.c
 *
 * Created: 12/15/2024 5:48:53 PM
 * Author : alaa hassan
 */
/*
#include <util/delay.h>
#include "lib/std_typs.h"
#include "MCAL/DIO_intervace.h"
#include "hal/CLCD_intreface.h"
#include "hal/MQ2_interface.h"
#include "hal/MQ2_config.h"

int main(void) {

    CLCD_voidInit();


    MQ2_Config_t MQ2_Config = {
        .Copy_u8Channel = MQ2_CHANNEL_3,
        .Copy_u8VoltageRefrence = MQ2_VREF_AVCC,
        .Copy_u8ADCRes = MQ2_RES_10_BIT,
        .Copy_u16R0 = MQ2_DEFAULT_R0,
        .Copy_u16RL = MQ2_DEFAULT_RL
    };

    MQ2_enumInit(&MQ2_Config);


    MQ2_enumCalibrate(&MQ2_Config);

    while (1) {
        u16 GasValue = 0;
        u8 Buffer[16];


        MQ2_enumGetGasConcentration(&MQ2_Config, &GasValue);


        sprintf((char*)Buffer, "Gas: %4u ppm", GasValue);


        CLCD_voidClearScreen();
        CLCD_voidSetPosition(CLCD_Row_1, 1);
        CLCD_voidsendString(Buffer);

        _delay_ms(1000); // تأخير 1 ثانية
    }

    return 0;
}*/
/* main.c */
/*#include "lib/std_typs.h"
#include "MCAL/DIO_intervace.h"
#include "hal/CLCD_intreface.h"
#include "hal/PIR_interface.h"

int main(void) {
    u8 Local_u8PIRState;


    PIR_voidInit();
    CLCD_voidInit();


    CLCD_voidClearScreen();
    CLCD_voidSetPosition(CLCD_Row_1, CLCD_col_1);
    CLCD_voidsendString("PIR Sensor:");

    while(1) {

        Local_u8PIRState = PIR_u8ReadDebounced();


        CLCD_voidSetPosition(CLCD_Row_2, CLCD_col_1);
         u8 PIR_DETECTED;
        if(Local_u8PIRState == PIR_DETECTED) {
            CLCD_voidsendString("Motion Detected! ");
        } else {
            CLCD_voidsendString("No Motion      ");
        }


        _delay_ms(100);
    }

    return 0;
}*/
#include "lib/std_typs.h"
#include "MCAL/DIO_intervace.h"
#include "hal/CLCD_intreface.h"
#include "hal/DHT11_interface.h"

int main(void) {
    // تهيئة شاشة الـLCD وحساس DHT11
    CLCD_voidInit();
    DHT11_voidInit();

    // تعريف متغيرات لحفظ القراءات
    DHT11_Data SensorData;
    u8 Local_u8Error;

    // عرض رسالة بداية
    CLCD_voidSetPosition(CLCD_Row_1, CLCD_col_1);
    CLCD_voidsendString("DHT11 Sensor:");

    while (1) {
        // قراءة البيانات من الحساس
        Local_u8Error = DHT11_u8ReadData(&SensorData);

        if (Local_u8Error == OK) {
            // عرض الرطوبة
            CLCD_voidSetPosition(CLCD_Row_2, CLCD_col_1);
            CLCD_voidsendString("H:");
            CLCD_vSendIntNumber(SensorData.Humidity);
            CLCD_voidsendData('%');

            // عرض درجة الحرارة
            CLCD_voidSetPosition(CLCD_Row_2, CLCD_col_9);
            CLCD_voidsendString("T:");
            CLCD_vSendIntNumber(SensorData.Temperature);
            CLCD_voidsendData('C');
        } else {
            // عرض رسالة خطأ
            CLCD_voidSetPosition(CLCD_Row_2, CLCD_col_1);
            CLCD_voidsendString("Error!");
        }

        _delay_ms(2000); // انتظر 2 ثانية قبل التحديث
        CLCD_voidClearScreen();
    }

    return 0;
}

