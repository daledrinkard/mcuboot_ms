/*
 * resource.h
 *
 *  Created on: Mar 25, 2025
 *      Author: daled
 */

#ifndef RESOURCES_RESOURCE_H_
#define RESOURCES_RESOURCE_H_

typedef struct res_s {
    uint8_t header[0x200];
    uint8_t data[1024];
}res_t;
extern const res_t resources;

#endif /* RESOURCES_RESOURCE_H_ */
