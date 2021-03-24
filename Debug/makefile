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
	@echo '正在调用： C Linker Debug'
	kf8link_debug.exe -O3 KF8A100GQS_monitor.lib libkf8v4.lib KF8A100GQS.lib KF8_Touch_Fun.lib -s"E:/KungFuIDE/kfl/KF8A100GQS.kfl" -o "EF1E-A.hex" $(OBJS) $(USER_RELS) $(LIBS)
	@echo '已结束构建目标： $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# 其他目标
clean:
	-$(RM) $(OBJS)$(EXECUTABLES)$(C_DEPS) EF1E-A.hex
	-@echo ' '

post-build:
	-kf8exec_debug.exe EF1E-A
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
