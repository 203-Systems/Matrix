#include <stdlib.h>
#include "usb_mass_mal.h"


#define USB_MASS_MAL_FAIL    1
#define USB_MASS_MAL_SUCCESS 0

MassStorageDriveInfo usb_mass_drives[USB_MASS_MAX_DRIVES] = { { 0 } };

uint16_t usb_mass_mal_init(uint8_t lun) {
	if (lun >= USB_MASS_MAX_DRIVES || (usb_mass_drives[lun].init != NULL && ! usb_mass_drives[lun].init()))
		return USB_MASS_MAL_FAIL;
	else
		return USB_MASS_MAL_SUCCESS;
}

void usb_mass_mal_format(uint8_t lun) {
	if (lun < USB_MASS_MAX_DRIVES && usb_mass_drives[lun].format != NULL)
		usb_mass_drives[lun].format();
}

uint16_t usb_mass_mal_get_status(uint8_t lun) {
	if (lun >= USB_MASS_MAX_DRIVES || (usb_mass_drives[lun].status != NULL && ! usb_mass_drives[lun].status()))
		return USB_MASS_MAL_FAIL;
	else
		return USB_MASS_MAL_SUCCESS;
}

uint16_t usb_mass_mal_read_memory(uint8_t lun, uint32_t memoryOffset, uint8_t *readbuff, uint16_t transferLength) {
	if (lun >= USB_MASS_MAX_DRIVES || ! usb_mass_drives[lun].read(memoryOffset, readbuff, transferLength))
		return USB_MASS_MAL_FAIL;
	else
		return USB_MASS_MAL_SUCCESS;
}

uint16_t usb_mass_mal_write_memory(uint8_t lun, uint32_t memoryOffset, uint8_t *writebuff, uint16_t transferLength) {
	if (lun >= USB_MASS_MAX_DRIVES || usb_mass_drives[lun].write == NULL 
			|| ! usb_mass_drives[lun].write(memoryOffset, writebuff, transferLength))
		return USB_MASS_MAL_FAIL;
	else
		return USB_MASS_MAL_SUCCESS;
}
