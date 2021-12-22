import yaml
import argparse
from pprint import pprint

COMMENT_BLOCK = """/****************************************
 * common.h
 * Fort Knocks tests source code
 * 
 * Pinout
 ****************************************/

"""

DEBUG_BLOCK = """#ifdef DEBUG
#define debug(statement, ...) Serial.println(statement, ##__VA_ARGS__);
#else
#define debug(statement, ...)
#endif

"""

PINS_DEFINE = """%s

"""

SETUP_FUNC = """void setupPins() {
    #ifdef DEBUG
    Serial.begin(2000000);
    #endif

    %s
}"""


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--test-case", type=str)

    args = parser.parse_args()

    with open("pins.yaml") as config:
        pins = yaml.safe_load(config)
        pprint(pins)

    with open(f"tests/{args.test_case}/common.h", "w") as common_h:
        common_h.write(COMMENT_BLOCK)
        common_h.write("#ifndef COMMON_H\n#define COMMON_H\n\n")
        if pins.get("debug", False):
            common_h.write("#define DEBUG\n\n")
        common_h.write(DEBUG_BLOCK)

        pinout = []
        pinmodes = []

        for key, val in pins.items():
            if key != "debug":
                pin_number = val["pin"]
                pin_mode = val["mode"]
                pinout.append(f"#define {key} {pin_number}")
                pinmodes.append(f"pinMode({key}, {pin_mode});")
        
        common_h.write(PINS_DEFINE % "\n".join(pinout))
        common_h.write(SETUP_FUNC % "\n\t".join(pinmodes))

        common_h.write("\n\n#endif /* COMMON_H */")


if __name__ == "__main__":
    main()