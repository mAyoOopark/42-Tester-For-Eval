#!/bin/bash

# 색상 및 환경 설정
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
NC='\033[0m'
PROGRAM="./ex04"

if [ ! -f "$PROGRAM" ]; then
    echo -e "${RED}컴파일된 $PROGRAM 파일이 없습니다. make를 먼저 실행하세요.${NC}"
    exit 1
fi

# 테스트 결과를 비교하는 함수
run_advanced_test() {
    local test_name=$1
    local filename=$2
    local s1=$3
    local s2=$4
    local expected_file=$5

    echo -e "${YELLOW}▶ 테스트 중: ${test_name}${NC}"
    
    # 프로그램 실행
    $PROGRAM "$filename" "$s1" "$s2"
    
    # 결과 확인
    if [ -f "${filename}.replace" ]; then
        # diff를 사용하여 파일 전체를 비교 (-q는 결과만 출력)
        if diff -q "${filename}.replace" "$expected_file" > /dev/null; then
            echo -e "${GREEN}[PASS]${NC} 정상적으로 변환되었습니다."
        else
            echo -e "${RED}[FAIL]${NC} 결과가 예상과 다릅니다."
            echo "--- 차이점 (diff) ---"
            diff "${filename}.replace" "$expected_file" | head -n 10
            echo "..."
        fi
    else
        echo -e "${RED}[FAIL]${NC} 출력 파일(${filename}.replace)이 생성되지 않았습니다."
    fi
    echo "--------------------------------------------------"
}

echo "=================================================="
echo "        SED IS FOR LOSERS - HARDCORE TESTS        "
echo "=================================================="

# 1. 대용량 파일 스트레스 테스트 (10,000줄)
# 메모리 누수나 버퍼 오버플로우가 발생하지 않는지 확인합니다.
echo "생성 중: 대용량 파일 (10,000줄)..."
yes "Hello 42 World! 42 is everything." | head -n 10000 > stress.txt
yes "Hello 4242 World! 4242 is everything." | head -n 10000 > expected_stress.txt
run_advanced_test "대용량 스트레스 테스트 (10,000줄)" "stress.txt" "42" "4242" "expected_stress.txt"

# 2. 개행 문자(\n)가 아예 없는 극단적으로 긴 한 줄 테스트
# getline 등을 사용할 때 버퍼 크기 제한에 걸리지 않는지 확인합니다.
echo "생성 중: 개행 없는 매우 긴 한 줄..."
for i in {1..5000}; do printf "longtext_"; done > longline.txt
printf "END" >> longline.txt
for i in {1..5000}; do printf "SHORTtext_"; done > expected_longline.txt
printf "END" >> expected_longline.txt
run_advanced_test "개행 없는 초장문 텍스트" "longline.txt" "long" "SHORT" "expected_longline.txt"

# 3. 무한 루프 악성 트랩 (s2가 s1을 포함할 때)
# s1의 길이만큼 정확히 인덱스를 점프하지 않으면 영원히 끝나지 않습니다.
echo "생성 중: 무한 루프 트랩..."
echo "a a a a a" > loop_trap.txt
echo "aa aa aa aa aa" > expected_loop_trap.txt
run_advanced_test "무한 루프 방어 (a -> aa)" "loop_trap.txt" "a" "aa" "expected_loop_trap.txt"

# 4. 빈 줄이 연속으로 엄청나게 많은 경우
# 빈 줄을 무시하거나 개행 문자를 누락하는 오류를 잡습니다.
echo "생성 중: 연속된 빈 줄 테스트..."
printf "\n\n\nmatch\n\n\n\nmatch\n\n" > empty_lines.txt
printf "\n\n\nREPLACED\n\n\n\nREPLACED\n\n" > expected_empty_lines.txt
run_advanced_test "연속된 빈 줄 및 개행 유지" "empty_lines.txt" "match" "REPLACED" "expected_empty_lines.txt"

# 5. 권한 거부 테스트 (읽기 권한 없음)
# ifstream이 열리지 않을 때 프로그램이 크래시되지 않고 우아하게 종료되는지 확인합니다.
echo -e "${YELLOW}▶ 테스트 중: 읽기 권한 없는 파일 에러 처리${NC}"
echo "TOP SECRET" > no_read.txt
chmod 000 no_read.txt
$PROGRAM "no_read.txt" "TOP" "BOTTOM"
if [ ! -f "no_read.txt.replace" ]; then
    echo -e "${GREEN}[PASS]${NC} .replace 파일이 생성되지 않고 에러를 잘 처리했습니다."
else
    echo -e "${RED}[FAIL]${NC} 읽을 수 없는 파일인데 .replace가 생성되었습니다!"
fi
chmod 644 no_read.txt # 원상복구
echo "--------------------------------------------------"

# 6. 쓰기 권한 없는 디렉토리에서의 실행 테스트
# ofstream이 실패할 때의 예외 처리 확인
echo -e "${YELLOW}▶ 테스트 중: 쓰기 불가능한 디렉토리 에러 처리${NC}"
mkdir -p no_write_dir
echo "test" > no_write_dir/test.txt
chmod 500 no_write_dir # 디렉토리 쓰기 권한 제거
$PROGRAM "no_write_dir/test.txt" "test" "pass"
if [ ! -f "no_write_dir/test.txt.replace" ]; then
    echo -e "${GREEN}[PASS]${NC} 쓰기 권한 에러를 잘 처리했습니다."
else
    echo -e "${RED}[FAIL]${NC} 쓰기 권한이 없는데 파일이 생성되었습니다!"
fi
chmod 700 no_write_dir # 원상복구
rm -rf no_write_dir
echo "--------------------------------------------------"

# 테스트가 끝난 후 만들어진 임시 파일들 정리
echo -e "${YELLOW}임시 파일들을 정리합니다...${NC}"
rm -f stress.txt expected_stress.txt stress.txt.replace
rm -f longline.txt expected_longline.txt longline.txt.replace
rm -f loop_trap.txt expected_loop_trap.txt loop_trap.txt.replace
rm -f empty_lines.txt expected_empty_lines.txt empty_lines.txt.replace
rm -f no_read.txt

echo -e "${GREEN}모든 하드코어 테스트가 완료되었습니다!${NC}"