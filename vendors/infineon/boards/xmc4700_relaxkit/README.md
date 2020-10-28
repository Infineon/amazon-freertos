# Getting Started with the Infineon XMC4700 Relax Kit and OPTIGA Trust X/M

This tutorial provides instructions for getting started with the Infineon XMC4700 Relax Kit in various configurations, namely:
1. Without Secure Element
2. with OPTIGA Trust X Secure Element
3. With OPTIGA Trust M Secure Element

You need the following hardware:

1. [Infineon XMC4700 Relax Kit](https://www.infineon.com/cms/en/product/evaluation-boards/kit_xmc47_relax_v1/)
2. [Infineon MyIoT Adapter](https://www.infineon.com/cms/en/product/evaluation-boards/my-iot-adapter/)
3. Secure Elements:
  1. [Shield2Go Security OPTIGA™ Trust X](https://www.infineon.com/cms/en/product/evaluation-boards/s2go-security-optiga-x/) (optional)
  2. [Shield2Go Security OPTIGA™ Trust M](https://www.infineon.com/cms/en/product/evaluation-boards/s2go-security-optiga-m/) (optional)

Before you begin, you must configure AWS IoT and your FreeRTOS download to connect your device to the AWS Cloud\. For instructions, see [Option \#2: Onboard Private Key Generation](https://docs.aws.amazon.com/freertos/latest/userguide/dev-mode-key-provisioning.html)\. In this tutorial, the path to the FreeRTOS download directory is referred to as `<freertos>`\.

## Overview<a name="getting_started_infineon_trust_m_overview"></a>

This tutorial contains the following steps:

1. Connecting your board to a host machine.

1. Install software on the host machine to develop and debug embedded applications for your microcontroller board\.

1. Cross\-compile a FreeRTOS demo application to a binary image\.

1. Load the application binary image to your board, and then run the application\.

1. For monitoring and debugging purposes, interact with the application running on your board across a serial connection\.

## Hardware setup

The following diagram give a detailed description of the board hardware

![alt text](docs/PCB_block.png)

To set up the XMC4700 RelaxKit + Optiga Trust X/M:

1. Connect your computer to the Debugger Micro USB port on your XMC4700 RelaxKit. The On-board USB debug probe is used to program the board and provides Virtual COM Port support for logging purposes.

1. Connect a router or internet-connected Ethernet port to the Ethernet on your XMC4700 RelaxKit.

1. Plug the Infineon MyIoT Adapter in the Arduino Pin Header

1. Plug the Shield2Go Security OPTIGA™ Trust X/M in Socket 3 of the Infineon MyIoT Adapter

Note: if you don't want to use a SE, you can skip the last step.

![alt text](docs/hardware_setup.png)

## Set up Your Development Environment<a name="infineon_trust_m_setup_env"></a>

FreeRTOS uses Infineon's DAVE development environment to program the XMC4700\. Before you begin, download and install DAVE and some J\-Link drivers to communicate with the on\-board debugger\.

### Install DAVE<a name="infineon_trust_m_install_dave"></a>

1. Go to Infineon's [DAVE software download](https://infineoncommunity.com/dave-download_ID645) page\.

1. Choose the DAVE package for your operating system and submit your registration information\. After you register, you should receive a confirmation email with a link to download a \.zip file\.

1. Download the DAVE package \.zip file \(`DAVE_version_os_date.zip`\), and unzip it to the location where you want to install DAVE \(for example, `C:\DAVE4`\)\. 
**Note**  
Some Windows users have reported problems using Windows Explorer to unzip the file\. We recommend that you use a third\-party program such as 7\-Zip\.

1. To launch DAVE, run the executable file found in the unzipped `DAVE_version_os_date.zip` folder\.

For more information, see the [DAVE Quick Start Guide](https://www.infineon.com/dgdl/Infineon-DAVE_Quick_Start-GS-v02_00-EN.pdf?fileId=5546d4624cb7f111014d059f7b8c712d) and visit [DAVE Forum](https://www.infineonforums.com/threads/6212-Install-DAVE%C2%99-IDE-for-XMC%C2%99-microcontrollers)\. 

### Install Segger J\-Link Drivers<a name="infineon_trust_m_install_jlink"></a>

To communicate with the XMC4700 Relax Kit's on\-board debugging probe, you need the drivers included in the J\-Link Software and Documentation pack\. You can download the J\-Link Software and Documentation pack from Segger's [J\-Link software download](https://www.segger.com/downloads/jlink/#J-LinkSoftwareAndDocumentationPack) page\.

### Establishing a serial connection
To establish a serial connection between your host machine and your board

1. Identify the USB serial port number for the connection to the board on your host computer.
2. Start a serial terminal and open a connection with the following settings:
   * Baud rate: 115200
   * Data: 8 bit
   * Parity: None
   * Stop bits: 1
   * Flow control: None

For more information about installing a terminal and setting up a serial connection, see [Installing a terminal emulator](https://docs.aws.amazon.com/freertos/latest/userguide/uart-term.html). 

## Build and Run the FreeRTOS Demo Project<a name="infineon_trust_m_build_and_run_example"></a>

### Import the FreeRTOS Demo into DAVE<a name="infineon_trust_m_freertos_import-project"></a><a name="infineon_trust_m_load_project"></a>

1. Start DAVE\.

1. In DAVE, choose **File**, and then choose **Import**\. Expand the **Infineon** folder, choose **DAVE Project**, and then choose **Next**\.

1. In the **Import DAVE Projects** window, choose **Select Root Directory**, choose **Browse**, and then choose the XMC4700 demo project\.

   In the directory where you unzipped your FreeRTOS download, the demo project is located in `<freertos>/projects/infineon/xmc4700_relaxkit/dave4/aws_demos`\.

   Make sure that **Copy Projects Into Workspace** is cleared\.

1. Choose **Finish**\.

   The `aws_demos` project should be imported into your workspace and activated\.

1. Follow the **Initial Configuration** and **Demo Project Configuration** steps in [Option \#2: Onboard Private Key Generation](https://docs.aws.amazon.com/freertos/latest/userguide/dev-mode-key-provisioning.html)\.

1. From the **Project** menu, choose **Build Active Project**\. 

   Make sure that the project builds without errors\.

1. From **Project Explorer**, right\-click `aws_demos`, choose **Debug As**, and then choose **DAVE C/C\+\+ Application**\.

1. Double\-click **GDB SEGGER J\-Link Debugging** to create a debug confirmation\. Choose **Debug**\.

1. When the debugger stops at the breakpoint in `main()`, from the **Run** menu, choose **Resume**\.

1. In the serial terminal you should see something similar to below snapshot. Follow now the remaining steps in [Option \#2: Onboard Private Key Generation](https://docs.aws.amazon.com/freertos/latest/userguide/dev-mode-key-provisioning.html)\.

```
0 313 [] Warning: the client certificate should be updated. Please see https://aws.amazon.com/freertos/getting-started/.
1 313 [] Device public key, 91 bytes:
3059 3013 0607 2a86 48ce 3d02 0106 082a
8648 ce3d 0301 0703 4200 040a bee9 8c39
c7f5 f042 1e66 97ed 5c96 12dd 2531 5d88
f367 5ee5 3f8b fd2b bc14 7202 f51e e908
a614 c437 99aa b2a7 7554 55eb d2a3 463d
c099 c33f 88e6 1a78 0dcd a5
```

### Run the FreeRTOS Demo Project<a name="infineon_trust_m_run_examples"></a>

Once the new client certificate is ACTIVE and associated with a thing and a policy, run the MQTT Hello World demo again. This time, the connection to the AWS IoT MQTT broker will succeed. 

1. From the **Project** menu, choose **Rebuild Active Project** to rebuild `aws_demos` and confirm that your configuration changes are picked up\.

1. From **Project Explorer**, right\-click `aws_demos`, choose **Debug As**, and then choose **DAVE C/C\+\+ Application**\.

1. Double\-click **GDB SEGGER J\-Link Debugging** to create a debug confirmation\. Choose **Debug**\.

1. When the debugger stops at the breakpoint in `main()`, from the **Run** menu, choose **Resume**\.

Through the device's serial connection, you should see something like this on the UART output:

```
0 0 [Tmr Svc] Starting key provisioning...
1 1 [Tmr Svc] Write root certificate...
2 4 [Tmr Svc] Write device private key...
3 82 [Tmr Svc] Write device certificate...
4 86 [Tmr Svc] Key provisioning done...
5 291 [Tmr Svc] Wi-Fi module initialized. Connecting to AP...
.6 8046 [Tmr Svc] Wi-Fi Connected to AP. Creating tasks which use network...
7 8058 [Tmr Svc] IP Address acquired [IP Address]
8 8058 [Tmr Svc] Creating MQTT Echo Task...
9 8059 [MQTTEcho] MQTT echo attempting to connect to [MQTT Broker].
...10 23010 [MQTTEcho] MQTT echo connected.
11 23010 [MQTTEcho] MQTT echo test echoing task created.
.12 26011 [MQTTEcho] MQTT Echo demo subscribed to iotdemo/#
13 29012 [MQTTEcho] Echo successfully published 'Hello World 0'
.14 32096 [Echoing] Message returned with ACK: 'Hello World 0 ACK'
.15 37013 [MQTTEcho] Echo successfully published 'Hello World 1'
16 40080 [Echoing] Message returned with ACK: 'Hello World 1 ACK'
.17 45014 [MQTTEcho] Echo successfully published 'Hello World 2'
.18 48091 [Echoing] Message returned with ACK: 'Hello World 2 ACK'
.19 53015 [MQTTEcho] Echo successfully published 'Hello World 3'
.20 56087 [Echoing] Message returned with ACK: 'Hello World 3 ACK'
.21 61016 [MQTTEcho] Echo successfully published 'Hello World 4'
22 64083 [Echoing] Message returned with ACK: 'Hello World 4 ACK'
.23 69017 [MQTTEcho] Echo successfully published 'Hello World 5'
.24 72091 [Echoing] Message returned with ACK: 'Hello World 5 ACK'
.25 77018 [MQTTEcho] Echo successfully published 'Hello World 6'
26 80085 [Echoing] Message returned with ACK: 'Hello World 6 ACK'
.27 85019 [MQTTEcho] Echo successfully published 'Hello World 7'
.28 88086 [Echoing] Message returned with ACK: 'Hello World 7 ACK'
.29 93020 [MQTTEcho] Echo successfully published 'Hello World 8'
.30 96088 [Echoing] Message returned with ACK: 'Hello World 8 ACK'
.31 101021 [MQTTEcho] Echo successfully published 'Hello World 9'
32 104102 [Echoing] Message returned with ACK: 'Hello World 9 ACK'
.33 109022 [MQTTEcho] Echo successfully published 'Hello World 10'
.34 112047 [Echoing] Message returned with ACK: 'Hello World 10 ACK'
.35 117023 [MQTTEcho] Echo successfully published 'Hello World 11'
36 120089 [Echoing] Message returned with ACK: 'Hello World 11 ACK'
.37 122068 [MQTTEcho] MQTT echo demo finished.
38 122068 [MQTTEcho] ----Demo finished----
```

#### Build the FreeRTOS Demo with CMake<a name="infineon_trust_m_cmake"></a>

This section covers using CMake on Windows with MingW as the native build system\. For more information about using CMake with other operating systems and options, see [Using CMake with FreeRTOS](https://docs.aws.amazon.com/freertos/latest/userguide/getting-started-cmake.html)\.

If you prefer not to use an IDE for FreeRTOS development, you can use CMake to build and run the demo applications or applications that you have developed using third\-party code editors and debugging tools\.

**To build the FreeRTOS demo with CMake**

1. Set up the GNU Arm Embedded Toolchain\.

   1. Download a Windows version of the toolchain from the [Arm Embedded Toolchain download page](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)\. 
**Note**  
Due to [a bug reported](https://bugs.launchpad.net/gcc-arm-embedded/+bug/1810274) in the objcopy utility, we recommend that you download a version other than "8\-2018\-q4\-major\."

   1. Open the downloaded toolchain installer, and follow the instructions in the wizard\.

   1. On the final page of the installation wizard, select **Add path to environment variable** to add the toolchain path to the system path environment variable\.

1. Install CMake and MingW\.

   For instructions, see [CMake Prerequisites](https://docs.aws.amazon.com/freertos/latest/qualificationguide/building-cmake-prereqs.html)\.

1. Create a folder to contain the generated build files \(*<BUILD\_FOLDER>*\)\. 

1. Change directories to your FreeRTOS download directory \(`<freertos>`\), and use the following command to generate the build files:

   ```
   cmake -DVENDOR=infineon -DBOARD=xmc4700_relaxkit -DCOMPILER=arm-gcc -S . -B <BUILD_FOLDER> -G "MinGW Makefiles" -DAFR_ENABLE_TESTS=0
   ```

1. Change directories to the build directory \(*<BUILD\_FOLDER>*\), and use the following command to build the binary:

   ```
   cmake --build . --parallel 8
   ```

   This command builds the output binary `aws_demos.hex` to the build directory\.

1. Flash and run the image with [JLINK](https://www.segger.com/downloads/jlink/#J-LinkSoftwareAndDocumentationPack)\.

   1. From the build directory \(*<BUILD\_FOLDER>*\), use the following commands to create a flash script:

      ```
      echo loadfile aws_demos.hex > flash.jlink
      echo r >> flash.jlink
      echo g >> flash.jlink
      echo q >> flash.jlink
      ```

   1. Flash the image using the JLNIK executable\.

      ```
      <JLINK_PATH>\JLink.exe  -device XMC4700-2048 -if SWD -speed auto -CommanderScript flash.jlink
      ```

      The application logs should be visible through [ the serial connection](#establishing-a-serial-connection) that you established with the board\. Continue to the public key extraction step in [Option \#2: Onboard Private Key Generation](https://docs.aws.amazon.com/freertos/latest/userguide/dev-mode-key-provisioning.html)\. After all the steps are complete, go to the AWS IoT console\. The MQTT client you set up previously should display the MQTT messages sent by your device\. 

### Troubleshooting<a name="infineon_trust_m_troubleshooting"></a>

For general troubleshooting information, see [Troubleshooting Getting Started](https://github.com/awsdocs/aws-freertos-docs/blob/master/doc_source/userguide/gsg-troubleshooting.md)\.


## Monitoring MQTT Messages on the Cloud<a name="infineon_trust_m_monitoring"></a>

You can use the MQTT client in the AWS IoT console to monitor the messages that your device sends to the AWS Cloud\. You might want to set this up before the device runs the demo project\.

**To subscribe to the MQTT topic with the AWS IoT MQTT client**

1. Sign in to the [AWS IoT console](https://console.aws.amazon.com/iotv2/)\.

1. In the navigation pane, choose **Test** to open the MQTT client\.

1. In **Subscription topic**, enter **iotdemo/\#**, and then choose **Subscribe to topic**\.
