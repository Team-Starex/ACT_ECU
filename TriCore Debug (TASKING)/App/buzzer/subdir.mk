################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../App/buzzer/App_Buzzer.c" 

COMPILED_SRCS += \
"App/buzzer/App_Buzzer.src" 

C_DEPS += \
"./App/buzzer/App_Buzzer.d" 

OBJS += \
"App/buzzer/App_Buzzer.o" 


# Each subdirectory must supply rules for building sources it contributes
"App/buzzer/App_Buzzer.src":"../App/buzzer/App_Buzzer.c" "App/buzzer/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc27xd "-fC:/Users/USER/AURIX-v1.10.28-workspace/TC275_ACT_tb/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"App/buzzer/App_Buzzer.o":"App/buzzer/App_Buzzer.src" "App/buzzer/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-App-2f-buzzer

clean-App-2f-buzzer:
	-$(RM) ./App/buzzer/App_Buzzer.d ./App/buzzer/App_Buzzer.o ./App/buzzer/App_Buzzer.src

.PHONY: clean-App-2f-buzzer

