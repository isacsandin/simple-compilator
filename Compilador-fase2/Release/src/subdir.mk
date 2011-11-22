################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Compilador.cpp \
../src/Hash.cpp \
../src/LexAnalyser.cpp 

OBJS += \
./src/Compilador.o \
./src/Hash.o \
./src/LexAnalyser.o 

CPP_DEPS += \
./src/Compilador.d \
./src/Hash.d \
./src/LexAnalyser.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


