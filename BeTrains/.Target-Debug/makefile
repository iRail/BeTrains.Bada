################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

REPOSITORY_ROOT := C:/bada/2.0.0/IDE/workspace/repository/BeTrains/Target-Debug

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/view/subdir.mk
-include src/model/subdir.mk
-include src/controller/subdir.mk
-include src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: BeTrains.exe

# Tool invocations
BeTrains.exe: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: bada C++ Linker'
	@echo 'ldflags: -L"C:/bada/2.0.0/Model/WaveWVGA/Target" -L"C:/Users/Jan/BeTrains.Bada/BeTrains.Bada/BeTrains/lib" -shared -march=armv7-a -mthumb -mthumb-interwork -mfpu=vfpv3 -mfloat-abi=hard -o"BeTrains.exe" ./src/view/FormLiveboard.o ./src/view/FormRouteplanner.o ./src/view/HeaderForm.o ./src/view/LiveBoardResults.o ./src/view/RoutePlannerResults.o ./src/view/SelectStationForm.o ./src/view/Utils.o ./src/model/AppData.o ./src/model/Connection.o ./src/model/ConnectionNode.o ./src/model/IRailAPI.o ./src/model/LiveBoardRequest.o ./src/model/LiveBoardResult.o ./src/model/Request.o ./src/model/Station.o ./src/model/Trip.o ./src/model/Vehicle.o ./src/controller/Controller.o ./src/controller/LiveBoardRequestManager.o ./src/controller/RouteRequestManager.o ./src/BeTrains.o ./src/BeTrainsEntry.o '
	arm-samsung-nucleuseabi-g++ @ldflags @ldobjs  $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C++_DEPS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(CXX_DEPS)$(C_UPPER_DEPS) BeTrains.exe $(REPOSITORY_ROOT)/temp/*  $(REPOSITORY_ROOT)/*
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
