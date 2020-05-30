# Hikvision Decrypter
A simple cross platform program written in C++ used for decrypting the configuration files created by Hikvision Security Cameras for extracting user credentials and other data. This is the successor to my somewhat popular dirty script I made over a year ago called [hikvision-xor-decrypter](https://github.com/wormchickenwizard/hikvision-xor-decrypter) that did the xor decryption of the halfway decrypted configuration files.

**[Get the latest binary from the releases tab](https://github.com/WormChickenWizard/hikvision-decrypter/releases)**

## Compilation

Libraries Used (and Specific Versions):  
[wxWidgets](https://www.wxwidgets.org/) ([3.1.3](https://github.com/wxWidgets/wxWidgets/releases/download/v3.1.3/wxWidgets-3.1.3.zip))  
[SergyBel's AES implementation](https://github.com/SergeyBel/AES)  

Programs:  
[Visual Studio 2019](https://visualstudio.microsoft.com/downloads/) 

Define/Modify the following system environment variables:  
WXWIN - Points to the root of the wxWidgets library folder

## Usage
In order to use this program, you first must obtain a camera's configuration file. If the camera is running firmware 5.4.4 or below, you can use the following url to retrieve it.  
```http://camera.ip/System/configurationFile?auth=YWRtaW46MTEK```  
One you obtain the configuration file, simply load it into the program, decrypt it, and save it.Then you can use a hex editor to search for the passwords. At some point, I would like to implement the ability to read and edit the database from inside of the program.

## Bugs
Feel free to submit any bug reports. I may not get to them in a timely manner since I am currently a student (Kinda like this program I said I was going to make on the old repo :laughing:) but when I get time, i'll be more than happy to fix them.

## Backstory
So I (WormChickenWizard) created the original script when I was a senior in high school and our IT guy had installed a bunch of Advidia security cameras a couple of years prior. Me being me, I had to get access to them. Nothing had been VLAN'd off so I was able to login to them with the default credentials. He found out a few months later and changed the passwords so I started searching the internet for some known vulnerabilities. I found out that you could dump the config file with the method in the "Usage" section. Luckily the firmware that the cameras used were vulnerable to that exploit so I was able to dump and decrypt half of the config files with the openssl command using a static key. The other half I decrypted with the hikvision-xor-decrypter script I created that iterated over the file's content stored as a byte array performing an xor operation. That would then return the final output that could be analyzed with a hex editor or potentially viewed with a database viewer (If anybody knows what the type of database it is, please let me know. I'd like to incorporate viewing/editing of the database inside the program in the future). If the ol' IT guy, "Big Brother", sees this, I made it just for your gentle torment and to facilitate the current students' masochism :stuck_out_tongue_closed_eyes:
