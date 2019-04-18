# Application Development I-IT1-N3
==================================
*This project is to run a Raspberry PI as an audio device. The device is able to
do 2 functions: as a sound collector and as a test-tone generator.
##Table of Content
        1. Configuration Instructions
        2. Installation Instructions
        3. Operating Instructions
        4. File list (Mainfest)
        5. Copyright/ Copyleft
        6. Contact Information
        7. Credits and Acknowledgements

##1. Configuration Instructions

*The application is running on a Raspberry Pi 3 model B. This Pi should
*come with a USB sound card, a network connection, a microphone.

###1.1 Configure USB sound card as default audio device

####1.1.a Hardware configuration

*First of all,we have to change the default audio device to be USB
*sound card.Because,RPi onboard sound card doesn’t have microphone interface. 

*Boot up RPi, and apply the USB sound card.Use “lsusb” command to check
*if your USB sound card is mounted.

*Use “sudo nano /etc/asound.conf”command and put following content to
*the file
```
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
```
*After that, go to your home directory. Use “nano .asoundrc” command and
*put the same content to the file.
*Then, run “alsamixer”command. You should be able to see that USB sound card is the default audio device. For a more sensitive sound *detection, it is better
*to maximize the volume of “Mic”.

####1.1.b Software configuration
 
*This program require alsa-utils 1.0.25 if your system is using the 1.0.28 version, it is recommended to downgrade to the 1.0.24 version *in order to avoid bugs.
 
*To downgrade alsa-ultis, follow these instructions:
	*Use “sudo nano /etc/apt/sources.list” command and add the last line
	*Run “sudo apt-get update
	*Run “sudo aptitude versions alsa-utils” to check if version 1.0.25 of alsa-util is available:
	*Run “sudo apt-get install alsa-utils=1.0.25-4” to downgrade.
	*Reboot (if necessary)
 
*To make sure alsa-ultils installation was ready:
	*Run “arecord -r44100 -c1 -f S16_LE -d5 test.wav” to test that your microphone is working. You should see a “test.wav” file in         *the current folder.
	*Put earphone on. Run “aplay test.wav” to check that your recording is okay.
 
*This program also requrie libcurl library To install libcurl, follow these instructions:
	*First use command “ls /usr/include/curl” to identify that /usr/include/curl/ folder exists or not.
	*If the folder doesn’t exist. Run “sudo apt-get update” to update the application list.
	*Run “sudo apt-get install libcurl3” to install the libcurl3.
	*Run “sudo apt-get install libcurl4-openssl-dev” to install the development API of libcurl4.

##2. Installtion Instructions
	*Connect the Raspberry Pi 3 device to Ethernet cable with internet
	*Insert the microSD card containing the Sound Level project to the
	*Rasberry Pi device
	*Attach the USB sound card to one USB port in the Rasberry Pi device
	*Connect the microphone to the right microphone slot in the sound card
	*Turn on the Raspberry Pi device by connecting it to the power supply
	*Make sure the sound card and microphone are all turned on
	*Watch the internet connection if successfully established as the LAN LED on the Raspberry Pi blinks.

##3. Operating Instructions
	*Check the IP address of the Raspberry Pi enclosed in an email sent to configured email address inbox
	*Access to Raspberry Pi by logging in with its IP address and personal account
	*The source code can be obtain from github by the command: git pull https://github.com/SaberPhung/-kieuphong
        *Once the source code has been downloaded, open the file comm.h to edit the url to your own receiving php file:
        *#define URL "http://www.cc.puv.fi/~e1800920/sound.php" (change to your account and your php file)
        *Then use the command make to automatically compile the program: make
        *Run the program with command ./sound.out
	*See the results displayed on the computer screen
##4.File List
	*C-language source code files: main.c, screen.c, sound.c, comm.c
	*C-language library files: screen.h, sound.h, comm.h
	*Information files: README.md
	*Compiling file: makefile
##5.Copyright And License
	*Copyright (c) 2019, Phung Nguyen Quynh Giao
	*Permission is granted to copy, distribute and/or modify this document under the terms of the GNU Free Documentation License, 		*Version 1.3
	*or any later version published by the Free Software Foundation, with no Invariant Sections, no Front-Cover Texts, and no Back-		*Cover Texts.
##6.Contact Information
	*Name:Nguyen Quynh Giao Phung
	*Instituition:Vaasa University of Applied Sciences
	*Address:Woffintie 30, Vaasa 65100, Finland
	*Student Webpage:www.cc.puv.fi/~e1800920
	*Email:phgiao408@gmail.com
	*Mobile: +358 465 715 538
##7.Credis And Acknowledgements
	*This program will complete with the help of PhD Gao Chao
