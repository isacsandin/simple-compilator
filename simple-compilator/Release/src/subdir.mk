################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Compilador.cpp \
../src/Hash.cpp \
../src/LexAnalyser.cpp \
../src/SynAnalyzer.cpp 

OBJS += \
./src/Compilador.o \
./src/Hash.o \
./src/LexAnalyser.o \
./src/SynAnalyzer.o 

CPP_DEPS += \
./src/Compilador.d \
./src/Hash.d \
./src/LexAnalyser.d \
./src/SynAnalyzer.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


