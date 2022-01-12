.PHONY: main esp clean--eeprom

main:
	arduino-cli compile --fqbn arduino:avr:uno --verify main
	arduino-cli upload --fqbn arduino:avr:uno -p /dev/cu.usbmodem* --verbose main

test-%: config-%
	@echo Test directory: `pwd`/tests/`echo $@ | cut -d "-" -f2`
	arduino-cli compile --fqbn arduino:avr:uno --verify tests/`echo $@ | cut -d "-" -f2`
	arduino-cli upload --fqbn arduino:avr:uno -p /dev/cu.usbmodem* --verbose tests/`echo $@ | cut -d "-" -f2`

clean:
	rm ./tests/**/common.h

clean-eeprom:
	arduino-cli compile --fqbn arduino:avr:uno --verify erase
	arduino-cli upload --fqbn arduino:avr:uno -p /dev/cu.usbmodem* --verbose erase

config-%:
	python3 utils/config.py --test-case `echo $@ | cut -d "-" -f2`
