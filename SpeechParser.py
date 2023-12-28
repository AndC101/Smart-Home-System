# Author: Andrew Chen and Ethan Lin
# Date: December 12th 2023
# Description: Uses pythons speech recognition library and the google speech recognition API to parse speech into a string which is then sent into the arduino code thorugh the serial

#import libraries for speech recognition
import speech_recognition as sr
import serial

#set up the serial and recognizer
ser = serial.Serial('COM3', 115200, timeout=0)
rec = sr.Recognizer()

#adjusts for ambient (room) noise for 5 seconds to calibrate the system
with sr.Microphone() as mic: 
    print("Silence please, calibrating...")
    rec.adjust_for_ambient_noise(mic, duration=5)


#continuously loop for mic input for the command
while True:

    #uses the laptop microphone for speech recognition 
    with sr.Microphone() as mic:

        #adjust the ambient noise to release the resources of the mic -- must be done otherwise there is a large delay
        rec.adjust_for_ambient_noise(mic, duration=0.5)

        #trys to take input from mic via google speech recognition API
        try:
            print("calibrated, speak now...")
            audio = rec.listen(mic)
            text = rec.recognize_google(audio)
            text = text.lower()

            #outputs the command to the python console for user debugging 
            print("You said "+text+"\n")

            #writes the command to the serial which is processed by arduino 
            ser.write(str.encode(text))
            
        #catch error if message is nonsensical    
        except sr.UnknownValueError:
            print("Audio could not be understood")
            
        
