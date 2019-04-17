# this is the first version
this project is to run a Raspberry PI as an audio device. The device is able to
do 2 functions: as a sound collector and as a test-tone generator.
Table of Content
        1. Configuration Instructions
        2. Installation Instructions
        3. Operating Instructions
        4. File list (Mainfest)
        5. Copyright/ Copyleft
        6. Contact Information
        7. Credits and Acknowledgements

1. Configuration Instructions

The application is running on a Raspberry Pi 3 model B. This Pi should
come with a USB sound card, a network connection, a microphone.

1.1 Configure USB sound card as default audio device

First of all,we have to change the default audio device to be USB
sound card1.Because,RPi onboard sound card doesn’t have microphone interface. 

Boot up RPi, and apply the USB sound card.Use “lsusb” command to check
if your USB sound card is mounted.

Use “sudo nano /etc/asound.conf”command and put following content to
the file

pcm.!default {
  type plug
  slave {
    pcm "hw:1,0"
  }
}
ctl.!default {
    type hw
    card 1
}

After that, go to your home directory. Use “nano .asoundrc” command and
put the same content to the file.
Then, run “alsamixer”command. You should be able to see that USB sound card is the default audio device. For a more sensitive sound detection, it is better
 to maximize the volume of “Mic”.
