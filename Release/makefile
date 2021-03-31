################################################################################
# 自动生成的文件。不要编辑！
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

-include $(C_DEPS)

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# 所有目标
all: EF1E-A.hex

# 工具调用
EF1E-A.hex: $(OBJS) $(USER_RELS)
	@echo '正在构建目标： $@'
	@echo '正在调用： C Project Linker Release'
	kf8link -O3 -c -m libkf8v4.lib KF8A200GQS.lib KF8_Touch_Fun.lib -s"C:/ChipONCC/kfl/KF8A200GQS.kfl" -o "EF1E-A.hex" $(OBJS) $(USER_RELS) $(LIBS)
	@echo '已结束构建目标： $@'
	@echo ' '

# 其他目标
clean:
	-$(RM) $(OBJS)$(EXECUTABLES)$(C_DEPS) EF1E-A.hex
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
