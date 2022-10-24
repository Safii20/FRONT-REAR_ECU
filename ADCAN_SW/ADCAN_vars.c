/**************************************************************************/
/*       Declaracio de totes les variables utilitzades en ADCAN.c           */
/**************************************************************************/

// VARIABLES: CAN

unsigned int16 cobid=0;             // CAN: message cobid
int8 lengthCAN=0;                   // CAN: message length
int8 contCAN = 0;                   // CAN: sincronism counter
unsigned int8 _alive = 0;            // CAN: alive counter 
unsigned int not_first_message = 0; // CAN: first message initial condition 
unsigned int32 data=0;               // CAN: message information
unsigned int32 data_bis=0;           // CAN: extra information
int8 CAN_flag = 0;                  // CAN: sincronism flag


// VARIABLES: Sensors

int32 APPS1_sum = 0;              // Sensor: suma APP 1
int32 APPS2_sum = 0;              // Sensor: suma APP 2
int32 BrakeS_sum = 0;             // Sensor: suma Brake 
int32 Steering_sum = 0;           // Sensor: suma Steering
int32 SpringFR_sum = 0;           // Sensor: suma Suspension Front Right
int32 SpringFL_sum = 0;           // Sensor: suma Suspension Front Left
//int32 AUX1 = 0;                  // Sensor: suma Auxiliar signal 1 
//int32 AUX2 = 0;                  // Sensor: suma Auxiliar signal 2 

int16 APPS1 = 0;                  // Sensor: APP 1 (MEAN)
int16 APPS2 = 0;                  // Sensor: APP 2 (MEAN)
int16 BrakeSensor = 0;              // Sensor: Brake (MEAN)
int16 SteeringSensor = 0;            // Sensor: Steering (MEAN) 
int16 SUSPFR = 0;                  // Sensor: Suspension Front Right (MEAN)
int16 SUSPFL = 0;                  // Sensor: Suspension Front Left (MEAN)
//int16 AUX1_mean = 0;                // Sensor: Auxiliar signal 1 (MEAN)
//int16 AUX2_mean = 0;             // Sensor: Auxiliar signal 1 (MEAN)



// VARIABLES: program
unsigned int mean_filter_flag = 0;  // Timer 2
unsigned int read_ADC_flag = 0;     // Timer 2 
signed int16 SUMA = 0;              // variable temporal per recollir dades sensors