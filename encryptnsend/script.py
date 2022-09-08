import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
import sys


def send_email(filePath, recipient):

    try:
        with open(filePath) as f:
            attachment = MIMEText(f.read())
    except IOError:
        return "file doesn`t found"

    sender = "**********"  #here should be the mail from which the file is sent
    password = "************"  #there should be a password from the mail from which the file is sent

    server = smtplib.SMTP("smtp.gmail.com", 587)
    server.starttls()

    server.login(sender, password)

    msg = MIMEMultipart()
    attachment.add_header('content-disposition', 'attachment', filename="*******.txt") #here should be the name of the file that will be displayed on the mail
    msg["Subject"] = "Encrypted file" #subtitle may be changed
    msg.attach(attachment)

    server.sendmail(sender, recipient, msg.as_string())


if __name__ == '__main__':
    fileMessage = sys.argv[2]
    recipient = sys.argv[1]
    send_email(filePath=fileMessage, recipient=recipient)


