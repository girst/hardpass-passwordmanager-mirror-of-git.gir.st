all:
	g++ -Ofast -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s -Wall  -lArduiPi_OLED -Wno-write-strings oled_menu.cpp -o oled_menu
	g++ -Ofast -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s -Wall  -lArduiPi_OLED -Wno-write-strings oled_passwd.cpp -o oled_passwd
	g++ -Ofast -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s -Wall  -lArduiPi_OLED -Wno-write-strings oled_clear.cpp -o oled_clear
run:
	./run.sh


