################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/View/IView.cpp 

OBJS += \
./src/View/IView.o 

CPP_DEPS += \
./src/View/IView.d 


# Each subdirectory must supply rules for building sources it contributes
src/View/%.o: ../src/View/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: bada C++ Compiler'
	i686-mingw32-g++ -D_DEBUG -DSHP -DBUILD_DLL -I"C:/bada/1.1.0b1/include" -I"C:/bada/1.1.0b1/IDE/workspace/BeTrains.Bada/BeTrains/inc" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	i686-mingw32-g++ -D_DEBUG -DSHP -DBUILD_DLL -I"C:/bada/1.1.0b1/include" -I"C:/bada/1.1.0b1/IDE/workspace/BeTrains.Bada/BeTrains/inc" -O0 -g3 -Wall -E -fmessage-length=0 -o"C:/bada/1.1.0b1/IDE/workspace/BeTrains.Bada/repository/BeTrains/Simulator-Debug/$(notdir $(basename $@).i)" "$<"
	@echo 'Finished building: $<'
	@echo ' '


