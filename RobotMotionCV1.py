#!/usr/bin/python
#!/usr/bin/python
"""
This program is demonstration for face and object detection using haar-like features.
The program finds faces in a camera image or video stream and displays a red box around them.
  
Original C implementation by:  ?
Python implementation by: Roman Stanchak, James Bowman
"""

import cv2.cv as cv
import serial
  
AX_COMNUM = 4  # COM5: com number - 1
XL_COMNUM = 5  # COM6: com number - 1

# count face detected frames in serial frames
SumFDFrames = 0 
# flag to control sending message to mcu
face_flag = 1
flag = 1  
  
min_size = (20, 20)
image_scale = 2
haar_scale = 1.2
min_neighbors = 2
haar_flags = 0
  
def detect_and_draw(img, cascade):
    global SumFDFrames    
    global face_flag
    global flag
    # allocate temporary images
    gray = cv.CreateImage((img.width,img.height), 8, 1)
    small_img = cv.CreateImage((cv.Round(img.width / image_scale),
                   cv.Round (img.height / image_scale)), 8, 1)
  
    # convert color input image to grayscale
    cv.CvtColor(img, gray, cv.CV_BGR2GRAY)
  
    # scale input image for faster processing
    cv.Resize(gray, small_img, cv.CV_INTER_LINEAR)
  
    cv.EqualizeHist(small_img, small_img)
  
    if(cascade):
        t = cv.GetTickCount()
        faces = cv.HaarDetectObjects(small_img, cascade, cv.CreateMemStorage(0),
                                     haar_scale, min_neighbors, haar_flags, min_size)
        t = cv.GetTickCount() - t
        print "detection time = %gms" % (t/(cv.GetTickFrequency()*1000.))
        if faces:
            for ((x, y, w, h), n) in faces:
                # the input to cv.HaarDetectObjects was resized, so scale the
                # bounding box of each face and convert it to two CvPoints
                pt1 = (int(x * image_scale), int(y * image_scale))
                pt2 = (int((x + w) * image_scale), int((y + h) * image_scale))
                cv.Rectangle(img, pt1, pt2, cv.RGB(255, 0, 0), 3, 8, 0)
                
            # count number of face detected frames
            SumFDFrames = SumFDFrames + 1
            
            if SumFDFrames > 1 and SumFDFrames < 30:
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
  
    cv.ShowImage("result", img)
  
if __name__ == '__main__':
  
   
    

    
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
    

  
 
    cascade = cv.Load("haarcascades/haarcascade_frontalface_alt_tree.xml")
  
    capture = cv.CreateCameraCapture(0)
    
    cv.SetCaptureProperty(capture,cv.CV_CAP_PROP_FRAME_WIDTH,360)
    cv.SetCaptureProperty(capture,cv.CV_CAP_PROP_FRAME_HEIGHT,240)
  
    cv.NamedWindow("result", 1)
  

    frame_copy = None
    while True:
        frame = cv.QueryFrame(capture)
        if not frame:
            cv.WaitKey(0)
            break
        if not frame_copy:
            frame_copy = cv.CreateImage((frame.width,frame.height),
                                        cv.IPL_DEPTH_8U, frame.nChannels)
        if frame.origin == cv.IPL_ORIGIN_TL:
            cv.Copy(frame, frame_copy)
        else:
            cv.Flip(frame, frame_copy, 0)
  
        detect_and_draw(frame_copy, cascade)
  
        key = cv.WaitKey(10)
        # press esc -> exit
        if key == 27:
            if not TestRunWithoutCOM:
                if cm900_com.isOpen():
                    cm900_com.close()
 
                if cm904_com.isOpen():
                    cm904_com.close()
                print 'closing'
                
            cv.DestroyWindow("result")
            break