################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/BetrainsPrototype.cpp \
../src/BetrainsPrototypeEntry.cpp \
../src/Connection.cpp \
../src/IRailConnection.cpp \
../src/ItemFactory.cpp \
../src/MainOptionList.cpp \
../src/PlannerSearchForm.cpp \
../src/TextItem.cpp \
../src/TrainsResultsForm.cpp 

OBJS += \
./src/BetrainsPrototype.o \
./src/BetrainsPrototypeEntry.o \
./src/Connection.o \
./src/IRailConnection.o \
./src/ItemFactory.o \
./src/MainOptionList.o \
./src/PlannerSearchForm.o \
./src/TextItem.o \
./src/TrainsResultsForm.o 

CPP_DEPS += \
./src/BetrainsPrototype.d \
./src/BetrainsPrototypeEntry.d \
./src/Connection.d \
./src/IRailConnection.d \
./src/ItemFactory.d \
./src/MainOptionList.d \
./src/PlannerSearchForm.d \
./src/TextItem.d \
./src/TrainsResultsForm.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: bada C++ Compiler'
	i686-mingw32-g++ -D_DEBUG -DSHP -DBUILD_DLL -I"C:/bada/1.1.0/include" -I"C:/Users/Jan/Bada/BetrainsApp/BeTrainsPrototype/inc" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	i686-mingw32-g++ -D_DEBUG -DSHP -DBUILD_DLL -I"C:/bada/1.1.0/include" -I"C:/Users/Jan/Bada/BetrainsApp/BeTrainsPrototype/inc" -O0 -g3 -Wall -E -fmessage-length=0 -o"C:/bada/1.1.0/IDE/workspace/repository/BeTrainsPrototype/Simulator-Debug/$(notdir $(basename $@).i)" "$<"
	@echo 'Finished building: $<'
	@echo ' '


