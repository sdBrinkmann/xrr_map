// xxr.h -- function prototypes

#ifndef XXR_H_
#define XXR_H_

#include <X11/Xlib.h>
#include <X11/Xatom.h>
//#include <X11/extensions/XI.h>
#include <X11/extensions/XInput.h>
#include <X11/extensions/Xrandr.h>

#include <stdio.h>
#include <stdlib.h>




// Routines

int MapInteractive(void);
int resetMap(void);
int listDevices(void);

// Helper Functions

XDevice* SelectWacomDev(Display *display);
int input_choice(int m_count);
void mapDevToMonitor(int choice, Display *display, XDevice *device, XRRMonitorInfo *info);

#endif
