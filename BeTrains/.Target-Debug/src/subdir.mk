################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/BeTrains.cpp \
../src/BeTrainsEntry.cpp 

OBJS += \
./src/BeTrains.o \
./src/BeTrainsEntry.o 

CPP_DEPS += \
./src/BeTrains.d \
./src/BeTrainsEntry.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: bada C++ Compiler'
	arm-samsung-nucleuseabi-g++ -D_DEBUG -DSHP -I"C:/bada/2.0.0/include" -I"C:/Users/Jan/BeTrains.Bada/BeTrains.Bada/BeTrains/inc" -O0 -g -Wall -c -funsigned-char -fshort-wchar -fpic -march=armv7-a -mthumb -mthumb-interwork -mfpu=vfpv3 -mfloat-abi=hard -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	arm-samsung-nucleuseabi-g++ -D_DEBUG -DSHP -I"C:/bada/2.0.0/include" -I"C:/Users/Jan/BeTrains.Bada/BeTrains.Bada/BeTrains/inc" -O0 -g -Wall -E -funsigned-char -fshort-wchar -fpic -march=armv7-a -mthumb -mthumb-interwork -mfpu=vfpv3 -mfloat-abi=hard -o"C:/bada/2.0.0/IDE/workspace/repository/BeTrains/Target-Debug/$(notdir $(basename $@).i)" "$<"
	@echo 'Finished building: $<'
	@echo ' '


