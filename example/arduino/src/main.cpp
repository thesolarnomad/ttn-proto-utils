#include <Arduino.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include <test.pb.h>

com_example_MyMessage message;
uint8_t buffer[com_example_MyMessage_size];
size_t message_length;
bool status;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop() {
    /* Encode our message */
    {
        /* Allocate space on the stack to store the message data. */
        message = com_example_MyMessage_init_zero;
        
        /* Create a stream that will write to our buffer. */
        pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
        
        message.humidity = random(101);
        message.gain = com_example_MyMessage_AdsGain_GAIN_TWOTHIRDS;
        
        /* Now we are ready to encode the message! */
        status = pb_encode(&stream, com_example_MyMessage_fields, &message);
        message_length = stream.bytes_written;
        
        /* Then just check for any errors.. */
        if (!status) {
            Serial.print(F("Encoding failed: "));
            Serial.println(PB_GET_ERROR(&stream));
        }
    }
    
    /* Transmit the message over network here */

    /* But because we are lazy, we will just decode it immediately. */
    {
        /* Allocate space for the decoded message. */
        message = com_example_MyMessage_init_zero;
        
        /* Create a stream that reads from the buffer. */
        pb_istream_t stream = pb_istream_from_buffer(buffer, message_length);
        
        /* Now we are ready to decode the message. */
        status = pb_decode(&stream, com_example_MyMessage_fields, &message);
        
        /* Check for errors... */
        if (!status) {
            Serial.print(F("Decoding failed: "));
            Serial.println(PB_GET_ERROR(&stream));
        }
        
        /* Print the data contained in the message. */
        Serial.print(F("Today's humidity: "));
        Serial.println((double) message.humidity / 100, 2);
    }
}