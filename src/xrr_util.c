// xxr_util.cpp


#include "xrr.h"

#include <string.h>
#include <stdbool.h>


/*
 Returns (Wacom) device user selects for mapping
*/


XDevice* SelectWacomDev(Display *display) {

  // list devices

  int ndevs;

  XDeviceInfo *devs;
  devs = XListInputDevices(display, &ndevs);
  

  // get & list Wacom devices

  int wacom_devs[40];

  Atom wacom_prop = XInternAtom(display, "Wacom Tool Type", True);
  if (wacom_prop == None) {
    fprintf(stderr, "No Wacom devices found\n");
    XFreeDeviceList(devs);
    return NULL;
  }
  
  int w_ndevs = 0;
  for (int i = 0; i < ndevs; i++) {
    if (devs[i].use == IsXKeyboard || devs[i].use == IsXPointer) continue;
    //if (devs->type == None) continue;
    if (strstr(devs[i].name, "Wacom") != NULL) {
      if (!w_ndevs++) puts("Found following devices:");
      printf("  Device %d : %s\n", w_ndevs, devs[i].name);
      wacom_devs[w_ndevs-1] = i;
    }
  }

  
  if (w_ndevs == 0) {
    puts("No Wacom tablet devices found!");
    XFreeDeviceList(devs);
    return NULL;
  }
      
  printf("Type 1 to %d to select corresponding Wacom device to be mapped\n", w_ndevs);
 
  int dn;

  while (true) {
    scanf("%d",&dn);
    if (dn > 0 && dn <= w_ndevs)
      break;
    else
      printf("Please enter a valid number from 1 to %d \n", w_ndevs);
  }

  XDevice *device = XOpenDevice(display, devs[wacom_devs[dn-1]].id);
  
  XFreeDeviceList(devs);
  
  return device;
}






/*
  get monitor number for mapping
 */  

int input_choice(int m_count) {

  
  printf( "Type 1 to %d in\
order to map wacom tablet solely to the corresponding monitor \n\
or type 0 to remap tablet to all active monitors\n",
	  m_count);
  
	  

  int choice;

  while (true) {
    scanf("%d", &choice);
    if (choice >= 0 && choice <= m_count)
      break;
    else
      printf("Please enter a valid number from 1  to %d\n", m_count);
  }

  return choice;
}

/*
  Map Wacom Device to Selected Monitor(s)
*/

void mapDevToMonitor(int choice, Display *display, XDevice *device, XRRMonitorInfo *info) {

  // Get Dimensions
  float matrix[9] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
 
  if (choice != 0) {
    float h, w;

    h = DisplayHeight(display, DefaultScreen(display));
    w = DisplayWidth(display, DefaultScreen(display));
    
    matrix[0] = info[choice-1].width / w;
    matrix[4] = info[choice-1].height / h;

    matrix[2] = info[choice-1].x / w;
    matrix[5] = info[choice-1].y / h;     
  }
  
  
  
  // Change mapping

  Atom matrix_prop = XInternAtom(display, "Coordinate Transformation Matrix", True);
  Atom type;
  int format;
  unsigned long nitems, bytes_after;
  float *data;
  long trans_matrix[9] = {0};

  XGetDeviceProperty(display, device, matrix_prop, 0, 9, False, AnyPropertyType, &type,
		     &format, &nitems, &bytes_after, (unsigned char**)&data);

  for (size_t i = 0; i < 9; i++) {
    *(float*)(trans_matrix + i) = matrix[i];
  }

  
  XChangeDeviceProperty(display, device, matrix_prop, type, format, PropModeReplace,
			(unsigned char*)trans_matrix, 9);


  XFree(data);
}
