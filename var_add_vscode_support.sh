#!/bin/bash

# -e  Exit immediately if a command exits with a non-zero status.
set -e

readonly SCRIPT_NAME=${0##*/}
readonly BSP_BASE_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
readonly PATH_TO_ARM_TOOLCHAIN="${BSP_BASE_DIR}/../gcc-arm-none-eabi-9-2020-q2-update"
CM_ID=cm_c0
CM4_CORE_DIR=cm4_core0

usage()
{
	echo
	echo "This script generates a .vscode folder to add Visual Studio Code support to freertos-variscite demos"
	echo
	echo " Usage: $0 OPTIONS"
	echo
	echo " OPTIONS:"
	echo " -b <dart_mx8mm|som_mx8mn|dart_mx8mp|som_mx8mp|dart_mx8mq>                                 board folder (DART-MX8M)."
	echo " -c <cm_c0|cm_c1>                                                                          optional cortex-m core id, if missing the default is cm_c0"
	echo " -d <GDBServer folder>"
	echo " -e <options>"
	echo "    path/to/example/folder                                                                 (armgcc folder parent, where will be generated .vscode folder)"
	echo "    all                                                                                    (to generate .vscode folder for all demos)"
	echo " -t <tcm/ddr>				                                                   ram target"
	echo
	echo "Examples of use for DART-MX8M:"
	echo "  generate .vscode folder for hello_world demo: ./${SCRIPT_NAME} -b dart_mx8mq -e boards/dart_mx8mq/demo_apps/hello_world -t ddr -d /opt/SEGGER/JLink_Linux_V754c_x86_64"
	echo "  generate .vscode folder for all demos:        ./${SCRIPT_NAME} -b dart_mx8mq -e all -t ddr -d /opt/SEGGER/JLink_Linux_V754c_x86_64"
	echo
}

check_params()
{
	if [ "$BSP_BASE_DIR" != "$PWD" ]; then
		echo "ERROR0: Script must be run from $BSP_BASE_DIR"
		usage
		exit 1
	fi

	if [[ ! -d boards/$BOARD_DIR ]] ; then
		echo "ERROR1: \"boards/$BOARD_DIR\" does not exist"
		usage
		exit 1
	fi

	if [[ ! -d $GDBSERVER_DIR ]] ; then
		echo "ERROR2: \"$GDBSERVER_DIR\" does not exist"
		echo "Download and Install J-Link Software: https://www.segger.com/downloads/jlink/"
		echo "e.g. sudo dpkg -i ~/Downloads/JLink_Linux_V754d_x86_64.deb"
		usage
		exit 1
	fi

	if [[ $PATH_TO_DEMO_SRC != "all" && ! -d $PATH_TO_DEMO_SRC ]] ; then
		echo "ERROR3: \"$PATH_TO_DEMO_SRC\" does not exist"
		usage
		exit 1
	fi

	if [[ $RAM_TARGET != "tcm" && $RAM_TARGET != "ddr" ]]; then
		echo "ERROR4: \"$RAM_TARGET\" does not exist"
		usage
		exit 1
	fi

	if [[ ! -d $PATH_TO_ARM_TOOLCHAIN ]] ; then
		echo "ERROR5: \"$PATH_TO_ARM_TOOLCHAIN\" does not exist"
		echo "Download the SDK:"
		echo "wget https://developer.arm.com/-/media/Files/downloads/gnu-rm/9-2020q2/gcc-arm-none-eabi-9-2020-q2-update-x86_64-linux.tar.bz2"
		echo "tar xvf gcc-arm-none-eabi-9-2020-q2-update-x86_64-linux.tar.bz2"
		usage
		exit 1
	fi

	if [[ $CM_ID != "cm_c0" && $CM_ID != "cm_c1" ]]; then
		echo "ERROR6: \"$CM_ID\" invalid parameter. Use cm_c0/cm_c1"
		usage
		exit 1
	fi
}

make_demo_vscode()
{
	DEMO_SRC=$1
	echo "generating .vscode for ${DEMO_SRC}"

	# Get EXECUTABLE_NAME
	EXECUTABLE_NAME_ELF="$(cat ${DEMO_SRC}/armgcc/CMakeLists.txt | grep -oP '(?<=MCUX_SDK_PROJECT_NAME ).+?(?=\))')"
	EXECUTABLE_NAME_BIN="$(cat ${DEMO_SRC}/armgcc/CMakeLists.txt | grep "{EXECUTABLE_OUTPUT_PATH}" | awk '{print $3}' | grep -oP '(?<=OUTPUT_PATH}/).+?(?=\))')"

	# set build target
	if [[ $RAM_TARGET == "tcm" ]] ; then
		BUILD_TARGET="debug"
	else
		BUILD_TARGET="ddr_debug"
	fi

	# cp vscode templates to example source folder
	if [[ -d $DEMO_SRC/.vscode ]] ; then
		rm -r $DEMO_SRC/.vscode
	fi
	mkdir $DEMO_SRC/.vscode
	cp -r var-vscode-template/* $DEMO_SRC/.vscode

	# cp svd file
	cp $SOC_INCLUDE_PATH/$SVD_FILE_NAME.xml $DEMO_SRC/.vscode/$SVD_FILE_NAME.svd

	# adjust settings.json
	sed -i "s|t_path_to_arm_gcc_dir|$PATH_TO_ARM_TOOLCHAIN|g" "$DEMO_SRC/.vscode/settings.json"
	sed -i "s|t_path_to_gdb_server_dir|$GDBSERVER_DIR|g" "$DEMO_SRC/.vscode/settings.json"
	sed -i "s|t_path_to_soc_include|$SOC_INCLUDE_PATH|g" "$DEMO_SRC/.vscode/settings.json"
	sed -i "s|t_path_to_rtos_include|$RTOS_INCLUDE_PATH|g" "$DEMO_SRC/.vscode/settings.json"
	sed -i "s|t_path_to_middleware_include|$MIDDLEWARE_INCLUDE_PATH|g" "$DEMO_SRC/.vscode/settings.json"
	sed -i "s|t_build_target|$BUILD_TARGET|g" "$DEMO_SRC/.vscode/settings.json"

	# adjust launch.json
	sed -i "s|t_path_to_arm_toolchain|$PATH_TO_ARM_TOOLCHAIN/bin|g" "$DEMO_SRC/.vscode/launch.json"
	sed -i "s|t_path_to_JLinkScript|$PATH_TO_JLINKSCRIPT|g" "$DEMO_SRC/.vscode/launch.json"
	sed -i "s|t_path_tosvd_file|\${workspaceRoot}/.vscode/$SVD_FILE_NAME.svd|g" "$DEMO_SRC/.vscode/launch.json"
	sed -i "s|t_path_to_executable|armgcc/\${config:VARISCITE.BUILD_TARGET}/$EXECUTABLE_NAME_ELF|g" "$DEMO_SRC/.vscode/launch.json"
	sed -i "s|t_soc-cm|$CM_DEVICE_ID|g" "$DEMO_SRC/.vscode/launch.json"
	sed -i "s|t_cortex-m-cpu|$CORTEX_M_CPU|g" "$DEMO_SRC/.vscode/launch.json"
}

make_vscode()
{
	case $BOARD_DIR in
	dart_mx8mm)
		readonly FREE_RTOS_DEVICE_DIR="MIMX8MM6"
		readonly DEVICE_SPECIFIC_CFG_FILE="${BSP_BASE_DIR}/devices/$FREE_RTOS_DEVICE_DIR/system_MIMX8MM6_cm4.c"
		readonly CM_DEVICE_ID="MIMX8MM6_M4"
		readonly PATH_TO_JLINKSCRIPT=iMX8MM/NXP_iMX8M_Connect_CortexM4.JLinkScript
		readonly SVD_FILE_NAME=MIMX8MM6_cm4
		readonly CORTEX_M_CPU=cortex-m4
		;;

	dart_mx8mp|som_mx8mp)
		readonly FREE_RTOS_DEVICE_DIR="MIMX8ML8"
		readonly CM_DEVICE_ID="MIMX8ML8_M7"
		readonly PATH_TO_JLINKSCRIPT=iMX8ML/NXP_iMX8M_Connect_CortexM7.JLinkScript
		readonly SVD_FILE_NAME=MIMX8ML8_cm7
		# The correct CORTEX_M_CPU is cortex-m7 but code doesen't recognize it !
		readonly CORTEX_M_CPU=cortex-m4
		;;

	dart_mx8mq)
		readonly FREE_RTOS_DEVICE_DIR="MIMX8MQ6"
		readonly DEVICE_SPECIFIC_CFG_FILE="${BSP_BASE_DIR}/devices/$FREE_RTOS_DEVICE_DIR/system_MIMX8MQ6_cm4.c"
		readonly CM_DEVICE_ID="MIMX8MQ6_M4"
		readonly PATH_TO_JLINKSCRIPT=iMX8M/NXP_iMX8M_Connect_CortexM4.JLinkScript
		readonly SVD_FILE_NAME=MIMX8MQ6_cm4
		readonly CORTEX_M_CPU=cortex-m4
		;;

	som_mx8mn)
		readonly FREE_RTOS_DEVICE_DIR="MIMX8MN6"
		readonly CM_DEVICE_ID="MIMX8MN6_M7"
		readonly PATH_TO_JLINKSCRIPT=iMX8MN/NXP_iMX8M_Connect_CortexM7.JLinkScript
		readonly SVD_FILE_NAME=MIMX8MN6_cm7
		# The correct CORTEX_M_CPU is cortex-m7 but code doesen't recognize it !
		readonly CORTEX_M_CPU=cortex-m4
		;;
	esac

	readonly SOC_INCLUDE_PATH="${BSP_BASE_DIR}/devices/${FREE_RTOS_DEVICE_DIR}"
	readonly RTOS_INCLUDE_PATH="${BSP_BASE_DIR}/rtos"
	readonly MIDDLEWARE_INCLUDE_PATH="${BSP_BASE_DIR}/middleware"

	if [[ $PATH_TO_DEMO_SRC == "all" ]] ; then
		if [[ $BOARD_DIR != "som_mx8qm" ]] ; then
			for i in $(find $BSP_BASE_DIR/boards/$BOARD_DIR -name armgcc)
			do
				cd $i;
				cd ..
				path_to_demo_src=$PWD
				cd $BSP_BASE_DIR
				make_demo_vscode "$path_to_demo_src"
			done
		else
			for i in $(find $BSP_BASE_DIR/boards/$BOARD_DIR -name $CM4_CORE_DIR)
			do
				if [[ -d "$i/armgcc" ]] ; then
					cd $i;
					path_to_demo_src=$PWD
					cd $BSP_BASE_DIR
					make_demo_vscode "$path_to_demo_src"
				fi
			done
		fi
	else
		make_demo_vscode "$PATH_TO_DEMO_SRC"
		echo
		echo "Open new VS Code project directory:"
		echo "$ code $BSP_BASE_DIR/$PATH_TO_DEMO_SRC"
		echo
	fi

	#recommondations
	if [ $CORTEX_M_CPU == "cortex-m4" ] && [ $RAM_TARGET == "ddr" ] && [ $CM_DEVICE_ID != "MIMX8MN6_M7" ] && [ $CM_DEVICE_ID != "MIMX8ML8_M7" ]; then
		echo
		echo "NOTE: to debug applications mapped in DDR, is mandatory to not enable cache"
		echo "      the function to be changed is SystemInit() in the $DEVICE_SPECIFIC_CFG_FILE file"
		echo
	fi
}

while getopts :b:c:d:e:t: OPTION;
do
	case $OPTION in
	b)
		readonly BOARD_DIR=$OPTARG
		;;
	c)
		CM_ID=$OPTARG
		;;
	d)
		readonly GDBSERVER_DIR=$OPTARG
		;;
	e)
		readonly PATH_TO_DEMO_SRC=$OPTARG
		;;
	t)
		readonly RAM_TARGET=$OPTARG
		;;
	*)
		usage
		exit 1
		;;
	esac
done

check_params
make_vscode

exit 0
