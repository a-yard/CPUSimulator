CPUSimulator_HOME = .
C_SRC = $(CPUSimulator_HOME)/wemu_main.cpp \
		$(CPUSimulator_HOME)/src/BUS/BUS.cpp \
		$(CPUSimulator_HOME)/src/CPU/CPU.cpp \
		$(CPUSimulator_HOME)/src/CPU/ISA/riscv32/riscv32.cpp \
		$(CPUSimulator_HOME)/src/CPU/ISA/ISA.cpp \
		$(CPUSimulator_HOME)/src/CPU/ISA/DiffTestDut.cpp \
		$(CPUSimulator_HOME)/src/Monitor/Monitor.cpp \
		$(CPUSimulator_HOME)/src/Monitor/sdb/sdb.cpp \
		$(CPUSimulator_HOME)/src/Monitor/sdb/expr.cpp \
		$(CPUSimulator_HOME)/src/Monitor/sdb/watchpoint.cpp \
		$(CPUSimulator_HOME)/src/SOC/SOC.cpp \
		$(CPUSimulator_HOME)/src/Drvice/Memory.cpp \
		$(CPUSimulator_HOME)/src/Drvice/BlockDevice.cpp \
		$(CPUSimulator_HOME)/src/Drvice/CharacterDevice.cpp \
		$(CPUSimulator_HOME)/src/Drvice/Flash.cpp \
		$(CPUSimulator_HOME)/src/Drvice/SRAM.cpp \
		$(CPUSimulator_HOME)/src/Drvice/MROM.cpp \
		$(CPUSimulator_HOME)/src/Drvice/UART.cpp \
		$(CPUSimulator_HOME)/src/Drvice/CLINT.cpp \

LIBS  += -lreadline -lhistory



menuconfig:
	@kconfig-mconf KConfig
	@./KConfig.sh
	
GetColCount:
	@echo "代码 行数"
	@find . -type f \( -name "*.cpp" -o -name "*.hpp"  -o -name "*.h" -o -name "*.c" \) -exec cat {} + | wc -l

CreateExec:compileDeviceTree
	@g++ -w  $(C_SRC) -o $(CPUSimulator_HOME)/build/wemu $(LIBS)
compileDeviceTree:
	@dtc -I dts -O dtb -o ./build/HaiTang.dtb ./DeviceTree/HaiTang.dts
run:CreateExec
	@./build/wemu  -t  build/HaiTang.dtb  $(IMG) 

getTest:
	cp -rf /home/wsp/riscv-tests/isa/rv32* ./test/isa/
	echo $(rv32uiPTests)

runOpenSpi: CreateExec compileDeviceTree
	@./build/wemu  -t ./build/HaiTang.dtb    $(CPUSimulator_HOME)/build/fw_jump.bin


makeOpenSBI:
	make -C /home/wsp/StartLinux/opensbi/  PLATFORM=HaiTang CROSS_COMPILE=riscv64-linux-gnu-  FW_DISASM=y
	cp /home/wsp/StartLinux/opensbi/build/platform/HaiTang/firmware/fw_jump.bin build/fw_jump.bin
	cp /home/wsp/StartLinux/opensbi/build/platform/HaiTang/firmware/fw_jump.elf build/fw_jump.elf
	/opt/riscv/bin/riscv64-unknown-elf-objdump -D /home/wsp/StartLinux/opensbi/build/platform/HaiTang/firmware/fw_jump.elf > build/fw_jump.s
	

rundlimage: CreateExec
	@./build/wemu -b -t ./build/HaiTang.dtb    $(CPUSimulator_HOME)/build/DownloadedImage

runtest:CreateExec
	cp ./test/$(name).dump .
	riscv64-unknown-elf-objcopy -O binary ./test/$(name) $(name).bin
	@./build/wemu -b -t ./build/HaiTang.dtb    $(name).bin
	@rm $(name).bin
	@rm $(name).dump


clean:
	@rm -rf ../opensbi/build
	@rm build/disassembly.s
	@rm build/fw_jump.bin
	@rm build/fw_jump*
qemu:
	qemu-system-riscv32 -M virt -smp 4 -m 4G -bios ../opensbi/build/platform/HaiTang/firmware/fw_jump.bin -kernel build/DownloadedImage -display none -serial stdio -s -S
gdb:
	/opt/riscv/bin/riscv64-unknown-elf-gdb ../opensbi/build/platform/HaiTang/firmware/fw_jump.bin
makeqemu:
	make -C /home/wsp/StartLinux/opensbi/  CROSS_COMPILE=riscv64-linux-gnu-  PLATFORM=generic

get:
	cp /home/wsp/StartLinux/mini-rv32ima/mini-rv32ima/mini-rv32ima .

# /home/wsp/StartLinux/qemu/build/qemu-system-riscv64 -M virt -smp 4 -m 4G \
# -bios opensbi/build/platform/generic/firmware/fw_jump.bin \
# -kernel linux-5.15.180/arch/riscv/boot/Image \
# -initrd buildroot-2025.02/output/images/rootfs.cpio \
# -append "root=/dev/ram" \
# -display none -serial stdio \
# -device virtio-scsi-device  -s -S