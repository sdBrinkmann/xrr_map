# xrr_map
Command line tool written in C for mapping Wacom tablets to selected monitor(s). The default mode allows for the interactive selection of both monitor and wacom input to map. 
Only works for X11 with respective wacom drivers (`xf86-input-wacom`).

### Prerequisites 
`libXi`, `libX11`, `libXrandr`

### Install
`make & make install`

### Usage
Look up man page or type `xrr_map --help`. xrr_map defaults to interactive mode when called.
