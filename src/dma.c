/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <metal/machine.h>
#include <metal/dma.h>


extern inline void metal_dma_init(struct metal_dma *dma, unsigned int chan, struct metal_dma_chan_config *config);
extern inline int metal_enable_dma(struct metal_dma *dma, unsigned int chan, struct metal_dma_chan_config *config);
extern inline int metal_disable_dma(struct metal_dma *dma, unsigned int chan);
extern inline int metal_channel_active(struct metal_dma *dma, unsigned int chan);
extern inline void metal_dma_setup_jobques(struct metal_dma *dma, struct metal_dma_chan_config *config);

struct metal_dma *metal_dma_get_device(int device_num)
{
    if(device_num >= __METAL_DT_MAX_DMAS) {
        return NULL;
    }

    return (struct metal_dma *) __metal_dma_table[device_num];
}
