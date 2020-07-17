/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#ifndef METAL__PMP_H
#define METAL__PMP_H

/*!
 * @file metal/pmp.h
 *
 * @brief API for Configuring Physical Memory Protection on RISC-V Cores
 *
 * The Physical Memory Protection (PMP) interface on RISC-V cores
 * is a form of memory protection unit which allows for a finite number
 * of physical memory regions to be configured with certain access
 * permissions.
 *
 * Additional information about the use and configuration rules for PMPs
 * can be found by reading the RISC-V Privileged Architecture Specification.
 */

#include <metal/generated/cpu.h>
#include <stddef.h>

struct metal_pmp;

/*!
 * @brief Set of available PMP addressing modes
 */
enum metal_pmp_address_mode {
    /*! @brief Disable the PMP region */
    METAL_PMP_OFF = 0,
    /*! @brief Use Top-of-Range mode */
    METAL_PMP_TOR = 1,
    /*! @brief Use naturally-aligned 4-byte region mode */
    METAL_PMP_NA4 = 2,
    /*! @brief Use naturally-aligned power-of-two mode */
    METAL_PMP_NAPOT = 3
};

/*!
 * @brief Configuration for a PMP region
 */
struct metal_pmp_config {
    /*! @brief Sets whether reads to the PMP region succeed */
    unsigned int R : 1;
    /*! @brief Sets whether writes to the PMP region succeed */
    unsigned int W : 1;
    /*! @brief Sets whether the PMP region is executable */
    unsigned int X : 1;

    /*! @brief Sets the addressing mode of the PMP region */
    enum metal_pmp_address_mode A : 2;

    int _pad : 2;

    /*! @brief Sets whether the PMP region is locked */
    enum metal_pmp_locked {
        METAL_PMP_UNLOCKED = 0,
        METAL_PMP_LOCKED = 1
    } L : 1;
};

/*!
 * @brief Get the number of pmp regions for the hartid
 */
int metal_pmp_num_regions(int hartid);

/*!
 * @brief Initialize the PMP
 *
 * The PMP initialization routine is optional and may be called as many times
 * as is desired. The effect of the initialization routine is to attempt to set
 * all regions to unlocked and disabled, as well as to clear the X, W, and R
 * bits. Only the pmp configuration of the hart which executes the routine will
 * be affected.
 *
 * If any regions are fused to preset values by the implementation or locked,
 * those PMP regions will silently remain uninitialized.
 */
void metal_pmp_init(void);

/*!
 * @brief Configure a PMP region
 * @param region The PMP region to configure
 * @param config The desired configuration of the PMP region
 * @param address The desired address of the PMP region
 * @return 0 upon success
 */
int metal_pmp_set_region(unsigned int region, struct metal_pmp_config config,
                         size_t address);

/*!
 * @brief Get the configuration for a PMP region
 * @param region The PMP region to read
 * @param config Variable to store the PMP region configuration
 * @param address Variable to store the PMP region address
 * @return 0 if the region is read successfully
 */
int metal_pmp_get_region(unsigned int region, struct metal_pmp_config *config,
                         size_t *address);

/*!
 * @brief Lock a PMP region
 * @param region The PMP region to lock
 * @return 0 if the region is successfully locked
 */
int metal_pmp_lock(unsigned int region);

/*!
 * @brief Set the address for a PMP region
 * @param region The PMP region to set
 * @param address The desired address of the PMP region
 * @return 0 if the address is successfully set
 */
int metal_pmp_set_address(unsigned int region, size_t address);

/*!
 * @brief Get the address of a PMP region
 * @param region The PMP region to read
 * @return The address of the PMP region, or 0 if the region could not be read
 */
size_t metal_pmp_get_address(unsigned int region);

/*!
 * @brief Set the addressing mode of a PMP region
 * @param region The PMP region to set
 * @param mode The PMP addressing mode to set
 * @return 0 if the addressing mode is successfully set
 */
int metal_pmp_set_address_mode(unsigned int region,
                               enum metal_pmp_address_mode mode);

/*!
 * @brief Get the addressing mode of a PMP region
 * @param region The PMP region to read
 * @return The address mode of the PMP region
 */
enum metal_pmp_address_mode metal_pmp_get_address_mode(unsigned int region);

/*!
 * @brief Set the executable bit for a PMP region
 * @param region The PMP region to set
 * @param X The desired value of the executable bit
 * @return 0 if the executable bit is successfully set
 */
int metal_pmp_set_executable(unsigned int region, int X);

/*!
 * @brief Get the executable bit for a PMP region
 * @param region The PMP region to read
 * @return the value of the executable bit
 */
int metal_pmp_get_executable(unsigned int region);

/*!
 * @brief Set the writable bit for a PMP region
 * @param region The PMP region to set
 * @param W The desired value of the writable bit
 * @return 0 if the writable bit is successfully set
 */
int metal_pmp_set_writeable(unsigned int region, int W);

/*!
 * @brief Get the writable bit for a PMP region
 * @param region The PMP region to read
 * @return the value of the writable bit
 */
int metal_pmp_get_writeable(unsigned int region);

/*!
 * @brief Set the readable bit for a PMP region
 * @param region The PMP region to set
 * @param R The desired value of the readable bit
 * @return 0 if the readable bit is successfully set
 */
int metal_pmp_set_readable(unsigned int region, int R);

/*!
 * @brief Set the readable bit for a PMP region
 * @param region The PMP region to read
 * @return the value of the readable bit
 */
int metal_pmp_get_readable(unsigned int region);

#endif
