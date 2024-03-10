/*
 * isrdefs.h
 *
 *  Created on: Mar 11, 2024
 *      Author: sibislaw
 */

#ifndef ISRDEFS_H_
#define ISRDEFS_H_

void tim2update() __interrupt(TIM2_OVR_UIF_IRQ);
void tim3update() __interrupt(TIM3_OVR_UIF_IRQ);

#endif /* ISRDEFS_H_ */
