################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CalendarTest.cpp \
../src/CalendarTestEntry.cpp \
../src/Form1.cpp 

OBJS += \
./src/CalendarTest.o \
./src/CalendarTestEntry.o \
./src/Form1.o 

CPP_DEPS += \
./src/CalendarTest.d \
./src/CalendarTestEntry.d \
./src/Form1.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: bada C++ Compiler'
	arm-samsung-nucleuseabi-g++ -D_DEBUG -DSHP -I"C:/bada/2.0.0/include" -I"C:/bada/2.0.0/IDE/workspace/CalendarTest/inc" -O0 -g -Wall -c -funsigned-char -fshort-wchar -fpic -march=armv7-a -mthumb -mthumb-interwork -mfpu=vfpv3 -mfloat-abi=hard -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	arm-samsung-nucleuseabi-g++ -D_DEBUG -DSHP -I"C:/bada/2.0.0/include" -I"C:/bada/2.0.0/IDE/workspace/CalendarTest/inc" -O0 -g -Wall -E -funsigned-char -fshort-wchar -fpic -march=armv7-a -mthumb -mthumb-interwork -mfpu=vfpv3 -mfloat-abi=hard -o"C:/bada/2.0.0/IDE/workspace/repository/CalendarTest/Target-Debug/$(notdir $(basename $@).i)" "$<"
	@echo 'Finished building: $<'
	@echo ' '


