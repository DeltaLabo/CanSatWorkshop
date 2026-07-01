# Variable Getter Template

- The CanSat distinguishes between *data acquisition* and *data processing.* Data acquisition means getting raw data from a sensor. Data processing means applying math to the raw data to determine the value of a relevant variable. Not all raw data sources need processing, but naturally data acquisition is always necessary.
- If your subsystem needs to process sensor data, you need to define the following two functions: data acquisition and data processing.
- If your subsystem uses sensors that directly provide *variable measurements,* then a single data acquistion function is sufficient.
- For example, the ADS subsystem might implement a data acquisition function to read magnetic field strength from an IMU sensor (a variable that is not sent to the GS or used for any other purpose), then a data processing function to calculate pitch, roll, and yaw (the actually relevant variables) from said measurement.
- For variables with a decimal component, you need to define the precision at which you want to log the measurements, and discard the rest of the decimal digits. This is done both to minimize the LoRa payload size and to avoid logging noise.
- To convert a decimal variable to fixed precision:
    - Multiply it by 10^(number of decimal places to keep)
    - Convert it to a 32-bit integer

> For integration purposes, you only need to provide a variable getter function (or more than one, as needed) in which you encapsulate all data acquisition and processing code.

> What happens inside the getter isn’t relevant to the overall system so there are no restrictions or guidelines for it The return value, however, needs to meet the following requirements: 

```cpp
// Example for altitude sensor
// Note how the getter hides all measurement complexity

/**
* @brief Returns the current temperature multiplied by 100 to preserve 2 decimal places.

* @param output 32-bit integer address to save the measurement to.
* @return result Byte containing the result of the get operation.
								 0: Success
								 1: Overflow
								 2: Underflow
*/
unsigned short getTemperature(long* output) {
  /*** Raw data acquisition ***/
	// Each subsystem implements this function without restrictions
	// as it is sensor-specific
	float rawTemperature;

	// Read from the sensor
	// If your sensor provides a result code, retrieve it here
	readTemperatureSensor(&rawTemperature);

	/*** Data processing ***/
	// Can also be implemented without restrictions
	
	// Basic example, converting from Fahrenheit to Celsius
	rawTemperature = (rawTemperature - 32) / 1.8;
	
	// Use multiplier to preserve 2 decimal places
	// Saved to a double to avoid overflow
	double multipliedTemperature = rawTemperature * 100.0;
	
	/*** Error checking ***/
	// Most sensors won't overflow or underflow a 32-bit integer,
	// but other errors, mainly communication-related, can occur
	
	if (multipliedTemperature > INT32_MAX) {
		*output = INT32_MAX;
		// Error code 1: Overflow
		return 1;
	} else if (multipliedTemperature < -(INT32_MAX+1)) {
		*output = -(INT32_MAX+1);
		// Error code 2: Underflow
		return 2;
	} else {
		*output = (long)multipliedTemperature;
		// Success
		return 0;
	}
}
```

Then, to read the variable, the OBCC will use your getter as follows:

```cpp
// Variable that will be logged via LoRa
long temperature;
// Error or success code
unsigned short resultCode;
resultCode = getTemperature(&temperature);
```

The result code will be used for both startup and runtime health checks.