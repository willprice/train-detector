typedef enum { NO_TRAIN, TRAIN, WAIT } STATE;
typedef enum { NO_EVENT, TRAIN_ARRIVED, ACKNOWLEDGE } EVENT;

#define ALARM_PIN 9
#define TRAIN_TRIGGER_PIN 8
#define ALARM_DISABLE_PIN 7

// Uncomment the line below to enable serial port debugging
#define DEBUG
#define SD_ChipSelectPin 10

// Delay (in seconds)
#define DELAY 30
// C4
#define NOTE 262
