#!/usr/bin/env python3
import serial
import cv2



if len(objects) > 0:
    for x, y, w, h in objects:
        object_center_x = x + w // 2
        object_center_y = y + h // 2

        frame_center_x = frame.shape[1] // 2
        frame_center_y = frame.shape[0] // 2
        if object_center_x < frame_center_x - 50:
            condition1 = True
        elif object_center_x > frame_center_x + 50:
            conditon2 = True
        elif object_center_y < frame_center_y - 50:
            condition3 = True
        elif object_center_y > frame_center_y - 50:
            condition4 = True
        else:
            condition1, conditon2, conditon3, conditon4 = False
            condition5 = True

frame_height, frame_width = frame.shape[:2]
frame_center = (frame_width // 2, frame_height // 2)

cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 0, 0), 2)
cv2.circle(frame, (object_center_x, object_center_y), 5, (0, 0, 255), -1)
cv2.imshow("object detection", frame)


def perform_action():
    print("Action triggered! 'w' sent.")
    data = "W"
    serial.write(data.encode())

serial.write
def perform_action2():
    print("Action Trigeered! 'S' was sent.")
    data1 = "S"
    serial.write(data1.encode())


def perform_action3():
    print("Action Triggered! 'A' was sent.")
    data2 = "A"
    serial.write(data2.encode())


def perform_action4():
    print("Action Triggered! 'E' was sent.")
    data3 = "E"
    serial.write(data3.encode())


try:
    print("Looking for data to trigger Action...")
    while True:
        if condition1:
            perform_action()
        if conditon2:
            perform_action2()
        if condition3:
            perform_action3()
        if condition4:
            perform_action4()
except KeyboardInterrupt:
    print("Exiting...")
finally:
    uart.close()  # Close the serial connection when done
