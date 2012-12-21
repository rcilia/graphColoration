################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ColorationEngine.cpp \
../src/Graph.cpp \
../src/Main.cpp \
../src/Vertex.cpp 

OBJS += \
./src/ColorationEngine.o \
./src/Graph.o \
./src/Main.o \
./src/Vertex.o 

CPP_DEPS += \
./src/ColorationEngine.d \
./src/Graph.d \
./src/Main.d \
./src/Vertex.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


