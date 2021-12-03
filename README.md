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

## Important branches/tags to know
202007-MTBAFR2149 --> PSoC 6 and CYW Evaluation Kit support (latest release)

201910-MTBAFR2149 --> PSoC 6 and CYW Evaluation Kit support (this release)

feature/infineon  --> XMC and OPTIGA support

## Getting Started

For more information on Amazon FreeRTOS, refer to the [Getting Started section of Amazon FreeRTOS webpage](https://aws.amazon.com/freertos).

To directly access the **Getting Started Guide** for supported hardware platforms, click the corresponding link in the Supported Hardware section below.

For detailed documentation on Amazon FreeRTOS, refer to the [Amazon FreeRTOS User Guide](https://aws.amazon.com/documentation/freertos).

For support or more detailed information on Cypress Boards, refer to the [Cypress Community Forum](https://community.cypress.com/welcome)

## Supported Hardware

The following MCU boards are supported for Amazon FreeRTOS:
1. **Cypress CY8CPROTO-062-4343W** - [Cypress PSoC 6 Wi-Fi BT Prototyping Kit](http://www.cypress.com/CY8CPROTO-062-4343W).
    * [Getting Started Guide](https://community.infineon.com/t5/Resource-Library/Getting-Started-with-Amazon-FreeRTOS-and-PSoC62-43xxx/ta-p/260261)
    * IDEs: [ModusToolbox](https://www.cypress.com/products/modustoolbox)
2. **Cypress CY8CKIT-062-WIFI-BT** - [Cypress PSoC 6 WiFi-BT Pioneer Kit](https://www.cypress.com/CY8CKIT-062-WiFi-BT).
    * [Getting Started Guide](https://community.infineon.com/t5/Resource-Library/Getting-Started-with-Amazon-FreeRTOS-and-PSoC62-43xxx/ta-p/260261)
    * IDEs: [ModusToolbox](https://www.cypress.com/products/modustoolbox)
3. **Cypress CYW54907** - [Cypress CYW954907AEVAL1F Evaluation Kit](https://www.cypress.com/documentation/development-kitsboards/cyw954907aeval1f-evaluation-kit)
    * [Getting Started Guide](https://docs.aws.amazon.com/freertos/latest/userguide/getting_started_cypress_54.html)
    * IDE: [WICED Studio](https://community.cypress.com/community/wiced-wifi)
4. **Cypress CYW43907** - [Cypress CYW943907AEVAL1F Evaluation Kit](https://www.cypress.com/documentation/development-kitsboards/cyw943907aeval1f-evaluation-kit)
    * [Getting Started Guide](https://docs.aws.amazon.com/freertos/latest/userguide/getting_started_cypress_43.html)
    * IDE: [WICED Studio](https://community.cypress.com/community/wiced-wifi)


## amazon-freeRTOS/projects
The ```./projects``` folder contains the IDE test and demo projects for Cypress boards. The majority of boards can be built with both IDE and cmake (there are some exceptions!). Please refer to the Getting Started Guides above for board specific instructions.

## Important Information

Programming PSoC 6 devices with this release may result in a permanent disabling of the debug port.
See document [Unable to Connect PSoC 6 MCU After Programming Mbed OS or FreeRTOS Project](https://community.infineon.com/t5/Knowledge-Base-Articles/Unable-to-Connect-PSoC-6-MCU-After-Programming-Mbed-OS-or/ta-p/265127) for more information and corrective action.