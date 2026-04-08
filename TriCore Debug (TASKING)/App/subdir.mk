################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../App/App_Buzzer.c" \
"../App/App_DfPlayer.c" \
"../App/App_Led.c" \
"../App/App_Scheduler.c" \
"../App/App_Servo.c" \
"../App/Cpu0_Main.c" 

COMPILED_SRCS += \
"App/App_Buzzer.src" \
"App/App_DfPlayer.src" \
"App/App_Led.src" \
"App/App_Scheduler.src" \
"App/App_Servo.src" \
"App/Cpu0_Main.src" 

C_DEPS += \
"./App/App_Buzzer.d" \
"./App/App_DfPlayer.d" \
"./App/App_Led.d" \
"./App/App_Scheduler.d" \
"./App/App_Servo.d" \
"./App/Cpu0_Main.d" 

OBJS += \
"App/App_Buzzer.o" \
"App/App_DfPlayer.o" \
"App/App_Led.o" \
"App/App_Scheduler.o" \
"App/App_Servo.o" \
"App/Cpu0_Main.o" 


# Each subdirectory must supply rules for building sources it contributes
"App/App_Buzzer.src":"../App/App_Buzzer.c" "App/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc27xd "-fC:/Users/USER/AURIX-v1.10.28-workspace/TC275_ACT_ECU/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"App/App_Buzzer.o":"App/App_Buzzer.src" "App/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"App/App_DfPlayer.src":"../App/App_DfPlayer.c" "App/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc27xd "-fC:/Users/USER/AURIX-v1.10.28-workspace/TC275_ACT_ECU/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"App/App_DfPlayer.o":"App/App_DfPlayer.src" "App/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"App/App_Led.src":"../App/App_Led.c" "App/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc27xd "-fC:/Users/USER/AURIX-v1.10.28-workspace/TC275_ACT_ECU/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"App/App_Led.o":"App/App_Led.src" "App/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"App/App_Scheduler.src":"../App/App_Scheduler.c" "App/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc27xd "-fC:/Users/USER/AURIX-v1.10.28-workspace/TC275_ACT_ECU/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"App/App_Scheduler.o":"App/App_Scheduler.src" "App/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"App/App_Servo.src":"../App/App_Servo.c" "App/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc27xd "-fC:/Users/USER/AURIX-v1.10.28-workspace/TC275_ACT_ECU/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"App/App_Servo.o":"App/App_Servo.src" "App/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"App/Cpu0_Main.src":"../App/Cpu0_Main.c" "App/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc27xd "-fC:/Users/USER/AURIX-v1.10.28-workspace/TC275_ACT_ECU/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"App/Cpu0_Main.o":"App/Cpu0_Main.src" "App/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-App

clean-App:
	-$(RM) ./App/App_Buzzer.d ./App/App_Buzzer.o ./App/App_Buzzer.src ./App/App_DfPlayer.d ./App/App_DfPlayer.o ./App/App_DfPlayer.src ./App/App_Led.d ./App/App_Led.o ./App/App_Led.src ./App/App_Scheduler.d ./App/App_Scheduler.o ./App/App_Scheduler.src ./App/App_Servo.d ./App/App_Servo.o ./App/App_Servo.src ./App/Cpu0_Main.d ./App/Cpu0_Main.o ./App/Cpu0_Main.src

.PHONY: clean-App

