################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../Driver/stm/Driver_Stm.c" 

COMPILED_SRCS += \
"Driver/stm/Driver_Stm.src" 

C_DEPS += \
"./Driver/stm/Driver_Stm.d" 

OBJS += \
"Driver/stm/Driver_Stm.o" 


# Each subdirectory must supply rules for building sources it contributes
"Driver/stm/Driver_Stm.src":"../Driver/stm/Driver_Stm.c" "Driver/stm/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc27xd "-fC:/Users/USER/AURIX-v1.10.28-workspace/TC275_ACT_ECU/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"Driver/stm/Driver_Stm.o":"Driver/stm/Driver_Stm.src" "Driver/stm/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-Driver-2f-stm

clean-Driver-2f-stm:
	-$(RM) ./Driver/stm/Driver_Stm.d ./Driver/stm/Driver_Stm.o ./Driver/stm/Driver_Stm.src

.PHONY: clean-Driver-2f-stm

