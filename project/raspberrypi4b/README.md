### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(ads1110 REQUIRED)
```

### 3. ADS1110

#### 3.1 Command Instruction

1. Show ads1110 chip and driver information.

    ```shell
    ads1110 (-i | --information)  
    ```

2. Show ads1110 help.

    ```shell
    ads1110 (-h | --help)        
    ```

3. Show ads1110 pin connections of the current board.

    ```shell
    ads1110 (-p | --port)        
    ```

4. Run ads1110 register test.

    ```shell
    ads1110 (-t reg | --test=reg) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]         
    ```

5. Run ads1110 read test, num means test times.

    ```shell
    ads1110 (-t read | --test=read) [--times=<num>] [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]
    ```

6. Run ads1110 read function, num means read times.

    ```shell
    ads1110 (-e read | --example=read) [--times=<num>] [--addr=0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]      
    ```

7. Run ads1110 shot function, num means read times.

    ```shell
    ads1110 (-e shot | --example=shot) [--times=<num>] [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]      
    ```

#### 3.2 Command Example

```shell
./ads1110 -i

ads1110: chip is Texas Instruments ADS1110.
ads1110: manufacturer is Texas Instruments.
ads1110: interface is IIC.
ads1110: driver version is 1.0.
ads1110: min supply voltage is 2.7V.
ads1110: max supply voltage is 5.5V.
ads1110: max current is 0.35mA.
ads1110: max temperature is 85.0C.
ads1110: min temperature is -40.0C.
```

```shell
./ads1110 -p

ads1110: SCL connected to GPIO3(BCM).
ads1110: SDA connected to GPIO2(BCM).
```

```shell
./ads1110 -t reg --addr=0 

ads1110: chip is Texas Instruments ADS1110.
ads1110: manufacturer is Texas Instruments.
ads1110: interface is IIC.
ads1110: driver version is 1.0.
ads1110: min supply voltage is 2.7V.
ads1110: max supply voltage is 5.5V.
ads1110: max current is 0.35mA.
ads1110: max temperature is 85.0C.
ads1110: min temperature is -40.0C.
ads1110: start register test.
ads1110: ads1110_set_addr_pin/ads1110_get_addr_pin test.
ads1110: set addr pin 0.
ads1110: check addr pin ok.
ads1110: set addr pin 1.
ads1110: check addr pin ok.
ads1110: set addr pin 2.
ads1110: check addr pin ok.
ads1110: set addr pin 3.
ads1110: check addr pin ok.
ads1110: set addr pin 4.
ads1110: check addr pin ok.
ads1110: set addr pin 5.
ads1110: check addr pin ok.
ads1110: set addr pin 6.
ads1110: check addr pin ok.
ads1110: set addr pin 7.
ads1110: check addr pin ok.
ads1110: ads1110_set_rate/ads1110_get_rate test.
ads1110: set rate 15 sps.
ads1110: check rate ok.
ads1110: set rate 30 sps.
ads1110: check rate ok.
ads1110: set rate 60 sps.
ads1110: check rate ok.
ads1110: set rate 240 sps.
ads1110: check rate ok.
ads1110: ads1110_set_gain/ads1110_get_gain test.
ads1110: set gain 1.
ads1110: check gain ok.
ads1110: set gain 2.
ads1110: check gain ok.
ads1110: set gain 4.
ads1110: check gain ok.
ads1110: set gain 8.
ads1110: check gain ok.
ads1110: finish register test.
```

```shell
./ads1110 -t read --times=3 --addr=0

