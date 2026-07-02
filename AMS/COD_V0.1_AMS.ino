// In this file you can find the 0.1 version of the code

#include <Wire.h>
#include <limits.h>
#include <math.h>

#include "Adafruit_Sensor.h"
#include "Adafruit_BME280.h"

#define BME280_ADDRESS 0x76
#define SEA_LEVEL_HPA 1013.25
#define TIMEOUT_US 5000

Adafruit_BME280 bme;

// ============================================================
// INIT
// ============================================================

bool initBME280() {

  if (!bme.begin(BME280_ADDRESS)) {
    return false;
  }

  bme.setSampling(
    Adafruit_BME280::MODE_NORMAL,
    Adafruit_BME280::SAMPLING_X1,
    Adafruit_BME280::SAMPLING_X1,
    Adafruit_BME280::SAMPLING_NONE,
    Adafruit_BME280::FILTER_OFF,
    Adafruit_BME280::STANDBY_MS_1
  );

  return true;
}

// ============================================================
// RAW DATA ACQUISITION
// ============================================================

/**
 * @brief Reads raw temperature from BME280.
 *
 * @param output Address to store raw temperature.
 *
 * @return result code
 *         0: Success
 *         3: Invalid measurement / sensor failure
 */
unsigned short readRawTemperature(float* output) {

  unsigned long start = micros();

  float rawTemperature = bme.readTemperature();

  if ((micros() - start) > TIMEOUT_US) {
    return 3;
  }

  if (isnan(rawTemperature)) {
    return 3;
  }

  *output = rawTemperature;

  return 0;
}

/**
 * @brief Reads raw pressure from BME280.
 *
 * @param output Address to store raw pressure.
 *
 * @return result code
 *         0: Success
 *         3: Invalid measurement / sensor failure
 */
unsigned short readRawPressure(float* output) {

  unsigned long start = micros();

  float rawPressure = bme.readPressure();

  if ((micros() - start) > TIMEOUT_US) {
    return 3;
  }

  if (isnan(rawPressure)) {
    return 3;
  }

  *output = rawPressure;

  return 0;
}

/**
 * @brief Reads raw altitude from BME280.
 *
 * @param output Address to store raw altitude.
 *
 * @return result code
 *         0: Success
 *         3: Invalid measurement / sensor failure
 */
unsigned short readRawAltitude(float* output) {

  unsigned long start = micros();

  float rawAltitude = bme.readAltitude(SEA_LEVEL_HPA);

  if ((micros() - start) > TIMEOUT_US) {
    return 3;
  }

  if (isnan(rawAltitude)) {
    return 3;
  }

  *output = rawAltitude;

  return 0;
}

// ============================================================
// DATA PROCESSING
// ============================================================

/**
 * @brief Processes temperature data.
 *
 * @param rawTemperature Raw temperature in Celsius.
 * @return processed temperature.
 */
float processTemperature(float rawTemperature) {

  // BME280 already returns Celsius
  return rawTemperature;
}

/**
 * @brief Processes pressure data.
 *
 * @param rawPressure Raw pressure in Pa.
 * @return processed pressure in kPa.
 */
float processPressure(float rawPressure) {

  return rawPressure / 1000.0;
}

/**
 * @brief Processes altitude data.
 *
 * @param rawAltitude Raw altitude in meters.
 * @return processed altitude.
 */
float processAltitude(float rawAltitude) {

  return rawAltitude;
}

// ============================================================
// VARIABLE GETTERS
// ============================================================

/**
 * @brief Returns current temperature multiplied by 100.
 *
 * Preserves 2 decimal places.
 *
 * @param output Address to store processed measurement.
 *
 * @return result code
 *         0: Success
 *         1: Overflow
 *         2: Underflow
 *         3: Invalid measurement / sensor failure
 *        
 */
unsigned short getTemperature(long* output) {

  // ------------------------------------------------
  // RAW DATA ACQUISITION
  // ------------------------------------------------

  float rawTemperature;

  unsigned short acquisitionResult =
    readRawTemperature(&rawTemperature);

  if (acquisitionResult != 0) {

    *output = 0;
    return acquisitionResult;
  }

  // ------------------------------------------------
  // DATA PROCESSING
  // ------------------------------------------------

  float processedTemperature =
    processTemperature(rawTemperature);

  // ------------------------------------------------
  // PLAUSIBILITY CHECK
  // ------------------------------------------------

  if (
    processedTemperature < -40.0 ||
    processedTemperature > 85.0
  ) {

    *output = 0;
    return 3;
  }

  // Preserve 2 decimal places
  double multipliedTemperature =
    processedTemperature * 100.0;

  // ------------------------------------------------
  // ERROR CHECKING
  // ------------------------------------------------

  if (multipliedTemperature > INT32_MAX) {

    *output = INT32_MAX;
    return 1;

  } else if (
    multipliedTemperature < -(INT32_MAX + 1.0)
  ) {

    *output = -(INT32_MAX + 1);
    return 2;
  }

  *output = (long)multipliedTemperature;

  return 0;
}

