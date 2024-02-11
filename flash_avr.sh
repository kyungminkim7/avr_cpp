#!/bin/bash

#-------------------------------------
# Flashes a binary program onto the AVR
#-------------------------------------

# Parse arguments
scriptName=$(basename $0)

usage() {
    echo "Usage: $scriptName -p <PROGRAMMER> -m <MCU> <PROGRAM>"
    echo "  -p|--programmer <PROGRAMMER>"
    echo "  -m|--mcu <MCU>"
}

ARGS=$(getopt --name "$scriptName" --options 'p:m:' --longoptions 'programmer:,mcu:' -- "$@")

if [[ $? -ne 0 ]]; then
    usage
    exit 1;
fi

eval set -- "$ARGS"
unset ARGS

while true; do
    case "$1" in
        '-p'|'--programmer')
            PROGRAMMER="$2"
            shift 2
            continue
        ;;

        '-m'|'--mcu')
            MCU="$2"
            shift 2
            continue
        ;;

        '--')
            shift
            break
        ;;

        *)
            usage
            exit 1
        ;;
    esac
done

if [ -z "$PROGRAMMER" ] || [ -z "$MCU" ]; then
    echo "ERROR: Missing arguments"
    usage
    exit 1
fi

# Flash AVR
elfFilePath="$1"
elfFileName="$(basename $elfFilePath)"
elfBaseName="${elfFileName%%.*}"
elfDir="$(dirname $elfFilePath)"
hexFilePath="${elfDir}/${elfBaseName}.hex"

avr-size --format=avr --mcu=${MCU} "$elfFilePath"
avr-objcopy --output-target ihex --remove-section .eeprom "$elfFilePath" "$hexFilePath"
avrdude -c "$PROGRAMMER" -p "$MCU" -U "flash:w:${hexFilePath}:i"