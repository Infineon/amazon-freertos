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
