compile:
	arduino-cli compile /home/daddyagx/Arduino/marbella --fqbn=arduino:megaavr:uno2018 --libraries=/home/daddyagx/Documents/arduino-1.8.19-linuxaarch64/arduino-1.8.19/libraries,/home/daddyagx/Arduino/libraries

upload: compile
	arduino-cli upload /home/daddyagx/Arduino/marbella --port=/dev/ttyACM0 --fqbn=arduino:megaavr:uno2018
