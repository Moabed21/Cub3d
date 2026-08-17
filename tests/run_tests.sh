#!/usr/bin/env bash

# ==============================================================================
#                       Cub3D Comprehensive Test Suite
# ==============================================================================

# Colors & Formatting
BOLD="\033[1m"
DIM="\033[2m"
CYAN="\033[36m"
GREEN="\033[32m"
RED="\033[31m"
YELLOW="\033[33m"
MAGENTA="\033[35m"
RESET="\033[0m"

# Paths
ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
CUB3D="${ROOT_DIR}/cub3D"
TESTS_DIR="${ROOT_DIR}/tests"
VALID_MAPS_DIR="${TESTS_DIR}/maps/valid"
INVALID_MAPS_DIR="${TESTS_DIR}/maps/invalid"

# Counters
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0
CRASHED_TESTS=0

# Ensure binary is built
if [ ! -f "$CUB3D" ]; then
    echo -e "${YELLOW}Building cub3D executable...${RESET}"
    make -C "$ROOT_DIR"
    if [ ! -f "$CUB3D" ]; then
        echo -e "${RED}Error: Build failed. Please compile cub3D first.${RESET}"
        exit 1
    fi
fi

print_header() {
    echo -e "${BOLD}${CYAN}================================================================${RESET}"
    echo -e "${BOLD}${CYAN}                   Cub3D Test Suite Runner                      ${RESET}"
    echo -e "${BOLD}${CYAN}================================================================${RESET}\n"
}

print_category() {
    local title="$1"
    echo -e "\n${BOLD}${MAGENTA}▶ [Category] ${title}${RESET}"
    echo -e "${DIM}----------------------------------------------------------------${RESET}"
}

# Run a negative test (expects failure with "Error" output)
run_invalid_test() {
    local test_name="$1"
    local map_path="$2"
    TOTAL_TESTS=$((TOTAL_TESTS + 1))

    output=$( "$CUB3D" "$map_path" 2>&1 )
    exit_code=$?

    # Check for crash (signals are > 128)
    if [ $exit_code -gt 128 ]; then
        CRASHED_TESTS=$((CRASHED_TESTS + 1))
        echo -e "  [${RED}CRASH${RESET}] ${test_name} (signal $((exit_code - 128)))"
        return
    fi

    # Check if failed cleanly with error output
    if [ $exit_code -ne 0 ]; then
        first_line=$(echo "$output" | head -n 1)
        err_msg=$(echo "$output" | head -n 2 | tail -n 1)
        if [[ "$first_line" == "Error" ]]; then
            PASSED_TESTS=$((PASSED_TESTS + 1))
            echo -e "  [${GREEN}PASS${RESET}] ${test_name} ${DIM}→ (${err_msg})${RESET}"
        else
            FAILED_TESTS=$((FAILED_TESTS + 1))
            echo -e "  [${RED}FAIL${RESET}] ${test_name} ${YELLOW}(Missing 'Error' prefix)${RESET}"
        fi
    else
        FAILED_TESTS=$((FAILED_TESTS + 1))
        echo -e "  [${RED}FAIL${RESET}] ${test_name} ${YELLOW}(Accepted invalid map with exit 0)${RESET}"
    fi
}

# Run a CLI argument test (expects failure)
run_cli_test() {
    local test_name="$1"
    shift
    TOTAL_TESTS=$((TOTAL_TESTS + 1))

    output=$( "$CUB3D" "$@" 2>&1 )
    exit_code=$?

    if [ $exit_code -gt 128 ]; then
        CRASHED_TESTS=$((CRASHED_TESTS + 1))
        echo -e "  [${RED}CRASH${RESET}] ${test_name} (signal $((exit_code - 128)))"
        return
    fi

    if [ $exit_code -ne 0 ]; then
        first_line=$(echo "$output" | head -n 1)
        err_msg=$(echo "$output" | head -n 2 | tail -n 1)
        if [[ "$first_line" == "Error" ]]; then
            PASSED_TESTS=$((PASSED_TESTS + 1))
            echo -e "  [${GREEN}PASS${RESET}] ${test_name} ${DIM}→ (${err_msg})${RESET}"
        else
            FAILED_TESTS=$((FAILED_TESTS + 1))
            echo -e "  [${RED}FAIL${RESET}] ${test_name} ${YELLOW}(Missing 'Error' prefix)${RESET}"
        fi
    else
        FAILED_TESTS=$((FAILED_TESTS + 1))
        echo -e "  [${RED}FAIL${RESET}] ${test_name} ${YELLOW}(Accepted invalid CLI args with exit 0)${RESET}"
    fi
}

