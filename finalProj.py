from playsound import playsound
import keyboard ##make sure you install these libraries
import pygame
import os
import random

startVal = 0
##Flex values
flexOne = 0 #Thumb
flexTwo = 0 #Pointer and Middle
flexThree = 0 #Ring and Pinky
isExtended = [0,0,0] #0 is extended, 1 is not
wasExtended = [0,0,0] #used for comparison to check when to play sound

pointing = [] ##cat0
gun = [] ##cat1

##name = 03.mp3

#print (Flex[0])

## FLOT
import serial
Number = 0.0
Number2 = 0.0
Number3 = 0.0

ser = serial.Serial('COM6', baudrate = 9600, timeout=1)


##FLOT


def FindFile(name, path):
    for root, dirs, files in os.walk(path):
        if name in files:
            return os.path.join(root, name)

def AssignSounds():
    numSet = 0
    while(numSet < 7):
        namePoint = str(numSet) + ".mp3"
        pointing.append(FindFile(namePoint,"finalNoises/"))
        numSet = numSet + 1
    else:
        print(pointing)

AssignSounds()

def PlaySound(cat,rangeMin,rangeMax):
    randNum = random.randint(rangeMin,rangeMax)
    pygame.mixer.init()
    pygame.mixer.music.load(cat[randNum])
    pygame.mixer.music.play()

#def Playgun()
#    pygame.mixer.init()
#    pygame.mixer.music.load(cat[0])
#    pygame.mixer.music.play()


while(startVal == 0):

        arduinoData = ser.readline().decode('ascii')
        #arduinoData2 = ser.readline().decode('ascii')
        #arduinoData3 = ser.readline().decode('ascii')
        try:
            Number = float(arduinoData[0:3])
            Number2 = float(arduinoData[6:9])
            Number3 = float(arduinoData[12:15])
            #Number2 = arduinoData2
            #Number3 = arduinoData3
            print(Number)
            print(Number2)
            print(Number3)
            #print(Number)
            #print(" " + Number2)
            #print("  " + Number3)
            #print(Number2)
            #print(Number3)
        except:
            print(0)
            print(Number)
            print(Number2)
            print(Number3)


        flexOne = Number
        flexTwo = Number2
        flexThree = Number3

        #flexThree = flexThree + 1 #imagine this is the ring finger contracting

        if flexOne < 370:
            wasExtended[0] = 0
        else:
            wasExtended[0] = 1
        if flexTwo < 400:
            wasExtended[1] = 0
        else:
            wasExtended[1] = 1
        if flexThree < 50:
            wasExtended[2] = 0
        else:
            wasExtended[2] = 1

        print(wasExtended)
        print(isExtended)

        if wasExtended != isExtended:
            if flexOne < 370 and flexTwo < 400 and flexThree > 50:
                #PlaySound(pointing,6,7)
                print("gun cocked")
                isExtended = [0,0,1]
            if flexOne > 370 and flexTwo < 400 and flexThree > 50: ##Pointing
                if isExtended == [1,1,1]:
                    PlaySound(pointing,2,3)
                    print("from nothing")
                    isExtended = [1,0,1]
                else:
                    PlaySound(pointing,0,1) ##Fire Gun
                    print("BANG")
                    isExtended = [1,0,1]
            if flexOne < 370 and flexTwo > 400 and flexThree > 50: ##Thumbs up
                if isExtended == [1,1,1]:
                    PlaySound(pointing,4,5)
                    print("Thumbs Up")
                    isExtended = [0,1,1]
            if flexOne > 370 and flexTwo > 400 and flexThree > 50: ##All closed
                print("crunch")
                isExtended = [1,1,1]

        if keyboard.is_pressed('x'):
            startVal = 1

        ##print(arduinoData[0:3])
        ##print(len(arduinoData))
        ##print(float(Number))
