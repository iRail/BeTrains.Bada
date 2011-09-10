################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Controller.cpp \
../src/FormLiveboard.cpp \
../src/FormRouteplanner.cpp \
../src/HeaderForm.cpp \
../src/tabtest.cpp \
../src/tabtestEntry.cpp 

OBJS += \
./src/Controller.o \
./src/FormLiveboard.o \
./src/FormRouteplanner.o \
./src/HeaderForm.o \
./src/tabtest.o \
./src/tabtestEntry.o 

CPP_DEPS += \
./src/Controller.d \
./src/FormLiveboard.d \
./src/FormRouteplanner.d \
./src/HeaderForm.d \
./src/tabtest.d \
./src/tabtestEntry.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: bada C++ Compiler'
	arm-samsung-nucleuseabi-g++ -D_DEBUG -DSHP -I"C:/bada/2.0.0/include" -I"C:/bada/2.0.0/IDE/workspace/BeTrains/inc" -O0 -g -Wall -c -funsigned-char -fshort-wchar -fpic -march=armv7-a -mthumb -mthumb-interwork -mfpu=vfpv3 -mfloat-abi=hard -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	arm-samsung-nucleuseabi-g++ -D_DEBUG -DSHP -I"C:/bada/2.0.0/include" -I"C:/bada/2.0.0/IDE/workspace/BeTrains/inc" -O0 -g -Wall -E -funsigned-char -fshort-wchar -fpic -march=armv7-a -mthumb -mthumb-interwork -mfpu=vfpv3 -mfloat-abi=hard -o"C:/bada/2.0.0/IDE/workspace/repository/BeTrains/Target-Debug/$(notdir $(basename $@).i)" "$<"
	@echo 'Finished building: $<'
	@echo ' '


