################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Lissandra/delayer/delayer.c 

OBJS += \
./Lissandra/delayer/delayer.o 

C_DEPS += \
./Lissandra/delayer/delayer.d 


# Each subdirectory must supply rules for building sources it contributes
Lissandra/delayer/%.o: ../Lissandra/delayer/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/utnso/workspace/tp-2019-1c-Los-Sinequi/sharedLib" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


