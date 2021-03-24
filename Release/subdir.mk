################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GPIO.c \
../Led.c \
../OSC.c \
../SoftSpi.c \
../Work.c \
../config_set.c \
../main.c \
../timer.c 

OBJS += \
./GPIO.o \
./Led.o \
./OSC.o \
./SoftSpi.o \
./Work.o \
./config_set.o \
./main.o \
./timer.o 

C_DEPS += \
./GPIO.dep \
./Led.dep \
./OSC.dep \
./SoftSpi.dep \
./Work.dep \
./config_set.dep \
./main.dep \
./timer.dep 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo '正在构建文件： $<'
	@echo '正在调用： C Compiler'
	kf8cc -c -pKF8A200GQS -I"E:\KungFuIDE\include" -I"C:\Users\Rick\Desktop\EF1E\程序\EF1E-2" -o"$@" "$<"
	@echo '已结束构建： $<'
	@echo ' '


