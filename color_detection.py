import numpy as np
import cv2
import time
import random

import RPi.GPIO as GPIO

import pygame


audio_files = ['Thanos.wav', 'satz1_v2.wav', 'satz1_v4.wav', 'satz2_v4.wav','satz3_v4.wav','satz4_v4.wav','satz5_v4.wav','satz6_v4.wav', 'satz7_v4.wav','satz8_v4.wav','satz9_v4.wav','satz10_v4.wav','satz1_v4.wav',  'satz21_v2.wav', 'satz15_v2.wav',  'satz30_v2.wav', 'satz8_v2.wav', 'satz25_v2.wav'] # add additional file names here
pygame.mixer.init()

def random_audio():
    rnd = random.randrange(0, len(audio_files))
    return audio_files[rnd]

sound = pygame.mixer.Sound('/home/pi/trash_model/'+ random_audio())#audio_files[0])

GPIO.setmode(GPIO.BOARD)
rightTrash = 12 # output pin pi
wrongTrash = 13 # output pin pi
GPIO.setup(rightTrash, GPIO.OUT)
GPIO.output(rightTrash, GPIO.HIGH)

GPIO.setup(wrongTrash,GPIO.OUT)
GPIO.output(wrongTrash,GPIO.HIGH)

red_lower = np.array([136,87,111], np.uint8)
red_upper = np.array([180,255,255], np.uint8)

green_lower = np.array([25,52,72],np.uint8)
green_upper = np.array([89,209,145],np.uint8) #[102,255,255]

#red_lower = np.array([136,87,111], np.uint8)
#red_upper = np.array([180,255,255], np.uint8)

#green_lower = np.array([25,52,72],np.uint8) # [25,52,72] #[77,255,190]
#green_upper = np.array([60,111,2],np.uint8) #[60,111,2]

video = cv2.VideoCapture(0)
#video.set(cv2.CAP_PROP_BUFFERSIZE, 1)

def right_trash():
    print("correct")
    GPIO.output(rightTrash, GPIO.LOW)
    time.sleep(5)
    GPIO.output(rightTrash, GPIO.HIGH)
    time.sleep(20) # waits 45 seconds before contiuning
    print("ready")
    return

def wrong_trash():
    print("DAMN IDIOT:D")
    GPIO.output(wrongTrash, GPIO.LOW)
    time.sleep(5)
    GPIO.output(wrongTrash,GPIO.HIGH)

    playing = sound.play()
    print("audio:", random_audio())
    while playing.get_busy():
        pygame.time.delay(50)
    time.sleep(20) # waits 45 seconds before continuing
    print("ready")
    return
    
def empty_framebuffer():
    video.read()
    video.read()
    video.read()
    video.read()
    video.read()
    video.read()
    video.read()
    video.read()
           

while(True):
    ret, frame = video.read()
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    
    red_mask= cv2.inRange(hsv, red_lower, red_upper)
    kernal = np.ones((5,5), "uint8")

    red_mask = cv2.dilate(red_mask,kernal)
    res_red = cv2.bitwise_and(frame, frame, mask = red_mask)

    green_mask = cv2.inRange(hsv, green_lower, green_upper)
    res_green = cv2.bitwise_and(frame, frame, mask = green_mask)

    contours, hierarchy = cv2.findContours(green_mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

    for pic, contour in enumerate(contours):
        area = cv2.contourArea(contour)
        if(area > 300):
            right_trash()
            #print("GREEEEEEN")
            empty_framebuffer()
        
    contours, hierarchy = cv2.findContours(red_mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
   # print("before loop")
    for pic, contour in enumerate(contours):
        area = cv2.contourArea(contour)
        if(area>300): # adjust accordingly to camera perspective
            wrong_trash()
            #break
            #print("REEeeeED")
            empty_framebuffer()
            
        else:
            print("no red :(")
            #right_trash()
            #break
           # empty_framebuffer()
        break