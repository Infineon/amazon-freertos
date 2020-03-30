__This repository is a forked version of the main FreeRTOS github [repo](https://github.com/aws/amazon-freertos/).
It focuses on helping to integrate the OPTIGA Trust X and M embedded security solutions.__

## Cloning
This repo uses [Git Submodules](https://git-scm.com/book/en/v2/Git-Tools-Submodules) to bring in dependent components.

Note: If you download the ZIP file provided by GitHub UI, you will not get the contents of the submodules. (The ZIP file is also not a valid git repository)

To clone using HTTPS:
```
git clone https://github.com/aws/amazon-freertos.git --recurse-submodules
```
Using SSH:
```
git clone git@github.com:aws/amazon-freertos.git --recurse-submodules
```

If you have downloaded the repo without using the `--recurse-submodules` argument, you need to run:
```
git submodule update --init --recursive
```

To checkout the branch with both Trust X and Trust M, you need to run:
```
git checkout feature/trustm
```

## Getting Started

For more information on FreeRTOS, refer to the [Getting Started section of FreeRTOS webpage](https://aws.amazon.com/freertos).

To directly access the **Getting Started Guide** for supported hardware platforms, click the corresponding link in the Supported Hardware section below.

For detailed documentation on FreeRTOS, refer to the [FreeRTOS User Guide](https://aws.amazon.com/documentation/freertos).

## Supported Hardware

For additional boards that are supported for FreeRTOS, please visit the [AWS Device Catalog](https://devices.amazonaws.com/search?kw=freertos)

The following MCU boards are supported for FreeRTOS:

1. **Infineon** - [Infineon XMC4800 IoT Connectivity Kit](https://www.infineon.com/connectivitykit)
    * [Getting Started Guide](https://docs.aws.amazon.com/freertos/latest/userguide/getting_started_infineon.html)
    * [Getting Started Guide for Trust X](https://docs.aws.amazon.com/freertos/latest/userguide/getting_started_infineon_trust_x.html)
    * [Getting Started Guide for Trust M rev.1](https://github.com/Infineon/amazon-freertos-optiga-trust/tree/feature/trustm/vendors/infineon/boards/xmc4800_plus_optiga_trust_m)
    * IDE: [DAVE](https://infineoncommunity.com/dave-download_ID645)


## amazon-freeRTOS/projects
The ```./projects``` folder contains the IDE test and demo projects for each vendor and their boards. The majority of boards can be built with both IDE and cmake (there are some exceptions!). Please refer to the Getting Started Guides above for board specific instructions.

## Porting guide to enable Trust M on your FreeRTOS compatible board

IF you want to port Trust X/M onto any board listed [here](https://github.com/Infineon/amazon-freertos-optiga-trust/tree/feature/trustm/vendors), you can follow the steps below. The OPTIGA Trust X/M integrates into FreeRTOS comaptible board in three points, namely:
1) **PKCS#11 Interface integration**. It doesn't require any further porting. As soon as you FreeRTOS board is compatile to version 201910 and above the PKCS#11 interface can be taken as it is. You can read more about this [here](https://github.com/Infineon/amazon-freertos-optiga-trust/tree/feature/trustm/libraries/abstractions/pkcs11).
2) **mbedTLS TLS protocol implementation**. mbedTLS is a crypto library used in FreeRTOS to perform TLS Handshke (secure channel establishment). This library uses an interface, which allows to substitute some of it's functionality by third-party crypto implemementations. Trust X/M substitutes standard software crypto implemementation for FreeRTOS/mbedTLS for such functions as: ECDSA, ECDHE, Random Number Generation. You can read more about this [here](https://github.com/Infineon/mbedtls-optiga-trust-m).
This intergation point also doesn't require additional proting, as it works on top of the OPTIGA Trust Software Framework. 
3) **Platform Abstraction Layer**. This is the only integration point which requires actual porting from one platform to another. Generic steps are described [here](https://github.com/Infineon/optiga-trust-m/wiki/Porting-Guide). It is recommended, though to use the existing [template](https://github.com/Infineon/amazon-freertos-optiga-trust/tree/feature/trustm/vendors/infineon/secure_elements/optiga_trust_m/pal/new_board_template). In many cases you need to consider only three files for modifications.

Another important aspect is about how to prepare all the configuration files for a different board, how to refer to resources, etc.
Generic rule is to take an existing FreeRTOS quailified board (and test is ideally before you will try out the same option, but with a secure elemenent), and create a new configuration based on it.
The example below shows a **sample** process of creating a new porting, for the ```stm32l475_discovery``` board using cmake build system. For a successfull qualification you need as well a new porject-based setup, but this step is very different from IDE to IDE and isn't covered here.

0) Try out FreeRTOS for the ```stm32l475_discovery``` without any secure elements https://docs.aws.amazon.com/freertos/latest/userguide/getting_started_st.html
1) Create a new folder in [boards](https://github.com/Infineon/amazon-freertos-optiga-trust/tree/feature/trustm/vendors/st/boards); e.g. ```stm32l475_discovery_with_trust_m``` and copy all the content from the source board ```stm32l475_discovery```. 
2) Using this [CMakeLists](https://github.com/Infineon/amazon-freertos-optiga-trust/blob/feature/trustm/vendors/infineon/boards/xmc4800_plus_optiga_trust_m/CMakeLists.txt) update the same file in newly created ```stm32l475_discovery_with_trust_m```board
3) Similarly update the manifest https://github.com/Infineon/amazon-freertos-optiga-trust/blob/feature/trustm/vendors/st/manifest.cmake

**Note**: All the Trust X/M related parts should be located at Infineon folder, and you cmake files should take them from there.
