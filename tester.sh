#!/bin/bash

PHILO_EXEC="./philo"
LOG_DIR="./logs"
mkdir -p "$LOG_DIR"

# Colors
RED="\033[0;31m"
GREEN="\033[0;32m"
BLUE="\033[1;34m"
PURPLE="\033[1;35m"
RESET="\033[0m"
BOLD="\033[1m"

# Tests: "EXPECTED arg1 arg2 arg3 arg4 [arg5]"
TESTS=(
  # Should DIE
  "DIE 4 310 200 100 2"
  "DIE 2 180 91 60 2"
  "DIE 6 180 181 60 2"
  "DIE 8 180 60 121 2"
  "DIE 20 180 60 181 2"
  "DIE 3 180 89 89 2"
  "DIE 5 180 180 60 2"
  "DIE 7 120 60 60 2"
  "DIE 3 800 300 60 2"
  "DIE 19 210 71 60 2"

  # Should NOT DIE
  "NODIE 4 410 200 200 10"
  "NODIE 2 180 60 60 10"
  "NODIE 4 800 390 60 10"
  "NODIE 8 180 85 85 10"
  "NODIE 18 180 85 85 10"
  "NODIE 3 210 65 135 10"
  "NODIE 3 210 60 145 10"
  "NODIE 5 900 295 60 10"
  "NODIE 7 300 60 60 10"
  "NODIE 19 210 69 139 10"
)

print_header() {
  echo -e "${BOLD}${BLUE}=== 42 PHILO TESTER ===${RESET}"
}

pass_count=0
total_count=0

run_test() {
  local index="$1"
  local test="${TESTS[$index]}"
  local args=($test)
  local expected="${args[0]}"
  unset args[0]
  local arg_str="${args[*]}"
  local log_file="$LOG_DIR/test_${index}.log"
  total_count=$((total_count + 1))

  echo -e "${PURPLE}Test #$index:${RESET} [expected: ${expected}] ./philo ${arg_str}"

  if [ "${#args[@]}" -eq 4 ]; then
    echo -e "${BLUE}[INFO] Infinite test — running up to 10s...${RESET}"
    $PHILO_EXEC $arg_str > "$log_file" 2>&1 &
    pid=$!
    sleep 10
    if kill -0 "$pid" 2>/dev/null; then
      kill "$pid" 2>/dev/null
      echo -e "${BLUE}[INFO] Process killed after 10s${RESET}" >> "$log_file"
    fi
    wait "$pid" 2>/dev/null
  else
    $PHILO_EXEC $arg_str > "$log_file" 2>&1
  fi

  if grep -q "died" "$log_file"; then
    actual="DIE"
  else
    actual="NODIE"
  fi

  if [ "$actual" = "$expected" ]; then
    echo -e "${GREEN}${BOLD}OK${RESET}"
    pass_count=$((pass_count + 1))
  else
    echo -e "${RED}KO${RESET} — got $actual, expected $expected"
    echo -e "${BLUE}Last log lines:${RESET}"
    tail -n 5 "$log_file"
  fi
}

# Run all tests
print_header
for i in "${!TESTS[@]}"; do
  run_test "$i"
done

# Final summary
echo -e "\n${BOLD}Summary:${RESET} ${GREEN}$pass_count${RESET} / ${total_count} tests passed."
