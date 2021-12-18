import serial
import time
import datetime
import csv
import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from datetime import datetime

first_run = True
previous_status = "OFF"

def get_status(data):
    if data.split(',')[2] == "1":
        return "ON"
    else:
        return "OFF"

arduino_port = "Your Port" #serial port of Arduino on mac will be similar to /dev/cu.usbmodem145101
baud = 9600 #arduino uno runs at 9600 baud
fileName="Your_CSV_file.csv" #name of the CSV file generated


ser = serial.Serial(arduino_port, baud)
print("Connected to Arduino port:" + arduino_port)
file = open(fileName, "a")
print("Created file")


# to send email
def send_email(status):
    me = "ac.control.arduino@gmail.com"
    my_password = r"ac12345678"
    you = "YourEmail@gmail.com"

    msg = MIMEMultipart('alternative')
    msg['Subject'] = "AC Alert"
    msg['From'] = me
    msg['To'] = you

    html = '<html><body><p>Hi, your AC is {status}!<br />AC status changed at: {timestamp}</p></body></html>'.format(status=status, timestamp=timestamp)
    part2 = MIMEText(html, 'html')

    msg.attach(part2)
    s = smtplib.SMTP_SSL('smtp.gmail.com')
    s.login(me, my_password)
    s.sendmail(me, you, msg.as_string())
    s.quit()

file = open(fileName, "w") #append the data to the file
file.write('created_at,field1,field2,field3')
file.write('\n')


samples = 10 #how many samples to collect
print_labels = False
line = 0 #start at 0 because our header is 0 (not real data)
while line <= samples:
    now = datetime.now()
    current_time = now.strftime("%Y-%m-%d %H:%M:%S") #if not work, try: ("%d-%m-%Y %H:%M:%S")
    timestamp=current_time
    
    getData=str(ser.readline())
    data=getData[0:][:-2]
    print(data)
    
	# to send only when the ac status changes, assume the first status will be ON
    if first_run:
        send_email(get_status(data))
        first_run=False
        previous_status = get_status(data)
    elif get_status(data) != previous_status:
        send_email(get_status(data))
        previous_status = get_status(data)


    if print_labels:
        if line==0:
            print("Printing Column Headers")
        else:
            print("Line " + str(line) + ": writing...")
   
    file = open(fileName, "a")
    file.write(timestamp + "," + data )
    file.write('\n')

    line = line+1
    time.sleep(1)

print("Data collection complete!")
file.close()