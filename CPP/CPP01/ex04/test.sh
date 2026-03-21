#!/bin/bash

# 색상 정의
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

PROGRAM="./ex04" # 컴파일된 실행 파일 이름

# 실행 파일 존재 여부 확인
if [ ! -f "$PROGRAM" ]; then
    echo -e "${RED}Error: $PROGRAM executable not found. Run 'make' first.${NC}"
    exit 1
fi

# 테스트 함수
run_test() {
    local test_name=$1
    local filename=$2
    local s1=$3
    local s2=$4
    local expected_content=$5

    echo -e "Running Test: ${test_name}"
    
    # 프로그램 실행
    $PROGRAM "$filename" "$s1" "$s2"
    
    if [ -f "${filename}.replace" ]; then
        actual_content=$(cat "${filename}.replace")
        if [ "$actual_content" == "$expected_content" ]; then
            echo -e "${GREEN}[PASS]${NC}"
        else
            echo -e "${RED}[FAIL]${NC}"
            echo "Expected: $expected_content"
            echo "Actual  : $actual_content"
        fi
    else
        echo -e "${RED}[FAIL]${NC} - Result file ${filename}.replace not created."
    fi
    echo "---------------------------------------"
}

# 1. 기본 교체 테스트
echo "This is a test file." > test1.txt
run_test "Basic replacement" "test1.txt" "test" "example" "This is a example file."

# 2. 여러 개 교체 테스트
echo "apple banana apple orange apple" > test2.txt
run_test "Multiple occurrences" "test2.txt" "apple" "pear" "pear banana pear orange pear"

# 3. 빈 문자열로 교체 (삭제 효과)
echo "Hello World" > test3.txt
run_test "Replace with empty string" "test3.txt" "World" "" "Hello "

# 4. s1이 빈 문자열인 경우 (에러 처리 확인)
echo "Content" > test4.txt
echo "Test: Empty s1 (Should handle error)"
$PROGRAM "test4.txt" "" "replacement"
echo "---------------------------------------"

# 5. 파일이 존재하지 않는 경우 (에러 처리 확인)
echo "Test: Non-existent file (Should handle error)"
$PROGRAM "non_existent.txt" "s1" "s2"
echo "---------------------------------------"

# 6. 특수 문자가 포함된 경우
echo "123!@#456" > test6.txt
run_test "Special characters" "test6.txt" "!@#" "???" "123???456"

# 7. s1과 s2가 같은 경우
echo "No change here" > test7.txt
run_test "Same s1 and s2" "test7.txt" "change" "change" "No change here"

# 8. 여러 줄 텍스트 테스트
printf "line1\nline2\nline1" > test8.txt
expected_8=$(printf "replaced\nline2\nreplaced")
run_test "Multi-line file" "test8.txt" "line1" "replaced" "$expected_8"

# 9. 권한 없는 파일 (에러 처리 확인)
echo "Secret" > test9.txt
chmod 000 test9.txt
echo "Test: Permission denied (Should handle error)"
$PROGRAM "test9.txt" "Secret" "Public"
chmod 644 test9.txt # 원상 복구
echo "---------------------------------------"

# 테스트 후 생성된 .replace 및 임시 파일 삭제 (선택 사항)
# rm *.replace test*.txt