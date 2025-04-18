
#ifndef MY_MCUBOOT_CONFIG_H_
#define MY_MCUBOOT_CONFIG_H_

//@@ #define XSPI_AREA_MCUBOOT_OFFSET 0x01000000  //<-- puts MCUboot partition at 16MB (half way)
#define XSPI_AREA_MCUBOOT_OFFSET 0x00800000  //<-- puts MCUboot partition at 8MB because of issues with jlink

#define RESOURCES_SIZE  (1024*1024)

/** Area that is linked in the application **/
#define FLASH_AREA_RESOURCES_ID (8)
#define FLASH_AREA_RESOURCES_OFFSET (0x60000000)
#define FLASH_AREA_RESOURCES_SIZE (RESOURCES_SIZE)

/** Area that holds the update OTA **/
#define FLASH_AREA_RESOURCES_UPDATE_ID (9)
#define FLASH_AREA_RESOURCES_UPDATE_OFFSET (0x60000000 + XSPI_AREA_MCUBOOT_OFFSET)
#define FLASH_AREA_RESOURCESUPDATE_SIZE (1024 * 1024)


#endif /* MY_MCUBOOT_CONFIG_H_ */
