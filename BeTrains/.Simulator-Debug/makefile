################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

REPOSITORY_ROOT := C:/bada/1.1.0b1/IDE/workspace/BeTrains.Bada/repository/BeTrains/Simulator-Debug

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/View/subdir.mk
-include src/Model/subdir.mk
-include src/Controller/subdir.mk
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
	@echo 'ldflags: -L"C:/bada/1.1.0b1/Model/WaveWQ_LP1/Simulator" -L"C:/bada/1.1.0b1/Lib" -L"C:/bada/1.1.0b1/IDE/workspace/BeTrains.Bada/BeTrains/lib" -shared -o"BeTrains.exe" ./src/View/IView.o ./src/Model/Connection.o ./src/Model/ConnectionNode.o ./src/Model/Request.o ./src/Model/Station.o ./src/Model/Trip.o ./src/Controller/Controller.o ./src/Controller/IRoutePlannerController.o ./src/BeTrains.o ./src/BeTrainsEntry.o '
	i686-mingw32-g++ @ldflags @ldobjs  $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C++_DEPS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(CXX_DEPS)$(C_UPPER_DEPS) BeTrains.exe $(REPOSITORY_ROOT)/*
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
