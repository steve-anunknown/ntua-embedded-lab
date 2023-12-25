################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/calcDist.cpp \
../src/main.cpp 

OBJS += \
./src/calcDist.o \
./src/main.o 

CPP_DEPS += \
./src/calcDist.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: SDS++ Compiler'
	sds++ -Wall -O0 -g -I"../src" -c -fmessage-length=0 -MT"$@" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<" -sds-hw calcDistancesHW calcDist.cpp  -clkid 1 -sds-end -perf-root main -perf-est swdata.xml -perf-funcs calcDistancesHW -sds-sys-config linux -sds-proc a9_0 -sds-pf "zybo"
	@echo 'Finished building: $<'
	@echo ' '


