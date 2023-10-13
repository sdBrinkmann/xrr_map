// xrr_routines.cpp


#include "xrr.h"

#include <string.h>

int MapInteractive() {

  int monitor_count = 0;

  Display *display = XOpenDisplay(NULL);
  if (display == NULL) {
    fprintf(stderr, "Failed to open display!\n");
    return -1;
  }

  XDevice *device = SelectWacomDev(display);

  if (device == NULL) 
    return -1;

  // get & list monitors
  
  Window wnd = XDefaultRootWindow(display);
  // 0 = active, 1 = inactive

  XRRMonitorInfo *info = XRRGetMonitors(display, wnd, 0, &monitor_count);
  printf("Found %d active monitor(s):\n", monitor_count);
  
  
  for (int i = 0; i < monitor_count; i++) {
    printf("  Monitor: %d %s ", i+1, XGetAtomName(display, info[i].name));
    printf("%dx%d\n", info[i].width, info[i].height);
  }

  // get monitor number 

  int choice = input_choice(monitor_count);


  mapDevToMonitor(choice, display, device, info);
  
  XRRFreeMonitors(info);
  XFlush(display);
  
  XCloseDevice(display, device);
  XCloseDisplay(display);


  return 0;
}

int resetMap() {

  Display *display = XOpenDisplay(NULL);
  if (display == NULL) {
    fprintf(stderr, "Failed to open display!\n");
    return -1;
  }

    int ndevs;

  XDeviceInfo *devs;
  devs = XListInputDevices(display, &ndevs);
  

  // get & list Wacom devices

  //int wacom_devs[40];

  Atom wacom_prop = XInternAtom(display, "Wacom Tool Type", True);
  if (wacom_prop == None) {
    fprintf(stderr, "No Wacom devices found\n");
    XFreeDeviceList(devs);
    return -1;
  }
  
  int w_ndevs = 0;
  for (int i = 0; i < ndevs; i++) {
    if (devs[i].use == IsXKeyboard || devs[i].use == IsXPointer) continue;
    //if (devs->type == None) continue;
    if (strstr(devs[i].name, "Wacom") != NULL && strstr(devs[i].name, "stylus") != NULL) {
      if (!w_ndevs++) puts("Found following devices:");
      printf("  Device %d : %s\n", w_ndevs, devs[i].name);
      XDevice *device = XOpenDevice(display, devs[i].id);
      mapDevToMonitor(0, display, device, NULL);
      XCloseDevice(display, device);
    }
  }

  
  XFreeDeviceList(devs);
  XFlush(display);
  XCloseDisplay(display);

  return 0;
}


int listDevices() {

  
  Display *display = XOpenDisplay(NULL);
  if (display == NULL) {
    fprintf(stderr, "Failed to open display!\n");
    return -1;
  }

  int ndevs;

  XDeviceInfo *devs;
  devs = XListInputDevices(display, &ndevs);
  

  // get & list Wacom devices


  Atom wacom_prop = XInternAtom(display, "Wacom Tool Type", True);
  if (wacom_prop == None) {
    fprintf(stderr, "No Wacom devices found\n\n");
  } else {
    int w_ndevs = 0;
    for (int i = 0; i < ndevs; i++) {
      if (devs[i].use == IsXKeyboard || devs[i].use == IsXPointer) continue;
      //if (devs->type == None) continue;
      if (strstr(devs[i].name, "Wacom") != NULL) {
	if (!w_ndevs++) puts("Found following devices:");
	printf("  Device %d : %s\n", w_ndevs, devs[i].name);
      }
    }
  }
   // get & list Wacom devices

  int monitor_count = 0;
  
  Window wnd = XDefaultRootWindow(display);
  // 0 = active, 1 = inactive

  XRRMonitorInfo *info = XRRGetMonitors(display, wnd, 0, &monitor_count);
  printf("Found %d active monitor(s):\n", monitor_count);
  
  
  for (int i = 0; i < monitor_count; i++) {
    printf("  Monitor: %d %s ", i+1, XGetAtomName(display, info[i].name));
    printf("%dx%d\n", info[i].width, info[i].height);
  }

  XFreeDeviceList(devs);
  XFlush(display);

  XRRFreeMonitors(info);
  
  XCloseDisplay(display);


  return 0;
}
