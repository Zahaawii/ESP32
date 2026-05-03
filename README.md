ESP32 project to alter lights for a guitar as the strings get played.


Never used ESP32 before, so this project is going to be made with LLM:

References:
https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/macos-setup.html#online-installation-using-eim-cli
https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/macos-setup.html
https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/macos-setup.html

Command to run:
source "/Users/zahaawii/.espressif/tools/activate_idf_v6.0.1.sh"
idf.py create-project hello_world
cd hello_world
idf.py set-target esp32
idf.py build

Find board port
ls /dev/cu.*

idf.py -p /dev/cu.usbserial-10 flash
idf.py -p /dev/cu.usbserial-10 monitor



In order to connect the LED board with the ESP we combine the following:
- ESP board
- Crocodile Clip
- LED board

Since the LED boards cable does not align with the ESP pins we have to use crocodile clips:
White goes to GND
Green goes to 4
Red goes to 5

In that order the LED board gets connected to the ESP and then the code gets trickered.

The code right now is simple turn on the LED lights in with a loop, horizontal, vertical to understand the matrix of the board
