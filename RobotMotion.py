# -*- coding: utf-8 -*-
"""
Created on Mon Jan 19 21:07:30 2015

@author: shimba

http://www.janeriksolem.net/2014/05/how-to-calibrate-camera-with-opencv-and.html

Space key: save image
ESC key: exit

"""

# -*- coding: utf-8 -*-

# base camera: Left one

import numpy as np
import cv2
import serial

AX_COMNUM = 4  # COM5: com number - 1
XL_COMNUM = 5  # COM6: com number - 1

cascade_path = "haarcascades/haarcascade_frontalface_alt_tree.xml"

cascade = cv2.CascadeClassifier(cascade_path)
color = (0, 0, 255) #白
 
# copy parameters to arrays
K = np.array([[2.6464323304785165e+002, 0, 3.3791136676498763e+002], [0, 2.6409855795950494e+002, 2.2906319549080325e+002], [0, 0, 1]])
d = np.array([-5.6834334127630226e-001, 2.6883985894325729e-001, -8.2054230747011204e-004, 7.8395208461409609e-004, 2.8962461363950861e-002, -2.5035352954873352e-001, 6.4862553670382905e-002, 1.2689653440493187e-001]) # just use first two terms (no translation) 
h, w = 480, 640



def main():
    # カメラ映像の取得
    cap_l = cv2.VideoCapture(0)
    
    # count face detected frames in serial frames
    SumFDFrames = 0    
    

    
    # open serial connection
    try:
        cm900_com = serial.Serial(AX_COMNUM, baudrate = 96000)
    except serial.serialutil.SerialException:
        cm900_com = None

    try:
        cm904_com = serial.Serial(XL_COMNUM, baudrate = 96000)
    except serial.serialutil.SerialException:
        cm904_com = None

    TestRunWithoutCOM = False
    #if TestRunWithoutCOM:
    if cm900_com == None:
        TestRunWithoutCOM = True
        #if cm900_com.isOpen():
            #cm900_com.close()
        if cm904_com != None:
            if cm904_com.isOpen():
                cm904_com.close()
        print 'test run 1'

    if cm904_com == None:
        TestRunWithoutCOM = True
        #if cm904_com.isOpen():
            #cm904_com.close()
        if cm900_com != None:
            if cm900_com.isOpen():
                cm900_com.close()
        print 'test run 2'
        
    

    
    useSerial = False        
    if cm900_com != None and cm904_com != None:
        if cm900_com.isOpen() and cm904_com.isOpen():
            useSerial = True
    
    # flag to control sending message to mcu
    face_flag = 1
    flag = 1
    
    while(1):
        ret_l, im_l = cap_l.read()
        
        # undistort
        newcamera, roi = cv2.getOptimalNewCameraMatrix(K, d, (640,480), 0)
        newim_l = cv2.undistort(im_l, K, d, None, newcamera)

        grayim_l = cv2.cvtColor(newim_l, cv2.cv.CV_BGR2GRAY)

        # Face detection
        facerect = cascade.detectMultiScale(grayim_l, scaleFactor=1.1, minNeighbors=1, minSize=(1, 1))
        
        if len(facerect) > 0:
            flag = 1
            #検出した顔を囲む矩形の作成
            for rect in facerect:
                cv2.rectangle(newim_l, tuple(rect[0:2]),tuple(rect[0:2]+rect[2:4]), color, thickness=2)
            
            # count number of face detected frames
            SumFDFrames = SumFDFrames + 1
            
            if SumFDFrames > 10 and SumFDFrames < 30:
                if face_flag == 1 and useSerial:
                    cm900_com.write('b0200')
                    cm904_com.write('b0200')
                face_flag = 0
            elif SumFDFrames == 30:
                face_flag = 1
                
            if SumFDFrames > 30 and SumFDFrames < 60:
                if face_flag == 1 and useSerial:
                    cm900_com.write('c0001')
                    cm904_com.write('c0001')
                face_flag = 0
            elif SumFDFrames == 60:
                face_flag = 1
            
            if SumFDFrames > 60:
                if face_flag == 1 and useSerial:
                    cm900_com.write('d0001')
                    cm904_com.write('d0001')
                face_flag = 0        
            
        else:
            if flag == 1 and useSerial:
                cm900_com.write('a1023')
                cm904_com.write('a1023')
            SumFDFrames = 0
            flag = 0
       
        # show face detection result
        cv2.imshow("Camera Test Left", newim_l)
        
        
        key = cv2.waitKey(10)
        # press esc -> exit
        if key == 27:
            if not TestRunWithoutCOM:
                if cm900_com.isOpen():
                    cm900_com.close()
 
                if cm904_com.isOpen():
                    cm904_com.close()
                print 'closing'
                
            cap_l.release()
            cv2.destroyAllWindows()
            break        
 
if __name__ == '__main__':
    main()