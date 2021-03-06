# hueplusplus
A simple and easy to use library for Philips Hue Lights

| Branch | Travis CI | Codecov | Codacy |
|:-|:-|:-|:-|
| [Master](https://github.com/enwi/hueplusplus/tree/master) | [![Build Status](https://travis-ci.com/enwi/hueplusplus.svg?branch=master)](https://travis-ci.com/enwi/hueplusplus) | [![codecov](https://codecov.io/gh/enwi/hueplusplus/branch/master/graph/badge.svg)](https://codecov.io/gh/enwi/hueplusplus) | [![Codacy Badge](https://api.codacy.com/project/badge/Grade/558c343dddf4418c85a4b2d52538be04?branch=master)](https://www.codacy.com/app/enwi/hueplusplus?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=enwi/hueplusplus&amp;utm_campaign=Badge_Grade) |
| [Development](https://github.com/enwi/hueplusplus/tree/development) | [![Build Status](https://travis-ci.com/enwi/hueplusplus.svg?branch=development)](https://travis-ci.com/enwi/hueplusplus) | [![codecov](https://codecov.io/gh/enwi/hueplusplus/branch/development/graph/badge.svg)](https://codecov.io/gh/enwi/hueplusplus) | [![Codacy Badge](https://api.codacy.com/project/badge/Grade/558c343dddf4418c85a4b2d52538be04?branch=development)](https://www.codacy.com/app/enwi/hueplusplus?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=enwi/hueplusplus&amp;utm_campaign=Badge_Grade) |

## Features
* find bridges with SSDP or set an ip manually
* function to assign a username or set one manually
* all common light functions (brightness, color, temperature)
* extended alert() functions, which alert in a specific color (good for notifications)
* documented with doxygen
* tested with google test, google mock and gcov/lcov

## Compatibility
* Linux
* Windows
* MacOS
* Espressif ESP32 SDK & Arduino

## How to use
### <a name="searchingBridges"></a>Searching for Bridges
To start searching for a Hue Bridge you will need to choose an IHttpHandler and create one. The options are a "WinHttpHandler" (for windows) or a "LinHttpHandler" (for linux).
Then create a HueFinder object with the handler.
The handler is needed, because it tells the finder which functions to use to communicate with a bridge or your local network.
After that you can call FindBridges(), which will return a vector containing the ip and mac address of all found Bridges.
If no Bridges were found the vector is empty, so make sure that in that case you provide an ip and mac address.
```C++
// For windows use std::make_shared<WinHttpHandler>();
handler = std::make_shared<LinHttpHandler>();
HueFinder finder(handler);
std::vector<HueFinder::HueIdentification> bridges = finder.FindBridges();
if (bridges.empty())
{
	bridges.push_back({ "<ip address>", "<mac address>" });
}
```

### Authenticate Bridges
If you have found the Bridge you were looking for, you can then move on with the authentication process.
To get a new username from the Bridge (for now) you simply call GetBridge(bridges[\<index\>]),
where index is your preferred Bridge from the part [Searching for Bridges](#searchingBridges).
```C++
Hue bridge = finder.GetBridge(bridges[0]);
```
If you on the other hand already have a username you can add your bridge like so
```C++
finder.AddUsername(bridges[0].mac, "<username>");
Hue bridge = finder.GetBridge(bridges[0]);
```
If you do not want to use the HueFinder or you already know the ip and username of your bridge you have the option to create your own Hue object.
Here you will need to provide the ip address, the port number, a username and an HttpHandler
```C++
// For windows use std::make_shared<WinHttpHandler>();
handler = std::make_shared<LinHttpHandler>();
Hue bridge("192.168.2.102", 80, "<username>", handler);
```

### Controlling lights
If you have your Bridge all set up, you can now control its lights.
For that create a new HueLight object and call getLight(\<id\>) on your bridge object to get a reference to a specific light, where id
is the id of the light set internally by the Hue Bridge.
```C++
HueLight light1 = bridge.getLight(1);
```
If you don't know the id of a specific light or want to get an overview over all lights that are controlled by your bridge, you can get a vector containing them by calling getAllLights() on your bridge object. If no lights are found the vector will be empty.
```C++
std::vector<std::reference_wrapper<HueLight>> lights = bridge.getAllLights();
```
If you now want to control a light, call a specific function of it.
```C++
light1.On();
light1.setBrightness(120);
light1.alertHueSaturation(25500, 255);
light1.setColorLoop(true);
light1.setColorRGB(255, 128, 0);
lights[1].Off();
lights.at(1).setColorHue(4562);
```
But keep in mind that some light types do not have all functions available. So you might call a
specific function, but nothing will happen. For that you might want to check what type
of a light you are controlling. For that you can call the function getColorType(), which will return
a ColorType.
```C++
ColorType type1 = light1.getColorType();
```
There's also a new way to check whether specific functions of a light are available:
```C++
light1.hasBrightnessControl();
light1.hasTemperatureControl();
light1.hasColorControl();
```
These will either return true(light has specified function) or false(light lacks specified function).

### Further reading
If you want to know more about all functions just look inside the doxygen description,
which for now can be found in the regarding sourcecode file or create the documentation
with the provided Doxyfile yourself.

## Build and install
### Basic installation
If you want to build the library you can use cmake (at least version 2.8.3). First create a build folder and then execute cmake.
```bash
mkdir build
cd build
cmake ..
```
Then compile the code with make. If you are inpatient use the option -j\<number\>, where number specifies how many files are compiled at the same time. Note this number should not exceed the number of cores*2 of your machine.
```bash
make
```
```bash
make -j4
```
If you want to install the library use
```bash
make install
```
To remove it
```bash
make uninstall
```

### Advanced usage
If you have a project that already uses CMake you probably want to add the hueplusplus library directly in your cmake file.
For that the best way is to use find_package().
When cmake finds the hueplusplus library you can then link against either the shared or static version of the library.
```cmake
find_package(hueplusplus)

target_link_libraries(<executable> hueplusplusstatic)
```
But this will only work if the hueplusplus library is already installed.
To get around this problem there is a pretty awesome way.
If you have the hueplusplus repository included in your project repository (as a submodule) or know where the folder lives you can do the following:
```cmake
find_package(hueplusplus)
if(NOT hueplusplus_FOUND)
    message(STATUS "-- hueplusplus not found, building it")
    add_subdirectory("${CMAKE_SOURCE_DIR}/<path to directory>/hueplusplus" "${CMAKE_BINARY_DIR}/hueplusplus")
endif()

target_link_libraries(<executable> hueplusplusstatic)
```
This will check if the hueplusplus library was found by find_package() and if not it will use the specified path to the library source and compile it during the build process.

### Running tests
If you additionally want to run the tests use cmake with the option -Dhueplusplus_TESTS=ON. Testing is done with Google gtest and gmock. Note that you wont need to install gtest/gmock yourself, because cmake will automatically download them and include them during the build. Since I added a custom target you will only need to call "make unittest" and the tests are compiled and executed.
```bash
mkdir build
cd build
cmake .. -Dhueplusplus_TESTS=ON
make unittest
```
If you also want to execute coverage tests you will need to install gcov and lcov yourself. To run the coverage test use
```bash
make coveragetest
```


## Copyright
Copyright (c) 2017 Jan Rogall & Moritz Wirger. See LICENSE for further details.
