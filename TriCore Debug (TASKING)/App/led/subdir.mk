################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../App/led/App_Led.c" 

COMPILED_SRCS += \
"App/led/App_Led.src" 

C_DEPS += \
"./App/led/App_Led.d" 

OBJS += \
"App/led/App_Led.o" 


# Each subdirectory must supply rules for building sources it contributes
"App/led/App_Led.src":"../App/led/App_Led.c" "App/led/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc27xd "-fC:/Users/USER/AURIX-v1.10.28-workspace/TC275_ACT_tb/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"App/led/App_Led.o":"App/led/App_Led.src" "App/led/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-App-2f-led

clean-App-2f-led:
	-$(RM) ./App/led/App_Led.d ./App/led/App_Led.o ./App/led/App_Led.src

.PHONY: clean-App-2f-led

