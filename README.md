# Arduino-AccelGyro-autohold

This project was meant to test an ADXL345 board which includes an Accelerometer and a Gyroscope by making a light connected to a servo maitain its orientation to the ground no matter how tilted the main board would get. 

The code is based on a running average filter that eliminates the jitter/noise the sensor picks up but introduces a small delay, acceptable for this test.

I was planning to add this to my car as a way to automatically lower the light beams when going uphill as to improve the lighting performance, but it was scrapped in the end being to much of a hassle to tear down the headlights.

Video:

https://youtu.be/afgOVt5PyhE

https://youtu.be/kwjo-ewOvLU

https://youtu.be/FKWuex2R4Vw
