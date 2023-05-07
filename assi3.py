class CourseHistory:
    # 추후 계산에 사용될 전역 변수들
    submit_gpa, archive_gpa = 0, 0  # 제출용 학점, 열람용 학점
    submit_time, archive_time = 0, 0  # 제출용 시수, 열람용 시수
    def __init__(self):
        self.course_id = {'id': 12345}  # 임의의 과목 코드는 12345에 1씩 추가
        self.taken_course_list = []
        self.empty_tuple = ()



    # 평점 변환기
    @classmethod
    def gpa_intpret(cls,course_gpa):
        match course_gpa:
            case 'A+':
                return 4.5
            case 'A':
                return 4
            case 'B+':
                return 3.5
            case 'B':
                return 3
            case 'C+':
                return 2.5
            case 'C':
                return 2
            case 'D+':
                return 1.5
            case 'D':
                return 1
            case 'F':
                return 0

    # 1번 선택시 질문(입력) 함수, 동시에 계산까지 미리 수행
    def input_machine(self):
        global submit_gpa, archive_gpa
        global submit_time, archive_time
        course_name = input('과목명을 입력하세요 : ')  # course_id, taken_course_list 로 이동
        self.append_id_func(course_name)
        course_time = int(input('학점을 입력하세요 : '))  # grade_info_tuple로 이동
        course_gpa = input('평점을 입력하세요 : ')  # grade_info_tuple로 이동
        self.append_time_func(course_time, course_gpa)
        submitgpa, archivegpa = 0, 0  # 분자
        submittime, archivetime = 0, 0  # 분모

        if course_gpa != 'F':  # 제출용(F 미포함)
            submitgpa += course_time * self.gpa_intpret(course_gpa)
            submittime += course_time

        archivegpa += course_time * self.gpa_intpret(course_gpa)  # 열람용(F 포함)
        archivetime += course_time
        print('입력되었습니다. \n')

        CourseHistory.submit_gpa += submitgpa
        CourseHistory.submit_time += submittime
        CourseHistory.archive_gpa += archivegpa
        CourseHistory.archive_time += archivetime

    # 1-1 input
    def append_id_func(self, course_name):
        if course_name not in self.course_id:
            new_id = ((int(self.course_id['id']) + 1))  # str로 받아야 출력할 때 int로 나옴
            self.course_id['id'] = new_id  # 새로운 아이디 생성기일 뿐
            self.course_id[course_name] = new_id
            self.course_id[new_id] = course_name  # 이 코드가 있어야 2번을 눌렀을 때 과목명이 튀어나올 수 있음, 왜냐하면 키값이 'id'와 겹침

    # 1-2 add
    def append_time_func(self, course_time, course_gpa):
        grade_info_tuple = (self.course_id['id'], course_time, course_gpa)
        self.taken_course_list.append(grade_info_tuple)
        grade_info_tuple = self.empty_tuple

    # 1_3 calculation
    def final_calc(self):
        print('제출용: ', CourseHistory.submit_time, '학점 (GPA:', CourseHistory.submit_gpa / CourseHistory.submit_time, ')')
        print('제출용: ', CourseHistory.archive_time, '학점 (GPA:', CourseHistory.archive_gpa / CourseHistory.archive_time, ')')
    def numtwofunc(self):
        for element in self.taken_course_list:
            print('[' + (self.course_id[element[0]]) + ']', element[1], '학점: ' + element[2])

    def numthreefunc(self):
        search = str(input("조회할 과목을 입력하시오 :"))
        for element in self.taken_course_list:
            if search == self.course_id[element[0]]:
                print('[' + search + ']', element[1], '학점: ' + element[2])
                break
        else:
            print("해당하는 과목이 없습니다.")


course_history = CourseHistory()
# 본체!!
while 1:
    print('작업을 선택하세요.')
    print('1. 입력')
    print('2. 출력')
    print('3. 조회')
    print('4. 계산')
    print('5. 종료')
    # 사용자 입력(1 or 2 or 3 or 4 or 5)
    num = int(input())
    # 1. 입력
    if num == 1:
        course_history.input_machine()
    # 2. 출력
    elif num == 2:
        course_history.numtwofunc()
    # 3. 조회
    elif num == 3:
        course_history.numthreefunc()
    # 4. 계산
    elif num == 4:
        course_history.final_calc()
    # 5. 종료
    else:
        print('프로그램을 종료합니다.')
        break

