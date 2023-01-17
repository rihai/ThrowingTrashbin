import numpy as np
import cv2
import time
import random

import RPi.GPIO as GPIO

import pygame


audio_files = ['Thanos.wav', 'Loki.wav']
pygame.mixer.init()
sound = pygame.mixer.Sound('/home/pi/trash_model/'+ audio_files[0])

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
green_upper = np.array([102,255,255],np.uint8)

video = cv2.VideoCapture(0)

def right_trash():
    print("correct")
    GPIO.output(rightTrash, GPIO.LOW)
    time.sleep(5)
    GPIO.output(rightTrash, GPIO.HIGH)
    time.sleep(10) # waits 45 seconds before contiuning
    return

def wrong_trash():
    print("DAMN IDIOT:D")
    GPIO.output(wrongTrash, GPIO.LOW)
    time.sleep(5)
    GPIO.output(wrongTrash,GPIO.HIGH)

    playing = sound.play()
    while playing.get_busy():
        pygame.time.delay(50)
    time.sleep(10) # waits 45 seconds before continuing
    return
    


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
            print("GREEEEEEN")
        

    contours, hierarchy = cv2.findContours(red_mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    print("before loop")
    for pic, contour in enumerate(contours):
        area = cv2.contourArea(contour)
        if(area>300): # adjust accordingly to camera perspective
            wrong_trash()
            #break
            print("REEeeeED")
            
        else:
            print("no red :(")
            #right_trash()
            #break
        break