ads1110: chip is Texas Instruments ADS1110.
ads1110: manufacturer is Texas Instruments.
ads1110: interface is IIC.
ads1110: driver version is 1.0.
ads1110: min supply voltage is 2.7V.
ads1110: max supply voltage is 5.5V.
ads1110: max current is 0.35mA.
ads1110: max temperature is 85.0C.
ads1110: min temperature is -40.0C.
ads1110: set gain 1.
ads1110: set 15sps rate.
ads1110: continuous read test.
ads1110: continues mode 0.062V.
ads1110: continues mode 0.062V.
ads1110: continues mode 0.062V.
ads1110: single read test.
ads1110: single mode 0.062V.
ads1110: single mode 0.062V.
ads1110: single mode 0.062V.
ads1110: set 30sps rate.
ads1110: continuous read test.
ads1110: continues mode 0.062V.
ads1110: continues mode 0.062V.
ads1110: continues mode 0.062V.
ads1110: single read test.
ads1110: single mode 0.062V.
ads1110: single mode 0.062V.
ads1110: single mode 0.062V.
ads1110: set 60sps rate.
ads1110: continuous read test.
ads1110: continues mode 0.062V.
ads1110: continues mode 0.062V.
ads1110: continues mode 0.062V.
ads1110: single read test.
ads1110: single mode 0.062V.
ads1110: single mode 0.062V.
ads1110: single mode 0.062V.
ads1110: set 240sps rate.
ads1110: continuous read test.
ads1110: continues mode 0.062V.
ads1110: continues mode 0.062V.
ads1110: continues mode 0.062V.
ads1110: single read test.
ads1110: single mode 0.062V.
ads1110: single mode 0.062V.
ads1110: single mode 0.062V.
ads1110: set gain 2.
ads1110: set 15sps rate.
ads1110: continuous read test.
ads1110: continues mode 0.066V.
ads1110: continues mode 0.066V.
ads1110: continues mode 0.066V.
ads1110: single read test.
ads1110: single mode 0.066V.
ads1110: single mode 0.066V.
ads1110: single mode 0.066V.
ads1110: set 30sps rate.
ads1110: continuous read test.
ads1110: continues mode 0.066V.
ads1110: continues mode 0.066V.
ads1110: continues mode 0.066V.
ads1110: single read test.
ads1110: single mode 0.066V.
ads1110: single mode 0.066V.
ads1110: single mode 0.066V.
ads1110: set 60sps rate.
ads1110: continuous read test.
ads1110: continues mode 0.066V.
ads1110: continues mode 0.066V.
ads1110: continues mode 0.066V.
ads1110: single read test.
ads1110: single mode 0.066V.
ads1110: single mode 0.066V.
ads1110: single mode 0.066V.
ads1110: set 240sps rate.
ads1110: continuous read test.
ads1110: continues mode 0.067V.
ads1110: continues mode 0.067V.
ads1110: continues mode 0.067V.
ads1110: single read test.
ads1110: single mode 0.067V.
ads1110: single mode 0.067V.
ads1110: single mode 0.067V.
ads1110: set gain 8.
ads1110: set 15sps rate.
ads1110: continuous read test.
ads1110: continues mode 0.070V.
ads1110: continues mode 0.070V.
ads1110: continues mode 0.070V.
ads1110: single read test.
ads1110: single mode 0.070V.
ads1110: single mode 0.070V.
ads1110: single mode 0.070V.
ads1110: set 30sps rate.
ads1110: continuous read test.
ads1110: continues mode 0.070V.
ads1110: continues mode 0.070V.
ads1110: continues mode 0.070V.
ads1110: single read test.
ads1110: single mode 0.070V.
ads1110: single mode 0.070V.
ads1110: single mode 0.070V.
ads1110: set 60sps rate.
ads1110: continuous read test.
ads1110: continues mode 0.070V.
ads1110: continues mode 0.070V.
ads1110: continues mode 0.070V.
ads1110: single read test.
ads1110: single mode 0.070V.
ads1110: single mode 0.070V.
ads1110: single mode 0.070V.
ads1110: set 240sps rate.
ads1110: continuous read test.
ads1110: continues mode 0.070V.
ads1110: continues mode 0.070V.
ads1110: continues mode 0.070V.
ads1110: single read test.
ads1110: single mode 0.070V.
ads1110: single mode 0.070V.
ads1110: single mode 0.070V.
ads1110: set gain 4.
ads1110: set 15sps rate.
ads1110: continuous read test.
ads1110: continues mode 0.069V.
ads1110: continues mode 0.069V.
ads1110: continues mode 0.069V.
ads1110: single read test.
ads1110: single mode 0.069V.
ads1110: single mode 0.069V.
ads1110: single mode 0.069V.
ads1110: set 30sps rate.
ads1110: continuous read test.
ads1110: continues mode 0.069V.
ads1110: continues mode 0.069V.
ads1110: continues mode 0.069V.
ads1110: single read test.
ads1110: single mode 0.069V.
ads1110: single mode 0.069V.
ads1110: single mode 0.069V.
ads1110: set 60sps rate.
ads1110: continuous read test.
ads1110: continues mode 0.069V.
ads1110: continues mode 0.069V.
ads1110: continues mode 0.069V.
ads1110: single read test.
ads1110: single mode 0.069V.
ads1110: single mode 0.069V.
ads1110: single mode 0.069V.
ads1110: set 240sps rate.
ads1110: continuous read test.
ads1110: continues mode 0.069V.
ads1110: continues mode 0.069V.
ads1110: continues mode 0.069V.
ads1110: single read test.
ads1110: single mode 0.069V.
ads1110: single mode 0.069V.
ads1110: single mode 0.069V.
ads1110: finish read test.
```

```shell
./ads1110 -e read --times=3 --addr=0

ads1110: 1/3.
ads1110: adc is 0.1117V.
ads1110: 2/3.
ads1110: adc is 0.1043V.
ads1110: 3/3.
ads1110: adc is 0.1044V.
```

```shell
./ads1110 -e shot --times=3 --addr=0

ads1110: 1/3.
ads1110: adc is 0.1024V.
ads1110: 2/3.
ads1110: adc is 0.1153V.
ads1110: 3/3.
ads1110: adc is 0.1095V.
```

```shell
./ads1110 -h

Usage:
  ads1110 (-i | --information)
  ads1110 (-h | --help)
  ads1110 (-p | --port)
  ads1110 (-t reg | --test=reg) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]
  ads1110 (-t read | --test=read) [--times=<num>] [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]
  ads1110 (-e read | --example=read) [--times=<num>] [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]
  ads1110 (-e shot | --example shot) [--times=<num>] [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]

Options:
      --addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>
                                         Set the connection of the addr pin.([default: 0])
  -e <read | shot>, --example=<read | shot>
                                         Run the driver example.
  -h, --help                             Show the help.
  -i, --information                      Show the chip information.
  -p, --port                             Display the pins used by this device.
  -t <reg | read>, --test=<reg | read>   Run the driver test.
      --times=<num>                      Set the running times.([default: 3])
```
