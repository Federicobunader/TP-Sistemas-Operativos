################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Lissandra/select/subdir.mk
-include Lissandra/memtable/subdir.mk
-include Lissandra/insert/subdir.mk
-include Lissandra/dump/subdir.mk
-include Lissandra/drop/subdir.mk
-include Lissandra/describe/subdir.mk
-include Lissandra/delayer/subdir.mk
-include Lissandra/create/subdir.mk
-include Lissandra/connection/subdir.mk
-include Lissandra/compactador/subdir.mk
-include Lissandra/api/subdir.mk
-include Fs/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: FileSystem

dependents:
	-cd /home/utnso/workspace/tp-2019-1c-Los-Sinequi/sharedLib/Debug && $(MAKE) all

# Tool invocations
FileSystem: $(OBJS) $(USER_OBJS) /home/utnso/workspace/tp-2019-1c-Los-Sinequi/sharedLib/Debug/libsharedLib.so
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	gcc -L"/home/utnso/workspace/tp-2019-1c-Los-Sinequi/sharedLib/Debug" -o "FileSystem" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) FileSystem
	-@echo ' '

.PHONY: all clean dependents
/home/utnso/workspace/tp-2019-1c-Los-Sinequi/sharedLib/Debug/libsharedLib.so:

-include ../makefile.targets
