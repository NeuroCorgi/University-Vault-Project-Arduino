# Saxion vault project

## Requirements
### System dependencies
1. arduino-cli
2. make
3. python3
### Arduino dependencies
1. Servo.h
2. EEPROM.h
3. 

## Main program
```bash
make main
```

## Run tests

### Configuration
Configuration in the yaml file
#### Configuration syntax
```yaml
debug: [false, true]
pinName:
    mode: [OUTPUT, INPUT, INPUT_PULLUP]
    pin: [Number of any arduino pin]
```

### Execution
```bash
make test-(testname)
```
testname
: name of the component to test

## Note
- Tested only on Linux/MacOs 
- It is known that the implementations of the functions should be putted in source files rather than in header files, but it will not work that way for unknown reason