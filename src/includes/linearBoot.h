//
//  linearBoot.h
//  concreteOS
//
//  Created by Jonathan Archer on 10/16/17.
//

#ifndef linearBoot_h
#define linearBoot_h

#ifdef __cplusplus
extern "C" {
#endif

extern void gdtEnable(), idtEnable();
extern unsigned char keyCode;

#ifdef __cplusplus
}
#endif

#endif