/**
 * @brief Returns current pressure multiplied by 100.
 *
 * Pressure returned in kPa.
 *
 * @param output Address to store processed measurement.
 *
 * @return result code
 *         0: Success
 *         1: Overflow
 *         2: Underflow
 *         3: Invalid measurement / sensor failure
 *         
 */
unsigned short getPressure(long* output) {

  // ------------------------------------------------
  // RAW DATA ACQUISITION
  // ------------------------------------------------

  float rawPressure;

  unsigned short acquisitionResult =
    readRawPressure(&rawPressure);

  if (acquisitionResult != 0) {

    *output = 0;
    return acquisitionResult;
  }

  // ------------------------------------------------
  // DATA PROCESSING
  // ------------------------------------------------

  float processedPressure =
    processPressure(rawPressure);

  // ------------------------------------------------
  // PLAUSIBILITY CHECK
  // ------------------------------------------------

  // Pressure in kPa
  // Typical atmospheric pressure:
  // ~101.3 kPa

  if (
    processedPressure < 10.0 ||
    processedPressure > 120.0
  ) {

    *output = 0;
    return 3;
  }

  // Preserve 2 decimal places
  double multipliedPressure =
    processedPressure * 100.0;

  // ------------------------------------------------
  // ERROR CHECKING
  // ------------------------------------------------

  if (multipliedPressure > INT32_MAX) {

    *output = INT32_MAX;
    return 1;

  } else if (
    multipliedPressure < -(INT32_MAX + 1.0)
  ) {

    *output = -(INT32_MAX + 1);
    return 2;
  }

  *output = (long)multipliedPressure;

  return 0;
}

/**
 * @brief Returns current altitude multiplied by 100.
 *
 * Altitude returned in meters.
 *
 * @param output Address to store processed measurement.
 *
 * @return result code
 *         0: Success
 *         1: Overflow
 *         2: Underflow
 *         3: Invalid measurement / sensor failure
 *         
 */
unsigned short getAltitude(long* output) {

  // ------------------------------------------------
  // RAW DATA ACQUISITION
  // ------------------------------------------------

  float rawAltitude;

  unsigned short acquisitionResult =
    readRawAltitude(&rawAltitude);

  if (acquisitionResult != 0) {

    *output = 0;
    return acquisitionResult;
  }

  // ------------------------------------------------
  // DATA PROCESSING
  // ------------------------------------------------

  float processedAltitude =
    processAltitude(rawAltitude);

  // ------------------------------------------------
  // PLAUSIBILITY CHECK
  // ------------------------------------------------

  if (
    processedAltitude < -500.0 ||
    processedAltitude > 10000.0
  ) {

    *output = 0;
    return 3;
  }

  // Preserve 2 decimal places
  double multipliedAltitude =
    processedAltitude * 100.0;

  // ------------------------------------------------
  // ERROR CHECKING
  // ------------------------------------------------

  if (multipliedAltitude > INT32_MAX) {

    *output = INT32_MAX;
    return 1;

  } else if (
    multipliedAltitude < -(INT32_MAX + 1.0)
  ) {

    *output = -(INT32_MAX + 1);
    return 2;
  }

  *output = (long)multipliedAltitude;

  return 0;
}

// ============================================================
// SETUP
// ============================================================

void setup() {

  Serial.begin(9600);

  Wire.begin();

  if (!initBME280()) {

    Serial.println("BME280 INIT FAILED");

    while (1);
  }

  Serial.println("BME280 INIT OK");
}

// ============================================================
// LOOP
// ============================================================

void loop() {

  long temperature;
  long pressure;
  long altitude;

  unsigned short tResult;
  unsigned short pResult;
  unsigned short aResult;

  tResult = getTemperature(&temperature);
  pResult = getPressure(&pressure);
  aResult = getAltitude(&altitude);

  Serial.print("Temperature: ");

  if (tResult == 0) {
    Serial.print(temperature / 100.0);
    Serial.print(" C");
  } else {
    Serial.print("INVALID");
  }

  Serial.print(" | Result: ");
  Serial.println(tResult);

  Serial.print("Pressure: ");

  if (pResult == 0) {
    Serial.print(pressure / 100.0);
    Serial.print(" kPa");
  } else {
    Serial.print("INVALID");
  }

  Serial.print(" | Result: ");
  Serial.println(pResult);

  Serial.print("Altitude: ");

  if (aResult == 0) {
    Serial.print(altitude / 100.0);
    Serial.print(" m");
  } else {
    Serial.print("INVALID");
  }

  Serial.print(" | Result: ");
  Serial.println(aResult);

  Serial.println();

  delay(1000);
}
