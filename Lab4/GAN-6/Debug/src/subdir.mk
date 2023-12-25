################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/main.cpp \
../src/network.cpp 

OBJS += \
./src/main.o \
./src/network.o 

CPP_DEPS += \
./src/main.d \
./src/network.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: SDS++ Compiler'
	sds++ -Wall -O0 -g -I"../src" -c -fmessage-length=0 -MT"$@" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<" -sds-hw forward_propagation network.cpp  -clkid 1 -sds-end -sds-sys-config linux -sds-proc a9_0 -sds-pf "zybo"
	@echo 'Finished building: $<'
	@echo ' '


