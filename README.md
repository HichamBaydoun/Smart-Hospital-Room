# Smart-Hospital-Room
The main objective of the project is to help doctors and patients especially through the current coronavirus situation by updating the environment used in the hospital
#### Doctors:
In every patient’s room there will be a machine (made by us) to enter and view patient’s data (diagnosis and daily checkup notes) issued by the doctor/nurse.
The doctor can:
- Press 1 on the keypad to enter patient’s data to the serial monitor, that will be saved on the SD card
- Press 2 on the keypad to read patient’s data from the SD card, and display it on the serial monitor
- Press 3 to send an emergency signal to the staff, which will turn the piezo on so that the nurses would come
#### Patients:
Patients will be able to access multiple elements in room through their phones without them coming out of bed or calling a nurse, therefore they can have an easy experience at the hospital, especially during our current coronavirus situation
- All the patient’s actions will be done through the Blynk app
The patient can:
- Turn on and off the lights (LED) in his room (using a button)
- Adjust the brightness of the lights (LED) of the room (using a slider)
- Call for help by pressing a button, which will turn the piezo on so that the nurses would come (using a button)
- Adjust his bed’s angle by choosing an angle through a slider on the app that will turn the servo motor (representing the bed) to that angle
#### Component’s used:
- Keypad
- SD Card
- Serial Monitor
- Node MCU (with Blynk app)
- Servo Motor
- Piezo
- LED
