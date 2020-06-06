# Biot-Savharp

Directory of folders/files in this repository
- ATTiny: Arduino code running on ATTiny45s (generating square waves sent to electromagnets to actuate strings)
- ArduinoISP: Arduino code to use an Arduino as an ISP to program ATTiny45s. This code is identical to the one found in the official Arduino Examples and requires some tweaking depending on what master Arduino is being used, etc.
- Datasheets: datasheets for the various chips used in the electromagnet driver board (AND gates, driver, and MOSFET)
- EM Harp: Eagle PCB layout files for the electromagnet driver board (.brd for board, .dru for design rules, .sch for schematic, and .epf for eagle project file)
- Keyboard: Arduino code running on an Arduino MEGA getting inputs from the keyboard and transmitting on/off signals for each key to the electromagnet driver board
- Keyboard_Laser: DWG file for laser-cutting the wooden keys of the keyboard
- MEGA Shield: Arduino MEGA breakout board interfacing with the keyboard and with connectors to the electromagnet driver board
- Notebook.pdf: my design notebook! The authoritative source of documentation, and a record of all the failures that led to eventual success
- harp_string_lengths.xlsx: an excel spreadsheet for calculating string lengths depending on tension