# Run a positive test (expects clean launch and raycasting loop)
run_valid_test() {
    local test_name="$1"
    local map_path="$2"
    TOTAL_TESTS=$((TOTAL_TESTS + 1))

    # Use timeout to test graphics loop initialization without hanging
    output=$( timeout 0.4s "$CUB3D" "$map_path" 2>&1 )
    exit_code=$?

    # Exit code 124 means timeout killed it -> it entered the loop successfully!
    if [ $exit_code -eq 124 ]; then
        PASSED_TESTS=$((PASSED_TESTS + 1))
        echo -e "  [${GREEN}PASS${RESET}] ${test_name} ${DIM}(Graphics & raycasting loop running successfully)${RESET}"
    elif [ $exit_code -gt 128 ]; then
        CRASHED_TESTS=$((CRASHED_TESTS + 1))
        echo -e "  [${RED}CRASH${RESET}] ${test_name} (Signal $((exit_code - 128)))"
    elif [ $exit_code -ne 0 ]; then
        FAILED_TESTS=$((FAILED_TESTS + 1))
        err_msg=$(echo "$output" | head -n 2)
        echo -e "  [${RED}FAIL${RESET}] ${test_name} ${YELLOW}(Rejected valid map: ${err_msg})${RESET}"
    else
        # In case it exited immediately with 0
        PASSED_TESTS=$((PASSED_TESTS + 1))
        echo -e "  [${GREEN}PASS${RESET}] ${test_name} ${DIM}(Clean exit 0)${RESET}"
    fi
}

# Main execution
print_header

# 1. CLI Arguments Tests
print_category "1. CLI Arguments & File Opening"
run_cli_test "No arguments"
run_cli_test "Too many arguments" "map1.cub" "map2.cub"
run_cli_test "Non-existent file" "non_existent_map.cub"
run_cli_test "Directory as map" "${TESTS_DIR}"
for f in "${INVALID_MAPS_DIR}/args"/*; do
    [ -e "$f" ] || continue
    run_invalid_test "$(basename "$f")" "$f"
done

# 2. Textures Tests
print_category "2. Textures & Identifiers Validation"
for f in "${INVALID_MAPS_DIR}/textures"/*; do
    [ -e "$f" ] || continue
    run_invalid_test "$(basename "$f")" "$f"
done

# 3. Colors Tests
print_category "3. Floor / Ceiling RGB Colors Validation"
for f in "${INVALID_MAPS_DIR}/colors"/*; do
    [ -e "$f" ] || continue
    run_invalid_test "$(basename "$f")" "$f"
done

# 4. Player Tests
print_category "4. Player Orientation & Count Validation"
for f in "${INVALID_MAPS_DIR}/player"/*; do
    [ -e "$f" ] || continue
    run_invalid_test "$(basename "$f")" "$f"
done

# 5. Border & Enclosure Tests
print_category "5. Wall Enclosure & Space Boundary Validation"
for f in "${INVALID_MAPS_DIR}/borders"/*; do
    [ -e "$f" ] || continue
    run_invalid_test "$(basename "$f")" "$f"
done

# 6. Character Validation Tests
print_category "6. Map Character Validation"
for f in "${INVALID_MAPS_DIR}/chars"/*; do
    [ -e "$f" ] || continue
    run_invalid_test "$(basename "$f")" "$f"
done

# 7. Valid Maps Tests
print_category "7. Valid Maps & Raycasting Execution Loop"
for f in "${VALID_MAPS_DIR}"/*; do
    [ -e "$f" ] || continue
    run_valid_test "$(basename "$f")" "$f"
done

# Summary Table
echo -e "\n${BOLD}${CYAN}================================================================${RESET}"
echo -e "${BOLD}${CYAN}                        Test Summary                            ${RESET}"
echo -e "${BOLD}${CYAN}================================================================${RESET}"
echo -e "  Total Tests:    ${BOLD}${TOTAL_TESTS}${RESET}"
echo -e "  Passed:         ${BOLD}${GREEN}${PASSED_TESTS}${RESET}"
echo -e "  Failed:         ${BOLD}${RED}${FAILED_TESTS}${RESET}"
echo -e "  Crashes:        ${BOLD}${RED}${CRASHED_TESTS}${RESET}"

if [ $TOTAL_TESTS -gt 0 ]; then
    PASS_RATE=$(( (PASSED_TESTS * 100) / TOTAL_TESTS ))
    echo -e "  Pass Rate:      ${BOLD}${CYAN}${PASS_RATE}%${RESET}"
fi

echo -e "${BOLD}${CYAN}================================================================${RESET}\n"

if [ $FAILED_TESTS -eq 0 ] && [ $CRASHED_TESTS -eq 0 ]; then
    echo -e "${BOLD}${GREEN}✔ All Cub3D tests passed successfully!${RESET}\n"
    exit 0
else
    echo -e "${BOLD}${RED}✘ Some tests failed. Please review the output above.${RESET}\n"
    exit 1
fi
