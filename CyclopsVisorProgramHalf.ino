  #include <Wire.h>
  #include <Adafruit_GFX.h>
  #include <Adafruit_SSD1306.h>
  #include <Adafruit_VL53L0X.h>
  #include <TensorFlowLite_ESP32.h>
  // Oled display setup
  #define SCREEN_WIDTH 128
  #define SCREEN_HEIGHT 64
  #define OLED_RESET -1
  #define SCREEN_ADDRESS 0x3C
  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
  //
  Adafruit_VL53L0X tof = Adafruit_VL53L0X();
  VL53L0X_RangingMeasurementData_t measure; // intialzing variable for use later
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // intialize the oled display
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
  } else {
    Serial.println("OLED OK!");
  }

  //initialize ToF hardware
  if(!tof.begin()) {
    Serial.println(F("failed to boot ToF sensor"));
  } else {
  Serial.println("ToF OK!");
  }

  display.clearDisplay();
// Text formatting
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
// display testing
  display.println(F("Initializing..."));
  display.println(F("ESP32 Ready!"));
  display.display();
  delay(1000);

}

void loop() {
  // put your main code here, to run repeatedly:
  // Data reading from TOF sensor and translating said data
  tof.getRangingMeasurement(&measure, false); //assign data to variable measuremnt that we manipulate later
  // if the status of measurement is not failed, save data into interger in mm

  int distance_mm = -1; // defauclt value for invalid casses

  if (measure.RangeStatus != 4) {
    distance_mm = measure.RangeMilliMeter;
    }

    //Print display
    Serial.print("Distance (mm):");
    Serial.println(distance_mm);

    // update the display
    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    // formatting and preving it from saying -1 mm when out of range.
    if (distance_mm != -1) {
    display.println("Distance");
    display.print(distance_mm);
    display.println("mm");
    } else {
    display.println("Person out of range");
    }
    display.display();
    delay(100);
}
