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
Feel free to submit any bug reports. I may not get to them in a timely manner since I am currently a student but when I get time, i'll be more than happy to fix them.
